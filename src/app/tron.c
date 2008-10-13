#include "../../include/defs.h"
#include "../../include/fd.h"
#include "../../include/strings.h"
#include "../../include/io.h"
#include "../../include/kernel.h"
#include "../../include/drivers/video.h"
#include "../../include/drivers/keyboard.h"

#define BUFFER_SIZE	255

static char * video = (char *)__M_VIDEO;

static int checkCollision(char * video, int pos);

static int drawVideo(char * video, int pos, char color);

int init_tron(int ppid, int pid, char * parameters)
{
	int key = 0, ser = 0, salir = 0;
	int pos, oppPos;
	int myColor, oppColor;
	
	clearScreen();
	printf("Welcome to tron (pid %d), press 'x' to connect...\n", pid);
	

	
	pos = 840;
	oppPos = 2000-840;
	
	myColor = 0x10;
	oppColor = 0x20;
	
	clearScreen();
	
	drawVideo(video, oppPos, oppColor);
	drawVideo(video, pos, myColor);
	stdser = fd_open(SERIAL);
	
	while (!salir)
	{
		ser = fgetc(stdser);
		
		
		if ( (ser) > 0) {
			switch (ser)
			{
				case 1:	printf("Your buddy quit the game, press ESC to exit"); 
							salir = 1;
							break;			
				case 2:		printf("You won");
							salir = 1;
							break;
				case 5 :	if(checkCollision(video, oppPos - 80)) {
								printf("You won");
								salir = 1;
							} else
							drawVideo(video, oppPos-=80, oppColor); 
							break;
				case 6 :	if(checkCollision(video, oppPos + 80)) {
								printf("You won");
								salir = 1;
							} else
							drawVideo(video, oppPos+=80, oppColor); 
							break;
				case 7 :	if(checkCollision(video, oppPos - 1)) {
								printf("You won");
								salir = 1;
							} else
							drawVideo(video, oppPos-=1, oppColor); 
							break;
				case 8 :if(checkCollision(video, oppPos + 1)) {
								printf("You won");
								salir = 1;
							} else
							drawVideo(video, oppPos+=1, oppColor); 
							break;
			}
		}
		
		if ( (key = fgetc(stdin))) {
			switch (key)
			{
				case ESC:	fputc(stdser, 1);
							return 0;
							break;
				case UP :	if(checkCollision(video, pos - 80)) {
								fputc(stdser, 2);
								printf("You Lost");
								salir = 1;
							} else {
							fputc(stdser, 6);
							drawVideo(video, pos-=80, myColor);
							}
							break;
				case DOWN :	if(checkCollision(video, pos + 80)) {
								fputc(stdser, 2);
								printf("You Lost");
								salir = 1;
							} else {
							fputc(stdser, 5);
							drawVideo(video, pos+=80, myColor);
							}
							break;
				case LEFT :	if(checkCollision(video, pos - 1)) {
								fputc(stdser, 2);
								printf("You Lost");
								salir = 1;		
							} else {
							fputc(stdser, 8);
							drawVideo(video, pos-=1, myColor);
							}
							break;
				case RIGHT:	if(checkCollision(video, pos + 1)) {
								fputc(stdser, 2);
								printf("You Lost");
								salir = 1;
							} else {
							fputc(stdser, 7);
							drawVideo(video, pos+=1, myColor);
							}
							break;
			}
		}
		
	}
	
	fd_close(stdser);
	while((ser = fgetc(stdin)) != ESC);
	clearScreen();
	return 0;
}

static int checkCollision(char * video, int pos) {
	return (pos < 0 || pos > 4000 || video[(pos*2) + 1]!=0x07);
}

static int drawVideo(char * video, int pos, char color) {
	return (video[(pos * 2) + 1] = color);
}
