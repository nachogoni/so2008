#ifndef _tty_
#define _tty_

/* TTYs */

#include "kernel.h"

#define TTY_INITIAL_COUNT 7
#define	SCREEN_HEIGHT	25
#define	SCREEN_WIDTH	80
#define SCREEN_BLACK	0x07
#define	STDIN_WIDTH	80
#define __M_VIDEO 	0xb8000
#define TTY_TAB		8

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

#endif
