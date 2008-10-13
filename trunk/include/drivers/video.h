#include "../../include/kernel.h"

/********************************** 
*
*  Driver de Video
*
***********************************/

#ifndef _video_
#define _video_

/* espacio del tab */
#define I_TAB		8
/* direccion de comienzo de la zona de memoria */
#define __M_VIDEO 	0xb8000 

/************************ FUNCIONES REQUERIDAS POR EL SO ***********************/

/*
* video_setByte
* Funcion que setea un byte en pantalla
*
* Recibe como parametros:
* - byte b: byte a imprimir en pantalla
*/
size_t video_setByte (int b);

/*
* video_getByte
* No hace nada
*/
size_t video_getByte(int b);

/*
* init_video
*
* Funcion que inicializa el driver de pantalla
*/
int init_video();

/*
* init_video
*
* Funcion que finaliza el driver de pantalla
*/
int close_video();

/********************** FIN FUNCIONES REQUERIDAS POR EL SO ***********************/

void clearScreen(void);

void setPosition(int x, int y);

int videoScroll(int height);

#endif

