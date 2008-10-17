#include "processes.h"
#include "io.h"
#include "tty.h"
#include "kernel.h"
#include "kasm.h"

int a(int a,int b,char * c)
{
	sleep(1);
	while(1)
	{
		sleep(2);
		tty_set_color(SCREEN_FORE_YELLOW, SCREEN_BACK_BLACK);
		printf("a");
		tty_set_color(SCREEN_FORE_WHITE, SCREEN_BACK_BLACK);
	}
	return 0;
}
int b(int a,int b,char * c)
{
	sleep(5);
	while(1)
	{

		sleep(1);
		tty_set_color(SCREEN_FORE_VIOLET, SCREEN_BACK_BLACK);
		printf("b");
		tty_set_color(SCREEN_FORE_WHITE, SCREEN_BACK_BLACK);
	}
	return 0;
}
int c(int a,int b,char * c)
{
	sleep(1);
	while(1)
	{
		sleep(1);
		tty_set_color(SCREEN_FORE_RED, SCREEN_BACK_BLACK);
		printf("c");
		tty_set_color(SCREEN_FORE_WHITE, SCREEN_BACK_BLACK);
	}
	return 0;
}

int d(int a,int b,char * c)
{
	sleep(10);
	while(1)
	{
		sleep(20);
		tty_set_color(SCREEN_FORE_WHITE2, SCREEN_BACK_BLACK);
		printf("d");
		tty_set_color(SCREEN_FORE_WHITE, SCREEN_BACK_BLACK);
	}
	return 0;
}

/* Inicia el chat */
int duplicate(int ppid, int pid, char * parameters)
{
	exec(a, "duplicate_a", "");
	exec(b, "duplicate_b", "");
	exec(c, "duplicate_c", "");
	exec_wait(d, "duplicate_d", "");
	return 0;
}
