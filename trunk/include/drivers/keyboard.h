#ifndef _keyboard_h_
#define _keyboard_h_

#include "../../include/kernel.h"
#include "../../include/fd.h"

enum kLayoutT {KEYBOARD_US = 0, KEYBOARD_ES};

#define NOP	-01
#define	MAKE	-02
#define	CPS_LCK	-05
#define	NUM_LCK	-06
#define	SCR_LCK	-07
#define	ESC	-11
#define	L_CTRL	-12
#define	R_CTRL	-13	
#define	L_SHIFT	-14
#define	R_SHIFT	-15
#define	L_ALT	-16
#define	R_ALT	-17
#define	F01	-18
#define	F02	-19
#define	F03	-20
#define	F04	-21
#define	F05	-22
#define	F06	-23
#define	F07	-24
#define	F08	-25
#define	F09	-26
#define	F10	-27
#define	F11	-28
#define	F12	-29
#define	HOME	-30
#define	UP	-31
#define	PG_UP	-32
#define	LEFT	-33
#define	CENTER	-34
#define	RIGHT	-35
#define	END	-36
#define	DOWN	-37
#define	PG_DW	-38
#define	INSERT	-39
#define	DELETE	-40

#define K_BUFFER_SIZE 256

size_t keyboard_setChar (int b);

size_t keyboard_getChar (int * b);

size_t keyboard_writeBuffer (int b);

int set_layout(int klayout);

int get_layout(void);

int handle_keyboard(void);

int init_keyboard(void);

int close_keyboard(int fd);

#endif

