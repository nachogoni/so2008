#include "../include/memory.h"
#include "../include/io.h"

/********************************** 
*
*  Memory Manager
*
***********************************/

void *mem_addr;
size_t   mem_size;

/* memcpy
*  Copia segmentos de memoria
*
*  Recibe por parametros:
*  - source de donde copiar
*  - destino a donde se copia
*  - size a copiar
*/
size_t
memcpy(void* dest, void* source, size_t size)
{
	size_t i;
	
	if (source == NULL || dest == NULL || size<=0)
		return 0;
	
	for(i=0;i<size;i++)
		((unsigned char*)dest)[i]=((unsigned char*)source)[i];

	return i;
}


typedef struct s_memory_block *memory_block;

/* 20 bytes */
struct s_memory_block
{
	unsigned char* address;
	size_t offset;
	int free;
	memory_block next;
	memory_block back;
};

/* 16 bytes */
struct s_memory_block_header
{
	int cant;
	memory_block fst_free;
	memory_block last;
	int size_free;
};

/*  set_memory_addr
*	Funcion que inicializa la direccion memoria para el uso del malloc
*
*    Recibe como parametros:
*	- void* memory: zona de memoria donde comienza la memoria para allocar
*	- size: size de la memoria
*/
void
__set_memory_addr(void* i_memory, size_t i_size)
{
	mem_addr=i_memory;
	mem_size=i_size;
	
	return;
}

/*   init memory
*	Funcion que inicializa la memoria para su uso
*
*    Recibe como parametros:
*	- void* memory: zona de memoria donde comienza la memoria para allocar
*	- size: size de la memoria
*/
void
__init_memory(void* i_memory, size_t i_size)
{
	struct s_memory_block_header header;
	struct s_memory_block new;

	mem_addr=i_memory;
	mem_size=i_size;

	//Si existe un error de memoria dinamica asigna memoria estatica
	if (mem_addr == NULL || i_size<=0)
	{
		mem_addr = (void*)MEM_START;
		mem_size = MEM_SIZE;
	}

	//armo el header
	header.cant=1;
	header.fst_free=(memory_block)(mem_addr + sizeof(struct s_memory_block_header));
	header.last=(memory_block)(mem_addr + sizeof(struct s_memory_block_header));
	header.size_free = mem_size - sizeof(struct s_memory_block_header) - sizeof(struct s_memory_block);

	/* la copio en la memoria - la primera pos es el header */
	memcpy((void*)mem_addr, (void*)&header, sizeof(struct s_memory_block_header));

	/* armo un nuevo bloque de espacio vacio */
	new.address = mem_addr + sizeof(struct s_memory_block) + sizeof(struct s_memory_block_header);
	new.offset = mem_size - sizeof(struct s_memory_block) - sizeof(struct s_memory_block_header);
	new.free = 1;
	new.next = NULL;
	new.back = NULL;

	/* lo copio a memoria */
	memcpy((void*)mem_addr + sizeof(struct s_memory_block_header), (void*)&new, sizeof(struct s_memory_block));

	return;
}

/*   malloc
*	Reserva una zona de memoria para utilizar
*
*    Recibe como parametros:
*	- size: espacio requerido
*/
void* 
malloc(size_t size) 
{
	memory_block aux;
	struct s_memory_block new;
	struct s_memory_block_header* header;
	
	if (size<=0)
		return NULL;

	/* tengo que cargar el primer bloque de header
	*  si esta libre y me alcanza el espacio (size<offset)
	*  - le doy la posicion de memoria 
	*  - si el bloque contiguo existe entonces armo uno nuevo al final y acomodo los punteros
    	*  - si no existe armo uno nuevo donde sigue
	*  si no esta libre busco el primero que este libre y checkeo lo de arriba
	*/

	//levanto el header
	header=(struct s_memory_block_header*)mem_addr;

	/* me muevo al primero libre */
	aux=header->fst_free;

	do
	{
		/* si quedan bloques */
		if (aux != NULL)
		{
			/* si tengo espacio lo aloco */
			if ((size <= aux->offset) && aux->free)
			{
				//Si me queda espacio suficiente agrego uno en el medio
				if ((aux->offset - size - sizeof(struct s_memory_block)) > 0)
				{
					//Asigno el nuevo
					new.address = (unsigned char*)aux + sizeof(struct s_memory_block)*2 + size;
					new.offset = aux->offset - size - sizeof(struct s_memory_block);
					new.free=1;
					new.next=aux->next;
					new.back=aux;

					//el anterior del proximo soy yo
					aux->next->back=(memory_block)(new.address);
			
					//Lo copio a memoria
					memcpy((void*)(new.address - sizeof(struct s_memory_block)), (void*)&new, sizeof(struct s_memory_block));

					//pongo el next del anterior a este y al header lo mismo
					header->fst_free = aux->next = (memory_block)(new.address - sizeof(struct s_memory_block));
					header->size_free-= (sizeof(struct s_memory_block) + size);
					header->cant++;
					//reasigno el bloque
					aux->offset = size;
					aux->free = 0;
					

					return aux->address;
				}
				//sino reasigno
				else
				{
					aux->free=0;
					return (void*)aux + sizeof(struct s_memory_block);
				}
			//Si no queda espacio tengo que buscar el siguiente
			}
			else
				aux=aux->next;
		}
		else
			return NULL;
	}while(aux != NULL);
	
	return NULL;
}

/*
*	recorro el listado de paginacion hasta encontrar el que se necesita borrar
*	si el anterior esta en free y el siguiente esta en free los tengo que borrar
*
*/


/*   free
*	Libera una zona de memoria devuelta por malloc
*
*    Recibe como parametros:
*	- address: direccion de memoria devuelta
*/
void
free(void* address)
{

	memory_block ant,act,sig;
	struct s_memory_block_header* header;
	
	if (address==NULL)
		return;

	//levanto el header
	header=(struct s_memory_block_header*)mem_addr;

	//levanto header del bloque
	act=(memory_block)((void*)address - sizeof(struct s_memory_block));
	ant=act->back;
	sig=act->next;

	//Limpio el bloque
	act->free=1;
	
	if (header->fst_free > act)
		header->fst_free=act;
	
	//Si el bloque que sigue esta libre lo junto
	if (sig->free)
	{
		act->offset+=sig->offset + sizeof(struct s_memory_block);
		act->free=1;
		header->cant--;
		if (header->fst_free > act)
			header->fst_free=act;
	}
	
	//Si el anterior esta libre lo junto
	if ((ant->free) && (ant != NULL))
	{
		ant->offset+=act->offset + sizeof(struct s_memory_block);
		ant->free=1;
		header->cant--;
		if (header->fst_free > ant)
			header->fst_free=ant;
	}
	
	return;
}


