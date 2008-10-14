#ifndef _tty_
#define _tty_

/* TTYs */

#include "kernel.h"

#define TTY_INITIAL_COUNT 7
#define	SCREEN_HEIGHT	25
#define	SCREEN_WIDTH	80
#define SCREEN_NORMAL	0x07
#define	STDIN_WIDTH	80
#define __M_VIDEO 	0xb8000
#define TTY_TAB		8

#define SCREEN_FORE_BLACK		0x00
#define SCREEN_FORE_BLUE		0x01
#define SCREEN_FORE_GREEN		0x02
#define SCREEN_FORE_CYAN		0x03
#define SCREEN_FORE_RED			0x04
#define SCREEN_FORE_MAGENTA		0x05
#define SCREEN_FORE_ORANGE		0x06
#define SCREEN_FORE_WHITE		0x07
#define SCREEN_FORE_GRAY		0x08
#define SCREEN_FORE_VIOLET		0x09
#define SCREEN_FORE_GREEN2		0x0A
#define SCREEN_FORE_CYAN2		0x0B
#define SCREEN_FORE_RED2		0x0C
#define SCREEN_FORE_MAGENTA2	0x0D
#define SCREEN_FORE_YELLOW		0x0E
#define SCREEN_FORE_WHITE2		0x0F
#define SCREEN_BACK_BLACK		0x00
#define SCREEN_BACK_BLUE		0x10
#define SCREEN_BACK_GREEN		0x20
#define SCREEN_BACK_CYAN		0x30
#define SCREEN_BACK_RED			0x40
#define SCREEN_BACK_MAGENTA		0x50
#define SCREEN_BACK_ORANGE		0x60
#define SCREEN_BACK_WHITE		0x70
#define SCREEN_BACK_GRAY		0x80
#define SCREEN_BACK_VIOLET		0x90
#define SCREEN_BACK_GREEN2		0xA0
#define SCREEN_BACK_CYAN2		0xB0
#define SCREEN_BACK_RED2		0xC0
#define SCREEN_BACK_MAGENTA2	0xD0
#define SCREEN_BACK_YELLOW		0xE0
#define SCREEN_BACK_WHITE2		0xF0

typedef enum {TTY_OK = 0, TTY_ERROR = -1, TTY_BAD_PARAMETERS = -2, TTY_MAX_TTYS_REACHED = -3, TTY_INVALID_ID = -4} tty_resp_t;

/* KERNEL FUNCTIONS */

/* Init a new tty
*
*	buffer_length	length of the video buffer, at least 24 rows
*	tty_switch	callback function of the kernel to switch to another tty
*
*	returns id of the new tty or a negative error code
*/
int tty_init();

/* Destroy an existing tty
*
*	returns TTY_OK if the existing tty was destroyed or a negative error code
*/
tty_resp_t tty_destroy();

/* Sets an existing tty to active and other to background
*
*	returns TTY_OK or a negative error code
*/
tty_resp_t tty_set_active(unsigned int tty_id_new);

/* Sets to witch tty will be write
*
*	returns TTY_OK or a negative error code
*/
tty_resp_t tty_set_actual(unsigned int tty_id_new);

/* Writes a new byte into the stdin buffer for an existing tty
*
*	returns the number of written bytes or a negative error code
*/
size_t tty_writeBuffer(int b);

/* Writes a new byte into an existing tty
*
*	returns the number of written bytes or a negative error code
*/
size_t tty_setByte (int b);

/* Reads a byte from an existing tty
*
*	returns the number of read bytes or a negative error code
*/
size_t tty_getByte(int * b);

/* USER FUNCTIONS */

tty_resp_t tty_clear_scr();

tty_resp_t tty_flush();

tty_resp_t tty_set_position(int x, int y);

tty_resp_t tty_get_position(int * x, int * y);

tty_resp_t tty_set_color(int foreground, int background);

#endif
