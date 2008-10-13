#ifndef _shell_h_
#define _shell_h_

#define BUFFER_SIZE	255
#define HISTORY_SIZE	10

#define prompt	"user@humix"

int init_shell(int ppid, int pid, char * param);

#endif

