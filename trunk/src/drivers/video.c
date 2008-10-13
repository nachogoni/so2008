#include "../../include/drivers/video.h"
#include "../../include/memory.h"
#include "kc.h"
#include "kasm.h"

/********************************** 
*
*  Driver de Video
*
***********************************/

/************************ ESTRUCTURA DE LA MEMORIA DE VIDEO ************************/

typedef struct 
{
	char *m_address;
	int offset;
}s_video;

/******************** FIN ESTRUCTURA DE LA MEMORIA DE VIDEO ************************/


/************************ VARIABLES GLOBALES DEL MODULO ************************/

s_video v_video;

/********************* FIN VARIABLES GLOBALES DEL MODULO ***********************/

/************************ FUNCIONES REQUERIDAS POR EL SO ***********************/

void move_csr(void)
{
    unsigned temp;

    /* The equation for finding the index in a linear
    *  chunk of memory can be represented by:
    *  Index = [(y * width) + x] */
    //temp = csr_y * 80 + csr_x;
temp=v_video.offset / 2;
    /* This sends a command to indicies 14 and 15 in the
    *  CRT Control Register of the VGA controller. These
    *  are the high and low bytes of the index that show
    *  where the hardware cursor is to be 'blinking'. To
    *  learn more, you should look up some VGA specific
    *  programming documents. A great start to graphics:
    *  http://www.brackeen.com/home/vga */
    outportb(0x3D4, 14);
    outportb(0x3D5, temp >> 8);
    outportb(0x3D4, 15);
    outportb(0x3D5, temp);
}


/*
* video_setByte
* Funcion que setea un byte en pantalla
*
* Recibe como parametros:
* - byte b: byte a imprimir en pantalla
*/
size_t 
video_setByte (int b)
{

	switch(b)
	{
		case '\n':
			//calculo el defasaje
			v_video.offset+= (160 - v_video.offset%160);
			break;
		case '\t':
			//agrego el defasaje
			v_video.offset+= I_TAB*2;
			v_video.offset-= (v_video.offset % (I_TAB*2));
			break;
		case '\r':
			//trae el carril
			v_video.offset-=v_video.offset%160;
			break;
		case '\b':
			//backspace
			v_video.offset-=2;
			if (v_video.offset < 0)
				v_video.offset = 0;
			video_setByte(' ');
			v_video.offset-=2;
			if (v_video.offset < 0)
				v_video.offset = 0;
			break;
		default:
			v_video.m_address[v_video.offset]=(char)b;
			v_video.offset+=2;
	}

	/* Si llego al final del offset tengo que mover la memoria para arriba */
	if (v_video.offset>=160*25)
	{
		videoScroll(25);
	}
	move_csr();
//	set_cursor_pos(v_video.offset / 2);
	
	return 1;
}

int videoScroll(int height)
{
	int i;

	//Muevo el contenido
	memcpy((void*)v_video.m_address, (void*)v_video.m_address+160, 160*(height-1));
	//Limpio la ultima linea
	for(i=0;i<160;i+=2)
		v_video.m_address[160*(height-1)+i]=' ';
	//Dejo el offset en la primera posicion del ultimo renglon
	v_video.offset=160*(height-1);

	return 1;
}

/*
* video_getByte
* No hace nada
*/
size_t 
video_getByte(int b)
{
	return 1;
}

/*
* init_video
*
* Funcion que inicializa el driver de pantalla
*/
int
init_video()
{
	//Inicializo las variables de video
	v_video.m_address = (char *) __M_VIDEO;
	v_video.offset=0;

	//borra la pantalla
	clearScreen();

	//pongo el cursor en la pos 0
	set_cursor_pos(0);

	return 1;
}

/*
* close_video
*
* Funcion que finaliza el driver de pantalla
*/
int
close_video()
{
	return 1;
}

/********************** FIN FUNCIONES REQUERIDAS POR EL SO ***********************/

void clearScreen(void)
{
	k_clear_screen();
	v_video.offset=0;
	set_cursor_pos(0);
	return;
}

void setPosition(int x, int y)
{
	if (x < 0 || y < 0 || x > 80 || y > 25)
		return;
		
	v_video.offset = y * 80 * 2 + x * 2;

	return;
}

