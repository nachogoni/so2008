#include "libFleds.h"
#include <sys/types.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>


typedef struct fledsCDT {
	int height;
	int width;
	char * device;
	int fd;
	column_t * pic;
	pic_t * movie;
} fledsCDT;

char letter[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,0x0, 0x0, 0x0, 0x4F, 
0x0, 0x0, 0x0, 0x0,0x0, 0x0, 0x07, 0x0, 0x07, 0x0, 0x0, 0x0,0x0, 0x14, 0x7F, 
0x14, 0x7F, 0x14, 0x0, 0x0,0x0, 0x24, 0x0, 0x7F, 0x0, 0x12, 0x0, 0x0,0x0, 
0x23, 0x13, 0x08, 0x64, 0x62, 0x0, 0x0,0x0, 0x36, 0x49, 0x55, 0x22, 0x50, 0x0,
0x0,0x0, 0x0, 0x05, 0x03, 0x0, 0x0, 0x0, 0x0,0x0, 0x0, 0x1C, 0x22, 0x41, 0x0, 
0x0, 0x0,0x0, 0x0, 0x41, 0x22, 0x1C, 0x0, 0x0, 0x0,0x0, 0x14, 0x08, 0x3E, 0x08,
0x14, 0x0, 0x0,0x0, 0x08, 0x08, 0x3E, 0x08, 0x08, 0x0, 0x0,0x0, 0x0, 0x50, 
0x30, 0x0, 0x0, 0x0, 0x0,0x0, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0, 0x0,0x0, 0x0,
0x60, 0x60, 0x0, 0x0, 0x0, 0x0,0x0, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x0,0x0,
0x3E, 0x51, 0x49, 0x45, 0x3E, 0x0, 0x0,0x0, 0x0, 0x42, 0x7F, 0x40, 0x0, 0x0, 0x0,
0x0, 0x42, 0x61, 0x51, 0x49, 0x46, 0x0, 0x0,0x0, 0x21, 0x41, 0x45, 0x4B, 0x31, 0x0, 
0x0,0x0, 0x18, 0x14, 0x12, 0x7F, 0x10, 0x0, 0x0,0x0, 0x27, 0x45, 0x45, 0x45, 0x39, 
0x0, 0x0,0x0, 0x3C, 0x0, 0x49, 0x49, 0x30, 0x0, 0x0,0x0, 0x03, 0x01, 0x71, 0x09, 
0x07, 0x0, 0x0,0x0, 0x36, 0x49, 0x49, 0x49, 0x36, 0x0, 0x0,0x0, 0x06, 0x49, 0x49, 
0x29, 0x1E, 0x0, 0x0,0x0, 0x0, 0x36, 0x36, 0x0, 0x0, 0x0, 0x0,0x0, 0x0, 0x56, 0x36, 
0x0, 0x0, 0x0, 0x0,0x0, 0x08, 0x14, 0x22, 0x41, 0x0, 0x0, 0x0,0x0, 0x14, 0x14, 
0x14, 0x14, 0x14, 0x0, 0x0,0x0, 0x0, 0x41, 0x22, 0x14, 0x08, 0x0, 0x0,0x0, 0x02, 
0x01, 0x51, 0x09, 0x06, 0x0, 0x0,0x0, 0x32, 0x49, 0x79, 0x41, 0x3E, 0x0, 0x0,0x0, 
0x7E, 0x11, 0x11, 0x11, 0x7E, 0x0, 0x0,0x0, 0x7F, 0x49, 0x49, 0x49, 0x36, 0x0, 0x0,
0x0, 0x3E, 0x41, 0x41, 0x41, 0x22, 0x0, 0x0,0x0, 0x7F, 0x41, 0x41, 0x22, 0x1C, 0x0, 
0x0,0x0, 0x7F, 0x49, 0x49, 0x49, 0x41, 0x0, 0x0,0x0, 0x7F, 0x09, 0x09, 0x09, 0x01, 
0x0, 0x0,0x0, 0x3E, 0x41, 0x49, 0x49, 0x0, 0x0, 0x0,0x0, 0x7F, 0x08, 0x08, 0x08, 
0x7F, 0x0, 0x0,0x0, 0x0, 0x41, 0x7F, 0x41, 0x0, 0x0, 0x0,0x0, 0x20, 0x40, 0x41, 
0x3F, 0x01, 0x0, 0x0,0x0, 0x7F, 0x08, 0x14, 0x22, 0x41, 0x0, 0x0,0x0, 0x7F, 0x40, 
0x40, 0x40, 0x40, 0x0, 0x0,0x0, 0x7F, 0x02, 0x1C, 0x02, 0x7F, 0x0, 0x0,0x0, 0x7F, 
0x04, 0x08, 0x10, 0x7F, 0x0, 0x0,0x0, 0x3E, 0x41, 0x41, 0x41, 0x3E, 0x0, 0x0,0x0, 
0x7F, 0x09, 0x09, 0x09, 0x06, 0x0, 0x0,0x0, 0x3E, 0x41, 0x51, 0x21, 0x5E, 0x0, 0x0,
0x0, 0x7E, 0x09, 0x19, 0x29, 0x46, 0x0, 0x0,0x0, 0x46, 0x49, 0x49, 0x49, 0x31, 0x0, 
0x00, 0x0, 0x01, 0x01, 0x7F, 0x01, 0x01, 0x0, 0x0,0x0, 0x3F, 0x40, 0x40, 0x40, 0x3F, 
0x0, 0x0,0x0, 0x1F, 0x20, 0x40, 0x20, 0x1F, 0x0, 0x0,0x0, 0x3F, 0x40, 0x38, 0x40, 
0x3F, 0x0, 0x0,0x0, 0x63, 0x14, 0x08, 0x14, 0x63, 0x0, 0x0,0x0, 0x07, 0x08, 0x70, 
0x08, 0x07, 0x0, 0x0,0x0, 0x61, 0x51, 0x49, 0x45, 0x43, 0x0, 0x0,0x0, 0x7F, 0x41, 
0x41, 0x0, 0x0, 0x0, 0x0,0x0, 0x02, 0x04, 0x08, 0x10, 0x20, 0x0, 0x0,0x0, 0x0, 0x0, 
0x41, 0x41, 0x7F, 0x0, 0x0,0x0, 0x04, 0x02, 0x01, 0x02, 0x04, 0x0, 0x0,0x0, 0x40, 
0x40, 0x40, 0x40, 0x40, 0x0, 0x0,0x0, 0x0, 0x0, 0x01, 0x02, 0x04, 0x0, 0x0,0x0, 0x20, 
0x54, 0x54, 0x54, 0x78, 0x0, 0x0,0x0, 0x7F, 0x48, 0x44, 0x44, 0x38, 0x0, 0x0,0x0, 
0x38, 0x44, 0x44, 0x44, 0x20, 0x0, 0x0,0x0, 0x38, 0x44, 0x44, 0x48, 0x3F, 0x0, 0x0,
0x0, 0x38, 0x54, 0x54, 0x54, 0x18, 0x0, 0x0,0x0, 0x10, 0x7E, 0x11, 0x01, 0x02, 0x0, 
0x0,0x0, 0x08, 0x54, 0x54, 0x54, 0x3C, 0x0, 0x0,0x0, 0x7F, 0x08, 0x04, 0x04, 0x78, 
0x0, 0x0,0x0, 0x0, 0x48, 0x7D, 0x40, 0x0, 0x0, 0x0,0x0, 0x20, 0x40, 0x44, 0x3D, 0x0, 
0x0, 0x0,0x0, 0x7F, 0x10, 0x28, 0x44, 0x0, 0x0, 0x0,0x0, 0x0, 0x41, 0x7F, 0x40, 0x0, 
0x0, 0x0,0x0, 0x7C, 0x04, 0x78, 0x04, 0x78, 0x0, 0x0,0x0, 0x7C, 0x08, 0x04, 0x04, 
0x78, 0x0, 0x0,0x0, 0x38, 0x44, 0x44, 0x44, 0x38, 0x0, 0x0,0x0, 0x7C, 0x14, 0x14, 
0x14, 0x08, 0x0, 0x0,0x0, 0x08, 0x14, 0x14, 0x18, 0x7C, 0x0, 0x0,0x0, 0x7C, 0x08, 
0x04, 0x04, 0x08, 0x0, 0x0,0x0, 0x48, 0x54, 0x54, 0x54, 0x20, 0x0, 0x0,0x0, 0x04, 
0x3F, 0x44, 0x40, 0x20, 0x0, 0x0,0x0, 0x3C, 0x40, 0x40, 0x20, 0x7C, 0x0, 0x0,0x0, 
0x1C, 0x20, 0x40, 0x20, 0x1C, 0x0, 0x0,0x0, 0x3C, 0x40, 0x30, 0x40, 0x3C, 0x0, 0x0,
0x0, 0x44, 0x28, 0x10, 0x28, 0x44, 0x0, 0x0,0x0, 0x0C, 0x50, 0x50, 0x50, 0x3C, 0x0, 
0x0,0x0, 0x0, 0x08, 0x36, 0x41, 0x0, 0x0, 0x0,0x0, 0x44, 0x64, 0x54, 0x4C, 0x44, 0x0, 
0x0,0x0, 0x0, 0x41, 0x36, 0x08, 0x0, 0x0, 0x0,0x0, 0x0, 0x0, 0x7F, 0x0, 0x0, 0x0, 0x0,
0x0, 0x10, 0x08, 0x08, 0x10, 0x08, 0x0, 0x00};

