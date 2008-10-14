#include "../include/pagination.h"
#include "../include/memory.h"
#include "../include/strings.h"
#include "../include/defs.h"

#ifndef IPC_SHM_H_
#define IPC_SHM_H_

typedef char * key_t;

int   
shm_open(key_t key, size_t size, int flags);

void*
mmap(int shmid);

int
shm_close(int shmid);


#endif /*IPC_SHM_H_*/
