/* TTYs */

// #include "stdio.h"

#include "tty.h"
#include "kasm.h"
#include "keyboard.h"
#include "memory.h"
#include "kernel.h"
#include "processes.h"

#define TTY_ACTIVE	0
#define TTY_BACKGROUND	TTY_ACTIVE + 1

#define TTY_FREE	0
#define TTY_IN_USE	TTY_FREE + 1

#define TTY_EMPTY		0
#define TTY_NOT_EMPTY	TTY_EMPTY + 1

typedef struct tty_t
{
	int tty_color;	// foreground and background color
	int using;		// sets if the current tty_id is been used
	int active;		// TTY_ACTIVE or TTY_BACKGROUND
	int stdout_length;	// length of the buffer
	int stdout_first;		// pointer to the first screen position
	int stdout_height;		// screen height
	int stdout_width;		// screen width
	int stdout_cursor;	// position of the cursor
//	char * stdout;		// stdout buffer (screen)
	char stdout[SCREEN_HEIGHT * 3 * SCREEN_WIDTH * 2];	// stdout buffer (screen)
	int stdin_read;		// position in stdin to be read
	int stdin_write;	// where to write a new input
	int stdin_empty;	// if stdin is empty
//	int * stdin;		// stdin buffer (keyboard)
	unsigned int stdin_blocked_proc;		// pid of the process blocked at stdin
	int stdin[STDIN_WIDTH];	// stdin buffer (keyboard)
} tty_t;

tty_t tty_vector[TTY_INITIAL_COUNT];	// vector where the ttys are
int tty_count = TTY_INITIAL_COUNT;	// count of ttys in the vector
int tty_id = 0;				// sets the actual tty where to write
int tty_fore_id = 0;				// sets the foregorund tty

char * video_address = (char *) __M_VIDEO;

/* STATIC FUNCTIONS */

static int new_tty(int buffer_length)
{
	int tty_id_new = TTY_ERROR;
	int i = 0;

	if (buffer_length < SCREEN_HEIGHT)
		buffer_length = SCREEN_HEIGHT;

	// Searchs for the firts free tty id
	for (i = 0; i < tty_count && tty_vector[i].using == TTY_IN_USE; i++);

	if (tty_vector[i].using == TTY_IN_USE)
		return TTY_MAX_TTYS_REACHED;
	
	// Sets the actual id
	tty_id_new = i;

	// Sets the parameters to the new tty
	tty_vector[tty_id_new].active = TTY_BACKGROUND;
//	tty_vector[tty_id_new].stdout_length = buffer_length;
	tty_vector[tty_id_new].stdout_length = SCREEN_WIDTH * SCREEN_HEIGHT * 2 * 3;
	tty_vector[tty_id_new].stdout_height = SCREEN_HEIGHT;
	tty_vector[tty_id_new].stdout_width = SCREEN_WIDTH;
	tty_vector[tty_id_new].stdout_first = 0;
	tty_vector[tty_id_new].stdout_cursor = 0;
	tty_vector[tty_id_new].stdin_read = 0;
	tty_vector[tty_id_new].stdin_write = 0;
	tty_vector[tty_id_new].stdin_empty = TTY_EMPTY;
	tty_vector[tty_id_new].tty_color = SCREEN_FORE_WHITE | SCREEN_BACK_BLACK;
	tty_vector[tty_id_new].stdin_blocked_proc = 0;

	/* malloc of the tty stdout buffer */
//	tty_vector[tty_id_new].stdout = malloc(tty_vector[tty_id_new].stdout_length * tty_vector[tty_id_new].stdout_width * 2 * sizeof(char));

	/* malloc of the tty stdin buffer */
//	tty_vector[tty_id_new].stdin = malloc(STDIN_WIDTH * sizeof(int));

	tty_vector[tty_id_new].using = TTY_IN_USE;
	
	return tty_id_new;
}

/* KERNEL FUNCTIONS */

int tty_init()
{
	int tty_id = TTY_ERROR, i = 0;
	
	for (i = 0; i < TTY_INITIAL_COUNT; i++)
		tty_id = new_tty(SCREEN_HEIGHT * 4);

	tty_set_active(0);

	return tty_id;
}

tty_resp_t tty_destroy()
{
	if (tty_id >= tty_count || tty_vector[tty_id].using != TTY_IN_USE)
		return TTY_INVALID_ID;

	/* buffers frees */
//	free(tty_vector[tty_id].stdout);
//	free(tty_vector[tty_id].stdin);

	/* seting as free the tty_id */
	tty_vector[tty_id].using = TTY_FREE;

	return TTY_OK;
}

