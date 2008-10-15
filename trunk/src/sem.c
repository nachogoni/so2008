#include "../include/sem.h"
#include "../include/pagination.h"
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

	/* si no existe lo creo */
	if (searchSem(&actual, &ant, key))
		return 1;

	/* armo el bloque nuevo en zona kernel */
	if ((new=(sem_block)malloc(sizeof(s_ipc_block_sem))) == NULL)
		return 0;

	/* copio los valores a la estructura */
	strcpy(new->key, key);
	new->flags = flags;
	new->proc_list = NULL;
	
	/* si es el primero */
	if (g_sem.count_keys == 0)
	{
		g_sem.first = new;
		new->next = NULL;
	}
	else
	{
		new->next = actual;
		ant->next = new;
	}

	return 1;
}

static void
addProcessSem(sem_block sem, unsigned long pid, int priority)
{
	sem_block_proc proc, ant, new;

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
		
		//addProcessSem(actual, getPid(), 1 ); //1=prioridad
		//bloquearProceso
	}
	//else
	/* sino bloqueo el semaforo */
	//	actual->bloquedBy=getPid();

	return 1;
}

int
sem_down(key_t key)
{


};

int
sem_close(key_t key)
{

};


void
__init_sem(void)
{
	g_sem.count_keys = 0;
	g_sem.first = NULL;

	return;
}

