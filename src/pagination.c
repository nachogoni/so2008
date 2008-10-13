#include "../include/pagination.h"
#include "../include/defs.h"
#include "../include/kasm.h"

/********************************** 
*
*  Pagination
*
***********************************/

typedef struct
{
	unsigned long *page_directory;
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
__init_pagination(unsigned long *page_directory, unsigned long *page_table, unsigned long kernel_size, unsigned long user_size)
{
	unsigned long address, page_count;
	
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
	set_page_zone(page_directory, page_table, 0, 0, 0, 0, kernel_size, KERNEL_PAGE_ATT_UP);
	
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
	
	//Muevo el puntero de la tabla de pagina
	page_table = (void*)page_table + g_pagination.kernel_used * 4*KB;
	
	//Seteo la zona de usuario
	set_page_zone(page_directory, page_table, g_pagination.start_user_zone_idx / PAGES_PER_TABLE_DIR, g_pagination.start_user_zone_idx * 4*KB, 0, 0, user_size, USER_PAGE_ATT_UP);
	
	// write_cr3, read_cr3, write_cr0, and read_cr0 all come from the assembly functions
	write_cr3(page_directory); // put that page directory address into CR3
	write_cr0(read_cr0() | 0x80000000); // set the paging bit in CR0 to 1
	
	return;

}

static void
set_page_zone(unsigned long *page_directory, unsigned long *page_table, unsigned long page_table_idx, unsigned long start_address, int page_start, unsigned long page_start_idx, unsigned long mem_size, char atts)
{
	unsigned long address;
	unsigned long page_count, page_count_left;
	int i, dir_idx=0;
	
	//Cantidad de paginas totales
	page_count_left = mem_size / (4*KB);
	
	address = start_address;
	
	while(page_count_left > 0)
	{
		
		//Calculo la cantidad de paginas a meter
		page_count = ((page_count_left + page_start_idx) > PAGES_PER_TABLE_DIR ? PAGES_PER_TABLE_DIR : page_count_left);
		
//		printf("pagino desde %d (%x) - %d con (%c)\n", page_start_idx, address, page_count,'0'+atts);
		//Seteo la primera pagina
		address = set_page_table(page_table, address, page_start_idx, page_count, atts);
		
		//La ingreso en el directorio
//		printf("ingreso la pagina %d\n",page_table_idx);
		add_page_table(page_directory, page_table, page_table_idx++, atts);
	
		//Paso a la proxima direccion
		page_table += 4096;
		
		page_start_idx = 0;
		
		//resto las que ya puse
		page_count_left = page_count_left - page_count;
	}
		
	return address;
}

/*
recibe:
- el vector de tabla de pagina
- la direccion inicial
- la cantidad de paginas
- atributos de las paginas
// attribute set to: supervisor level, read/write, present(011 in binary)
*/
static unsigned long
set_page_table(unsigned long *page_table, unsigned long start_address, int page_start, int page_count, char atts)
{
	int i;
	unsigned long address;

	//Seteo la direccion inicial
	address = start_address;

	//limpio los bits insignificantes de los atributos
	atts = atts & 7;

	for(i=page_start; i<page_count; i++)
	{
		page_table[i] = address | atts; 
		address = address + (4*KB); // 4096 = 4kb
	};
//	printf("Seteo zona %d (%x) - %d (%x) con atts %c\n",page_start, start_address ,page_count, address, '0' + atts);

	return address;
}

/*
 Setea una entrada en el directorio
 Recibe:
 - El vector de directorio
 - La pagina a asignar
 - El indice de la pagina
 - Los atributos de la pagina
*/

void
add_page_table(unsigned long *page_directory, unsigned long *page_table, int index, char atts)
{
	//limpio los bits insignificantes de los atributos
	atts = atts & 7;

	//seteo 
	page_directory[index] = page_table; // attribute set to: supervisor level, read/write, present(011 in binary)
	page_directory[index] = page_directory[index] | atts;
}

/*
 * Wrapper para setear los atributos de una pagina
 */
static void
set_page_atts(unsigned int index, char att)
{
    int idx_directory, idx_page;
    unsigned long *page_table;
   
    idx_directory = index / PAGES_PER_TABLE_DIR;
    idx_page = index % PAGES_PER_TABLE_DIR;
   
    //Obtengo la tabla de pagina donde se encuentra la pagina
    page_table = g_pagination.page_directory[idx_directory];
   
    //Dejo solo el ultimo bit para no cagarla
    att = att & 1;
   
    //Asigno
    page_table[idx_page] = page_table[idx_page] & 0xFFF8;
    page_table[idx_page] = page_table[idx_page] | att;
   
    return;
}

/*
 * Wrapper para levantar o bajar una pagina
 */
static void
set_page(unsigned int index, char att)
{
    int idx_directory, idx_page;
    unsigned long *page_table;
   
    idx_directory = index / PAGES_PER_TABLE_DIR;
    idx_page = index % PAGES_PER_TABLE_DIR;
   
    //Obtengo la tabla de pagina donde se encuentra la pagina
    page_table = g_pagination.page_directory[idx_directory];
   
    //Dejo solo el ultimo bit para no cagarla
    att = att & 1;
   
    //Asigno
    page_table[idx_page] = page_table[idx_page] & 0xFFFE;
    page_table[idx_page] = page_table[idx_page] | att;
   
    return;
}

/*
 * Habilita una pagina
 */
void
up_page(unsigned int index)
{
    set_page(index, 1);

    return;
}

/*
 * Deshabilita una pagina
 */
void
down_page(unsigned int index)
{
    set_page(index, 0);

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
	
	//bajo todas las paginas de usuario
	for (i=0;i<g_pagination.user_used;i++)
		down_page(g_pagination.start_user_zone_idx+i);
	
	//dejo activa solo las que me piden
	index_heap = (unsigned long)heap/(4*KB);
	up_page(index_heap);
	
	index_stack = (unsigned long)stack/(4*KB);
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
    
    index=g_pagination.start_user_zone_idx + g_pagination.user_used;
    
    idx_directory = index / PAGES_PER_TABLE_DIR;
    idx_page = index % PAGES_PER_TABLE_DIR;
   
    //Obtengo la tabla de pagina donde se encuentra la pagina
    page_table = g_pagination.page_directory[idx_directory];
	
    //como las direcciones son lineales en la paginacion (1a1) devuelvo directamente 
    address = idx_directory*4*MB + idx_page * 4*KB;
	
//	printf("Dir= %x\n", address);

	g_pagination.user_used++;
    
	
	return address;
	
}


