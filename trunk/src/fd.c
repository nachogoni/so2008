#include "../include/fd.h"

/********************************** 
*
*  Files Descriptor
*
***********************************/

/******************** DEFINICIONES GLOBALES DEL MODULO *************************/

/* fds que utiliza el so */
file_descriptors fds;

/******************* FIN DEFINICIONES GLOBALES DEL MODULO **********************/


/*
* Inicializa el fd manager
*/
void
__init_fd(void)  //TODO: limpiar los fd activos
{
	fds.cant=0;

	return;
}


/*
* Asigna todos los parametros del sistema al fd
*/
void
fd_assign (file_descriptor* fd, int type, int (*init)(void), size_t (*setByte)(int b), size_t (*getByte)(int * b), int (*close)(int fd), int user)
{
	fd->type = type;
	fd->init = init;
	fd->setByte=setByte;
	fd->getByte=getByte;
	fd->close = close;
	fd->user = user;
	fd->open = 0;

	return;
}

/* fd_open
* Abre el fd de ese tipo y devuelve su fd
*
* Recibe como parametros:
* - tFds type: 				 el tipo de fd 
*
* Retorna negativo si no existe
*/
int
fd_open(tFds type)
{
	int actual=0;

	//Busco el fd de ese tipo
	while(fds.cant>actual && fds.actives[actual].type != type)
		actual++;

	//Si no encontro el fd devuelvo -1	
	if (actual==fds.cant)
		return -1;

	//Si el fd no esta inicializado lo inicializo
	if (!fds.actives[actual].open)
		//Si se inicializo bien lo dejo como abierto
		if (fds.actives[actual].init())
			fds.actives[actual].open=1;

	//retorno su posicion de fd
	return actual;
}

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
void
set_fd(tFds type, int (*init)(void), size_t (*setByte)(int b), size_t (*getByte)(int * b), int (*close)(int fd))
{
	int actual=0;

	//Busco si existe un fd de ese tipo
	while(fds.cant>actual && fds.actives[actual].type != type)
		actual++;

	//Si no lo encontro asigno uno nuevo sino ya queda fijo en el que era
	if (actual==fds.cant)
		actual=fds.cant++;
	
	//asigno el fd
	fd_assign (&(fds.actives[actual]), type, init, setByte, getByte, close, active_user);

	return;
}

/*
* fd_close
* Recibe como parametros:
* - int fd: el numero de fd a cerrar
*/
int
fd_close(int fd)
{
	if (fd<0 || fd>fds.cant)
		return 0;

	//Si el fd esta inicializado lo cierro
	if (fds.actives[fd].open)
		//Si pudo cerrar bien cierro todo
		if (fds.actives[fd].close(fd))
		{
			fds.actives[fd].open=0;
			return 1;
		}
		
	return 0;
}

