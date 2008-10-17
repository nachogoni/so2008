#include "../include/ipc.h"
#include "../include/pagination.h"
#include "../include/memory.h"
#include "../include/strings.h"
#include "../include/defs.h"
#include "../include/kernel.h"

/********************************** 
*
*  IPCS - SHARE MEMORY
*
***********************************/

typedef struct s_ipc_block_shm *  shm_block;

typedef struct s_ipc_block_shm
{
   int         shmid;
   char        key[30];
   void *         address;
   size_t         size;
   int         flags;
   shm_block      next;
}s_ipc_block_shm;

typedef struct
{
   int         count_keys;
   shm_block      first;
}s_ipc_shm;

s_ipc_shm g_ipc;
extern unsigned int process_running;
extern process_t process_vector[];

void
__init_ipcs(void)
{
   g_ipc.count_keys = 0;
   g_ipc.first = NULL;

   return;
}

void
delShmToProcess(void *addr, size_t size)
{
	int i, found=0, exit=0;

	for (i=0;i<MAX_PROCESS_COUNT && !found && !exit;i++)
		if (process_vector[process_running].shm_vec[i].address != NULL)
		{
			if (process_vector[process_running].shm_vec[i].address == addr)
			{
				process_vector[process_running].shm_vec[i].address = NULL;
				found = 1;
			}
		}
		else
			exit=1;

	return;
}


void
addShmToProcess(void *addr, size_t size)
{
	int i, found=0, exit=0;

	for (i=0;i<MAX_PROCESS_COUNT && !found && !exit;i++)
		if (process_vector[process_running].shm_vec[i].address != NULL)
		{
			if (process_vector[process_running].shm_vec[i].address == addr)
			{
				found = 1;
			}
		}
		else
			exit=1;

	if (found)
		return;

	if (exit)
	{
		process_vector[process_running].shm_vec[i].address = addr;
		process_vector[process_running].shm_vec[i].size = size;
	}

	return;
}

/*
void *shmat(int, const void *, int);
int   shmctl(int, int, struct shmid_ds *);
int   shmdt(const void *);
*/

int   
__shm_open(key_t key, size_t size, int flags)
{
   shm_block actual, ant = NULL, new;
   int found=0, count_pages;
   void *address, *mem_addr;
   size_t mem_size;

   //Backup de la memoria anterior
   __get_memory_addr(&mem_addr, &mem_size);
   //Seteo zona de kernel
   __set_memory_addr((void*)KERNEL_MALLOC_ADDRESS, KERNEL_MALLOC_SIZE);

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
      {
  	 //Lo agrego al proceso
         addShmToProcess(actual->address, actual->size);

         return actual->shmid;   
      }
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
   if (g_ipc.first == NULL)
   {
      g_ipc.first = new;
      new->next = NULL;
   }
   else
   {
      new->next = actual;
      ant->next = new;
   }

   //Lo agrego al proceso
   addShmToProcess(new->address, new->size);


   //restauro
   __set_memory_addr(mem_addr, mem_size);

   return new->shmid;
}

void*
__mmap(int shmid)
{
   shm_block actual, ant = NULL;
   int found=0;

   /* si hay shms armados veo que no exista la key */
   if (g_ipc.first == NULL)
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
__shm_close(int shmid)
{
   shm_block actual, ant = NULL;
   int found=0;
   void *mem_addr;
   size_t mem_size;

   //Backup de la memoria anterior
   __get_memory_addr(&mem_addr, &mem_size);
   //Seteo zona de kernel
   __set_memory_addr((void*)KERNEL_MALLOC_ADDRESS, KERNEL_MALLOC_SIZE);

   /* si hay shms armados veo que no exista la key */
   if (g_ipc.first == NULL) 
      return -1;

   actual = g_ipc.first;

   /* busco a ver si existe */
   while((actual != NULL) && !found)
	if ((found = (shmid == actual->shmid)) == 0 )
	{
	      ant = actual;
	      actual = actual->next;
	}

   /* si lo encontro */
   if (found)
   {

      /* si es el primero */
      if (ant == NULL)
         g_ipc.first = actual->next;
      else
      {
         ant->next = actual->next;
      }

      delShmToProcess(actual->address, actual->size);
      free(actual);

      return 1;
   }

   //restauro
   __set_memory_addr(mem_addr, mem_size);

   return 0;
}

