#include "../include/scheduler.h"
#include "../include/strings.h"

extern process_t process_vector[MAX_PROCESS_COUNT];
extern unsigned int process_running;
extern unsigned int process_count;

unsigned int scheduler_roundRobin(unsigned int esp)
{
	process_vector[process_running].esp = esp;
	
	// paso al siguiente proceso no bloqueado
	do
		process_running = (process_running + 1) % process_count;
	while (process_vector[process_running].status != PROC_READY);
	
	return process_running;
}

unsigned int scheduler_priority_roundRobin(unsigned int esp)
{
	process_vector[process_running].esp = esp;
	
	if(process_vector[process_running].lived == process_vector[process_running].priority)
	{
		// reseteo el tiempo de vida del proceso actual
		process_vector[process_running].lived = 0;
		// paso al siguiente proceso no bloqueado
		do
			process_running = (process_running + 1) % process_count;
		while (process_vector[process_running].status != PROC_READY);
		// seteo el tiempo vivido del nuevo proceso en cero
		process_vector[process_running].lived = 0;
		return process_running;
	}
	// incremento el tiempo vivido total del proceso activo
	process_vector[process_running].lived++;
	return process_running;
}

void top( processTop ret[MAX_PROCESS_COUNT], int * n) {
	int i;	
	int total_cpu = 0;

	for (i = 0; i < process_count; i++) {
		if (process_vector[i].status == PROC_BLOQUED)
			total_cpu += process_vector[i].priority;
	}

	for (i = 0; i < process_count; i++) {
		strcpy(ret[i].name, process_vector[i].name);		
		ret[i].pid = process_vector[i].pid;		
		ret[i].parent = process_vector[i].parent;	
		ret[i].priority = process_vector[i].priority;
		ret[i].status = process_vector[i].status;
		ret[i].cpu = (double)(process_vector[i].priority) * 100 / total_cpu;
		if (ret[i].status == PROC_BLOQUED) 
			ret[i].cpu = 0;
	}
	*n = i;
}

