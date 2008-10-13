#include "defs.h"

#ifndef _grub_multiboot_
#define _grub_multiboot_

#define MAX_SIZE_BLOCK_MEM 40000000

/* Informacion extraida de http://www.gnu.org/software/grub/manual/multiboot/multiboot.html */

typedef struct mmapT
{
       unsigned long size;
       unsigned long base_addr_low;
       unsigned long base_addr_high;
       unsigned long length_low;
       unsigned long length_high;
       unsigned long type;
} mmapT;

typedef struct drivesT
{
	int size;
	unsigned char drive_number;
	unsigned char drive_mode;
	unsigned short int drive_cylinders;
	unsigned short int drive_heads;
	unsigned char drive_sectors;
	unsigned short int drive_ports;
} drivesT;

typedef struct amp_tableT
{
	unsigned short int version;
	unsigned short int cseg;
	unsigned short int offset;
	unsigned short int cseg_16;
	unsigned short int dseg;
	unsigned short int flags;
	unsigned short int len;
	unsigned short int cseg_16_len;
	unsigned short int dseg_len;
} amp_tableT;

typedef struct infoGrub
{
	// (required)
	int flags;			// (present if flags[0] is set)
	int mem_lower;			// lower memory in kb (starts in 0, max - 640kbytes)
	int mem_upper;			// upper memory in kb (starts at 1Mbyte)
	// (present if flags[1] is set)
	unsigned char boot_device[4];	// | part3 | part2 | part1 | device drive | 
	// (present if flags[2] is set)
	unsigned char * cmdline;	// NULL terminated parameters for the kernel
	// (present if flags[3] is set)
	int mods_count;			//what boot modules were loaded along with the kernel image
	int mods_addr;
	// (present if flags[4] or flags[5] is set)
	int syms[4];
	// (present if flags[6] is set)
	int mmap_length;		// The map provided is guaranteed to list all standard ram
	mmapT * mmap_addr;		//  that should be available for normal use
	// (present if flags[7] is set)
	int drives_length;		// size of first drive structure
	drivesT * drives_addr;		// first drive structure
	// (present if flags[8] is set)
	int config_table;		// BIOS GET CONFIGURATION call data
	// (present if flags[9] is set)
	unsigned char * boot_loader_name;	// NULL terminated boot loader name
	// (present if flags[10] is set)
	amp_tableT * apm_table;
	// (present if flags[11] is set)
	int vbe_control_info;		// graphics table
	int vbe_mode_info;
	int vbe_mode;
	int vbe_interface_seg;
	int vbe_interface_off;
	int vbe_interface_len;
} infoGrub;

/* set_multiBoot
*  setea la zona donde el grub devuelve 
*  la estructura de informacion
*
*  Recibe como parametros:
*  - infoStruct: direccion de memoria
*/
void set_multiBoot(unsigned long infoStruct);

/* showMem
*  Muestra la informacion de memoria
*
*/
int showMem(void);

/* showMem
*  Muestra la informacion de booteo
*
*/
int show_multiBoot();

/* getBlockMem
*  Devuelve la zona maxima contigua donde
*  se puede inicializar la memoria dinamica
*
*  Recibe como parametros:
*  - void **: direccion a donde poner el comienzo
* 	      de bloque
*  - int *: direccion a donde poner el espacio 
*           disponible
*/
int getBlockMem(void **, int *);

#endif