int isalpha(char c) {
	return(((c) >= 'a' && (c) <= 'z' ) || ((c) >= 'A' && (c)<='Z'));
}

int islower(char c) {
	return((c) >= 'a' && (c) <= 'z' );
}

int toupper(char c){
	return(islower(c)?(c)-'a'+'A':(c));
	} 
void usleep(int time)
{
	int i;
	i=time*USLEEP_TIME;
	while(i--);

	return;
}

char * strdup(char * str)
{
	char * aux;
	int i;

	if ((aux=malloc(strlen(str)+1))==NULL)
		return NULL;

	for(i=0;i<=strlen(str);i++)
		aux[i]=str[i];

	return aux;
}	

static int _initFleds(char * device) {
	return open(FLEDS_DEVICE, O_RDWR);
}

fledsADT newFleds (int height, int width, char * device) {
	fledsCDT * ret;
	ret = malloc(sizeof(struct fledsCDT));

	if (ret != NULL ) {
		ret->height = height;
		ret->width = width;
		ret->device = strdup(device);
		ret->pic = malloc(sizeof(column_t) * width /* agregar algo para la altura*/);

		if ((ret->fd=_initFleds(device)) < 0) {
			free(ret->device);
			free(ret->pic);
			free(ret);
			return NULL;
		}
	}
	printf("leds inicializados\n");
	return ret;
}

