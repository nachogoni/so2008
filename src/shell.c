#include "../include/defs.h"
#include "../include/fd.h"
#include "../include/strings.h"
#include "../include/io.h"
#include "../include/ipc.h"
#include "../include/sem.h"
#include "../include/kernel.h"
#include "../include/kasm.h"
#include "../include/memory.h"
#include "../include/shell.h"
#include "../include/grubInfo.h"
// #include "../include/drivers/video.h"
#include "../include/drivers/tty.h"
#include "../include/drivers/keyboard.h"
#include "../include/drivers/serial.h"
#include "processes.h"
#include "signal.h"

/* Aplicaciones */
#include "./app/top.h"
#include "./app/chat.h"
#include "./app/games.h"
#include "./app/tron.h"
//#include "./app/movie.h"
// #include "./app/presenta.h"

#define MIN(a,b)	((a) < (b))?(a):(b)
#define MAX(a,b)	((a) > (b))?(a):(b)

typedef int (* handlerT)(int ppid, int pid, char *);

static void cleanBuffer(char * buffer, int len);
static int getCommand(char * buffer, int length, char history[HISTORY_SIZE][BUFFER_SIZE + 1], int count);

static int handle_div0(int ppid, int pid, char * parameters);
static int handle_malloc(int ppid, int pid, char * parameters);
static int handle_help(int ppid, int pid, char * parameters);
static int handle_clear(int ppid, int pid, char * parameters);
static int handle_shell(int ppid, int pid, char * parameters);
static int handle_exit(int ppid, int pid, char * parameters);
static int handle_pid(int ppid, int pid, char * parameters);
static int handle_mem(int ppid, int pid, char * parameters);
static int handle_loadkeys(int ppid, int pid, char * parameters);
static int handle_mem(int ppid, int pid, char * parameters);
static int handle_configSerial(int ppid, int pid, char * parameters);
static int handle_top(int ppid, int pid, char * parameters);
static int handle_nros(int ppid, int pid, char * parameters);
static int handle_infinito(int ppid, int pid, char * parameters);
static int handle_kill(int ppid, int pid, char * parameters);
static int handle_sm1(int ppid, int pid, char * parameters);
static int handle_sm2(int ppid, int pid, char * parameters);
static int handle_reboot(int ppid, int pid, char * parameters);

static int next_pid = 1;

#define MAX_LEN_COMMAND		30
#define MAX_LEN_COMMAND_HELP	500

typedef struct
{
	char 	 name[MAX_LEN_COMMAND];
	handlerT instruction;
	char	 help[MAX_LEN_COMMAND_HELP];
}command;

/* Comandos disponibles del shell */
command commands_avaiable[] = {
			{"help", handle_help,"list this help"},
			{"clear", handle_clear,"clear screen"},
			{"shell", handle_shell, "launches a new shell"},
			{"exit", handle_exit, "exit actual process"},
			{"pid", handle_pid, "shows actual process id"},
			{"mem", handle_mem, "shows total memory"},
			{"chat", init_chat, "starts the chat"},
			{"loadkey", handle_loadkeys, "loadkey [es|us]: sets or gets the keyboard map"},
			{"tron", init_tron, "Help Hugo rescue Hugolina ;O)"},
//			{"wmplayer", init_wmplayer,"Starts wmplayer and plays StarWars"},
// 			{"presents", init_presents,"HumiX presentation"},
			{"div0", handle_div0, "Tries to divide by zero and raises an exception"},
			{"malloc",handle_malloc, "Tries to alloc memory until the systems runs out of it"},
			{"ser.cfg", handle_configSerial,"Configures serial ports"},
			{"hangman",hangman,"Hangman game"},
			{"nros",handle_nros,"secuencia hasta 5000"},
			{"infinito",handle_infinito,"secuencia infinita"},
			{"top",handle_top,"List of processes"},
			{"kill",handle_kill,"Kill a process"},
			{"sm1",handle_sm1,"Shared Memory 1"},
			{"sm2",handle_sm2,"Shared Memory 2"},
			{"0", NULL, ""}
			};




static 
int handle_sm1(int ppid, int pid, char * parameters)
{
    int shmId;
    char *memDir = NULL;

    if ( (shmId = shm_open("sm", 4, 0)) == -1 )
    {
        printf("sm1Error @ shm_open\n");
        return 0;
    }

    printf("shmID = %d\n", shmId);

    if ( (memDir = (char *)mmap(shmId)) == NULL )
    {
        printf("sm1: Error @ mmap\n");
        return 0;
    }

    memDir[0] = 'P';
    memDir[1] = '\0';

    shm_close(shmId);
    return 0;
}

static 
int handle_sm2(int ppid, int pid, char * parameters)
{
    int shmId;
    char *memDir = NULL;

    if ( (shmId = shm_open("sm", 1, 0)) == -1 )
    {
        printf("sm2\nError @ shm_open\n");
        return 0;
    }

    if ( (memDir = (char *)mmap(shmId)) == NULL )
    {
        printf("sm2\nError @ mmap\n");
        return 0;
    }

    printf("if P == %c\n", *memDir);

    shm_close(shmId);

    return 0;
}


