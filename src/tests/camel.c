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

			fleds = newFleds(8, strlen(s)*8*2+16,"/dev/fd0");
			loadText(fleds, s, 0,0);
			while(1)
				animate(fleds, CAMEL, strlen(s)*8, 0);

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