int freeFleds (fledsADT fleds) {
	close(fleds->fd);
	free(fleds->device);
	free(fleds->pic);
	free(fleds);
	return 0;
}

int loadText (fledsADT fleds, char * text, int x, int y) {
	int i = 0, j = 0;
	char c;
	if(text == NULL || strlen(text) > ((fleds->width)/8))
		return 1;

	while(*text) {
		if (*text >= ' ' && *text< (' '+95)) {
			fleds->pic[i++].red = letter[(*text-' ')* 8 + j++];
			fleds->pic[i++].red = letter[(*text-' ')* 8 + j++];
			fleds->pic[i++].red = letter[(*text-' ')* 8 + j++];
			fleds->pic[i++].red = letter[(*text-' ')* 8 + j++];
			fleds->pic[i++].red = letter[(*text-' ')* 8 + j++];
			fleds->pic[i++].red = letter[(*text-' ')* 8 + j++];
			j = 0;
		}
		text++;
	}
	return 0;
}

int loadPic (fledsADT fleds, pic_t pic, int x, int y) {
	int i = 0;

	while(i + y < fleds->width) {
		if(pic.cols[i].red != 0) {
			fleds->pic[i + y].red = pic.cols[i].red;
		}
		if(pic.cols[i].blue != 0) {
			fleds->pic[i + y].blue = pic.cols[i].blue;
		}
		if(pic.cols[i].green != 0) {
			fleds->pic[i + y].green = pic.cols[i].green;
		}

		i++;

	}
	return 0;
}