/* handle del infinito*/
static 
int handle_infinito(int ppid, int pid, char * parameters)
{
	int i = 0;

	for(;;i++)
		printf("%d\n", i);

	return 0;
}

/* handle del nros */
static 
int handle_nros(int ppid, int pid, char * parameters)
{
	int i = 0;

	for(i = 0; i < 5000; i++)
		printf("%d\n", i);

	return 0;
}

/* handle del top */
static 
int handle_top(int ppid, int pid, char * parameters)
{

    printf("TOP\n");
    topApp(ppid, pid, parameters);

    return 0;
}

static int handle_kill(int ppid, int pid, char * parameters)
{
	kill(atoi(parameters),SIGKILL);
	
	return 0;	
}
/* Inicializador del shell */
int 
init_shell(int ppid, int pid, char * param)
{
	char goOut = 0, fore = 1;	
	char buffer[BUFFER_SIZE + 1], * parameters;
	int len = 0, count = 0, i = 0, found = 0, w_spaces=0;
	char history[HISTORY_SIZE][BUFFER_SIZE + 1];

	while(!goOut)
	{
		tty_set_color(SCREEN_FORE_GREEN, SCREEN_BACK_BLACK);
		// Imprime el prompt
		printf("%s>", prompt);
		tty_set_color(SCREEN_FORE_WHITE, SCREEN_BACK_BLACK);
		

		cleanBuffer(buffer, BUFFER_SIZE + 1);
		// Obtiene el comando ingresado por el teclado
		len = getCommand(buffer, BUFFER_SIZE, history, count);

		//limpio los espacios del comienzo
		w_spaces=0;
		while(buffer[w_spaces]==' ')
			w_spaces++;

		parameters = NULL;
		//obtengo los parametros
		for (i = w_spaces; i < BUFFER_SIZE && buffer[i] != '\0' && parameters == NULL; i++)
			if (buffer[i] == ' ')
			{
				parameters = buffer + i + 1;
				buffer[i] = '\0';
			}

		fore = 1;		
	
		for(i = 0; i < strlen(parameters) && fore == 1; i++)
			if (parameters[i] == '&')
				fore = 0;

		found = 0;
		i = 0;

		// Busco la funcion correspondiente al comando ingresado
		while(strcmp(commands_avaiable[i].name,"0") && !found)
		{
			if (strcmp(buffer+w_spaces, commands_avaiable[i].name) == 0)
			{
				goOut = 0;//(commands_avaiable[i].instruction)(pid, ++next_pid, parameters);
				
				if (fore == 1)
				{
					exec_wait(commands_avaiable[i].instruction, commands_avaiable[i].name, parameters);
					goOut = __wait();
				}
				else
					exec(commands_avaiable[i].instruction, commands_avaiable[i].name, parameters);
				
				//goOut = handlers[i](pid, ++next_pid, parameters);
				found = 1;
			}
			i++;
		}

		if (!found && buffer[0] != '\0')
			printf("shell: %s command not found\n", buffer);

		//Restauro el buffer si es que fue cambiado
		if (parameters != NULL)
			*(parameters-1) = ' ';

		
		if (count < HISTORY_SIZE && len>0)
		{
			// Guardo el history del ultimo comando escrito
			strcpy(history[count], buffer);
			//actualizo la posicion
			count++;
		}
	}

	return 0;
}

/* handle del help */
static 
int handle_help(int ppid, int pid, char * parameters)
{
	int i=0;
	printf("= HELP =\n");
	
	printf("Commands:\n");
	while(strcmp(commands_avaiable[i].name,"0"))
	{
		printf("\t%s\t\t%s\n", commands_avaiable[i].name, commands_avaiable[i].help);
		i++;
	}

	return 0;
}

static int handle_malloc(int ppid, int pid, char * parameters) {
	malloccer();
}	
/* handle del clear screen */
static 
int handle_clear(int ppid, int pid, char * parameters)
{
	tty_clear_scr();
	return 0;
}

/* handle del loadkeys */
static 
int handle_loadkeys(int ppid, int pid, char * parameters)
{
	if (parameters == NULL)
		printf("Keyboard layout: %s\n", (get_layout() == KEYBOARD_US)?"us":"es");
	else
	{
		if (strcmp(parameters, "us") == 0)
			set_layout(KEYBOARD_US);
		else if (strcmp(parameters, "es") == 0)
			set_layout(KEYBOARD_ES);
		else
			printf("Unknown keyboard layout. Possible layouts: us es\n");
	}

	return 0;
}

/* handle de memoria */
static 
int handle_mem(int ppid, int pid, char * parameters)
{
	showMem();
	return 0;
}

/* handle del shell */
static 
int handle_shell(int ppid, int pid, char * parameters)
{
	init_shell(ppid, pid, parameters);
	return 0;
}

/* handle del exit */
static 
int handle_exit(int ppid, int pid, char * parameters)
{
	return ppid;
}

