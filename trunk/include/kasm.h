/*********************************************
kasm.h
************************************************/

#include "defs.h"

#ifndef _kasm_
#define _kasm_

unsigned int    read_msw();

void            _lidt (IDTR *idtr);

void		mascaraPIC1 (byte mascara);  /* Escribe mascara de PIC1 */
void		mascaraPIC2 (byte mascara);  /* Escribe mascara de PIC2 */

void		Cli(void);        /* Deshabilita interrupciones  */
void		Sti(void);	 /* Habilita interrupciones  */

void		_Cli(void);        /* Deshabilita interrupciones  */
void		_Sti(void);	 /* Habilita interrupciones  */
void 		beep(void);
void 		task_switch(void);
void		int_08_hand();      /* Timer tick */
void		int_09_hand();      /* Keyboard */
void		int_0c_hand();      /* Keyboard */
void		int_80_hand();      /* Keyboard */

unsigned int read(int fd, void * buf, unsigned int count);
unsigned int write(int fd, const void * buf, unsigned int count);

void		set_cursor_pos(unsigned int);

unsigned int	fork(void);

void		debug (void);

// Genera un stackFrame para que nuevos procesos puedan ser agregados al scheduler
int createStackFrame(int (*fn)(int ,int ,char *), void * dire);

int		read_cr0();
void 		write_cr0(int);
unsigned long*	read_cr3();
void 		write_cr3(unsigned long **);

#endif

