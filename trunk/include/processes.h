#ifndef PROCESSES_H_
#define PROCESSES_H_

typedef enum {NONE, PROC_CHILD_BLOQUED, PROC_SEM_BLOQUED, PROC_SLEEP_BLOQUED, PROC_STDIN_BLOQUED, PROC_READY, PROC_EXECUTING} procStatusT;

int createProcess(int (*fn)(int, int, char *), char * name, char * parameters, int tty, void (*ret_fn)(void));

void kernel_return_Function_no_unblock(void);

void kernel_return_Function_unblock(void);

int _kill(int pid, int signal);

void sleep(int seconds);

void createIdle(void);

void block_process(procStatusT block_type);

void unblock_process(unsigned int pid);

unsigned int getpid(void);

unsigned int getppid(void);

unsigned int getNextPID(void);

int getProcessTTY(void);

int getResponse(void);

int killCurrent(void);

int shell(int a,int b,char * c);
int a(int a,int b,char * c);
int b(int a,int b,char * c);
int c(int a,int b,char * c);
int d(int a,int b,char * c);

#endif /*PROCESSES_H_*/
