#include "../include/kernel.h"
#include "../include/fd.h"
#include "../include/io.h"

/********************************** 
*
*  Memory Manager
*
***********************************/

#ifndef _memory_manager_
#define _memory_manager_

/* Definiciones estaticas por si no asigna dinamicamente */
/* Inicio */
#define MEM_START			0x200000
/* size */
#define MEM_SIZE			512*KB

/*  set_memory_addr
*	Funcion que inicializa la direccion memoria para el uso del malloc
*
*    Recibe como parametros:
*	- void* memory: zona de memoria donde comienza la memoria para allocar
*	- size: size de la memoria
*/
void
__set_memory_addr(void* i_memory, size_t i_size);

/*   init memory
*	Funcion que inicializa la memoria para su uso
*
*    Recibe como parametros:
*	- void* memory: zona de memoria donde comienza la memoria para allocar
*	- size: size de la memoria
*/
void
__init_memory(void* i_memory, size_t i_size);

/* memcpy
*  Copia segmentos de memoria
*
*  Recibe por parametros:
*  - source de donde copiar
*  - destino a donde se copia
*  - size a copiar
*/
size_t memcpy(void* dest, void* source , size_t size);

/*   malloc
*	Reserva una zona de memoria para utilizar
*
*    Recibe como parametros:
*	- size: espacio requerido
*/
void* malloc(size_t size);

/*   free
*	Libera una zona de memoria devuelta por malloc
*
*    Recibe como parametros:
*	- address: direccion de memoria devuelta
*/
void free(void* address);

#endif



