#include "../../include/drivers/serial.h"
#include "../../include/strings.h"
#include "../../include/io.h"
#include "../../include/memory.h"
#include "../../include/kernel.h"

typedef struct {
	unsigned char LCR;
	unsigned char DLL;
	unsigned char DLM;
	unsigned char MCR;
	unsigned char IER;
} serialStateT;

typedef struct {
	int buffer[S_BUFFER_SIZE];
	int write;
	int read;
	int qty;
} serial_bufferT;

static serial_bufferT sread_buffer = {{0},0,0,0};
static serial_bufferT swrite_buffer = {{0},0,0,0};

static serialStateT serialState;

static int aSize;

static int initialized = 0;

static int commBase = COMM1_BASE;

static int bufferNotFull ( serial_bufferT b ) {
	return (b.qty != (S_BUFFER_SIZE -1) );
}

static int bufferNotEmpty ( serial_bufferT b ) {
	return (b.qty != 0);
}

size_t serial_setChar (int b) {
	if( bufferNotFull(swrite_buffer) ) {
		swrite_buffer.buffer[swrite_buffer.write] = b;
		swrite_buffer.qty++;
		if ( ++(swrite_buffer.write) == S_BUFFER_SIZE)
			swrite_buffer.write = 0;
		if(swrite_buffer.qty == aSize) {
			serial_flush(1);
		}
	}
	return 1;
}

size_t serial_readBuffer (int *data) {
	if ( bufferNotEmpty(swrite_buffer) ) {
		swrite_buffer.qty--;
		*data = swrite_buffer.buffer[swrite_buffer.read];
		if ( ++(swrite_buffer.read) == S_BUFFER_SIZE) 
			swrite_buffer.read = 0;
		return 1;
	}
	return 0;
}

size_t serial_flush (int b) {
	int data;
	while( serial_readBuffer(&data) != 0 ) {
		outportb(0x3f8, data);
	}
	return 1;
}
size_t serial_getChar (int * data) {
	if ( bufferNotEmpty(sread_buffer) ) {
		sread_buffer.qty--;
		*data = sread_buffer.buffer[sread_buffer.read];
		if ( ++(sread_buffer.read) == S_BUFFER_SIZE) 
			sread_buffer.read = 0;
		return 1;
	}
	return 0;
}

size_t serial_writeBuffer (int b) {
	if( bufferNotFull(sread_buffer) ) {
		sread_buffer.buffer[sread_buffer.write] = b;
		sread_buffer.qty++;
		if ( ++(sread_buffer.write) == S_BUFFER_SIZE) 
			sread_buffer.write = 0;
		return 1;
	}
	return 0;
}

int init_default(void)
{
	setInterrupt(SERIAL_INT_E_OFF);
	setParity(SERIAL_PARITY_OFF,SERIAL_PARITY_ODD);
	setMCR();
	setbps(SERIAL_S_9600);
	setStop(SERIAL_STOP_1);
	setBitCount(8);

	return 1;
}

int setMCR(void)
{
	outportb(commBase + 4, 0x08);
	return 1; 
}

int init_serial(void) {

	doReset();
	
	sread_buffer.qty = 0;
	sread_buffer.read = 0;
	sread_buffer.write = 0;
	
	swrite_buffer.qty = 0;
	swrite_buffer.read = 0;
	swrite_buffer.write = 0;

	aSize = 1;

	if (!initialized)
	{
		serialState.LCR = 0;
		serialState.DLL = 0;
		serialState.DLM = 0;
		serialState.MCR = 0;
		serialState.IER = 0;
	
		init_default();	

		initialized = 1;
	}

	doReset();
	setInterrupt(SERIAL_INT_E_ON);
	
	return 1;
}

int handle_serial(void)
{
	unsigned char data;
	data = inportb(0x3f8);
	serial_writeBuffer(data);
	return 1;
}

int close_serial(int fd)
{
	setInterrupt(SERIAL_INT_E_OFF);
	return 1;
}

int setInterrupt(int on)
{
	unsigned char ie = 0;	
	
	if (on)
		ie = 0x01;

	outportb(commBase + 3, serialState.LCR & 0x7F);
        outportb(commBase + 1, ie); 
	outportb(commBase + 3, serialState.LCR);
		 
	return 1;	 
}

int doReset(void)
{
	outportb(commBase + 3, serialState.LCR & 0x7F);
        outportb(commBase + 2, 0x06); 
	outportb(commBase + 3, serialState.LCR);
		 
	return 1;	 
}

int setbps(serialSpeedT speed)
{
	char speedReg[][2] = { {0x00, 0x09}, {0x80, 0x01}, {0x60, 0x00}, {0x30, 0x00},
	{0x18, 0x00}, {0x0C, 0x00}, {0x06, 0x00}, {0x03, 0x00}, {0x02, 0x00}, {0x01, 0x00}};
	
	outportb(commBase + 3, serialState.LCR | 0x80);
	outportb(commBase + 0, serialState.DLL = speedReg[speed][0]);
	outportb(commBase + 1, serialState.DLM = speedReg[speed][1]);
	outportb(commBase + 3, serialState.LCR);
		 
	return 1;	 
}

int setParity(int parity, int odd)
{
	unsigned char p = 0;

	if (parity)
	{
		p |= 0x08;
		if (!odd)
			p |= 0x10;
	}	
	
	serialState.LCR = (serialState.LCR & 0xE7) | p;
	
	outportb(commBase + 3, serialState.LCR);

	return 1;
}

int setStop(int stopBit)
{
	unsigned char s = 0;
	
	if (stopBit)
		s = 0x04;
	
	serialState.LCR = (serialState.LCR & 0xFB) | s;
	
	outportb(commBase + 3, serialState.LCR);

	return 1;
}

int setBitCount(int bitCount)
{
	if (bitCount >= 5 && bitCount <= 8)
		bitCount -= 5;
	
	serialState.LCR = (serialState.LCR & 0xFC) | bitCount;
	
	outportb(commBase + 3, serialState.LCR);

	return 1;
}

