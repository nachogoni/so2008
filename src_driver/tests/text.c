#include "libFleds.h"
#include <string.h>
#include <stdio.h>

int main (void) {

	pic_t movie[3];
	pic_t pic, frame1, frame2, framemuerto;
	int i = 0, read = 0;
	fledsADT fleds;
	char s[1000];
	char c;

	while(c = getchar()) {
		if(strcmp(s,"quit") == 0) {
			return 0;
		}
		if(c=='\n') {
			s[i] = '\0';

			fleds = newFleds(8, strlen(s)*8*2,"/dev/fd0");
			loadText(fleds, s, 15,0);
			show(fleds);

			animate(fleds, SCROLL_RIGHT_CARRY, strlen(s)*8*8, 100000);

			clear(fleds);
			hide(fleds);

			freeFleds(fleds);
			i = 0;
		} else {
			s[i++] = c;
		}
	}
	return 0;
}
