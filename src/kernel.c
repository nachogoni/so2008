#include "../include/kasm.h"
#include "../include/defs.h"
#include "../include/grubInfo.h"
#include "../include/kc.h"
#include "../include/fd.h"
#include "../include/strings.h"
#include "../include/io.h"
#include "../include/kernel.h"
#include "../include/memory.h"
#include "../include/shell.h"
#include "../include/drivers/serial.h"
#include "../include/drivers/video.h"
#include "../include/drivers/keyboard.h"
#include "../include/pagination.h"
#include "../include/drivers/tty.h"
#include "../include/processes.h"

#define CHECK_FLAG(flags,bit)   ((flags) & (1 << (bit)))

/******************** VARIABLE EXTERNAS AL SISTEMA ************************/

/* FILE DESCRIPTIRS */
extern file_descriptors fds;

/****************** FIN VARIABLE EXTERNAS AL SISTEMA **********************/


/********************* VARIABLE GLOBALES DE SISTEMA ***********************/

int shutdown_pc = 0;
int reboot_pc = 0;

/* IDT de 0x80h entradas*/
DESCR_INT idt[0x81];

/* IDTR */
IDTR idtr;					

/* Usuario activo del sistema */
int active_user;

/* fd default de salida */
int stdout;

/* fd default de entrada */
int stdin;

/* fd default del puerto serial */
int stdser;

/***************** FIN VARIABLE GLOBALES DE SISTEMA ***********************/

void int_08(void)
{
	if (player != NULL)
		player();

	return;
}

void int_09(void)
{
	handle_keyboard();
	return;
}

void int_0c(void) 
{
	handle_serial();
	return;
}

/* __read
*
* Recibe como parametros:
* - File Descriptor
* - Buffer a escribir
* - Cantidad
*
**/
size_t
__read(int fd, void* buffer, size_t count) 
{
	size_t i = 0;
	int s_read = 0;

	if (fd<0 || buffer == NULL || count <=0)
		return 0;

	//Ejecuto el setbyte del fd siempre y cuando este activo
	if (fds.actives[fd].getByte == NULL)
		return 0;

	do
	{
		s_read = fds.actives[fd].getByte( (int *) ((unsigned char *)buffer)+i );
		if (s_read)
			i++;
	} while((i<count) && s_read);

	return i;
}


/* __write
*
* Recibe como parametros:
* - File Descriptor
* - Buffer del source
* - Cantidad
*
**/
size_t  
__write(int fd, const void* buffer, size_t count) 
{
	size_t i = 0;
	int exit = 0;

	if (fd<0 || buffer == NULL || count <=0)
		return 0;

	//Ejecuto el setbyte del fd siempre y cuando este activo
	if (fds.actives[fd].setByte == NULL)
		return 0;
	
	while(i<count && !exit)
		exit=fds.actives[fd].setByte( (int) ((char*)buffer)[i++] );

	return i;
}

/* fork
 * 
 * Devuelve el pid 
 */
int
__fork(void)
{
	int pid;
	
	pid=0;
	
	//duplico el stack y el heap
	//creo la zona de memoria compartida
	
	//creo el proceso
	
	return pid;
}

/**********************************************
kmain() 
Punto de entrada de codigo C.
*************************************************/

void kmain(unsigned long infoStruct, unsigned long magicNumber) 
{
	/******************** CONFIGURACION DEL SO *************************/

	/* CARGA DE IDT CON LA RUTINA DE ATENCION DE IRQ0 - Timer Tick */
	setup_IDT_entry (&idt[0x08], 0x08, (dword)&int_08_hand, ACS_INT, 0);
	/* CARGA DE IDT CON LA RUTINA DE ATENCION DE IRQ1 - Keyboard */
	setup_IDT_entry (&idt[0x09], 0x08, (dword)&int_09_hand, ACS_INT, 0);	
	/* CARGA DE IDT CON LA RUTINA DE ATENCION DE IRQ1 - serial */
	setup_IDT_entry (&idt[0x0c], 0x08, (dword)&int_0c_hand, ACS_INT, 0);
	/* CARGA DE IDT CON LA RUTINA DE ATENCION DE 80h */
	setup_IDT_entry (&idt[0x80], 0x08, (dword)&int_80_hand, ACS_INT, 0);

	/* Carga de IDTR    */
	idtr.base = 0;
	idtr.base +=(dword) &idt;
	idtr.limit = sizeof(idt)-1;
	
	_lidt (&idtr);	

	_Cli();

	/* Habilito interrupcion de timer tic, keyboard y puerto serial*/
	mascaraPIC1(0xEC);
	mascaraPIC2(0xFF);

	/* Seteo al usuario activo como user */
	active_user = U_KERNEL;

	/* inicializacion del fd */
	__init_fd();
	
	/* asignacion de fd's */
	/* TTY Video */
	set_fd(TTY, tty_init, tty_setByte, tty_getByte, tty_destroy);
	stdout = fd_open(TTY);
	
	/* Keyboard */
	set_fd(KEYBOARD, init_keyboard, NULL, keyboard_getChar, close_keyboard);
	stdin = fd_open(TTY);

	/* Serial */
	//set_fd(SERIAL, init_serial, serial_setChar, serial_getChar, close_serial);
	//stdser=fd_open(SERIAL);

	/* Muestra la informacion que entrega el grub  */
	set_multiBoot(infoStruct);
	//show_multiBoot();

	/******************** INICIALIZACION DE MEMORIA ********************/
 	void* memory;
 	int memory_size;

	/* Si puedo asignar los bloques - devuelve memory_size 0 si no puede */
 	getBlockMem(&memory,&memory_size);

 	//Inicializo la paginacion en 2mb
	__init_pagination((unsigned long **) 0x200000, (unsigned long *) 0x201000, KERNEL_MEM_SIZE, 8*MB);

	/******************** FIN CONFIGURACION DEL SO *************************/

	/* Pantalla de inicio */
	//init_presents(OS_PID, OS_PID+1, NULL);
	//showSplashScreen();

	/* Seteo al usuario activo como user */
	active_user=U_NORMAL;

	/******************** INICIO DE ZONA LIBRE *************************/
	printf("Initializing multitasking services... OK\n");

	createProcess(&shell, "shell", 0);
	createProcess(&shell, "shell", 1);
	createProcess(&shell, "shell", 2);
	createProcess(&shell, "shell", 3);
	createProcess(&shell, "shell", 4);
	createProcess(&shell, "shell", 5);
	createProcess(&shell, "shell", 6);

//	createProcess(&a, "f_a", 6);
//	createProcess(&b, "f_b", 6);
//	createProcess(&c, "f_c", 6);
//	createProcess(&d, "f_d", 6);
	
	printf("fork %d\n",fork());
	
	_Sti();

	while(!shutdown_pc && !reboot_pc)
		asm volatile ("hlt");

	_Cli();
	
	printf("\n\n\n\nSystem is shutting down... OK\n");
	
	/******************** FINALIZACION DEL SO *************************/

	fd_close(SERIAL);
	fd_close(KEYBOARD);
	fd_close(TTY);

/*
	if (shutdown_pc)
		shutdown();
	if (reboot_pc)
		reboot();
*/
	
}

