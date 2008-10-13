#include "../include/defs.h"
#include "../include/fd.h"
#include "../include/kasm.h"
#include "../include/strings.h"
#include "../include/kernel.h"
#include "../include/io.h"
#include "../include/drivers/video.h"
#include "../include/drivers/keyboard.h"

#include <stdarg.h>

static void fprint_s(int fd, char *s);
static void fprint_d(int fd, int n);
static void fprint_x(int fd, int n);

/* putc
*
* Recibe como parametros:
* - char c: caracter a imprimir por el stdout
*
**/
void
putc(char c)
{
	fputc(stdout, c);
	
	return;
}

/* printf
*  Imprime por stdout la cadena recibida por parametro
*
*  Recibe como parametros:
*  - char *s: cadena a imprimir por el stdout
*
**/
void
printf(char* s, ...)
{
	size_t lenght=0;
	char *s_aux;
	int i_aux;

	va_list ap;

	/* Si s no esta salgo */
	if (s==NULL)
		return;

	/* Inicializo los argumentos variables */
	va_start(ap, s);

	while (s[lenght] != '\0')
		if (s[lenght] == '%')
		{
			//paso al siguiente
			switch(s[++lenght])
			{
				//Si es una cadena
				case 's':
					s_aux=va_arg(ap, char*);
					fprint_s(stdout, s_aux);
					break;
				case 'd':
					i_aux=va_arg(ap, int);
					fprint_d(stdout, i_aux);
					break;
				case 'x':
					i_aux=va_arg(ap, int);
					fprint_x(stdout, i_aux);
					break;
				case 'c':
					i_aux=va_arg(ap, unsigned int);
					fputc(stdout, i_aux);
					break;
			}
			lenght++;

		}
		else
			write(stdout,(void*)(s+lenght++),1);
	

	va_end(ap);

    return;
}

/* fputc
*
* Recibe como parametros:
* - char c: caracter a imprimir por el fd
*
**/
void
fputc(int fd, char c)
{
	write(fd, (const void *)&c, 1);
	
	return;
}

/* fprintf
*  Imprime por fd la cadena recibida por parametro
*
*  Recibe como parametros:
*  - char *s: cadena a imprimir por el fd
*
**/
void
fprintf(int fd, char* s, ...)
{
	size_t lenght=0;
	char *s_aux;
	int i_aux;

	va_list ap;

	/* Si s no esta salgo */
	if (s==NULL)
		return;

	/* Inicializo los argumentos variables */
	va_start(ap, s);

	while (s[lenght] != '\0')
		if (s[lenght] == '%')
		{
			//paso al siguiente
			switch(s[++lenght])
			{
				//Si es una cadena
				case 's':
					s_aux=va_arg(ap, char*);
					fprint_s(fd, s_aux);
					break;
				case 'd':
					i_aux=va_arg(ap, int);
					fprint_d(fd, (int)i_aux);
					break;
				case 'x':
					i_aux=va_arg(ap, int);
					fprint_x(fd, i_aux);
					break;
				case 'c':
					i_aux=va_arg(ap, unsigned int);
					fputc(fd, i_aux);
					break;
			}
			lenght++;

		}
		else
			write(fd,(void*)(s+lenght++),1);
	

	va_end(ap);

    return;
}

static void
fprint_s(int fd, char *s)
{
	if (s==NULL)
		return;

	while (*s != '\0')	
		fputc(fd, *s++);

	return;
}

static void
fprint_d(int fd, int n)
{
    if (n<0)
    {
        putc('-');
        n=-n;
    }
    if (n/10)
        fprint_d(fd, n/10);

    fputc(fd, n%10+'0');

    return;
}

static void
fprint_x(int fd, int n)
{
    if (n<0)
    {
        putc('-');
        n=-n;
    }
    if (n/16)
        fprint_x(fd, n/16);

    fputc(fd, ((n%16)<10)?(n%16)+'0':(n%16)-10+'A');

    return;
}

//Devuelvo caracteres imprimibles
int 
getc(void)
{
	int c = 0, resp = 0;

	//Mientras lee algo que no sea un caracter de control
	do
		resp = read(stdin, (void *)&c, 1);
	while (c <= 0 && resp == 1);
	
	return c;
}


char * gets(char * s, int len)
{
	int c = 0, i = 0, done = 0;
	
	while (!done && (c = fgetc(stdin)) != '\0' && i < (len - 1))
	{
		s[i++] = c;
		if (c == '\n')
		{
			s[i] = '\0';
			done = 1;
		}
	}
	
	return s;
}


int fgetc(int fd)
{
	int c = 0;

	read(fd, (void *)&c, 1);

//keyboard_getChar (&c);

	return c;
}

char * fgets(int fd, char * s, int len)
{
	int c = 0, i = 0, done = 0;
	
	while (!done && (c = fgetc(fd)) != '\0' && i < (len - 1))
	{
		s[i++] = c;
		if (c == '\n')
		{
			s[i] = '\0';
			done = 1;
		}
	}
	
	return s;
}

/* getchar
*  retorna un cacaracter imprimible y a su vez imprime en pantalla
*
**/
int
getchar()
{
	int val;
	
	while((val=getc()) <= 0);	

	return val;
}

/* getInt
*  retorna la cantidad de caracteres que copio en str de la 
*  entrada estandard
*
**/
int
getstring(char *str)
{
	int i=0, val, exit=0;

	while(!exit)
		switch(val=getchar())
		{
			case '\b':
				if (i>0)
				{
					str[i--]='\0';
					putc(val);
				}
				break;
			case '\n':
				str[i]='\0';
				putc(val);
				exit=1;
				break;
			default:
				str[i++]=val;
				putc(val);

		}

	return i;
}


int
scanf(char *s, ...)
{
	size_t lenght=0;
	char *s_aux;
	int i_aux;

	va_list ap;

	/* Si s no esta salgo */
	if (s==NULL)
		return -1;

	/* Inicializo los argumentos variables */
	va_start(ap, s);

	while (s[lenght] != '\0')
		if (s[lenght] == '%')
		{
			//paso al siguiente
			switch(s[++lenght])
			{
				//Si es una cadena
				case 's':
					s_aux=va_arg(ap, char*);
					getstring(s_aux);
					break;
				case 'd':
					i_aux=va_arg(ap, int);
					//fprint_d(stdout, i_aux);
					break;
				case 'x':
					i_aux=va_arg(ap, int);
					//fprint_x(stdout, i_aux);
					break;
				case 'c':
					i_aux=va_arg(ap, unsigned int);
					//fputc(stdout, i_aux);
					break;
			}
			lenght++;

		}
		else
			write(stdout,(void*)(s+lenght++),1);
	

	va_end(ap);

    return 1;
}

/* getInt
*  retorna un entero recibido por stdin, -1 si es invalido
*
**/
int
getInt()
{
	int i=0, val=0, exit=0, aux;

	while(!exit)
	{
		aux=getchar();

		switch(aux)
		{
			case '\b':
				if (i>0)
				{
					val=val/10;
					putc(aux);
					i--;
				}
				break;
			case '\n':
				putc(aux);
				exit=1;
				break;
			default:
				//muevo el valor
				if(isNumeric(aux))
				{
					val=val*10;
					val+=(aux-'0');
					putc(aux);
					i++;
				}

		}
	}


	return val;
}


/* Funciones extraidas de http://www.osdever.net/bkerndev/Docs/whatsleft.htm */

unsigned char inportb (unsigned short _port)
{
    unsigned char rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

void outportb (unsigned short _port, unsigned char _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}
