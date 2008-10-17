#ifndef _scheduler_
#define _scheduler_

#define DEFAULT_PRIORITY        1

enum {SCH_ROUND_ROBIN, SCH_ROUND_ROBIN_NOT_IDLE, SCH_PRIORITY_ROUND_ROBIN};

typedef struct processTop {
	char name[32];		// executable name
	unsigned int status;	// BLOCKED -READY - EXECUTING
	unsigned int pid;	// process id
	unsigned int tty;	// tty
	unsigned int parent;	// parent process id
	unsigned int priority;	// priority level of the process
	unsigned int cpu;	// percentage of cpu for this process
} processTop;

void _set_scheduler(int scheduler_id);

unsigned int scheduler(unsigned int esp);

unsigned int scheduler_roundRobin(unsigned int esp);

unsigned int scheduler_roundRobin_notIdle(unsigned int esp);

unsigned int scheduler_priority_roundRobin(unsigned int esp);

void top( processTop ret[MAX_PROCESS_COUNT], int * n);

int top2(int ppid, int pid, char * parameters);

#endif
