#include "../include/strings.h"
#include "../include/drivers/video.h"
#include "../include/io.h"
#include "../include/scheduler.h"
#include "top.h"

int topApp(int ppid, int pid, char * parameters)
{
	int q, i;
	processTop topList[MAX_PROCESS_COUNT];

	top(topList, &q);
	
	printf("PID\tPPID\tNiceness\tStatus\tCPU%c\tName\n", '%');
	for(i  = 0; i < q; i++) {
		printf("%d\t%d\t%d\t\t%d\t%d\t%s:%d\n", topList[i].pid, topList[i].parent, topList[i].priority, topList[i].status, topList[i].cpu, topList[i].name, topList[i].tty);
	}
	
	return 1;	
}