/*handle de dividebyzero */
static int handle_div0(int ppid, int pid, char *parameters)
{
	dividebyzero();
}

/* handle del process id */
static 
int handle_pid(int ppid, int pid, char * parameters)
{
	printf("PID=%d\n", ppid);
	return 0;
}

/* Pone en \0 la cantidad dada */
static 
void cleanBuffer(char * buffer, int len)
{
	int i = 0;

	if (buffer == NULL)
		return;
		
	for (i = 0; i < len; i++)
		buffer[i] = '\0';


	return;
}

/* Parsea la entrada devuelve el comando */
static 
int getCommand(char * buffer, int length, char history[HISTORY_SIZE][BUFFER_SIZE + 1], int count)
{
	int len = 0, c = 0, donne = 0, i = 0, last = 0;
	int input = stdin;

	//el ultimo comando es la cantidad del history
	last=count;
	
	while(!donne)
	{
		if ((c = fgetc(input)) == 0)
			continue;

		if (c > 0)
		{
			// Caracteres imprimibles
			switch (c)
			{
				case '\n':	// Acepta la cadena -> comando
					donne = 1;
					buffer[len] = '\0';
					putc(c);
					break;
			
				case '\b':	// Backspace
					if (len > 0)
					{
						buffer[len] = '\0';
						len--;
						putc(c);
					}/*
					else
						beep();*/	// TODO: beep();
					break;
				case '\t':	// Autocompleta
					// TODO: Autocompleta
					break;
				default:	// demas imprimibles
					if (len < length)
					{
						buffer[len++] = c;
						putc(c);
					}/*
					else
						beep();*/	// TODO: beep();
			}
		
		
		}
		else
		{
			// Caracteres de control
			switch (c)
			{
				case UP:	// Muestra el ultimo comando
					if ((count > 0) && (last>0))
					{
						for (i = 0; i < len; i++)
							putc('\b');
						// Copio el ultimo comando al buffer
						strcpy(buffer, history[--last]);
						// Imprimo el buffer en pantalla
						for (i = 0; buffer[i] != '\0'; i++)
							putc(buffer[i]);
						len = i;
					}/*
					else
						beep();*/	// TODO: beep();
					break;
				case DOWN:	// Muestra el siguiente comando
					if ((count > 0) && (last<count-1))
					{
						// Limpio la pantalla
						for (i = 0; i < len; i++)
							putc('\b');
						// Copio el ultimo comando al buffer
						strcpy(buffer, history[++last]);
						// Imprimo el buffer en pantalla
						for (i = 0; buffer[i] != '\0'; i++)
							putc(buffer[i]);
						len = i;
					}else if ((count > 0) && (last==count-1))
					{
						//Borro la pantalla
						for (i = 0; i < len; i++)
							putc('\b');
						//Len en 0 por que no hay nada y muevo el last
						len=0;
						last++;
					}/*
					else
						beep();*/	// TODO: beep();
					break;				
			}
		}
	}
	
	return len;
}

/* handle de la configuracion del serial */
static int handle_configSerial(int ppid, int pid, char * parameters)
{
	int i = 0;

	printf("= Serial config =\n");
	
	printf("Disabling serial interrupt...\n");
	/* deshabilita la interrupcion del serial */
	setInterrupt(SERIAL_INT_E_OFF);
	
	/* Seteo la cantidad de bits a transmitir por "paquete" */
	do
		printf("Set number bit to transmit (5, 6, 7 or 8): ");
	while((i = getInt()) < 5 || i > 8);

	setBitCount(i);
	
	/* Setea la paridad */
	do
		printf("Use parity? (1 - yes | 0 - no): ");
	while((i = getInt()) != 1 && i != 0);

	if (i == 0)
	{
		// Sin paridad
		setParity(SERIAL_PARITY_OFF, SERIAL_PARITY_ODD);
	}
	else
	{
		// Con paridad -> par? impar?
		do
			printf("What parity? (1 - even | 0 - odd): ");
		while((i = getInt()) != 1 && i != 0);
	
		setParity(SERIAL_PARITY_ON, (i == 1)? SERIAL_PARITY_EVEN : SERIAL_PARITY_ODD);
	}

	/* Setea la velocidad*/
	do
	{
		printf("= Speed =\n");
		printf("\t0 -> 50 bps\n");
		printf("\t1 -> 300 bps\n");
		printf("\t2 -> 1200 bps\n");
		printf("\t3 -> 2400 bps\n");
		printf("\t4 -> 4800 bps\n");
		printf("\t5 -> 9600 bps\n");
		printf("\t6 -> 19200 bps\n");
		printf("\t7 -> 38400 bps\n");
		printf("\t8 -> 57000 bps\n");
		printf("\t9 -> 115200 bps\n");
		printf("Select speed to transmit: ");
	}
	while((i = getInt()) < 0 || i > 9);

	setbps(i);

	printf("Applying configuration...\n");
	
	/* Resetea el driver */
	doReset();

	return 0;
}

