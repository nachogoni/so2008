#ifndef PROCESSES_H_
#define PROCESSES_H_


enum {NONE, PROC_BLOQUED, PROC_SLEEP_BLOQUED, PROC_STDIN_BLOQUED, PROC_READY, PROC_EXECUTING};

unsigned int scheduler(unsigned int esp);

int createProcess(int (*fn)(int ,int ,char * ), int tty);

void sleep(int seconds);


int shell(int a,int b,char * c);
int a(int a,int b,char * c);
int b(int a,int b,char * c);
int c(int a,int b,char * c);
int d(int a,int b,char * c);

#endif /*PROCESSES_H_*/
