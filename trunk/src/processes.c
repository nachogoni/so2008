#include "kasm.h"
#include "kernel.h"
#include "tty.h"
#include "scheduler.h"
#include "memory.h"
#include "pagination.h"
#include "shell.h"

int last_pid = INIT_PID;

process_t process_vector[MAX_PROCESS_COUNT];
unsigned int process_running = 0;
unsigned int process_count = 1;

int actual_scheduler = SCH_ROUND_ROBIN;

unsigned int scheduler(unsigned int esp)
{
	unsigned int next_process;
	
	switch(actual_scheduler)
	{
		case SCH_ROUND_ROBIN:
			next_process = scheduler_roundRobin(esp);
			break;
		case SCH_PRIORITY_ROUND_ROBIN:
			next_process = scheduler_priority_roundRobin(esp);
			break;
		default:
			next_process = scheduler_roundRobin(esp);
			break;
	}
	
	process_running = next_process;
	
	// set the tty_id global of the next process
	tty_set_actual(process_vector[next_process].tty_id);
	tty_flush();
	// set the heap address global for malloc into the next process
	__set_memory_addr(process_vector[next_process].heap_address, SIZE_PER_PAGE);
	// returns the esp value to finish the task switch
	return process_vector[next_process].esp;
}

int shell(int a,int b,char * c)
{
	last_pid++;
	init_shell(last_pid, last_pid + 1,"");
	return 1;
}

int createProcess(int (*fn)(int ,int ,char *), int tty)
{
	if (process_count>=MAX_PROCESS_COUNT)
		return -1;
	
	process_vector[process_count].tty_id = tty;
	
	process_vector[process_count].stack_address = get_free_page() + 0x0FFF;
	process_vector[process_count].heap_address = get_free_page();
	
	/* Inicializa la memoria del proceso*/
	__init_memory(process_vector[process_count].heap_address, SIZE_PER_PAGE);

	process_vector[process_count].esp = createStackFrame(fn, process_vector[process_count].stack_address);
	process_vector[process_count].status = PROC_READY;
	
	return process_count++;
}

void sleep(int seconds)
{
	process_vector[process_running].status = PROC_SLEEP_BLOQUED;
	process_vector[process_running].sleep = seconds * 18;
	//TODO	
	return;	
}
