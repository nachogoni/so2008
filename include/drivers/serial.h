#ifndef SERIAL_H_
#define SERIAL_H_

#include "../../include/kernel.h"
#include "../../include/fd.h"

#define S_BUFFER_SIZE 256

#define COMM1_BASE		0x3F8
#define COMM2_BASE		0x2F8

#define SERIAL_INT_E_ON		0x01
#define SERIAL_INT_E_OFF	0x00

#define SERIAL_PARITY_ON	0x01
#define SERIAL_PARITY_OFF	0x00

#define SERIAL_PARITY_ODD	0x00
#define SERIAL_PARITY_EVEN	0x01

#define SERIAL_STOP_1		0x00
#define SERIAL_STOP_2		0x01

typedef enum{SERIAL_S_50, SERIAL_S_300,SERIAL_S_1200, SERIAL_S_2400, SERIAL_S_4800, SERIAL_S_9600, SERIAL_S_19200, SERIAL_S_38400, SERIAL_S_57600, SERIAL_S_115200} serialSpeedT;

size_t serial_setChar (int b);

size_t serial_readBuffer (int *data);

size_t serial_flush (int b);

size_t serial_getChar (int * data);

size_t serial_writeBuffer (int b);

int init_serial(void);

int handle_serial(void);

int close_serial(int fd);

int setInterrupt(int on);
int setMCR(void);
int setbps(serialSpeedT speed);
int setParity(int parity, int odd);
int setStop(int stopBit);
int setBitCount(int bitCount);
int doReset(void);

#endif /*SERIAL_H_*/