int loadMovie (fledsADT fleds, pic_t * pic) {
	fleds->movie = pic;
	return 0;
}

int clear (fledsADT fleds) {
	int i = 0;

	while(i < fleds->width) {
		fleds->pic[i].red = 0;
		fleds->pic[i].green = 0;
		fleds->pic[i].blue = 0;
		fleds->pic[i].id = i;
		i++;
	}

	fleds->movie = NULL;

	return 0;
}

int show (fledsADT fleds) {
	int i = 0;
	int index;

	while(i < 16) {
		index = i + '@';
		write(fleds->fd,&index,1);
		write(fleds->fd,&(fleds->pic[i].red),1);
		write(fleds->fd,&(fleds->pic[i].green),1);
		write(fleds->fd,&(fleds->pic[i].blue),1);
		i++;
	}
	/*escribir al serial*/
	return 0;
}

int hide (fledsADT fleds) {
	char c=0;
	write(fleds->fd,&c,1);

	return 0;
}

static int _rotlChar(unsigned short int value) {
	return (value* 2)%128 + (value *2)/128;
}

static int _rotrChar(unsigned short int value) {
	if (value%2) {
		value /=2;
		value +=128;
	} else {
		value /=2;
	}
	value %= 255;
	return (value & 0x0ff);
}

static int scroll( fledsADT fleds, animation_t animation, int iterations, int speed) {
	int i = 0;
	column_t actual, proximo;

	show(fleds);

	if(iterations == 0)
		return 0;
	switch(animation) {
		case SCROLL_LEFT:
		case SCROLL_LEFT_CARRY:
			actual = fleds->pic[i];
			while(i < fleds->width) {
				proximo = fleds->pic[(i + 1)%fleds->width];
				fleds->pic[(i + 1)%fleds->width] = actual;
				actual = proximo;
				i++;
			}
			break;
		case SCROLL_RIGHT:
		case SCROLL_RIGHT_CARRY:
			actual = fleds->pic[i];
			i = fleds->width;
			while(i > 0) {
				proximo = fleds->pic[(i - 1)%fleds->width];
				fleds->pic[(i - 1)%fleds->width] = actual;
				actual = proximo;
				i--;
			}
			break;
		case SCROLL_UP:
		case SCROLL_UP_CARRY:
			while(i < fleds->width) {
				fleds->pic[i].red  = _rotlChar(fleds->pic[i].red);
				fleds->pic[i].blue = _rotlChar(fleds->pic[i].blue) ;
				fleds->pic[i].green = _rotlChar(fleds->pic[i].green);
				i++;
			}
		case SCROLL_DOWN:
		case SCROLL_DOWN_CARRY:
			while(i < fleds->width) {
				fleds->pic[i].red  = _rotrChar(fleds->pic[i].red);
				fleds->pic[i].blue = _rotrChar(fleds->pic[i].blue) ;
				fleds->pic[i].green = _rotrChar(fleds->pic[i].green);
				i++;
			}
	}
	usleep(speed);
	return scroll(fleds, animation, iterations - 1, speed);
}

