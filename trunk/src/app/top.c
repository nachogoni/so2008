#include "../include/strings.h"
#include "../include/drivers/video.h"
#include "../include/io.h"
#include "../include/scheduler.h"
#include "top.h"
#include "processes.h"

int topApp(int ppid, int pid, char * parameters)
{
	int q, i;
	processTop topList[MAX_PROCESS_COUNT];

	top(topList, &q);
	
	printf("PID\tPPID\tNiceness\tStatus\tCPU%c\tName\n", '%');
	for(i  = 0; i < q; i++) {
		printf("%d\t%d\t%d\t\t", topList[i].pid, topList[i].parent, topList[i].priority);

		if (topList[i].pid == getpid())
			printf("running");
		else
			switch (topList[i].status)
			{
				case PROC_CHILD_BLOQUED:
					printf("child");
				break;
				case PROC_SEM_BLOQUED:
					printf("sem");
				break;
				case PROC_SLEEP_BLOQUED:
					printf("sleep");
				break;
				case PROC_STDIN_BLOQUED:
					printf("read");
				break;
				case PROC_READY:
					printf("ready");
				break;
				case PROC_EXECUTING:
					printf("running");
				break;
				default:
					printf("¿?");
				break;
			}
		printf("\t%d\t%s:%d\n", topList[i].cpu, topList[i].name, topList[i].tty);
	}
	
	return 1;	
}