tty_resp_t tty_set_active(unsigned int tty_id_new)
{
	int i = 0;
	
	if (tty_id_new >= tty_count || tty_vector[tty_id_new].using != TTY_IN_USE)
		return TTY_INVALID_ID;

	// Sets all other ttys to BACKGROUND
	for (i = 0; i < tty_count; i++)
		tty_vector[i].active = TTY_BACKGROUND;

	tty_vector[tty_id_new].active = TTY_ACTIVE;

	tty_fore_id = tty_id_new;

	tty_set_actual(tty_id_new);

	return TTY_OK;
}

tty_resp_t tty_set_actual(unsigned int tty_id_new)
{
	if (tty_id_new >= tty_count || tty_vector[tty_id_new].using != TTY_IN_USE)
		return TTY_INVALID_ID;

	tty_id = tty_id_new;

	return TTY_OK;
}

size_t tty_writeBuffer(int b)
{
	if (tty_fore_id >= tty_count || tty_vector[tty_fore_id].using != TTY_IN_USE)
		return TTY_INVALID_ID;

	if ((tty_vector[tty_fore_id].stdin_empty != TTY_EMPTY) && (tty_vector[tty_fore_id].stdin_read == tty_vector[tty_fore_id].stdin_write))
	{
		beep();
		return 0;
	}

	// Change actual tty
	if (b >= F07 && b <= F01)
	{
		if (tty_fore_id >= tty_count || tty_vector[tty_fore_id].using != TTY_IN_USE)
			return 1;

		tty_set_active((TTY_INITIAL_COUNT - 1)-(b - F07));
		tty_flush();

		return 1;
	}
	
	if (b == PG_UP)
	{
		tty_vector[tty_fore_id].stdout_first -= tty_vector[tty_fore_id].stdout_width * 2;
		// to the first column
		tty_vector[tty_fore_id].stdout_first -= (tty_vector[tty_fore_id].stdout_first % (tty_vector[tty_fore_id].stdout_width * 2));
		// Not negative cursor
		if (tty_vector[tty_fore_id].stdout_first < 0)
			tty_vector[tty_fore_id].stdout_first = tty_vector[tty_fore_id].stdout_length - tty_vector[tty_fore_id].stdout_width * 2;
		tty_flush();
		return 1;
	}

	if (b == PG_DW)
	{
		tty_vector[tty_fore_id].stdout_first += tty_vector[tty_fore_id].stdout_width * 2;
		// to the first column
		tty_vector[tty_fore_id].stdout_first -= (tty_vector[tty_fore_id].stdout_first % (tty_vector[tty_fore_id].stdout_width * 2));
		tty_vector[tty_fore_id].stdout_first %= tty_vector[tty_fore_id].stdout_length;
		tty_flush();
		return 1;
	}
	
	tty_vector[tty_fore_id].stdin[tty_vector[tty_fore_id].stdin_write] = b;

	tty_vector[tty_fore_id].stdin_write = (tty_vector[tty_fore_id].stdin_write + 1) % STDIN_WIDTH;

	tty_vector[tty_fore_id].stdin_empty = TTY_NOT_EMPTY;
	
	if (tty_vector[tty_fore_id].stdin_blocked_proc != 0)
	{
		unblock_process(tty_vector[tty_fore_id].stdin_blocked_proc);
	}		
	
	return 1;
}

/* USER FUNCTIONS */

