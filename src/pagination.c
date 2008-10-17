#include "../include/pagination.h"
#include "../include/defs.h"
#include "../include/memory.h"
#include "../include/kasm.h"

/********************************** 
*
*  Pagination
*
***********************************/

typedef struct
{
	unsigned long **page_directory;
	unsigned long *page_table;
	unsigned long start_kernel_zone_idx;
	unsigned long kernel_used;
	unsigned long kernel_total;
	unsigned long start_user_zone_idx;
	unsigned long user_used;
	unsigned long user_total;
}s_pagination;


s_pagination g_pagination;

void
__init_pagination(unsigned long **page_directory, unsigned long *page_table, unsigned long kernel_size, unsigned long user_size)
{
	unsigned page_count, i, dir_aux, dir_used;
	unsigned long address=0; 
	
	g_pagination.page_directory = page_directory;
	g_pagination.page_table = page_table;
	
	//Cantidad de paginas de kernel usadas
	page_count = kernel_size / (4*KB);
	if (kernel_size % (4*KB))
		page_count++;
	
	//Guardo en que pagina empieza el kernel
	g_pagination.start_kernel_zone_idx = 0;
	//cantidad de paginas que usa el kernel
	g_pagination.kernel_used = page_count;
	//cantidad de paginas que tiene asignado el kernel
	g_pagination.kernel_total = page_count;
	
	//Seteo la zona de kernel
	for(i=0; i< g_pagination.kernel_total ; i++)
	{
		page_table[i] = address | KERNEL_PAGE_ATT_UP; // attribute set to: supervisor level, read/write, present(011 in binary)
		address = address + 4*KB;
	};

	//calculo cuantos tablas de pagina hizo
	dir_aux = g_pagination.kernel_total / PAGES_PER_TABLE_DIR;
	if (g_pagination.kernel_total % PAGES_PER_TABLE_DIR)
		dir_aux++;

	// las agrego en el directorio
	for (i=0; i< dir_aux; i++)
	{
		page_directory[i] = (void*)page_table + i*4*KB; // attribute set to: supervisor level, read/write, present(011 in binary)
		page_directory[i] = (unsigned long *)(((unsigned long)page_directory[i]) | KERNEL_PAGE_ATT_UP);
	}

	dir_used = dir_aux;

	//Asigno la zona de usuario
	page_count = user_size / (4*KB);
	if (user_size % (4*KB))
		page_count++;
		
	//index de la pagina donde empieza la zona de usuario
	g_pagination.start_user_zone_idx = g_pagination.kernel_used;
	//cantidad de paginas que tiene la zona de usuario
	g_pagination.user_total = page_count;
	//cantidad de paginas usadas
	g_pagination.user_used = 0;

	for(i=g_pagination.start_user_zone_idx; i< g_pagination.start_user_zone_idx + g_pagination.user_total ; i++)
	{
		page_table[i] = address | USER_PAGE_ATT_UP; // attribute set to: supervisor level, read/write, present(011 in binary)
		address = address + 4*KB;
	};

	//calculo cuantos tablas de pagina hizo
	dir_aux = g_pagination.user_total / PAGES_PER_TABLE_DIR;
	if (g_pagination.user_total % PAGES_PER_TABLE_DIR)
		dir_aux++;

	// las agrego en el directorio
	for (i=dir_used; i< dir_used + dir_aux; i++)
	{
		page_directory[i] = (void*)page_table + i*4*KB; // attribute set to: supervisor level, read/write, present(011 in binary)
		page_directory[i] = (unsigned long *)(((unsigned long)page_directory[i]) | KERNEL_PAGE_ATT_UP);
	}


	/* dejo inactivas las demas */
	for(i=dir_used + dir_aux; i<1024; i++)
		page_directory[i] = (unsigned long *)(0 | KERNEL_PAGE_ATT_DOWN);

	// write_cr3, read_cr3, write_cr0, and read_cr0 all come from the assembly functions
	write_cr3(page_directory); // put that page directory address into CR3
	write_cr0(read_cr0() | 0x80000000); // set the paging bit in CR0 to 1
	
	return;

}


/*
 * Wrapper para levantar o bajar una pagina
 */
static void
set_page(unsigned int index, char att)
{
    //Dejo solo el ultimo bit para no cagarla
    att = att & 1;
   
    //Asigno
    g_pagination.page_table[index] &= 0xFFFFFFFFE;
    g_pagination.page_table[index] |= att;
   
    return;
}

/*
 * Habilita una pagina
 */
void
up_page(unsigned int index)
{
    //set_page(index, 1);
    g_pagination.page_table[index] &= 0xFFFFFFFFE;
    g_pagination.page_table[index] |= 0x1;

    return;
}

/*
 * Deshabilita una pagina
 */
void
down_page(unsigned int index)
{
    g_pagination.page_table[index] &= 0xFFFFFFFFE;    	

    return;	
}

/* down_pages_process
 * 
 * Recibe la direccion dada del heap y del stack
 * dejando solo esas activas
 */
void
down_pages_process(void *heap, void* stack)
{
	unsigned long index_heap, index_stack,i;

	if (heap == NULL)
		return;
	
	index_heap = (unsigned long)heap/(4*KB);
	index_stack = (unsigned long)stack/(4*KB);
	
	//dejo inactivas solo las que me piden
	down_page(index_heap);
	down_page(index_stack);
	
	return;
}

void
up_pages_process(void *heap, void* stack)
{
	unsigned long index_heap, index_stack,i;

	if (heap == NULL)
		return;
	
	index_heap = (unsigned long)heap/(4*KB);
	index_stack = (unsigned long)stack/(4*KB);
	
	//dejo activa solo las que me piden
	up_page(index_heap);
	
	up_page(index_stack);
	
	return;
}


/*
typedef struct
{
	unsigned long *page_directory;
	unsigned long *page_table;
	unsigned long start_kernel_zone_idx;
	unsigned long kernel_used;
	unsigned long start_user_zone_idx;
	unsigned long user_used;
}s_pagination;
*/
void*
get_free_page(void)
{
    int idx_directory, idx_page, index;
    unsigned long *page_table;
    void* address;
    
    g_pagination.user_used++;

    index = g_pagination.start_user_zone_idx + g_pagination.user_used;
    
    idx_directory = index / PAGES_PER_TABLE_DIR;
    idx_page = index % PAGES_PER_TABLE_DIR;
   
    //Obtengo la tabla de pagina donde se encuentra la pagina
    page_table = g_pagination.page_directory[idx_directory];
	
    //como las direcciones son lineales en la paginacion (1a1) devuelvo directamente 
    address = (void *)(idx_directory*4 * MB + idx_page*4*KB);
	
    up_page(index);
   
    return address;
	
}

void*
duplicatePage(void *address)
{
    int idx_directory, idx_page, index;
    unsigned long *page_table;
    void* new_address;
    
    index=(unsigned long)address/(4*KB);
    
    idx_directory = index / PAGES_PER_TABLE_DIR;
    idx_page = index % PAGES_PER_TABLE_DIR;
   
    //Obtengo la tabla de pagina donde se encuentra la pagina
    page_table = g_pagination.page_directory[idx_directory];
	
    //como las direcciones son lineales en la paginacion (1a1) devuelvo directamente 
    address = (void *)(idx_directory*4*MB + idx_page * 4*KB);

    //obtengo una direccion nueva
    new_address = get_free_page();

    //copio el contenido
    memcpy(new_address, address, 4*KB);

    return new_address;
}
