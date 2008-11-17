#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>

#define		FAILED		0
#define		OK		FAILED + 1

#define		X_RESN		525
#define		Y_RESN		280
#define		LED_WIDTH	25
#define		LED_HEIGHT	25
#define		LED_X_DIF	30
#define		LED_Y_DIF	30

#define		WIDTH		16
#define		HEIGHT		8

#define		RED		255*255*255
#define		GREEN		255*255
#define		BLUE		255

int matrix[HEIGHT][WIDTH] = {
	{RED,	GREEN,	RED,	RED,	BLUE,	RED,	RED,	RED,	BLUE,	RED,	GREEN,	BLUE,	RED,	GREEN,	RED,	GREEN},
	{GREEN,	RED,	GREEN,	RED,	RED,	BLUE,	RED,	BLUE,	RED,	BLUE,	RED,	RED,	GREEN,	RED,	GREEN,	RED},
	{RED,	GREEN,	RED,	GREEN,	RED,	RED,	BLUE,	RED,	RED,	RED,	BLUE,	GREEN,	RED,	GREEN,	RED,	GREEN},
	{BLUE,	RED,	GREEN,	RED,	GREEN,	BLUE,	RED,	BLUE,	RED,	BLUE,	GREEN,	BLUE,	GREEN,	RED,	RED,	BLUE},
	{RED,	BLUE,	RED,	GREEN,	RED,	GREEN,	RED,	RED,	BLUE,	GREEN,	RED,	GREEN,	BLUE,	RED,	BLUE,	RED},
	{BLUE,	RED,	BLUE,	RED,	GREEN,	RED,	GREEN,	RED,	GREEN,	RED,	GREEN,	RED,	GREEN,	BLUE,	RED,	BLUE},
	{RED,	BLUE,	RED,	BLUE,	RED,	GREEN,	RED,	GREEN,	RED,	GREEN,	RED,	RED,	RED,	RED,	BLUE,	GREEN},
	{GREEN,	RED,	BLUE,	RED,	BLUE,	RED,	GREEN,	RED,	GREEN,	RED,	RED,	BLUE,	RED,	BLUE,	RED,	BLUE}
	};

Window win;
Display * display;
GC gc;

/* Serial functions */

/* http://www.easysw.com/~mike/serial/serial.html */

int open_port(char * port, int baudrate)
{
	int fd;
	struct termios options;

	if (port == NULL)
		return -1;

	fd = open(port, O_RDWR | O_NOCTTY | O_NDELAY);
	if (fd == -1)
	{
		printf("Unable to open serial port %s\n", port);
		return -1;
	}
	else
		fcntl(fd, F_SETFL, 0);


	tcgetattr(fd, &options);

	cfsetispeed(&options, baudrate);
	cfsetospeed(&options, baudrate);
	// Character size
	options.c_cflag &= ~CSIZE;
	options.c_cflag |= CS8;
	// 8N1
	options.c_cflag &= ~PARENB;
	options.c_cflag &= ~CSTOPB;
	options.c_cflag &= ~CSIZE;
	options.c_cflag |= CS8;
	// Disable hardware control flow
	options.c_cflag &= ~CRTSCTS;
	// Raw input
	options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

	options.c_cflag |= (CLOCAL | CREAD);

	tcsetattr(fd, TCSANOW, &options);

	return fd;
}

void close_port(int fd)
{
	if (fd >= 0)
		close(fd);

	return;
}

/* X11 funtions */

/* http://tronche.com/gui/x/xlib/ */

double randReal(double max)
{
	return (rand() / ( (double) RAND_MAX + 1)) * max;
}

void randomize(void)
{
	srand ( (int) time(NULL));
}

void regenerate(void)
{
	int i = 0, j = 0;

	randomize();

        // draw the led matrix
	for(i = 0; i < HEIGHT; i++) 
	{
        	for(j = 0; j < WIDTH; j++)
		{
			matrix[i][j] = randReal(255)*randReal(255)*randReal(255);
	        }
	}

	return;
}

