#include "../../include/drivers/key_layouts.h"
#include "../../include/drivers/keyboard.h"
#include "../../include/strings.h"
#include "../../include/io.h"
#include "../../include/memory.h"
#include "../../include/kernel.h"
#include "../../include/kasm.h"
#include "../../include/drivers/tty.h"

typedef struct 
{
	int buffer[K_BUFFER_SIZE];
	int write;
	int read;
	int qty;
}k_bufferT;

k_bufferT k_buffer;

static int setLeds(void);

static int bufferNotEmpty () {
	return (k_buffer.qty != 0);
}

static int readScanCode(int scanCode);

// Definicion del teclado numerico
int num_lock[] = {
//	HOME,  UP, PG_UP, LEFT, CENTER, RIGHT, END, DOWN, PG_DW, INSERT, DELETE
	 '7', '8',   '9',  '4',    '5',   '6', '1',  '2',   '3',    '0',    '.'
	};

// Estructura que mantiene los flags
typedef struct keyFlagsT
{
	char num_lock;
	char caps_lock;
	char scroll_lock;
	char lShift;
	char rShift;
	char lAlt;	
	char rAlt;
	char lCtrl;
	char rCtrl;
} keyFlagsT;

// Flags de control
static keyFlagsT flags;

// Determkina que idioma se usara para el teclado
static int layout;

static int readScanCode(int scanCode)
{
	int extendido = 0, shift = 0, set = 1, ascii = 0;

	// ScanCode extendido
	if (scanCode == 0xe0)
	{
		extendido=1;
		scanCode = inportb(0x60);
	}

	if (flags.lShift || flags.rShift)
		shift = 1;

	ascii = key_layouts[layout][shift][scanCode & 0x7F];

	// Convierte los ascii del teclado numerico si es el caso
	if (!extendido && flags.num_lock && ascii <= HOME && ascii >= DELETE)
		ascii = num_lock[(ascii * -1) + HOME];

	// Si es un break code y es un caracter imprimible -> lo convierto
	if ((scanCode & 0x80) == 0 && (ascii >= 0))
	{
		if (flags.caps_lock == 1 && flags.lShift == 0 && flags.rShift == 0)
			return toUpper(ascii);
		else if (flags.caps_lock == 1 && (flags.lShift == 1 || flags.rShift == 1))
			return toLower(ascii);
		else
			return ascii;
	}		

	if (scanCode & 0x80)
		set = 0;
	
	// Son scanCodes de control?
	switch (ascii)
	{
		case R_CTRL: // rCtrl
			flags.rCtrl = set;
			break;
		case L_CTRL: // lCtrl
			if (extendido)
				flags.rCtrl = set;
			else
				flags.lCtrl = set;
			break;
		case L_SHIFT: // lShift
			flags.lShift = set;
			break;
		case R_SHIFT: // rShift
			flags.rShift = set;
			break;
		case R_ALT: // rAlt
			flags.rAlt = set;
			break;
		case L_ALT: // rAlt
			if (extendido)
				flags.rAlt = set;
			else
				flags.lAlt = set;
			break;
		case CPS_LCK: // Caps_Lock
			if ((scanCode & 0x80) == 0)
			{
				if (flags.caps_lock)
					flags.caps_lock = 0;
				else
					flags.caps_lock = 1;
				setLeds();
			}
			break;
		case NUM_LCK: // Num_Lock
			if ((scanCode & 0x80) == 0)
			{
				if (flags.num_lock)
					flags.num_lock = 0;
				else
					flags.num_lock = 1;
				setLeds();
			}		
			break;
		case SCR_LCK: // Scroll_Lock
			if ((scanCode & 0x80) == 0)
			{
				if (flags.scroll_lock)
					flags.scroll_lock = 0;
				else
					flags.scroll_lock = 1;
				setLeds();
			}
			break;
	}

	

	return (scanCode & 0x80) ? MAKE : ascii;
}

size_t keyboard_setChar (int b) {
	return 0;
}

size_t keyboard_writeBuffer (int b) {
//	if( bufferNotFull() ) {
//		k_buffer.buffer[k_buffer.write] = b;
//		k_buffer.qty++;
//		if ( ++(k_buffer.write) == K_BUFFER_SIZE) 
//			k_buffer.write = 0;
//		return 1;
//	}
//	return 0;

return tty_writeBuffer(b);

}

//int keyboard_getChar (void) {
size_t keyboard_getChar (int * data) {
	if ( bufferNotEmpty() ) {
		k_buffer.qty--;
		*data = k_buffer.buffer[k_buffer.read];
		if ( ++(k_buffer.read) == K_BUFFER_SIZE) 
					k_buffer.read = 0;
		return 1;
	}
	return 0;
}

int init_keyboard(void) {
	//Inicializo las variables de teclado
	k_buffer.write = 0;
	k_buffer.read = 0;
	k_buffer.qty = 0;

	flags.num_lock = 0;
	flags.caps_lock = 0;
	flags.scroll_lock = 0;
	flags.lShift = 0;
	flags.rShift = 0;
	flags.lAlt = 0;
	flags.rAlt = 0;
	flags.lCtrl = 0;
	flags.rCtrl = 0;

	// Seteo el layout de teclado por default como us
	set_layout(KEYBOARD_US);

	setLeds();
	
	return 1;
}

int handle_keyboard(void)
{
	int resp = 0, scanCode;
	
	scanCode = inportb(0x60);
	
	// Analiza el scancode...
	resp = readScanCode(scanCode);
	
	if (resp > -11 && resp < 0)
	{
		// Teclas que no deben ir al buffer del teclado -> control!
		resp = 0;
	}
	else
	{
		// Agrega al buffer del teclado la tecla presionada
		keyboard_writeBuffer(resp);
		resp = 1;
	}
	
	return resp;
}

int setLeds(void)
{
	unsigned char leds = 0;

	leds = flags.caps_lock * 4 + flags.num_lock * 2 + flags.scroll_lock;
	// Deshabilito interrupciones
	_Cli();
	// Envio el Set indicators
	outportb((unsigned short)0x60, 0xED);
	// Espero el ACK
	while( inportb((unsigned short)0x60) != 0xFA);
	// Envio los leds
	outportb((unsigned short)0x60, leds);
	// Espero el ACK
	while( inportb((unsigned short)0x60) != 0xFA);
	// Rehabilito interrupciones
	_Sti();

	return 1;
}

int get_layout(void)
{
	return 	layout;
}

int set_layout(int klayout)
{
	return 	(layout = klayout);
}

int close_keyboard(int fd)
{
	return 1;
}


