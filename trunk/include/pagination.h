/********************************** 
*
*  Pagination
*
***********************************/

#ifndef _pagination_
#define _pagination_

#define KERNEL_PAGE_ATT_UP 3
#define KERNEL_PAGE_ATT_DOWN 2
#define USER_PAGE_ATT_UP   3
#define USER_PAGE_ATT_DOWN   2

#define PAGES_PER_TABLE_DIR	1024
#define SIZE_PER_PAGE		4*KB

/*
	Inicializa la paginacion
*/

void
__init_pagination(unsigned long **page_directory, unsigned long *page_table, unsigned long kernel_size, unsigned long user_size);

/*
 Setea una entrada en el directorio
 Recibe:
 - El vector de directorio
 - La pagina a asignar
 - El indice de la pagina
 - Los atributos de la pagina
*/

void
up_pages_process(void *heap, void* stack);

void
add_page_table(unsigned long **page_directory, unsigned long *page_table, int index, char atts);

void
up_page(unsigned int index);

/*
 * Deshabilita una pagina
 */
void
down_page(unsigned int index);

/* get_free_page
 * 
 * Devuelve la proxima direccion de memoria libre a usar
 */
void*
get_free_page(void);

/* down_pages_process
 * 
 * Recibe la direccion dada del heap y del stack
 * dejando solo esas activas
 */
void
down_pages_process(void *heap, void* stack);

void*
duplicatePage(void *address);

#endif

