#include "../include/defs.h"

/********************************** 
*
*  Kernel
*
***********************************/

#ifndef _kernel_
#define _kernel_

#define NONE_PROC	0
#define INIT_PID	NONE_PROC + 1

#define MAX_PROCESS_COUNT	64

#define KERNEL_MEM_SIZE		4*MB

#define KERNEL_PAGE_DIRECTORY	0x200000
#define KERNEL_TABLE_DIRECTORY	0x201000
#define KERNEL_MALLOC_ADDRESS	0x300000
#define KERNEL_MALLOC_SIZE	512*KB

// Process information
typedef struct process_t
{
	char name[32];	// executable name
	unsigned int status;	// BLOCKED -READY - EXECUTING
	unsigned int esp;		// stack pointer
	unsigned int pid;		// process id
	unsigned int ppid;	// parent process id
	unsigned int lived;		// count of timer ticks lived
	unsigned int sleep;		// count of timer ticks left to awake
	unsigned int priority;	// priority level of the process
	unsigned int tty_id;	// id of the tty for the process
	void * heap_address;	// address of heap page
	void * stack_address;	// address of the stack page
} process_t;

int (*player)(void);

typedef int size_t;
typedef short int ssize_t;
typedef enum eINT_80 {WRITE=0, READ, FORK=4} tINT_80;
typedef enum eUSER {U_KERNEL=0, U_NORMAL} tUSERS;

/* __write
*
* Recibe como parametros:
* - File Descriptor
* - Buffer del source
* - Cantidad
*
**/
size_t __write(int fd, const void* buffer, size_t count);

/* __read
*
* Recibe como parametros:
* - File Descriptor
* - Buffer a donde escribir
* - Cantidad
*
**/
size_t __read(int fd, void* buffer, size_t count);

int
__fork(void);

unsigned int scheduler (unsigned int esp);

#endif