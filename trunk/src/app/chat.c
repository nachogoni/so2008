#include "../../include/defs.h"
#include "../../include/fd.h"
#include "../../include/strings.h"
#include "../../include/io.h"
#include "../../include/kernel.h"
#include "../../include/drivers/video.h"

#define BUFFER_SIZE	60

static void cleanBuffer(char * buffer, int len);

static void cleanBuffer(char * buffer, int len)
{
	int i = 0;

	if (buffer == NULL)
		return;
		
	for (i = 0; i < len; i++)
		buffer[i] = '\0';


	return;
}

int cleanInput(int local_y)
{
	int i = 0;

	setPosition(0, local_y);
	for (i = 0;i < BUFFER_SIZE + 5; i++)
		putc(' ');
	setPosition(0, local_y);

	return 0;
}

/* Inicia el chat */
int init_chat(int ppid, int pid, char * parameters)
{
	int key = 0, ser = 0, salir = 0, len = 0;
	char buffer[BUFFER_SIZE + 1], recibe[BUFFER_SIZE + 1];
	int remoto_x = 0, conv_y = 0, local_y = 22;
	
	clearScreen();
	
	cleanBuffer(buffer, BUFFER_SIZE);
	cleanBuffer(recibe, BUFFER_SIZE);

	stdser = fd_open(SERIAL);
	
	while (!salir)
	{
		ser = fgetc(stdser);
		key = fgetc(stdin);
		
		if (key > 0)
		{
			// Imprimible -> buffer
			switch (key)
			{
				case '\n':	// Imprime lo que digo
					setPosition(0, conv_y++);
					printf("You: %s", buffer);
					if (strcmp(buffer, "quit") == 0)
						salir = 1;
					cleanBuffer(buffer, BUFFER_SIZE);
					len = 0;
					if (conv_y > 20)
					{
						videoScroll(21);
						conv_y = 20;
					}
					fputc(stdser, key);
					cleanInput(local_y);
					break;
				case '\b':	// Backspace
					if (len > 0)
					{
						buffer[--len] = '\0';
						cleanInput(local_y);
						setPosition(0, local_y);
						printf("%s", buffer);
						fputc(stdser, key);
					}/*
					else
						beep();*/	// TODO: beep();
					break;
				case '\t':	// No hace nada
					break;
				default:	// demas imprimibles
					if (len < BUFFER_SIZE)
					{
						buffer[len++] = key;
						setPosition(0, local_y);
						printf("%s", buffer);
						fputc(stdser, key);
					}/*
					else
						beep();*/	// TODO: beep();
			}
		}
		else if (key < 0)
		{
			// Caracteres de control
		}
		
		if (ser > 0)
		{
			// Recibi data del serial -> muestro por la pantalla
			if (ser == '\n' || (remoto_x == BUFFER_SIZE))
			{
				setPosition(0, conv_y++);
				printf("buddy: %s", recibe);
				if (remoto_x == BUFFER_SIZE)
					putc(ser);
				if (conv_y > 20)
				{
					videoScroll(21);
					conv_y--;
				}
				remoto_x = 0;
				cleanBuffer(recibe, BUFFER_SIZE);
			}
			else if (ser == '\b')
			{
				if (remoto_x > 0)
					recibe[remoto_x--] = '\0';
			}
			else
			{
				recibe[remoto_x++] = ser;
			}
		}
		
	}
	
	fd_close(stdser);
	
	return 0;
}
