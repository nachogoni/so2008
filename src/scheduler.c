#include "processes.h"
#include "strings.h"
#include "pagination.h"
#include "tty.h"
#include "scheduler.h"
#include "memory.h"
#include "signal.h"

extern process_t process_vector[MAX_PROCESS_COUNT];
extern unsigned int process_running;
extern unsigned int process_count;

int actual_scheduler = SCH_ROUND_ROBIN_NOT_IDLE;

void _set_scheduler(int scheduler_id)
{
	switch(scheduler_id)
	{
		case SCH_ROUND_ROBIN:
			actual_scheduler = SCH_ROUND_ROBIN;
			break;
		case SCH_ROUND_ROBIN_NOT_IDLE:
			actual_scheduler = SCH_ROUND_ROBIN_NOT_IDLE;
			break;
		case SCH_PRIORITY_ROUND_ROBIN:
			actual_scheduler = SCH_PRIORITY_ROUND_ROBIN;
			break;
		default:
			actual_scheduler = SCH_ROUND_ROBIN;
			break;
	}
	
	return;
}

unsigned int scheduler(unsigned int esp)
{
	unsigned int next_process;

	switch(actual_scheduler)
	{
		case SCH_ROUND_ROBIN:
			next_process = scheduler_roundRobin(esp);
			break;
		case SCH_ROUND_ROBIN_NOT_IDLE:
			next_process = scheduler_roundRobin_notIdle(esp);
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

static void new_timerTick(void)
{
	int i = 0;
	
	for (i = 0; i < process_count; i++)
	{
		if (process_vector[i].status == PROC_SLEEP_BLOQUED)
		{
			process_vector[i].sleep--;
			if (process_vector[i].sleep == 0)
				process_vector[i].status = PROC_READY;
		}
	}
	
	return;
}

unsigned int scheduler_roundRobin_notIdle(unsigned int esp)
{
	int new = 0;
	
	process_vector[process_running].esp = esp;

	new_timerTick();
	
	do
	{
		process_running = (process_running + 1) % process_count;
	}	
	while (process_vector[process_running].status != PROC_READY);
	
	// do not execute idle if it isnt needed
	if (process_running == 0)
	{
		do
		{
			new = (new + 1) % process_count;
		}	
		while (process_vector[new].status != PROC_READY);

		if (new != process_running)
			process_running = new;
	}
	
	
	process_vector[process_running].lived++;
	
	return process_running;
}

unsigned int scheduler_roundRobin(unsigned int esp)
{
	process_vector[process_running].esp = esp;

	new_timerTick();
	
	do
	{
		process_running = (process_running + 1) % process_count;
	}	
	while (process_vector[process_running].status != PROC_READY);
	
	process_vector[process_running].lived++;
	
	return process_running;
}

unsigned int scheduler_priority_roundRobin(unsigned int esp)
{

	process_vector[process_running].esp = esp;

	new_timerTick();
	

	if (process_vector[process_running].priority > 4 || process_vector[process_running].priority < 1) {
//		printf("cambiando prioridad al proceso: %d %s\n", process_vector[process_running].pid , process_vector[process_running].name);
		process_vector[process_running].priority = 1;
	}



//	if (process_vector[process_running].pid != 1)
//		printf("%d %s vivio %d / %d\n", process_vector[process_running].pid , process_vector[process_running].name, process_vector[process_running].lived, process_vector[process_running].priority);

	if (process_vector[process_running].lived >= process_vector[process_running].priority
		|| process_vector[process_running].lived != PROC_READY)
	{


		process_vector[process_running].lived = 0;
		// paso al siguiente proceso no bloqueado
		do
		{
			process_running = (process_running + 1) % process_count;
		}	
		while (process_vector[process_running].status != PROC_READY);

		// seteo el tiempo vivido del nuevo proceso en cero
		process_vector[process_running].lived = 0;
//		if (process_vector[process_running].pid != 1)
//			printf("entra al procesador el proceso: %d %s\n", process_vector[process_running].pid , process_vector[process_running].name);
		return process_running;
	}

	// incremento el tiempo vivido total del proceso activo
	process_vector[process_running].lived++;

	//printf("Lived : %d\n", process_vector[process_running].lived);
	return process_running;
}

void top( processTop ret[MAX_PROCESS_COUNT], int * n) {
	int i = 0, x = 0;	
	int total_cpu = 0;

	for (i = 0; i < process_count; i++)
        {
		if (process_vector[i].status == PROC_READY)
			total_cpu += process_vector[i].priority;
	}

	for (i = 0; i < process_count; i++)
	{
		if (process_vector[i].status != NONE)
        	{
			strcpy(ret[x].name, process_vector[i].name);
			ret[x].pid = process_vector[i].pid;
			ret[x].parent = process_vector[i].ppid;	
			ret[x].priority = process_vector[i].priority;
			ret[x].status = process_vector[i].status;
			ret[x].tty = process_vector[i].tty_id;
			
			/*TODO: total_cpu nunca debería ser 0. Sacar if
			cuando se implemente el blockeo.*/
			if (total_cpu && ret[x].status == PROC_READY)
			{
			  ret[x].cpu = process_vector[i].priority *1000 / total_cpu /10;
	        }
			else
			{
			  ret[x].cpu = 0;
	        }
	
			if (ret[x].status == PROC_SLEEP_BLOQUED || ret[x].status == PROC_SEM_BLOQUED ||
				ret[x].status == PROC_STDIN_BLOQUED || ret[x].status == PROC_CHILD_BLOQUED)
				ret[x].cpu = 0;
			x++;
        }
	}
	*n = x;
}

int top2(int ppid, int pid, char * parameters)
{
	int i = 0, total = 0, rest = 100, porc = 0;
	
	for (i = 0; i < process_count; i++)
    {
		if (process_vector[i].status != NONE)
			total += process_vector[i].lived;
	}
	printf("PID\tPPID\tNiceness\tStatus\tCPU%c\tName\n", '%');
	for (i = process_count - 1; i >= 0; i--)
	{
		if (process_vector[i].status != NONE)
		{
			printf("%d\t%d\t%d\t\t", process_vector[i].pid, process_vector[i].ppid, process_vector[i].priority);
	
			if (process_vector[i].pid == pid)
				printf("RUNNING");
			else
				switch (process_vector[i].status)
				{
					case PROC_CHILD_BLOQUED:
						printf("CHILD");
					break;
					case PROC_SEM_BLOQUED:
						printf("SEM");
					break;
					case PROC_SLEEP_BLOQUED:
						printf("SLEEP");
					break;
					case PROC_STDIN_BLOQUED:
						printf("READ");
					break;
					case PROC_READY:
						printf("READY");
					break;
					case PROC_EXECUTING:
						printf("RUNNING");
					break;
					default:
						printf("¿?");
					break;
				}
			
			porc = process_vector[i].lived * 100 / total;
			if (i == 0)
				porc = rest;
			rest -= porc;
			printf("\t%d\t%s:%d\n", porc, process_vector[i].name, process_vector[i].tty_id);
		}
		process_vector[i].lived = 0;
	}

	return 0;
}