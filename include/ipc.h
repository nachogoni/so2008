#include "../include/pagination.h"
#include "../include/memory.h"
#include "../include/strings.h"
#include "../include/defs.h"

#ifndef IPC_SHM_H_
#define IPC_SHM_H_

void
__init_ipcs(void);

int   
__shm_open(key_t key, size_t size, int flags);

void*
__mmap(int shmid);

int
__shm_close(int shmid);


#endif /*IPC_SHM_H_*/
