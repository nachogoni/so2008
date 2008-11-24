#define _VERSION_ "0.48"

#include <16F877.h>
#fuses HS,NOWDT,NOPROTECT,NOLVP,NOBROWNOUT,NOPUT
#use delay(clock=20000000, restart_wdt)
#use rs232(baud=4800, xmit=PIN_C6, rcv=PIN_C7)

/****** DEFINITIONS ******/
typedef enum {B1200 = 0, B2400, B4800, B9600, B19200, 
				B38400, B57600, B115200} bouds;

typedef enum {SCROLL_NONE = 0, SCROLL_RIGHT, SCROLL_LEFT,
			SCROLL_UP, SCROLL_DOWN, SCROLL_RIGHT_CARRY,
			SCROLL_LEFT_CARRY, SCROLL_UP_CARRY,
			SCROLL_DOWN_CARRY} scrolls;

#define _COMMAND_BASE			0
#define _PONG					_COMMAND_BASE + 'A'
#define _SET_SCROLL_FREQ		_COMMAND_BASE + 'B'
#define _SET_UART_SPEED			_COMMAND_BASE + 'C'
#define _START_SCROLL			_COMMAND_BASE + 'D'
#define _STOP_SCROLL			_COMMAND_BASE + 'E'
#define _GET_SCREEN				_COMMAND_BASE + 'F'
#define _SET_SCREEN				_COMMAND_BASE + 'G'
#define _SCROLL_DOWN_CARRY		_COMMAND_BASE + 'H'
#define _SCROLL_DOWN			_COMMAND_BASE + 'I'
#define _SCROLL_UP_CARRY		_COMMAND_BASE + 'J'
#define _SCROLL_UP				_COMMAND_BASE + 'K'
#define _SCROLL_LEFT_CARRY		_COMMAND_BASE + 'L'
#define _SCROLL_LEFT			_COMMAND_BASE + 'M'
#define _SCROLL_RIGHT_CARRY		_COMMAND_BASE + 'N'
#define _SCROLL_RIGHT			_COMMAND_BASE + 'O'
#define _CLEAR					_COMMAND_BASE + 'P'
#define _GET_COL				_COMMAND_BASE + 'Q'
#define _SET_COL				_COMMAND_BASE + 'R'

#define PARAM_SET_SCROLL_FREQ	_COMMAND_BASE + 1
#define PARAM_SET_UART_SPEED	_COMMAND_BASE + 2
#define PARAM_SET_SCREEN		_COMMAND_BASE + 3
#define PARAM_SET_COL			_COMMAND_BASE + 4

#define DISABLED			0
#define ENABLED				(DISABLED + 1)

/* STATUS*/
#define STATUS_ENA			output_high(PIN_D3);
#define LINK_ENA			output_high(PIN_D2);
#define STATUS_DIS			output_low(PIN_D3);
#define LINK_DIS			output_low(PIN_D2);

/* LEDS */
#define R_ENA				output_high(PIN_D7);
#define G_ENA				output_high(PIN_D6);
#define B_ENA				output_high(PIN_D5);
#define COL_ENA				output_low(PIN_D1);
#define R_DIS				output_low(PIN_D7);
#define G_DIS				output_low(PIN_D6);
#define B_DIS				output_low(PIN_D5);
#define COL_DIS				output_high(PIN_D1);
#define SET_74154_TIME		1
#define SET_74573_TIME		0
#define SCREEN_WIDTH		16
#define COLOR_COUNT			3
#define SCREEN				(COLOR_COUNT * SCREEN_WIDTH)

/* TIMER */
// 76 && 256 -> 1Hz
#define DEFAULT_TIMER_COUNT	76
#define DEFAULT_TIMER_DIV	RTCC_DIV_256
#define DEFAULT_PING_COUNT	38 // ping every 500ms
#define PING_PONG_COUNT		50

/****** FUNCTIONS ******/

/* LEDS */
void clear(void);
void set_red(byte color);
void set_green(byte color);
void set_blue(byte color);
void set_col(byte col);
void get_col(void);
void scrollUp(void);
void scrollUpCarry(void);
void scrollDown(void);
void scrollDownCarry(void);
void scrollLeft(void);
void scrollLeftCarry(void);
void scrollRight(void);
void scrollRightCarry(void);
void setScreen(byte * buffer);
void getScreen(void);
void clearScreen(void);
void stopScroll(void);
void startScroll(void);
void setUARTSpeed(byte speed);
void setScrollFreq(byte freq);
void ping(void);
void pong(void);

