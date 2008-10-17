/*********************************************
kasm.h
************************************************/

#include "defs.h"

#ifndef _kasm_
#define _kasm_

unsigned int read_msw();

void _lidt (IDTR *idtr);

void int_08_hand();      /* Timer tick */
void int_09_hand();      /* Keyboard */
void int_0c_hand();      /* Keyboard */
void int_80_hand();      /* Keyboard */

/* Functions */
void _Cli(void);		/* Deshabilita interrupciones  */
void _Sti(void);		/* Habilita interrupciones  */
void task_switch(void);
void set_cursor_pos(unsigned int);
void beep(void);
void mascaraPIC1 (byte mascara);  /* Escribe mascara de PIC1 */
void mascaraPIC2 (byte mascara);  /* Escribe mascara de PIC2 */
// Genera un stackFrame para que nuevos procesos puedan ser agregados al scheduler
int createStackFrame(int (*fn)(int ,int ,char *), void * dire, int ppid, int pid, char *parametros, void * ret);

/* System Calls*/
unsigned int read(int fd, void * buf, unsigned int count);
unsigned int write(int fd, const void * buf, unsigned int count);

unsigned int exec(int (*fn)(int ,int ,char *), char * process_name, char * parameters);
unsigned int exec_wait(int (*fn)(int ,int ,char *), char * process_name, char * parameters);

int shm_open(key_t key, size_t size, int flags);
int shm_close(int shmid);
void * mmap(int shmid);

int read_cr0(void);
void write_cr0 (int);
void write_cr3 (unsigned long **);
unsigned long * read_cr3(void);

#endif
