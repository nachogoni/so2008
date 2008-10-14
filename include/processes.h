#ifndef PROCESSES_H_
#define PROCESSES_H_


typedef enum {NONE, PROC_BLOQUED, PROC_SLEEP_BLOQUED, PROC_STDIN_BLOQUED, PROC_READY, PROC_EXECUTING} procStatusT;

int createProcess(int (*fn)(int ,int ,char * ), char * name, int tty);

void sleep(int seconds);

void block_process(procStatusT block_type);
void unblock_process(unsigned int pid);

unsigned int getpid(void);
unsigned int getppid(void);

int shell(int a,int b,char * c);
int a(int a,int b,char * c);
int b(int a,int b,char * c);
int c(int a,int b,char * c);
int d(int a,int b,char * c);

#endif /*PROCESSES_H_*/