/* TIMER */
byte matrix[SCREEN] = {	0x00, 0x00, 0xFF,
						0x00, 0x00, 0x00,
						0x00, 0x00, 0x00,
						0x00, 0x00, 0x00,
						0x00, 0x00, 0x00,
						0x00, 0x00, 0x00,
						0x00, 0x00, 0x00,
						0x00, 0x00, 0x00,
						0x00, 0x00, 0x00,
						0x00, 0x00, 0x00,
						0x00, 0x00, 0x00,
						0x00, 0x00, 0x00,
						0x00, 0x00, 0x00,
						0x00, 0x00, 0x00,
						0x00, 0x00, 0x00,
						0x00, 0x00, 0x00};

/****** IMPLEMENTATION ******/
byte timer_div = DEFAULT_TIMER_DIV;
byte timer_count = DEFAULT_TIMER_COUNT;
byte int_count = DEFAULT_TIMER_COUNT;
byte int_ping_count = DEFAULT_PING_COUNT;
byte ping_count = DEFAULT_PING_COUNT;
byte scroll = DISABLED;
byte scroll_type = SCROLL_NONE;
byte do_reset = PING_PONG_COUNT;
byte actual_col = 0;
byte buffer[SCREEN];
byte buffer_idx = 0;
byte status = _COMMAND_BASE;

/* INTERRUPT */
#INT_RDA
void recv_rs232(void)
{
	int recv = 0;
	//disable_interrupts(GLOBAL);
	LINK_ENA
	recv = getc();

	if (status == 0)
	{
		// Es un comando
		switch (recv)
		{
			// SCREEN parameters left
			case _SET_SCREEN:
				status = PARAM_SET_SCREEN;
				buffer_idx = 0;
				break;
			// 1 parameter left
			case _SET_SCROLL_FREQ:
				status = PARAM_SET_SCROLL_FREQ;
				break;
			case _SET_UART_SPEED:
				status = PARAM_SET_UART_SPEED;
				break;
			case _SET_COL:
				status = PARAM_SET_COL;
				break;
			// No parameters
			case _PONG:
				pong();
				break;
			case _START_SCROLL:
				startScroll();
				break;
			case _STOP_SCROLL:
				stopScroll();
				break;
			case _GET_SCREEN:
				getScreen();
				break;
			case _SCROLL_DOWN_CARRY:
				scroll_type = SCROLL_DOWN_CARRY;
				startScroll();
				break;
			case _SCROLL_DOWN:
				scroll_type = SCROLL_DOWN;
				startScroll();
				break;
			case _SCROLL_UP_CARRY:
				scroll_type = SCROLL_UP_CARRY;
				startScroll();
				break;
			case _SCROLL_UP:
				scroll_type = SCROLL_UP;
				startScroll();
				break;
			case _SCROLL_LEFT_CARRY:
				scroll_type = SCROLL_LEFT_CARRY;
				startScroll();
				break;
			case _SCROLL_LEFT:
				scroll_type = SCROLL_LEFT;
				startScroll();
				break;
			case _SCROLL_RIGHT_CARRY:
				scroll_type = SCROLL_RIGHT_CARRY;
				startScroll();
				break;
			case _SCROLL_RIGHT:
				scroll_type = SCROLL_RIGHT;
				startScroll();
				break;
			case _CLEAR:
				clearScreen();
				break;
			case _GET_COL:
				get_col();
				break;
			default:
				break;
		}
	}
	else if (PARAM_SET_SCROLL_FREQ == status)
	{
		// Freq @ recv
		if ((recv >= 0) && (recv <= 16)) 
			setScrollFreq(recv);
		status = _COMMAND_BASE;
	}
	else if (PARAM_SET_UART_SPEED == status)
	{
		// Speed @ recv
		if ((recv >= B1200) && (recv <= B115200)) 
			setUARTSpeed(recv);
		status = _COMMAND_BASE;
	}
	else if (PARAM_SET_SCREEN == status)
	{
		// Es un dato
		if (buffer_idx >= SCREEN)
		{
			// Buffer full -> flush to screen
			setScreen(buffer);
			buffer_idx = 0;
			status = _COMMAND_BASE;
		}
		else
			buffer[buffer_idx++] = recv;
	}
	else if (PARAM_SET_COL == status)
	{
		// <column @ recv
		if ((recv >= 0) && (recv < SCREEN_WIDTH)) 
			set_col(recv);
		status = _COMMAND_BASE;
	}/*
	else
	{
		// Es un dato
		idx %= SCREEN;
		matrix[idx++] = recv;
	}*/
	//enable_interrupts(GLOBAL);
	return;
}

