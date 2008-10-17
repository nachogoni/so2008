#include "../include/sem.h"
#include "../include/pagination.h"
#include "../include/processes.h"
#include "../include/memory.h"
#include "../include/strings.h"
#include "../include/defs.h"

/********************************** 
*
*  IPCS - SEMAFOROS
*
***********************************/

typedef struct s_ipc_block_sem *  sem_block;
typedef struct s_ipc_block_proc_sem *  sem_block_proc;

typedef struct s_ipc_block_proc_sem
{
	unsigned int		pid;
	int			priority;
	sem_block_proc		next;
}s_ipc_block_proc_sem;

typedef struct s_ipc_block_sem
{
	char 		 	key[30];
	int			flags;
	unsigned int		bloquedBy;
	sem_block		next;
	sem_block_proc		proc_list;
}s_ipc_block_sem;

typedef struct
{
	int 			count_keys;
	sem_block	 	first;
}s_ipc_sem;

s_ipc_sem g_sem;


static void
addProcessSem(sem_block sem, unsigned long pid, int priority);

static int
searchSem(sem_block *actual, sem_block *ant, key_t key);

static unsigned int
getFirstProc(sem_block sem);


static int
searchSem(sem_block *actual, sem_block *ant, key_t key)
{
	int found=0;
	/* si hay semaforos armados veo que no exista ya */
	
	if (g_sem.count_keys > 0)
	{
		//obtengo el primero
		*ant = *actual = g_sem.first;

		/* busco a ver si existe */
		while( (*actual != NULL) && (( found = strcmp((*actual)->key,key)) < 0 ))
		{
			*ant = *actual;
			*actual = (*actual)->next;
		}

		if (found == 0)
			return 1;	
	}

	return 0;
}


int   
sem_set(key_t key, int flags)
{
	sem_block actual, ant = NULL, new;
	void *mem_addr;
	size_t mem_size;

	//Backup de la memoria anterior
	__get_memory_addr(&mem_addr, &mem_size);
	//Seteo zona de kernel
	__set_memory_addr((void*)KERNEL_MALLOC_ADDRESS, KERNEL_MALLOC_SIZE);

	/* si no existe lo creo */
	if (searchSem(&actual, &ant, key)) {
		printf("ya existe");
		return 1;
	}

	/* armo el bloque nuevo en zona kernel */
	if ((new=(sem_block)malloc(sizeof(s_ipc_block_sem))) == NULL)
		return 0;

	/* copio los valores a la estructura */
	strcpy(new->key, key);
	new->flags = flags;
	new->proc_list = NULL;
	
	/* si es el primero */
	if (g_sem.count_keys++ == 0)
	{
		g_sem.first = new;
		new->next = NULL;
	}
	else
	{
		new->next = actual;
		ant->next = new;
	}

	//restauro
	__set_memory_addr(mem_addr, mem_size);
	return 1;
}

static void
addProcessSem(sem_block sem, unsigned long pid, int priority)
{
	sem_block_proc proc, ant, new;
	void *mem_addr;
	size_t mem_size;

	//Backup de la memoria anterior
	__get_memory_addr(&mem_addr, &mem_size);
	//Seteo zona de kernel
	__set_memory_addr((void*)KERNEL_MALLOC_ADDRESS, KERNEL_MALLOC_SIZE);

	/* No busco a ver si ya estaba por que es bloqueante */

	//obtengo el primero
	ant = proc = sem->proc_list;

	/* busco la posicion donde agregarlo */
	/* esta ordenado por prioridad y pid */
	while (proc != NULL) 
		if (proc->priority > priority)
		{
			ant = proc;
			proc = proc->next;
		}
		else if (proc->priority == priority)
			if (proc->pid > pid)
			{
				ant = proc;
				proc = proc->next;
			}

	/* armo la estructura */
	if ((new=(sem_block_proc)malloc(sizeof(s_ipc_block_proc_sem))) == NULL)
		return;		

	/* asigno */
	new->pid = pid;
	new->priority = priority;

	/* Si es el primero */
	if (proc == NULL)
	{
		new->next = NULL;
		sem->proc_list = new;
	}
	else
	{
		ant->next = new;
		new->next = proc;
	}

	//restauro
	__set_memory_addr(mem_addr, mem_size);
	return;
}

int
sem_up(key_t key)
{
	sem_block actual, ant = NULL;

	/* Busco el semaforo */
	if (!searchSem(&actual, &ant, key))
		return -1;

	/* el semaforo actual esta en actual */
	/* Si esta bloqueado lo agrego a la lista y lo bloqueo */
	if (actual->bloquedBy)
	{
		//agrego el proceso a la lista
		addProcessSem(actual, getpid(), 1 ); //1=prioridad
		//bloquearProceso
		block_process(PROC_SEM_BLOQUED);
	}
	else
	/* sino bloqueo el semaforo */
		actual->bloquedBy=getpid();

	return 1;
}

static unsigned int
getFirstProc(sem_block sem)
{
	sem_block_proc proc;
	unsigned long procid;
	void *mem_addr;
	size_t mem_size;

	//Backup de la memoria anterior
	__get_memory_addr(&mem_addr, &mem_size);
	//Seteo zona de kernel
	__set_memory_addr((void*)KERNEL_MALLOC_ADDRESS, KERNEL_MALLOC_SIZE);

	/* No busco a ver si ya estaba por que es bloqueante */

	//obtengo el primero
	proc = sem->proc_list;

	if (proc == NULL)
		return -1;
	else
	{
		sem->proc_list = proc->next;
		procid = proc->pid;
		free(proc);
	}

	//restauro
	__set_memory_addr(mem_addr, mem_size);

	return procid;
}

int
sem_down(key_t key)
{
	sem_block actual, ant = NULL;

	/* Busco el semaforo */
	if (!searchSem(&actual, &ant, key))
		return -1;

	/* el semaforo actual esta en actual */
	/* Si el proceso que quiere de dar de baja el semaforo es el actual */
	if (actual->bloquedBy == getpid())
	{
		//Busco el proximo proceso a darle el control
		actual->bloquedBy = getFirstProc(actual);

		if (actual->bloquedBy >= 0)
			unblock_process(actual->bloquedBy);
	}

	return 1;
};

int
sem_close(key_t key)
{
	sem_block actual, ant = NULL;
	void *mem_addr;
	size_t mem_size;

	//Backup de la memoria anterior
	__get_memory_addr(&mem_addr, &mem_size);
	//Seteo zona de kernel
	__set_memory_addr((void*)KERNEL_MALLOC_ADDRESS, KERNEL_MALLOC_SIZE);

	/* Busco el semaforo */
	if (!searchSem(&actual, &ant, key)) {
		printf("sem_close :no lo encontre\n");
		return -1;
	}

	/* Si tiene algun otro semaforo atacheado no lo libero */
	if (actual->bloquedBy >= 0) {
		printf("sem_close: no libero la shm");	
		return 1;
	}

	/* si es el unico */
	if (actual == ant)
		g_sem.first = NULL;
	/* si es el primero */
	else if (actual == g_sem.first)
	{
		g_sem.first = actual->next;
	}
	else
	{
		ant->next = actual->next;
	}
	
	free(actual);

   g_sem.count_keys--;

	//restauro
	__set_memory_addr(mem_addr, mem_size);
	printf("sem_close: salgo bien");
	return 1;	
}


void
__init_sem(void)
{
	g_sem.count_keys = 0;
	g_sem.first = NULL;
	printf("__init_sem: inicializa semaforos\n");
	return;
}

