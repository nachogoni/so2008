#include "kasm.h"
#include "kernel.h"
#include "tty.h"
#include "scheduler.h"
#include "strings.h"
#include "memory.h"
#include "pagination.h"
#include "processes.h"
#include "shell.h"

int last_pid = INIT_PID;

process_t process_vector[MAX_PROCESS_COUNT];
unsigned int process_running = 0;
unsigned int process_count = 1;

int shell(int a,int b,char * c)
{
	init_shell(process_vector[process_count].ppid, process_vector[process_count].pid,"");
	return 1;
}

int createProcess(int (*fn)(int ,int ,char *), char * name, int tty)
{
	if (process_count>=MAX_PROCESS_COUNT || name == NULL)
		return -1;
	
	process_vector[process_count].tty_id = tty;
	
	strcpy(process_vector[process_count].name, name);

	process_vector[process_count].pid = ++last_pid;
	process_vector[process_count].ppid = INIT_PID;
	
	process_vector[process_count].stack_address = get_free_page() + 0x0FFF;
	process_vector[process_count].heap_address = get_free_page();
	
	/* Inicializa la memoria del proceso*/
	__init_memory(process_vector[process_count].heap_address, SIZE_PER_PAGE);

	process_vector[process_count].esp = createStackFrame(fn, process_vector[process_count].stack_address, 1, 1, "matias");
	process_vector[process_count].status = PROC_READY;
	process_vector[process_count].priority = DEFAULT_PRIORITY;
	
	return process_count++;
}

void createIdle(void)
{
	process_vector[0].tty_id = 0;
	strcpy(process_vector[0].name, "idle");
	process_vector[0].pid = INIT_PID;
	process_vector[0].ppid = INIT_PID;
	process_vector[0].status = PROC_READY;
	process_vector[0].priority = DEFAULT_PRIORITY;
	
	return;
}

void block_process(procStatusT block_type)
{
	process_vector[process_running].status = block_type;
	task_switch();
	return;	
}

void unblock_process(unsigned int pid)
{
	int i = 0, found = 0;
	
	for (i = 0; i < process_count && !found; i++)
	{
		if (process_vector[i].pid == pid)
		{
			process_vector[i].status = PROC_READY;
			found = 1;
		}
	}
	
	return;	
}

unsigned int getpid(void)
{
	return process_vector[process_running].pid;
}

unsigned int getppid(void)
{
	return process_vector[process_running].ppid;
}

void sleep(int seconds)
{
	process_vector[process_running].sleep = seconds * 18;
	block_process(PROC_SLEEP_BLOQUED);
	return;	
}









int a(int a,int b,char * c)
{
	sleep(1);
	while(1)
	{
		sleep(2);
		tty_set_color(SCREEN_FORE_YELLOW, SCREEN_BACK_BLACK);
		printf("ppid :%d\n",a);
		printf("pid :%d\n",a);
		printf("parametros :%s\n",a);
		tty_set_color(SCREEN_FORE_WHITE, SCREEN_BACK_BLACK);
	}
	return 1;
}
int b(int a,int b,char * c)
{
	sleep(2);
	while(1)
	{
		sleep(1);
		tty_set_color(SCREEN_FORE_VIOLET, SCREEN_BACK_BLACK);
		printf("ppid :%d\n",a);
		printf("pid :%d\n",a);
		printf("parametros :%s\n",a);
		tty_set_color(SCREEN_FORE_WHITE, SCREEN_BACK_BLACK);
	}
	return 1;
}
int c(int a,int b,char * c)
{
	sleep(2);
	while(1)
	{
		sleep(1);
		tty_set_color(SCREEN_FORE_RED, SCREEN_BACK_BLACK);
		printf("ppid :%d\n",a);
		printf("pid :%d\n",a);
		printf("parametros :%s\n",a);
		tty_set_color(SCREEN_FORE_WHITE, SCREEN_BACK_BLACK);
	}
	return 1;
}

int d(int a,int b,char * c)
{
	sleep(10);
	while(1)
	{
		sleep(20);
		tty_set_color(SCREEN_FORE_WHITE2, SCREEN_BACK_BLACK);
		printf("ppid :%d\n",a);
		printf("pid :%d\n",a);
		printf("parametros :%s\n",a);
		tty_set_color(SCREEN_FORE_WHITE, SCREEN_BACK_BLACK);
	}
	return 1;
}