#INT_RTCC
void clock(void)
{
	LINK_DIS

	if(0 == (--int_ping_count))
	{
		ping();
		int_ping_count = ping_count;
		if (0 == do_reset--)
		{
			printf("\r\n# Ping timeout - check drivers#\r\n");
			reset_cpu();
		}
	}

	if((scroll == ENABLED) && (0 == (--int_count)))
	{
		switch (scroll_type)
		{
			case SCROLL_RIGHT:
				scrollRight();
				break;
			case SCROLL_LEFT:
				scrollLeft();
				break;
			case SCROLL_UP:
				scrollUp();
				break;
			case SCROLL_DOWN:
				scrollDown();
				break;
			case SCROLL_RIGHT_CARRY:
				scrollRightCarry();
				break;
			case SCROLL_LEFT_CARRY:
				scrollLeftCarry();
				break;
			case SCROLL_UP_CARRY:
				scrollUpCarry();
				break;
			case SCROLL_DOWN_CARRY:
				scrollDownCarry();
				break;
			default:
				stopScroll();
				break;
		}
		int_count = timer_count;
	}
}

/* MAIN */
void main(void)
{
	int i;
	unsigned byte alive = 0;

	set_tris_a(0x00);
	set_tris_b(0x00);
	set_tris_d(0x00);

	output_a(0x00);
	output_b(0xFF);
	output_d(0x00);

	for (i = 0; i < SCREEN; i++)
		buffer[i] = 0;

	status = 0; //means waiting for a command
	// scroll?
	scroll = DISABLED;
	scroll_type = SCROLL_NONE;
	// watch dog
	do_reset = PING_PONG_COUNT;
	ping_count = DEFAULT_PING_COUNT;
	// reset timer0
	set_rtcc(0);
	timer_div = RTCC_DIV_256;
	setup_counters (RTCC_INTERNAL, timer_div);
	//timer interrupt
	enable_interrupts (INT_RTCC);
	//serial interrupt
	enable_interrupts(INT_RDA);
	//global interrupt
	enable_interrupts(GLOBAL);

	printf("\r\nInitializing Fleds (ver %s)\r\n", _VERSION_);


	clear();

	set_col(0);
	while(1)
	{
		actual_col = 0;
		for (i = 0; i < SCREEN; i+=3)
		{
			COL_DIS
			set_red(matrix[i]);
			delay_ms(SET_74573_TIME);
			set_green(matrix[i+1]);
			delay_ms(SET_74573_TIME);
			set_blue(matrix[i+2]);
			delay_ms(SET_74573_TIME);
			set_col(actual_col++);
		}
		if (0 == alive)
			STATUS_ENA
		if (128 == alive++)
			STATUS_DIS
	}

 	return;
}

/* LEDS */
void set_col(byte col)
{
	if (col < 16)
	{
		output_a(col);
		COL_ENA
		delay_ms(SET_74154_TIME);
		//COL_DIS
	}
	return;
}

void get_col(void)
{
	putchar('<');
	putchar(actual_col);
	putchar('>');

	return;
}

void clear(void)
{
	R_ENA
	G_ENA
	B_ENA
	output_b(0xFF);
	delay_ms(SET_74573_TIME);
	R_DIS
	G_DIS
	B_DIS
	return;
}

void set_red(byte color)
{
	G_DIS
	B_DIS
	output_b(0xFF - color);
	R_ENA
	delay_ms(SET_74573_TIME);
	R_DIS
	return;
}

void set_green(byte color)
{
	G_DIS
	B_DIS
	output_b(0xFF - color);
	G_ENA
	delay_ms(SET_74573_TIME);
	G_DIS
	return;
}

void set_blue(byte color)
{
	G_DIS
	B_DIS
	output_b(0xFF - color);	
	B_ENA
	delay_ms(SET_74573_TIME);
	B_DIS
	return;
}

void scrollUpCarry(void)
{
	byte i = 0;
	for(i = 0; i < SCREEN; i++)
		rotate_right(matrix + i, 1);

	return;
}

void scrollUp(void)
{
	byte i = 0;
	for(i = 0; i < SCREEN; i++)
		shift_right(matrix + i, 1, 0);

	return;
}

void scrollDownCarry(void)
{
	byte i = 0;
	for(i = 0; i < SCREEN; i++)
		rotate_left(matrix + i, 1);

	return;
}

void scrollDown(void)
{
	byte i = 0;
	for(i = 0; i < SCREEN; i++)
		shift_left(matrix + i, 1, 0);

	return;
}

void scrollLeft(void)
{
	byte i = 0;
	for(i = 0; i < (SCREEN - 3); i++)
	{
		matrix[i] = matrix[i + 3];
	}
	// clear last column
	matrix[i] = 0;
	matrix[i+1] = 0;
	matrix[i+2] = 0;

	return;
}

void scrollLeftCarry(void)
{
	byte i = 0, r, g, b;

	// Backup first column
	r = matrix[0];
	g = matrix[1];
	b = matrix[2];

	for(i = 0; i < (SCREEN - 3); i++)
	{
		matrix[i] = matrix[i + 3];
	}
	// set last column
	matrix[i] = r;
	matrix[i+1] = g;
	matrix[i+2] = b;

	return;
}

