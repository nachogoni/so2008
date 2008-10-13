#ifndef _keylayout_h_
#define _keylayout_h_

#include "keyboard.h"
#include "../fd.h"
#include "../defs.h"

// Layout us_en
int key_layouts[][2][128] = {
	// -US- BEGIN
	{{		// Layout normal
	/*0      1    2     3     4     5     6     7     8     9*/
/*00*/	 NOP,  ESC,  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',
/*01*/	 '9',  '0',  '-',  '=', '\b', '\t',  'q',  'w',  'e',  'r',
/*02*/	 't',  'y',  'u',  'i',  'o',  'p',  '[',  ']', '\n',  L_CTRL,
/*03*/	 'a',  's',  'd',  'f',  'g',  'h',  'j',  'k',  'l',  ';',
/*04*/	'\'',  '`',  L_SHIFT, '\\',  'z',  'x',  'c',  'v',  'b',  'n',
/*05*/	 'm',  ',',  '.',  '/',  R_SHIFT,  '*',  L_ALT,  ' ',  CPS_LCK,  F01,
/*06*/	 F02,  F03,  F04,  F05,  F06,  F07,  F08,  F09,  F10,  NUM_LCK,
/*07*/	 SCR_LCK,  HOME,  UP,  PG_UP,  '-',  LEFT,  CENTER,  RIGHT,  '+',  END,
/*08*/	 DOWN,  PG_DW,  INSERT,  DELETE,  '/', '\n',  NOP,  NOP,  NOP,  NOP, 
/*09*/	 NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP,
/*10*/	 NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP,
/*11*/	 NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP,
/*12*/	 NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP
	},{			// Layout con shift
	/*0      1    2     3     4     5     6     7     8     9*/
/*00*/	 NOP,  ESC,  '!',  '@',  '#',  '$',  '%',  '^',  '&',  '*',
/*01*/	 '(',  ')',  '_',  '+', '\b', '\t',  'Q',  'W',  'E',  'R', 
/*02*/	 'T',  'Y',  'U',  'I',  'O',  'P',  '{',  '}', '\n',  L_CTRL,
/*03*/	 'A',  'S',  'D',  'F',  'G',  'H',  'J',  'K',  'L',  ':',
/*04*/	'\"',  '~',  L_SHIFT,  '|',  'Z',  'X',  'C',  'V',  'B',  'N',
/*05*/	 'M',  '<',  '>', '\?',  R_SHIFT,  '*',  L_ALT,  ' ',  CPS_LCK,  F01,
/*06*/	 F02,  F03,  F04,  F05,  F06,  F07,  F08,  F09,  F10,  NUM_LCK,
/*07*/	 SCR_LCK,  HOME,  UP,  PG_UP,  '-',  LEFT,  CENTER,  RIGHT,  '+',  END,  
/*08*/	 DOWN,  PG_DW,  INSERT,  DELETE,  '/', '\n',  NOP,  NOP,  NOP,  NOP, 
/*09*/	 NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP,
/*10*/	 NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP,
/*11*/	 NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP,
/*12*/	 NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP
	}},
	// -US- END
	// -ES- BEGIN
	{{		// Layout normal
	/*0      1    2     3     4     5     6     7     8     9*/
/*00*/	 NOP,  ESC,  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',
/*01*/	 '9',  '0', '\'',  173, '\b', '\t',  'q',  'w',  'e',  'r',
/*02*/	 't',  'y',  'u',  'i',  'o',  'p',  '`',  '+', '\n',  L_CTRL,
/*03*/	 'a',  's',  'd',  'f',  'g',  'h',  'j',  'k',  'l',  164,
/*04*/	 '[', '\\',  L_SHIFT, '{',  'z',  'x',  'c',  'v',  'b',  'n',
/*05*/	 'm',  ',',  '.',  '-',  R_SHIFT,  '*',  L_ALT,  ' ',  CPS_LCK,  F01,
/*06*/	 F02,  F03,  F04,  F05,  F06,  F07,  F08,  F09,  F10,  NUM_LCK,
/*07*/	 SCR_LCK,  HOME,  UP,  PG_UP,  '-',  LEFT,  CENTER,  RIGHT,  '+',  END,  
/*08*/	 DOWN,  PG_DW,  INSERT,  DELETE,  '/', '\n',  '<',  NOP,  NOP,  NOP, 
/*09*/	 NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP,
/*10*/	 NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP,
/*11*/	 NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP,
/*12*/	 NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP
	},{			// Layout con shift
	/*0      1    2     3     4     5     6     7     8     9*/
/*00*/	 NOP,  ESC,  '!', '\"',  '#',  '$',  '%',  '&',  '/',  '(',
/*01*/	 ')',  '=', '\?',  168, '\b', '\t',  'Q',  'W',  'E',  'R', 
/*02*/	 'T',  'Y',  'U',  'I',  'O',  'P',  '^',  '*', '\n',  L_CTRL,
/*03*/	 'A',  'S',  'D',  'F',  'G',  'H',  'J',  'K',  'L',  165,
/*04*/	 ']',  '|',  L_SHIFT,  '}',  'Z',  'X',  'C',  'V',  'B',  'N',
/*05*/	 'M',  ';',  ':',  '_',  R_SHIFT,  '*',  L_ALT,  ' ',  CPS_LCK,  F01,
/*06*/	 F02,  F03,  F04,  F05,  F06,  F07,  F08,  F09,  F10,  NUM_LCK,
/*07*/	 SCR_LCK,  HOME,  UP,  PG_UP,  '-',  LEFT,  CENTER,  RIGHT,  '+',  END,  
/*08*/	 DOWN,  PG_DW,  INSERT,  DELETE,  '/', '\n',  '>',  NOP,  NOP,  NOP, 
/*09*/	 NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP,
/*10*/	 NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP,
/*11*/	 NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP,
/*12*/	 NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP,  NOP
	}}
	// -ES- END
	};

#endif