size_t tty_setByte (int b)
{
	int screen_size = 0, i = 0, len = 0;
	int tty_id_actual = tty_id;

	if (tty_id_actual >= tty_count || tty_vector[tty_id_actual].using != TTY_IN_USE)
		return TTY_INVALID_ID;
	
	switch(b)
	{
		case '\n':
			// new line
			tty_vector[tty_id_actual].stdout_cursor += tty_vector[tty_id_actual].stdout_width * 2;
			// to the first column
			tty_vector[tty_id_actual].stdout_cursor -= (tty_vector[tty_id_actual].stdout_cursor % (tty_vector[tty_id_actual].stdout_width * 2));
			break;
		case '\t':
			// new tab
			tty_vector[tty_id_actual].stdout_cursor += TTY_TAB * 2;
			tty_vector[tty_id_actual].stdout_cursor -= tty_vector[tty_id_actual].stdout_cursor % (TTY_TAB * 2);
			break;
		case '\r':
			// carry return
			tty_vector[tty_id_actual].stdout_cursor -= tty_vector[tty_id_actual].stdout_width * 2;
			// to the first column
			tty_vector[tty_id_actual].stdout_cursor -= (tty_vector[tty_id_actual].stdout_cursor % (tty_vector[tty_id_actual].stdout_width * 2));
			// Not negative cursor
			if (tty_vector[tty_id_actual].stdout_cursor < 0)
				tty_vector[tty_id_actual].stdout_cursor = 0;
			break;
		case '\b':
			// backspace
			tty_vector[tty_id_actual].stdout_cursor -= 2;
			// Not negative cursor
			if (tty_vector[tty_id_actual].stdout_cursor < 0)
				tty_vector[tty_id_actual].stdout_cursor = 0;
			// write a blank
			tty_vector[tty_id_actual].stdout[tty_vector[tty_id_actual].stdout_cursor] = ' ';
			tty_vector[tty_id_actual].stdout[tty_vector[tty_id_actual].stdout_cursor + 1] = tty_vector[tty_id_actual].tty_color;
			break;
		default:
			// Sets the char into the buffer
			tty_vector[tty_id_actual].stdout[tty_vector[tty_id_actual].stdout_cursor] = (unsigned char)b;
			// Sets char format
			tty_vector[tty_id_actual].stdout[tty_vector[tty_id_actual].stdout_cursor + 1] = tty_vector[tty_id_actual].tty_color;
			// Increments to the next position into the buffer
			tty_vector[tty_id_actual].stdout_cursor += 2;
			break;
	}

	// Cursor must be into the screen	
	screen_size = (tty_vector[tty_id_actual].stdout_width * tty_vector[tty_id_actual].stdout_height * 2);
	
	// distance from first to cursor into the buffer
	if (tty_vector[tty_id_actual].stdout_cursor < tty_vector[tty_id_actual].stdout_first)
		len = tty_vector[tty_id_actual].stdout_cursor + (tty_vector[tty_id_actual].stdout_length - tty_vector[tty_id_actual].stdout_first);
	else
		len = tty_vector[tty_id_actual].stdout_cursor - tty_vector[tty_id_actual].stdout_first;
	
	len %= tty_vector[tty_id_actual].stdout_length;
	
	// what if the cursor left the screen? -> increments the firts line to show
	if (len >= screen_size)
		tty_vector[tty_id_actual].stdout_first += tty_vector[tty_id_actual].stdout_width * 2;

	// first must fit into the buffer
	tty_vector[tty_id_actual].stdout_cursor %= tty_vector[tty_id_actual].stdout_length;
	
	// first must fit into the buffer
	tty_vector[tty_id_actual].stdout_first %= tty_vector[tty_id_actual].stdout_length;
	
	if (b == '\n')
	{
		for (i = 0; i < tty_vector[tty_id_actual].stdout_width * 2; i += 2)
		{
			tty_vector[tty_id_actual].stdout[tty_vector[tty_id_actual].stdout_cursor + i + 1] = tty_vector[tty_id_actual].tty_color;
			tty_vector[tty_id_actual].stdout[tty_vector[tty_id_actual].stdout_cursor + i] = ' ';
		}
	}

	return 1;
}

size_t tty_getByte(int * b)
{
	if (tty_id >= tty_count || tty_vector[tty_id].using != TTY_IN_USE)
		return TTY_INVALID_ID;

	if (b == NULL)
		return TTY_BAD_PARAMETERS;
	
	if ((tty_vector[tty_id].stdin_empty == TTY_EMPTY) && (tty_vector[tty_id].stdin_read == tty_vector[tty_id].stdin_write))
	{
		// TODO: now we are blocked in stdin
		// TODO: sleep(-1);
		// return 0;


//_Sti();
//		while (tty_vector[tty_id].stdin_empty == TTY_EMPTY); //TODO:
		
		tty_vector[tty_id].stdin_blocked_proc = getpid();
		block_process(PROC_STDIN_BLOQUED);
		tty_vector[tty_id].stdin_blocked_proc = 0;
	}
	
	*b = (int)tty_vector[tty_id].stdin[tty_vector[tty_id].stdin_read];

	tty_vector[tty_id].stdin_read = (tty_vector[tty_id].stdin_read + 1) % STDIN_WIDTH;

	if (tty_vector[tty_id].stdin_read == tty_vector[tty_id].stdin_write)
		tty_vector[tty_id].stdin_empty = TTY_EMPTY;
	
	return 1;
}