void scrollRight(void)
{
	byte i = SCREEN-1;

	for(i = SCREEN-1; i >= 3; i--)
	{
		matrix[i] = matrix[i - 3];
	}
	// set last column
	matrix[0] = 0;
	matrix[1] = 0;
	matrix[2] = 0;

	return;
}

void scrollRightCarry(void)
{
	byte i = SCREEN-1, r, g, b;

	// Backup first column
	r = matrix[i-2];
	g = matrix[i-1];
	b = matrix[i];

	for(i = SCREEN-1; i >= 3; i--)
	{
		matrix[i] = matrix[i - 3];
	}
	// set last column
	matrix[0] = r;
	matrix[1] = g;
	matrix[2] = b;

	return;
}

void clearScreen(void)
{
	byte i = 0;
	
	for(i = 0; i < SCREEN; i++)
	{
		matrix[i] = 0;
	}
	return;
}

void setScreen(byte * buffer)
{
	byte i = 0;
	
	for(i = 0; i < SCREEN; i++)
	{
		matrix[i] = buffer[i];
	}
	return;
}

void getScreen(void)
{
	byte i = 0;
	
	putchar('[');
	for(i = 0; i < SCREEN; i++)
	{
		putchar(matrix[i]);
	}
	putchar(']');

	return;
}

void stopScroll(void)
{
	scroll = DISABLED;
	return;
}

void startScroll(void)
{
	disable_interrupts(GLOBAL);
	scroll = ENABLED;
	set_rtcc(0);
	setup_counters (RTCC_INTERNAL, timer_div);
	enable_interrupts(INT_RTCC);
	enable_interrupts(GLOBAL);
	return;
}

void setUARTSpeed(byte speed)
{
	switch(speed)
	{
		case B1200:
			setup_uart(1200);
			break;
		case B2400:
			setup_uart(2400);
			break;
		case B4800:
			setup_uart(4800);
			break;
		case B9600:
			setup_uart(9600);
			break;
		case B19200:
			setup_uart(19200);
			break;
		case B38400:
			setup_uart(38400);
			break;
		case B57600:
			setup_uart(57600);
			break;
		case B115200:
			setup_uart(115200);
			break;
		default:
			setup_uart(4800);
			break;
	}
	return;
}

void setScrollFreq(byte freq)
{
	//global interrupt
	disable_interrupts(GLOBAL);
	set_rtcc(0);

	switch(freq)
	{
		case 0:
			timer_div = RTCC_DIV_64;
			timer_count = 1;
			ping_count = 229;
			break;
		case 1:
			timer_div = RTCC_DIV_128;
			timer_count = 1;
			ping_count = 115;
			break;
		case 2:
			timer_div = RTCC_DIV_64;
			timer_count = 3;
			ping_count = 230;
			break;
		case 3:
			timer_div = RTCC_DIV_256;
			timer_count = 1;
			ping_count = 57;
			break;
		case 4:
			timer_div = RTCC_DIV_64;
			timer_count = 5;
			ping_count = 229;
			break;
		case 5:
			timer_div = RTCC_DIV_128;
			timer_count = 3;
			ping_count = 115;
			break;
		case 6:
			timer_div = RTCC_DIV_64;
			timer_count = 7;
			ping_count = 231;
			break;
		case 7:
			timer_div = RTCC_DIV_256;
			timer_count = 2;
			ping_count = 57;
			break;
		case 8:
			timer_div = RTCC_DIV_64;
			timer_count = 9;
			ping_count = 230;
			break;
		case 9:
			timer_div = RTCC_DIV_256;
			timer_count = 3;
			ping_count = 56;
			break;
		case 10:
			timer_div = RTCC_DIV_64;
			timer_count = 17;
			ping_count = 230;
			break;
		case 11:
			timer_div = RTCC_DIV_256;
			timer_count = 5;
			ping_count = 56;
			break;
		case 12:
			timer_div = RTCC_DIV_256;
			timer_count = 8;
			ping_count = 60;
			break;
		case 13:
			timer_div = RTCC_DIV_256;
			timer_count = 9;
			ping_count = 54;
			break;
		case 14:
			timer_div = RTCC_DIV_256;
			timer_count = 14;
			ping_count = 53;
			break;
		case 15:
			timer_div = RTCC_DIV_256;
			timer_count = 76;
			ping_count = 57;
			break;
		default:
			timer_div = DEFAULT_TIMER_DIV;
			timer_count = DEFAULT_TIMER_COUNT;
			ping_count = DEFAULT_PING_COUNT;
			break;
	}

	// Reset counters
	int_count = timer_count;
	int_ping_count = ping_count;

	//global interrupt
	enable_interrupts(GLOBAL);

	return;
}

void ping(void)
{

	putchar('?');

	return;
}

void pong(void)
{
	// do not do reset!
	do_reset = ping_count;

	return;
}