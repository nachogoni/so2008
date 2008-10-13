#ifndef PROCESSES_H_
#define PROCESSES_H_

unsigned int scheduler(unsigned int esp);

int shell(int a,int b,char * c);

int createProcess(int (*fn)(int ,int ,char * ), int tty);

#endif /*PROCESSES_H_*/
