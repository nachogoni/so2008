#ifndef _scheduler_
#define _scheduler_

#include "../include/kernel.h"

typedef struct processTop {
	char name[32];			// executable name
	unsigned int status;	// BLOCKED -READY - EXECUTING
	unsigned int pid;		// process id
	unsigned int parent;	// parent process id
	unsigned int priority;	// priority level of the process
	double cpu;				// percentage of cpu for this process
} processTop;

unsigned int scheduler_roundRobin(unsigned int esp);

unsigned int scheduler_priority_roundRobin(unsigned int esp);

void top( processTop ret[MAX_PROCESS_COUNT], int * n);
#endif