void resize(void)
{
	XResizeWindow(display, win, X_RESN, Y_RESN);
	return;
}

void redraw(void)
{
	int i = 0, j = 0, c = 0;

	randomize();

        // draw the led matrix
	for(i = 0; i < HEIGHT; i++) 
	{
        	for(j = 0; j < WIDTH; j++)
		{
			XSetForeground(display, gc, matrix[i][j]);
			XFillArc(display, win, gc, j * LED_X_DIF + LED_WIDTH, i * LED_Y_DIF + LED_HEIGHT, LED_WIDTH, LED_HEIGHT, 0 * 64, 360 * 64);
	        }
	}

	return;
}

int createWindow(void)
{
	char * window_name = "RGB Matrix Emulator", * display_name = NULL;
	unsigned int width = 0, height = 0, x = 0, y = 0, border_width = 0, display_width = 0, display_height = 0, screen = 0;
	unsigned  long valuemask = 0;
	XGCValues values;
	XSizeHints size_hints;
	Pixmap bitmap;
	XPoint points[X_RESN];
	FILE * fp, * fopen();
	char str[100];

	XSetWindowAttributes attr[1];

	// connect to Xserver
	if ((display = XOpenDisplay(display_name)) == NULL )
	{
		fprintf (stderr, "drawon: cannot connect to X server %s\n", XDisplayName (display_name) );
		return FAILED;
	}

	// get screen size
	screen = DefaultScreen(display);
	display_width = DisplayWidth(display, screen);
	display_height = DisplayHeight(display, screen);

	// set window size
	width = X_RESN;
	height = Y_RESN;

	// set window position
	x = 0;
	y = 0;

        // create opaque window
	border_width = 4;
	win = XCreateSimpleWindow(display, RootWindow(display, screen), x, y, width, height, border_width, BlackPixel(display, screen), WhitePixel(display, screen));

	size_hints.flags = USPosition | USSize;
	size_hints.x = x;
	size_hints.y = y;
	size_hints.width = width;
	size_hints.height = height;
	size_hints.min_width = width;
	size_hints.min_height = height;
	
	XSetNormalHints(display, win, &size_hints);

	XStoreName(display, win, window_name);

        // create graphics context
	gc = XCreateGC (display, win, valuemask, &values);

	XSetBackground (display, gc, WhitePixel(display, screen));
	XSetBackground (display, gc, BlackPixel(display, screen));
	
	XSetLineAttributes (display, gc, 1, LineSolid, CapRound, JoinRound);

	attr[0].backing_store = Always;
	attr[0].backing_planes = 1;
	attr[0].backing_pixel = BlackPixel(display, screen);

	XChangeWindowAttributes(display, win, CWBackingStore | CWBackingPlanes | CWBackingPixel, attr);

	XMapWindow(display, win);
	XSync(display, 0);

	XSelectInput(display, win, ExposureMask | ButtonPressMask | StructureNotifyMask | StructureNotifyMask);

	sleep(1);

	XFlush (display);

	return;
}

void destroyWindow(void)
{
	XFreeGC(display, gc);
	XCloseDisplay(display);

	return;
}

int main(void)
{
	XEvent new_event;
	int quit = 0, fd = -1;

	if ((fd = open_port("/dev/ttyS0", B9600)) == -1)
		exit(EXIT_FAILURE);

	if (createWindow() != OK)
	{
		close_port(fd);
		exit(EXIT_FAILURE);
	}

	redraw();

	while (!quit)
	{
		XNextEvent(display, &new_event);
		switch (new_event.type)
		{
			case DestroyNotify:
				quit = 1;
				break;
			case Expose:
				redraw();
				break;
			case ButtonPress:
				regenerate();
				redraw();
				break;
			case ConfigureNotify:
				resize();
				break;
			default:
				break;
		}
	}

	close_port(fd);

	destroyWindow();

	return 0;
}
