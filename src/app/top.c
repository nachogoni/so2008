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
	
	printf("Name\tPID\tPPID\tNiceness\tStatus\tCPU%c\n", '%');
	for(i  = 0; i < q; i++) {
		printf("%s\t%d\t%d\t%d\t\t%d\t%d\n", topList[i].name, topList[i].pid, topList[i].parent, topList[i].priority, topList[i].status, topList[i].cpu);
	}
	
	return 1;	
}
