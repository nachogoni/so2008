#include "processes.h"
#include "strings.h"
#include "pagination.h"
#include "tty.h"
#include "scheduler.h"
#include "memory.h"


extern process_t process_vector[MAX_PROCESS_COUNT];
extern unsigned int process_running;
extern unsigned int process_count;

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

unsigned int scheduler_roundRobin(unsigned int esp)
{
	process_vector[process_running].esp = esp;

	new_timerTick();
	
	do
		process_running = (process_running + 1) % process_count;
	while (process_vector[process_running].status != PROC_READY);

	return process_running;
}

unsigned int scheduler_priority_roundRobin(unsigned int esp)
{

        /*TODO: Revisar.
        * Dejé comentados los printfs que usé para debuggear.
        * Cambié el if por >= por si se baja la prioridad en ejecución,
        * no debería tener que esperar a que haga overflow para cambiar.
        */

	process_vector[process_running].esp = esp;
	if (process_vector[process_running].priority > 4 || process_vector[process_running].priority < 1)
		process_vector[process_running].priority = 1;

	if (process_vector[process_running].lived >= process_vector[process_running].priority)
	{
		// reseteo el tiempo de vida del proceso actual
		process_vector[process_running].lived = 0;

		// paso al siguiente proceso no bloqueado
		do
			process_running = (process_running + 1) % process_count;
		while (process_vector[process_running].status != PROC_READY);

		// seteo el tiempo vivido del nuevo proceso en cero
		process_vector[process_running].lived = 0;
// 		printf("Process runnin adentro: %d\n", process_running);
		return process_running;
	}

	// incremento el tiempo vivido total del proceso activo
	process_vector[process_running].lived++;

// 	printf("Process runnin afuera: %d\n", process_running);
// 	printf("Lived afuera: %d\n", process_vector[process_running].lived);
	return process_running;
}

void top( processTop ret[MAX_PROCESS_COUNT], int * n) {
	int i;	
	int total_cpu = 0;

	for (i = 0; i < process_count; i++)
        {
		if (process_vector[i].status == PROC_BLOQUED)
			total_cpu += process_vector[i].priority;
	}

	for (i = 0; i < process_count; i++)
        {
		strcpy(ret[i].name, process_vector[i].name);
		ret[i].pid = process_vector[i].pid;
		ret[i].parent = process_vector[i].ppid;	
		ret[i].priority = process_vector[i].priority;
		ret[i].status = process_vector[i].status;
		ret[i].tty = process_vector[i].tty_id;
		
		/*TODO: total_cpu nunca debería ser 0. Sacar if
		cuando se implemente el blockeo.*/
		if (total_cpu)
		{
		  ret[i].cpu = process_vector[i].priority *100.0 / total_cpu;
                }
		else
		{
		  ret[i].cpu = 0;
                }

		if (ret[i].status == PROC_BLOQUED)
			ret[i].cpu = 0;
	}
	*n = i;
}

