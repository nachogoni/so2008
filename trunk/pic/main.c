#include <16F877.h>
#fuses HS,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT
#use delay(clock=20000000)
#use rs232(baud=115200, xmit=PIN_C6, rcv=PIN_C7)

#define SET_74154_TIME	1
#define SET_74573_TIME	0

#define R_ENA				output_high(PIN_D7);
#define G_ENA				output_high(PIN_D6);
#define B_ENA				output_high(PIN_D5);
#define COL_ENA				output_low(PIN_D1);
#define STATUS_ENA			output_high(PIN_D3);
#define LINK_ENA			output_high(PIN_D2);

#define R_DIS				output_low(PIN_D7);
#define G_DIS				output_low(PIN_D6);
#define B_DIS				output_low(PIN_D5);
#define COL_DIS				output_high(PIN_D1);
#define STATUS_DIS			output_low(PIN_D3);
#define LINK_DIS			output_low(PIN_D2);

byte matriz[3 * 16] = {	0x00, 0x00, 0x00,
						0x00, 0x00, 0xFF,
						0x00, 0xFF, 0x00,
						0x00, 0xFF, 0xFF,
						0xFF, 0x00, 0x00,
						0xFF, 0x00, 0xFF,
						0xFF, 0xFF, 0x00,
						0xFF, 0xFF, 0xFF,
						0x00, 0x00, 0x00,
						0x00, 0x00, 0xFF,
						0x00, 0xFF, 0x00,
						0x00, 0xFF, 0xFF,
						0xFF, 0x00, 0x00,
						0xFF, 0x00, 0xFF,
						0xFF, 0xFF, 0x00,
						0xFF, 0xFF, 0xFF};

// Serial Rx buffer
byte buffer[3 * 16];
byte idx = 0;

#INT_RDA
void recv_rs232(){
	int recv = 0;

	recv = getc();

	if (recv == 'R')
	{
		idx = 0;
	}
	else
	{
		idx %= (3 * 16);
		matriz[idx++] = recv;
	}
}

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

void main()
{
	int i;
	byte c = 0;
	set_tris_a(0x00);
	set_tris_b(0x00);
	set_tris_d(0x00);

	output_a(0x00);
	output_b(0xFF);
	output_d(0x00);

	for (i = 0; i < (16 * 3); i++)
		buffer[i] = 0;

	enable_interrupts(GLOBAL);
	enable_interrupts(INT_RDA); 

	printf("Bienvenidos a Fleds!");

	clear();

	set_col(0);
	while(1)
	{
		c = 0;
		for (i = 0; i < (16 * 3); i+=3)
		{
			COL_DIS
			set_red(matriz[i]);
			delay_ms(SET_74573_TIME);
			set_green(matriz[i+1]);
			delay_ms(SET_74573_TIME);
			set_blue(matriz[i+2]);
			delay_ms(SET_74573_TIME);
			set_col(c++);
		}
	}

 	return;
}
