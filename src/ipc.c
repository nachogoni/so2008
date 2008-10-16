#include "../include/ipc.h"
#include "../include/pagination.h"
#include "../include/memory.h"
#include "../include/strings.h"
#include "../include/defs.h"

/********************************** 
*
*  IPCS - SHARE MEMORY
*
***********************************/

typedef struct s_ipc_block_shm *  shm_block;

typedef struct s_ipc_block_shm
{
	int			shmid;
	char 		 	key[30];
	void * 		 	address;
	size_t			size;
	int			flags;
	shm_block		next;
}s_ipc_block_shm;

typedef struct
{
	int 			count_keys;
	shm_block	 	first;
}s_ipc_shm;

s_ipc_shm g_ipc;

void
__init_ipcs(void)
{
	g_ipc.count_keys = 0;
	g_ipc.first = NULL;

	return;
}

/*
void *shmat(int, const void *, int);
int   shmctl(int, int, struct shmid_ds *);
int   shmdt(const void *);
*/

int   
shm_open(key_t key, size_t size, int flags)
{
	shm_block actual, ant = NULL, new;
	int found=0, count_pages;
	void *address;

	/* si hay shms armados veo que no exista la key */
	if (g_ipc.first != NULL)
	{
		//obtengo el primero
		ant = actual = g_ipc.first;

		/* busco a ver si existe */
		while( (actual != NULL) && (( found = strcmp(actual->key,key)) < 0 ))
		{
			ant = actual;
			actual = actual->next;
		}

		if (found == 0)
			return actual->shmid;	
	}

	/* armo el bloque nuevo en zona kernel */
	if ((new=(shm_block)malloc(sizeof(s_ipc_block_shm))) == NULL)
		return -1;

	/* obtengo las paginas */
	count_pages = size / (4*KB);
	if (size % (4*KB))
		count_pages++;

	/* obtengo la direccion inicial */
	if ((address = get_free_page()) == NULL)
		return -1;
	
	//Obtengo las paginas necesarias
	while(--count_pages)
		if (get_free_page() == NULL)
			return -1;
	
	/* copio los valores a la estructura */
	new->shmid = g_ipc.count_keys++;
	strcpy(new->key, key);
	new->address = address;
	new->size = size;
	new->flags = flags;
	
	/* si es el primero */
	if (g_ipc.first != NULL)
	{
		g_ipc.first = new;
		new->next = NULL;
	}
	else
	{
		new->next = actual;
		ant->next = new;
	}

	return new->shmid;
}

void*
mmap(int shmid)
{
	shm_block actual, ant = NULL;
	int found=0;

	/* si hay shms armados veo que no exista la key */
	if (g_ipc.first != NULL)
		return NULL;

	//obtengo el primero
	if ((ant = actual = g_ipc.first) == NULL)
		return 0;

	/* busco a ver si existe */
	while( (actual != NULL) && (( found = (shmid == actual->shmid)) == 0 ))
	{
		ant = actual;
		actual = actual->next;
	}

	/* si lo encontro */
	if (found)
		return actual->address;	

	return NULL;
}

int
shm_close(int shmid)
{
	shm_block actual, ant = NULL;
	int found=0;

	/* si hay shms armados veo que no exista la key */
	if (g_ipc.first != NULL)
		return -1;

	//obtengo el primero
	if ((ant = actual = g_ipc.first) == NULL)
		return 0;

	/* busco a ver si existe */
	while( (actual != NULL) && (( found = (shmid == actual->shmid)) == 0 ))
	{
		ant = actual;
		actual = actual->next;
	}

	/* si lo encontro */
	if (found)
	{
		/* si es el primero */
		if (ant == actual)
			g_ipc.first = actual->next;
		else
		{
			ant->next = actual->next;
			//TODO: si se hace lo de control de paginas, liberarlas
		}

		free(actual);

		return 1;
	}

	return 0;
}

