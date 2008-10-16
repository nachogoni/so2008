#include "../include/memory.h"
#include "../include/strings.h"
#include "../include/processes.h"
#include "../include/defs.h"

#ifndef IPC_SEM_H_
#define IPC_SEM_H_

int   
sem_set(key_t key, int flags);

int
sem_up(key_t key);

int
sem_down(key_t key);

int
sem_close(key_t key);

void
__init_sem(void);


#endif /*IPC_SEM_H_*/