static int scrollRow( fledsADT fleds, animation_t animation, int iterations, int speed) {
	int i= 0, j=0;
	int k = 0, aux = 0, x = 1;

	column_t actual, proximo;

	switch(animation) {
		case SCROLL_COLUMN_DOWN:
			while(i < iterations && i<fleds->width) {
				while(j < 8) {
					fleds->pic[i].red /=2;
					fleds->pic[i].green /=2;
					fleds->pic[i].blue /=2;
					j++;
					show(fleds);
					usleep(speed);
				}
				j=0;
				i++;
			}
			break;
		case SCROLL_COLUMN_UP:
			while(i < iterations && i<fleds->width) {
				while(j < 8) {
					fleds->pic[i].red *=2;
					fleds->pic[i].red %= 256;

					fleds->pic[i].green *=2;
					fleds->pic[i].green %= 256;

					fleds->pic[i].blue *=2;
					fleds->pic[i].blue %= 256;

					j++;
					show(fleds);
					usleep(speed);
				}
				j=0;
				i++;
			}
			break;
		case SCROLL_ROW_RIGHT:
				x = 1;
				for (j = 0; j < 8 && j< iterations; j++)
				{

					for( k = 0; k < fleds->width; k++)
					{
						for( i = fleds->width; i > 0; i--)
						{
							fleds->pic[i].red = (fleds->pic[i].red & (~x)) | (fleds->pic[i - 1].red & x);
							fleds->pic[i].green = (fleds->pic[i].green & (~x)) | (fleds->pic[i - 1].green & x);
							fleds->pic[i].blue = (fleds->pic[i].blue & (~x)) | (fleds->pic[i - 1].blue & x);
						}
						fleds->pic[0].red &= (~x);
						fleds->pic[0].green &= (~x);
						fleds->pic[0].blue &= (~x);

						show(fleds);
						usleep(speed);
					}
					x = x * 2;

				}
			break;
		default:break;
	}
	return 0;
}

