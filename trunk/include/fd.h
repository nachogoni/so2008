#include "../include/kernel.h"

/********************************** 
*
*  Files Descriptor
*
***********************************/

#ifndef _fd_
#define _fd_

/*********************** DEFINICIONES DEL MODULO *************************/

/* cantidad de fds utilizados */
#define FD_COUNT 3

/* typos de FD */
typedef enum eFds {VIDEO=0, KEYBOARD, SERIAL, TTY} tFds;

/******************* FIN DEFINICIONES DEL MODULO *************************/


/************************ ESTRUCTURAS DE LOS FDS ************************/

/* Descriptor de Archivos */
typedef struct
{
	tFds type;
	int (*init)(void);
	size_t (*setByte)(int b);
	size_t (*getByte)(int * b);
	int (*close)(int fd);
	int user;	// TODO: chequear quien trata de acceder a el
	int open;
} file_descriptor;

/* Manager de Fds */
typedef struct 
{
	int cant;
	file_descriptor actives[FD_COUNT]; //TODO: setear cuales son activos
}file_descriptors;

/********************** FIN ESTRUCTURAS DE LOS FDS **********************/

/******************** VARIABLE EXTERNAS AL MODULO ************************/

/* Usuario activo del sistema del kernel */
extern int active_user;

/* FILE DESCRIPTIRS */
extern file_descriptors fds;

/**************** FIN VARIABLE EXTERNAS AL MODULO ************************/

/*
* Inicializa el fd manager
*/
void
__init_fd(void);

/* fd_open
* Abre el fd de ese tipo y devuelve su fd
*
* Recibe como parametros:
* - tFds type: 				 el tipo de fd 
*
* Retorna negativo si no existe
*/
int fd_open(tFds type);

/*
* set_fd
* Setea un nuevo Fd
*
* Recibe como parametros:
* - tFds type: 		      el tipo de fd 
* - int (*init)(void): 		 funcion que inicializa el driver
* - size_t (*setByte)(byte b): funcion que setea un byte en el driver (para que utilice el kernel)
* - size_t (*getByte)(byte b): funcion que obtiene un byte del driver (para que utilice el kernel)
* - int (*close)(int fd):	 funcion que cierra el fd
*/
void set_fd(tFds type, int (*init)(void), size_t (*setByte)(int b), size_t (*getByte)(int * b), int (*close)(int fd));

/*
* fd_close
* Recibe como parametros:
* - int fd: el numero de fd a cerrar
*/
int fd_close(int fd);

#endif