tty_resp_t tty_clear_scr()
{
	int from = 0, to = 0, i = 0, screen_size = 0;
	
	if (tty_id >= tty_count || tty_vector[tty_id].using != TTY_IN_USE)
		return TTY_INVALID_ID;
	
	screen_size = (tty_vector[tty_id].stdout_width * tty_vector[tty_id].stdout_height * 2);
	
	// puts the cursor line at the top of the screen
	tty_vector[tty_id].stdout_first = tty_vector[tty_id].stdout_cursor;

	// Clears the new screen
	from = tty_vector[tty_id].stdout_first;
	to = (tty_vector[tty_id].stdout_first + tty_vector[tty_id].stdout_width * tty_vector[tty_id].stdout_height * 2) % tty_vector[tty_id].stdout_length;
	
	if (from > to)
	{
		// Clears the first part of the screen
		for (i = from; i < tty_vector[tty_id].stdout_length; i += 2)
		{
			tty_vector[tty_id].stdout[i + 1] = tty_vector[tty_id].tty_color;
			tty_vector[tty_id].stdout[i] = ' ';
		}
		
		// the last part of the screen
		for (i = 0; i < to; i += 2)
		{
			tty_vector[tty_id].stdout[i + 1] = tty_vector[tty_id].tty_color;
			tty_vector[tty_id].stdout[i] = ' ';
		}
	}
	else
	{
		// Clears the first part of the screen
		for (i = from; i < to; i += 2)
		{
			tty_vector[tty_id].stdout[i + 1] = tty_vector[tty_id].tty_color;
			tty_vector[tty_id].stdout[i] = ' ';
		}
	}

	if (tty_vector[tty_id].active == TTY_ACTIVE)
		tty_flush();
	
	return TTY_OK;
}

tty_resp_t tty_flush()
{
	int from = 0, to = 0, len = 0;
	
	if (tty_id >= tty_count || tty_vector[tty_id].using != TTY_IN_USE)
		return TTY_INVALID_ID;

	if (tty_vector[tty_id].active != TTY_ACTIVE)
		return TTY_INVALID_ID;
	
	from = tty_vector[tty_id].stdout_first;
	to = (tty_vector[tty_id].stdout_first + tty_vector[tty_id].stdout_width * tty_vector[tty_id].stdout_height * 2) % tty_vector[tty_id].stdout_length;
	
	if (from > to)
	{
		len = tty_vector[tty_id].stdout_length - from;
		
		// Copy the first part of the buffer into the video memory
		memcpy((void *)video_address, tty_vector[tty_id].stdout + from, len * sizeof(char));
		
		// Copy the last part of the buffer into the video memory
		memcpy((void *)video_address + len, tty_vector[tty_id].stdout, to * sizeof(char));
	}
	else
	{
		len = to - from;
		
		// Copy the buffer into the video memory
		memcpy((void *)video_address, tty_vector[tty_id].stdout + from, len * sizeof(char));
	}
	
	// distance from first to cursor into the buffer
	if (tty_vector[tty_id].stdout_cursor < tty_vector[tty_id].stdout_first)
		len = tty_vector[tty_id].stdout_cursor + (tty_vector[tty_id].stdout_length - tty_vector[tty_id].stdout_first);
	else
		len = tty_vector[tty_id].stdout_cursor - tty_vector[tty_id].stdout_first;
	
	len %= tty_vector[tty_id].stdout_length;
	
	set_cursor_pos(len/2);
	
	return TTY_OK;
}

tty_resp_t tty_set_position(int x, int y)
{
	if (tty_id >= tty_count || tty_vector[tty_id].using != TTY_IN_USE)
		return TTY_INVALID_ID;

	if (x > tty_vector[tty_id].stdout_width || y > tty_vector[tty_id].stdout_height)
		return TTY_BAD_PARAMETERS;

	// Sets the current stdout cursor
	tty_vector[tty_id].stdout_cursor = tty_vector[tty_id].stdout_first + (x + tty_vector[tty_id].stdout_width * y) * 2;

	tty_vector[tty_id].stdout_cursor %= tty_vector[tty_id].stdout_length;

	return TTY_OK;
}

tty_resp_t tty_get_position(int * x, int * y)
{
	if (tty_id >= tty_count || tty_vector[tty_id].using != TTY_IN_USE)
		return TTY_INVALID_ID;

	if (y == NULL || x == NULL)
		return TTY_BAD_PARAMETERS;
	//TODO: CHECK!
	*y = (int)(tty_vector[tty_id].stdout_cursor / (2 * tty_vector[tty_id].stdout_width));

	*x = ((int)(tty_vector[tty_id].stdout_cursor / (2 * tty_vector[tty_id].stdout_width))) % tty_vector[tty_id].stdout_width;

	return TTY_OK;
}

tty_resp_t tty_set_color(int foreground, int background)
{
	if (foreground > 0x0F || background > 0xF0)
		return TTY_BAD_PARAMETERS;
	
	tty_vector[tty_id].tty_color = (0x0F & foreground) | (0xF0 & background);
	
	return TTY_OK;
}