static int wave(fledsADT fleds, int iterations, int speed) {
	int i = 2;

	if (iterations == 0) {
		return 0;
	}
	show(fleds);
	usleep(speed);

	fleds->pic[0].red  = _rotlChar(fleds->pic[0].red);
	fleds->pic[0].blue = _rotlChar(fleds->pic[0].blue) ;
	fleds->pic[0].green = _rotlChar(fleds->pic[0].green);

	show(fleds);
	usleep(speed);

	fleds->pic[0].red  = _rotlChar(fleds->pic[0].red);
	fleds->pic[0].blue = _rotlChar(fleds->pic[0].blue) ;
	fleds->pic[0].green = _rotlChar(fleds->pic[0].green);

	fleds->pic[1].red  = _rotlChar(fleds->pic[1].red);
	fleds->pic[1].blue = _rotlChar(fleds->pic[1].blue) ;
	fleds->pic[1].green = _rotlChar(fleds->pic[1].green);

	show(fleds);
	usleep(speed);

	fleds->pic[0].red  = _rotrChar(fleds->pic[0].red);
	fleds->pic[0].blue = _rotrChar(fleds->pic[0].blue) ;
	fleds->pic[0].green = _rotrChar(fleds->pic[0].green);

	fleds->pic[1].red  = _rotlChar(fleds->pic[1].red);
	fleds->pic[1].blue = _rotlChar(fleds->pic[1].blue) ;
	fleds->pic[1].green = _rotlChar(fleds->pic[1].green);

	fleds->pic[2].red  = _rotlChar(fleds->pic[2].red);
	fleds->pic[2].blue = _rotlChar(fleds->pic[2].blue) ;
	fleds->pic[2].green = _rotlChar(fleds->pic[2].green);

	show(fleds);
	usleep(speed);


	while(i < fleds->width - 1) {
		fleds->pic[i-2].red  = _rotrChar(fleds->pic[i-2].red);
		fleds->pic[i-2].blue = _rotrChar(fleds->pic[i-2].blue) ;
		fleds->pic[i-2].green = _rotrChar(fleds->pic[i-2].green);

		fleds->pic[i-1].red  = _rotrChar(fleds->pic[i-1].red);
		fleds->pic[i-1].blue = _rotrChar(fleds->pic[i-1].blue) ;
		fleds->pic[i-1].green = _rotrChar(fleds->pic[i-1].green);

		fleds->pic[i].red  = _rotlChar(fleds->pic[i].red);
		fleds->pic[i].blue = _rotlChar(fleds->pic[i].blue) ;
		fleds->pic[i].green = _rotlChar(fleds->pic[i].green);

		fleds->pic[i+1].red  = _rotlChar(fleds->pic[i+1].red);
		fleds->pic[i+1].blue = _rotlChar(fleds->pic[i+1].blue) ;
		fleds->pic[i+1].green = _rotlChar(fleds->pic[i+1].green);

		show(fleds);
		usleep(speed);
		i++;
	}

	fleds->pic[fleds->width-3].red  = _rotrChar(fleds->pic[fleds->width-3].red);
	fleds->pic[fleds->width-3].blue = _rotrChar(fleds->pic[fleds->width-3].blue) ;
	fleds->pic[fleds->width-3].green = _rotrChar(fleds->pic[fleds->width-3].green);

	fleds->pic[fleds->width-2].red  = _rotrChar(fleds->pic[fleds->width-2].red);
	fleds->pic[fleds->width-2].blue = _rotrChar(fleds->pic[fleds->width-2].blue) ;
	fleds->pic[fleds->width-2].green = _rotrChar(fleds->pic[fleds->width-2].green);

	fleds->pic[fleds->width-1].red  = _rotlChar(fleds->pic[fleds->width-1].red);
	fleds->pic[fleds->width-1].blue = _rotlChar(fleds->pic[fleds->width-1].blue) ;
	fleds->pic[fleds->width-1].green = _rotlChar(fleds->pic[fleds->width-1].green);

	show(fleds);
	usleep(speed);

	fleds->pic[fleds->width-2].red  = _rotrChar(fleds->pic[fleds->width-2].red);
	fleds->pic[fleds->width-2].blue = _rotrChar(fleds->pic[fleds->width-2].blue) ;
	fleds->pic[fleds->width-2].green = _rotrChar(fleds->pic[fleds->width-2].green);

	fleds->pic[fleds->width-1].red  = _rotrChar(fleds->pic[fleds->width-1].red);
	fleds->pic[fleds->width-1].blue = _rotrChar(fleds->pic[fleds->width-1].blue) ;
	fleds->pic[fleds->width-1].green = _rotrChar(fleds->pic[fleds->width-1].green);

	show(fleds);
	usleep(speed);

	fleds->pic[fleds->width-1].red  = _rotrChar(fleds->pic[fleds->width-1].red);
	fleds->pic[fleds->width-1].blue = _rotrChar(fleds->pic[fleds->width-1].blue) ;
	fleds->pic[fleds->width-1].green = _rotrChar(fleds->pic[fleds->width-1].green);

	show(fleds);
	usleep(speed);

	return wave(fleds, iterations-1, speed);

}

static int twinkle(fledsADT fleds, int iterations, int speed) {

	show(fleds);
	usleep(speed);
	if(iterations == 0) {
		return 0;
	}
	hide(fleds);
	usleep(speed);
	return twinkle(fleds, iterations-1, speed);
}

static int life(fledsADT fleds, int iterations, int speed) {
	return 0;
}

static int lsd(fledsADT fleds, int iterations, int speed) {
	int i = 0;

	show(fleds);
	if(iterations == 0) {
		return 0;
	}

	while(i < fleds->width) {
		fleds->pic[i].red = (~(fleds->pic[i].green)+time(NULL))%256;
		fleds->pic[i].green = ~(fleds->pic[i].blue);
		fleds->pic[i].blue = (~((fleds->pic[i].red + fleds->pic[i].blue + fleds->pic[i].green )%256) + time(NULL))%256;
		i++;
	}

	usleep(speed);
	return lsd(fleds, iterations - 1, speed);
}

