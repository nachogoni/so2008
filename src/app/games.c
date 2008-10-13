#include "../../include/kasm.h"
#include "../../include/defs.h"
#include "../../include/grubInfo.h"
#include "../../include/fd.h"
#include "../../include/strings.h"
#include "../../include/io.h"
#include "../../include/kernel.h"
#include "../../include/memory.h"
#include "../../include/drivers/serial.h"
#include "../../include/drivers/video.h"
#include "../../include/drivers/keyboard.h"

//typedef int (* handlerT)(int ppid, int pid, char *);

int game(int ppid, int pid, char * parameters)
{

	char * cad;
	
	int val;

	cad=(char*)malloc(strlen(parameters));
	
	strcpy(cad,parameters);
	
	printf("%s - %s\n",cad, parameters);


	printf("Ingrese el valor:");

	if ((val = getInt())<0)
		printf("error");
	else
		printf("el valor fue %d\n", val);

	return 0;
}

int hangman(int ppid, int pid, char * parameters)
{
	char palabra[30], nombre[30], aux[30], *pos;
	int len_palabra=0, intentos=0,i,gano=0, len_letras=0, ok=0;
	int letra;

	
	do
		printf("Ingrese su nombre:");
	while(getstring(nombre)==0);
	do
		printf("Ingrese la palabra:");
	while((len_palabra=getstring(palabra))==0);


	for(i=0;i<len_palabra;i++)
		aux[i]='_';
	aux[i]='\0';

	while(intentos<len_palabra*2 && !gano)
	{
		clearScreen();

		printf("Va %d / %d intentos\n\n", intentos, len_palabra*2);
		printf("%s",aux);
	
		printf("\n\n\nIngrese caracter:");

		ok=0;
		
		while(!ok)
		{
			if ((letra=getchar())>0)
			{
				ok=1;
				putc(letra);	
			}
			else
				printf("\nCaracter Invalido %c",letra);
		}
		
		if (((pos=strchr(palabra, letra)) != NULL) && (strchr(aux, letra) == NULL))
			do
			{
				aux[pos-aux-60]=letra;
				len_letras++;
			}while( (pos=strchr(pos+1, letra)) != NULL);	
		else
		{
			printf("\nmmmm nop!\n");
			intentos++;
		}

		if (len_letras==len_palabra)
			gano=1;
	}	

	if (gano)
		printf("\n FELICITACIONES %s, GANASTE! Salvaste a Hugolina!\n",nombre);
	else
		printf("\n Se murio Hugolina :(... LA PALABRA ERA %s\n",palabra);

	return 0;
}
