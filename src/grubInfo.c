#include "../include/grubInfo.h"
#include "../include/io.h"
#include "../include/strings.h"

#define CHECK_FLAG(flags,bit)   ((flags) & (1 << (bit)))

static infoGrub * info;

int
getBlockMem(void **m_address, int * m_size)
{
	int addr, size=0;
	mmapT * mmap = NULL;
	
	//Si la informacion esta disponible
	if (CHECK_FLAG(info->flags, 6))
	{
		for (mmap = (mmapT *) info->mmap_addr;
			(mmap + sizeof (mmap->size)) < (info->mmap_addr + info->mmap_length);
			mmap = (mmapT *)((unsigned long) mmap + mmap->size + sizeof (mmap->size)))
			//Recorro los bloques de memoria para obtener el bloque mas grande 
				if (size<mmap->length_low && mmap->length_low<MAX_SIZE_BLOCK_MEM)
				{
					addr=mmap->base_addr_low;
					size=mmap->length_low;
				}
		//Si el addr empieza en 1MB hay que correrlo por que va a pisar al kernel
		if (addr==0x100000)
		{
			//Lo muevo 1MB
			addr+=1*MB;
			//Resto el MB a la memoria
			size-=1*MB;
		}

		*(char**)m_address=(char*)addr;
		*m_size=size;
	
		return 1;
	}
	
	return 0;	
}

int
getMemSize(void)
{
	return (CHECK_FLAG(info->flags, 0)) ? info->mem_upper : 0; 
}

int showMem(void)
{
	mmapT * mmap = NULL;

	if (CHECK_FLAG(info->flags, 0))
		printf("\nMemory count:\n\tLower memory: %dkb\n\tUpper memory: %dkb\n", info->mem_lower, info->mem_upper);

	if (CHECK_FLAG(info->flags, 6))
	{
		printf("\nMemory map:\n");
		
		//printf("\tMemory address: 0x%x, Memory length: 0x%x\n", info->mmap_addr, info->mmap_length);

		for (mmap = (mmapT *) info->mmap_addr;
			(mmap + sizeof (mmap->size)) < (info->mmap_addr + info->mmap_length) && mmap->size < 0x50;
			mmap = (mmapT *)((unsigned long) mmap + mmap->size + sizeof (mmap->size)))
				printf ("\taddress: 0x%x:%x\tlength: 0x%x%x\n",
				mmap->base_addr_high, mmap->base_addr_low, mmap->length_high,
				mmap->length_low);

	}

	return 0;
}

int 
show_multiBoot()
{
	printf("Booting from %s%s multiboot - bootloader...\n", info->boot_loader_name, CHECK_FLAG(info->flags, 9)?" ":"");

	if (CHECK_FLAG(info->flags, 2))
		printf("\nKernel parameters: '%s'\n", info->cmdline);

	showMem();
	
	return 1;
}

void
set_multiBoot(unsigned long infoStruct)
{
	//Seteo la variable global con la direccion
	info = (infoGrub *) infoStruct;	

	return;
}