static int showCamel(fledsADT fleds) {
	int i = 0;
	int index;

	index = 4 + '@';

	write(fleds->fd,&index,1);
	write(fleds->fd,&(fleds->pic[i].red),1);
	write(fleds->fd,&(fleds->pic[i].green),1);
	write(fleds->fd,&(fleds->pic[i].blue),1);

	return 0;
}

static int camel(fledsADT fleds, int iterations, int speed) {
	column_t actual, proximo;
	int i= 0;
	showCamel(fleds);

	if(iterations == 0) {
		return 0;
	}

	actual = fleds->pic[i];
	while(i < fleds->width) {
		proximo = fleds->pic[(i + 1)%fleds->width];
		fleds->pic[(i + 1)%fleds->width] = actual;
		actual = proximo;
		i++;
	}

	return camel(fleds,iterations-1, speed);
}

static int showFrame(pic_t pic, int width, int fd) {
	int i = 0;

	while(i < 16) {

		int index;

		index = i + '@';

		write(fd,&index,1);
		write(fd,&(pic.cols[i].red),1);
		write(fd,&(pic.cols[i].green),1);
		write(fd,&(pic.cols[i].blue),1);

		i++;
	}
	/*escribir al serial*/
	return 0;
}

static int play(fledsADT fleds, int iterations, int speed) {
	int i;

	while(iterations--) {
		while( ((fleds->movie)[i]).cols[0].id != -1 ) {
			showFrame((fleds->movie)[i], fleds->width, fleds->fd);
			i++;
			usleep(speed);
		}
		i = 0;
		usleep(speed);
	}

	return 0;
}

int animate (fledsADT fleds, animation_t animation, int iterations, int speed) {
	switch(animation) {

		case SCROLL_NONE:
			break;

		case SCROLL_RIGHT_CARRY:
		case SCROLL_RIGHT:
		case SCROLL_LEFT_CARRY:
		case SCROLL_LEFT:
		case SCROLL_UP_CARRY:
		case SCROLL_UP:
		case SCROLL_DOWN_CARRY:
		case SCROLL_DOWN: scroll(fleds, animation, iterations, speed);break;

		case SCROLL_ROW_LEFT:
		case SCROLL_COLUMN_DOWN:
		case SCROLL_ROW_RIGHT:
		case SCROLL_COLUMN_UP:scrollRow(fleds, animation, iterations, speed);break;

		case WAVE: wave(fleds, iterations, speed);break;

		case TWINKLE: twinkle(fleds, iterations, speed);break;

		case LIFE:life(fleds, iterations, speed);break;

		case LSD:lsd(fleds, iterations, speed);break;

		case CAMEL:camel(fleds, iterations, speed);break;

		case MOVIE:play(fleds, iterations, speed);break;

		default: break;
	}
	return 0;
}

int prueba(fledsADT fleds, int iterations)
{
	int k = 0, i = 0, j = 0, aux = 0, x = 1;

	for (j = 0; j < 8; j++)
	{
		x = 1;
		for( k = 0; k < fleds->width; k--)
		{
			for( i = fleds->width; i > 0; i--)
			{
				fleds->pic[i].red = (fleds->pic[i].red & (~x)) | (fleds->pic[i - 1].red & x);
				fleds->pic[i].green = (fleds->pic[i].green & (~x)) | (fleds->pic[i - 1].green & x);
				fleds->pic[i].blue = (fleds->pic[i].blue & (~x)) | (fleds->pic[i - 1].blue & x);
			}
			fleds->pic[0].red &= (~x);
			fleds->pic[0].green &= (~x);
			fleds->pic[0].blue &= (~x);
			x = x * 2;
		}
	}

	return 0;
}
