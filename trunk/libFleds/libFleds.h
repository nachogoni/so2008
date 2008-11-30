#define	PIC_WIDTH	16
#define FLEDS_DEVICE	"/dev/fleds"
#define USLEEP_TIME	100

typedef enum {SCROLL_NONE = 0, SCROLL_RIGHT, SCROLL_LEFT, SCROLL_UP, SCROLL_DOWN,
	SCROLL_RIGHT_CARRY,  SCROLL_LEFT_CARRY, SCROLL_UP_CARRY,  SCROLL_DOWN_CARRY,
 	SCROLL_ROW_LEFT, SCROLL_COLUMN_DOWN, SCROLL_ROW_RIGHT, SCROLL_COLUMN_UP,
 	WAVE, TWINKLE, LIFE, LSD, CAMEL, MOVIE} animation_t;

typedef struct column
{
	char id;
	char red;
	char green;
	char blue;
} column_t;

typedef struct pic
{
	column_t cols[PIC_WIDTH];
} pic_t;

typedef struct fledsCDT * fledsADT;

fledsADT newFleds (int height, int width, char * device);

int freeFleds (fledsADT fleds);

int loadText (fledsADT fleds, char * text, int x, int y);

int loadPic (fledsADT fleds, pic_t pic, int x, int y);

int loadMovie (fledsADT fleds, pic_t * pic);

int clear (fledsADT fleds);

int show (fledsADT fleds);

int hide (fledsADT fleds);

int animate (fledsADT fleds, animation_t animation, int iterations, int speed);

