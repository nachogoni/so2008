#include "kasm.h"
#include "kernel.h"
#include "tty.h"
#include "scheduler.h"
#include "ipc.h"
#include "strings.h"
#include "memory.h"
#include "pagination.h"
#include "processes.h"
#include "shell.h"
#include "signal.h"

int last_pid = INIT_PID;

process_t process_vector[MAX_PROCESS_COUNT];
unsigned int process_running = 0;
unsigned int process_count = 1;

void kernel_return_Function_unblock(void)
{
	int i, found, resp;

	 __asm__ __volatile__("mov %0, %%eax": "=aL" (resp));
		
	i = 0;
	found = 0;
	
	for (i = 0; i < process_count && !found; i++)
	{
		if (process_vector[i].pid == process_vector[process_running].ppid)
		{
			if (process_vector[i].status != NONE)
				process_vector[i].status = PROC_READY;
			process_vector[i].response = resp;
			found = 1;
		}
	}
	_kill(process_vector[process_running].pid, SIGKILL);
	
	task_switch();
	
	return;
}

void kernel_return_Function_no_unblock(void)
{
	process_vector[process_running].status = NONE;

	task_switch();
	
	return;
}

unsigned int getNextPID(void)
{
	return ++last_pid;
}

int createProcess(int (*fn)(int, int, char *), char * name, char * parameters, int tty, void (*ret_fn)(void))
{
	int new = 0, i = 0, found = 0;
	
	if (name == NULL)
		return -1;
	
	for (i = 0; i < MAX_PROCESS_COUNT && !found; i++)
	{
		if (process_vector[i].status == NONE)
		{
			found = 1;
			new = i;
		}
	}
	
	if (!found)
		return -1;
	
	process_vector[new].tty_id = tty;
	
	strcpy(process_vector[new].name, name);

	process_vector[new].pid = getNextPID();
	process_vector[new].ppid = getpid();
	
	process_vector[new].stack_address = get_free_page() + 0x0FFF;
	process_vector[new].heap_address = get_free_page();
	
	/* Inicializa la memoria del proceso*/
	__init_memory(process_vector[new].heap_address, SIZE_PER_PAGE);

	process_vector[new].esp = createStackFrame(fn, process_vector[new].stack_address,
		process_vector[new].ppid, process_vector[new].pid, parameters, ret_fn);
	process_vector[new].status = PROC_READY;
	process_vector[new].priority = DEFAULT_PRIORITY;
	
	if (process_count < MAX_PROCESS_COUNT)
		process_count++;
		
	addShmPipe(process_vector[new].ppid, process_vector[new].pid);
	
	return new;
}

void createIdle(void)
{
	process_vector[0].tty_id = 0;
	strcpy(process_vector[0].name, "init");
	process_vector[0].pid = INIT_PID;
	process_vector[0].ppid = INIT_PID;
	process_vector[0].status = PROC_READY;
	process_vector[0].priority = DEFAULT_PRIORITY;
	
	return;
}

void block_process(procStatusT block_type)
{
	process_vector[process_running].status = block_type;
	task_switch();
	return;	
}

void unblock_process(unsigned int pid)
{
	int i = 0, found = 0;
	
	for (i = 0; i < process_count && !found; i++)
	{
		if (process_vector[i].pid == pid)
		{
			process_vector[i].status = PROC_READY;
			found = 1;
		}
	}
	
	return;	
}

int getResponse(void)
{
	return process_vector[process_running].response;
}

unsigned int getpid(void)
{
	return process_vector[process_running].pid;
}

int getProcessTTY(void)
{
	return process_vector[process_running].tty_id;
}

unsigned int getppid(void)
{
	return process_vector[process_running].ppid;
}

void sleep(int seconds)
{
	process_vector[process_running].sleep = seconds * 18;
	block_process(PROC_SLEEP_BLOQUED);
	return;	
}

unsigned int _kill(unsigned int pid, int signal) {
	
	int i = 0;

	switch(signal) {
		case SIGKILL: 
			while(process_vector[i].pid != pid && i < process_count) {
//				printf("proceso :%d - %s no matado\n",process_vector[i].pid,process_vector[i].name);
				i++;
			}
			if  ( i != process_count) {
//				printf("matando a %d - %s\n",process_vector[i].pid,process_vector[i].name);
				process_vector[i].status = NONE;
				unblockPid(process_vector[i].ppid);
				task_switch();
				i = 0;
				while(i < process_count) {
					if(process_vector[i].ppid == pid) {
//						printf("\t-- entro a matar al hijo :%d - %s \n",process_vector[i].pid,process_vector[i].name);	
						_kill(process_vector[i].pid, SIGKILL);
					}	
					i++;
				}				
			}
			break;
		default: return 0;
	}			
	task_switch();
	return 0;	
}

unsigned int set_pid_priority(unsigned int pid, int priority)
{
	int i = 0;

	if (priority < 1 || priority > 4)
	{
		printf("Priority must be a number between 1 and 4\n");
		return 0;
	}
	
	while(process_vector[i].pid != pid && i < MAX_PROCESS_COUNT)
	{
		i++;
	}

	if  (i < MAX_PROCESS_COUNT && process_vector[i].pid == pid)
	{
		process_vector[i].priority = priority;
		printf("'%s' now has priority %d\n", process_vector[i].name, priority); 
	}
	else
		printf("No such process\n");
		
	return 0;
}

int killCurrent(void) {
	int pid = process_vector[process_running].pid;

	_kill(pid,SIGKILL);
	task_switch();
	
	return 0;
}

int unblockPid(int pid) {
	int i = 0;

	while(process_vector[i].pid != pid && i < process_count) {
		i++;
	}
	if (i != process_count ) {
//		printf("encontre al padre");
		if(process_vector[i].status == PROC_CHILD_BLOQUED)
			process_vector[i].status = PROC_READY;
	}
	return 0;
}
