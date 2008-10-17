#include "kernel.h"
#include "fd.h"

#ifndef _io_h_
#define _io_h_

/******************** VARIABLE EXTERNAS AL MODULO ************************/

extern int stdout;
extern int stdin;
extern int stdser;

/****************** FIN VARIABLE EXTERNAS AL MODULO **********************/

/* putc
*
* Recibe como parametros:
* - char c: caracter a imprimir por el stdout
*
**/
void putc(char c);

/* printf
*  Imprime por stdout la cadena recibida por parametro
*
*  Recibe como parametros:
*  - char *s: cadena a imprimir por el stdout
*
**/
void printf(char *s, ...);

/* fputc
*
* Recibe como parametros:
* - char c: caracter a imprimir por el fd
*
**/
void
fputc(int fd, char c);

/* fprintf
*  Imprime por fd la cadena recibida por parametro
*
*  Recibe como parametros:
*  - char *s: cadena a imprimir por el fd
*
**/
void
fprintf(int fd, char* s, ...);

/* getchar
*  retorna un cacaracter imprimible y a su vez imprime en pantalla
*
**/
int
getchar();


/* getInt
*  retorna un entero recibido por stdin, -1 si es invalido
*
**/
int
getInt();

/* getInt
*  retorna la cantidad de caracteres que copio en str de la 
*  entrada estandard
*
**/
int
getstring(char *str);

/* getc
*  retorna un cacaracter imprimible
*
**/
int 
getc(void);

int
scanf(char *fmt, ...);

/* gets
*  copia en la cadena la longitud de caracteres
*
**/
char * 
gets(char * s, int len);

/* fgetc
*  retorna un cacaracter imprimible y a su vez imprime en pantalla
*
**/
int 
fgetc(int fd);

/* fgets
*  retorna un cacaracter imprimible y a su vez imprime en pantalla
*
**/
char * 
fgets(int fd, char * s, int len);

int atoi(char * string);

unsigned char inportb (unsigned short _port);
void outportb (unsigned short _port, unsigned char _data);

#endif
