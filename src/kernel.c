#include "../include/kasm.h"
#include "../include/defs.h"
#include "../include/grubInfo.h"
#include "../include/kc.h"
#include "../include/fd.h"
#include "../include/strings.h"
#include "../include/io.h"
#include "../include/ipc.h"
#include "../include/kernel.h"
#include "../include/memory.h"
#include "../include/shell.h"
#include "../include/drivers/keyboard.h"
#include "../include/pagination.h"
#include "../include/drivers/tty.h"
#include "../include/processes.h"
#include "./app/top.h"

#define CHECK_FLAG(flags,bit)   ((flags) & (1 << (bit)))

/******************** VARIABLE EXTERNAS AL SISTEMA ************************/

/* FILE DESCRIPTIRS */
extern file_descriptors fds;

/****************** FIN VARIABLE EXTERNAS AL SISTEMA **********************/


/********************* VARIABLE GLOBALES DE SISTEMA ***********************/

int shutdown_pc = 0;
int reboot_pc = 0;

/* IDT de 0x80h entradas*/
DESCR_INT idt[0x81];

/* IDTR */
IDTR idtr;					

/* Usuario activo del sistema */
int active_user;

/* fd default de salida */
int stdout;

/* fd default de entrada */
int stdin;

/* fd default del puerto serial */
int stdser;

/***************** FIN VARIABLE GLOBALES DE SISTEMA ***********************/

void int_09(void)
{
	handle_keyboard();
	return;
}

void int_0c(void) 
{
//	handle_serial();
	return;
}

/* __read
*
* Recibe como parametros:
* - File Descriptor
* - Buffer a escribir
* - Cantidad
*
**/
size_t
__read(int fd, void* buffer, size_t count) 
{
	size_t i = 0;
	int s_read = 0;

	if (fd<0 || buffer == NULL || count <=0)
		return 0;

	//Ejecuto el setbyte del fd siempre y cuando este activo
	if (fds.actives[fd].getByte == NULL)
		return 0;

	do
	{
		s_read = fds.actives[fd].getByte( (int *) ((unsigned char *)buffer)+i );
		if (s_read)
			i++;
	} while((i<count) && s_read);

	return i;
}


/* __write
*
* Recibe como parametros:
* - File Descriptor
* - Buffer del source
* - Cantidad
*
**/
size_t  
__write(int fd, const void* buffer, size_t count) 
{
	size_t i = 0;
	int exit = 0;

	if (fd<0 || buffer == NULL || count <=0)
		return 0;

	//Ejecuto el setbyte del fd siempre y cuando este activo
	if (fds.actives[fd].setByte == NULL)
		return 0;
	
	while(i<count && !exit)
		exit=fds.actives[fd].setByte( (int) ((char*)buffer)[i++] );

	return i;
}

int __wait(void)
{
	return getResponse();
}

unsigned int __exec_(int (*fn)(int ,int ,char *), char * process_name, char * parameters, int tty_id, void (*ret_fn)(void))
{
	if (fn == NULL || process_name == NULL || ret_fn == NULL)
		return NONE_PROC;
	
	return createProcess(fn, process_name, parameters, tty_id, ret_fn);
}

unsigned int __exec(int (*fn)(int ,int ,char *), char * process_name, char * parameters)
{
	return __exec_(fn, process_name, parameters, getProcessTTY(), &kernel_return_Function_no_unblock);
}

unsigned int __exec_wait(int (*fn)(int ,int ,char *), char * process_name, char * parameters)
{
	unsigned int resp = 0;
	resp = __exec_(fn, process_name, parameters, getProcessTTY(), &kernel_return_Function_unblock);
	block_process(PROC_CHILD_BLOQUED);
	return resp;
}

unsigned int __kill(int pid, int signal) {
	return _kill(pid, signal);
}
/***************/
/* EXCEPCIONES */
/***************/

int __div0 (void) {
	printf("Divide by Zero Exception\n");
	killCurrent();
	return 0;
}

int __pgf (void) {
	printf("Page Fault\n");
	killCurrent();
	return 0;
}
int __invop (void) {
	printf("Invalid OPcode Exception\n");
	killCurrent();
	return 0;
}
int __gpf (void) {
	printf("General Protection Fault \n");
	killCurrent();
	return 0;
}
int __ssf (void) {
	printf("Stack Segment not Present Exception\n");
	killCurrent();
	return 0;
}
int __bounds (void) {
	printf("Out of Bounds Exception\n");
	killCurrent();
	return 0;
}

unsigned int __set_priority(unsigned int pid, int priority)
{
	set_pid_priority(pid, priority);
	return 0;
}

int __set_scheduler(int scheduler_id)
{
	_set_scheduler(scheduler_id);
	return 0;
}

int sysStat(int ppid, int pid, char * parameters) {
	while(1) {
		sleep(1);
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		tty_set_position(0,0);
		//tty_clear_scr();
		printf("\nSystem Status\n\n");
		top2(ppid,pid,parameters);
	}
}
void init(void)
{
	printf("Initializing multitasking services...\t");

	createIdle();
	
	__exec_(&init_shell, "shell", "", 0, &kernel_return_Function_no_unblock);
	__exec_(&init_shell, "shell", "", 1, &kernel_return_Function_no_unblock);
	__exec_(&init_shell, "shell", "", 2, &kernel_return_Function_no_unblock);
	__exec_(&init_shell, "shell", "", 3, &kernel_return_Function_no_unblock);
	__exec_(&init_shell, "shell", "", 4, &kernel_return_Function_no_unblock);
	__exec_(&init_shell, "shell", "", 5, &kernel_return_Function_no_unblock);
	__exec_(&sysStat, "System Status", "", 6, &kernel_return_Function_no_unblock);

//	__exec_(&a, "f_a", "", 6, &kernel_return_Function_no_unblock);
//	__exec_(&b, "f_b", "", 6, &kernel_return_Function_no_unblock);
//	__exec_(&c, "f_c", "", 6, &kernel_return_Function_no_unblock);
//	__exec_(&d, "f_d", "", 6, &kernel_return_Function_no_unblock);
	
	tty_set_color(SCREEN_FORE_VIOLET, SCREEN_BACK_BLACK);
	printf("[ ");
	tty_set_color(SCREEN_FORE_GREEN2, SCREEN_BACK_BLACK);
	printf("OK");
	tty_set_color(SCREEN_FORE_VIOLET, SCREEN_BACK_BLACK);
	printf(" ]\n");
	tty_set_color(SCREEN_FORE_WHITE, SCREEN_BACK_BLACK);
	
	return;
}

/**********************************************
kmain() 
Punto de entrada de codigo C.
*************************************************/

void kmain(unsigned long infoStruct, unsigned long magicNumber) 
{
	/******************** CONFIGURACION DEL SO *************************/

	/* CARGA DE IDT CON LA RUTINA DE ATENCION DE IRQ0 - Timer Tick */
	setup_IDT_entry (&idt[0x08], 0x08, (dword)&int_08_hand, ACS_INT, 0);
	/* CARGA DE IDT CON LA RUTINA DE ATENCION DE IRQ1 - Keyboard */
	setup_IDT_entry (&idt[0x09], 0x08, (dword)&int_09_hand, ACS_INT, 0);	
	/* CARGA DE IDT CON LA RUTINA DE ATENCION DE IRQ1 - serial */
	setup_IDT_entry (&idt[0x0c], 0x08, (dword)&int_0c_hand, ACS_INT, 0);
	/* CARGA DE IDT CON LA RUTINA DE ATENCION DE 80h */
	setup_IDT_entry (&idt[0x80], 0x08, (dword)&int_80_hand, ACS_INT, 0);

	/* CARGA DE IDT CON LA RUTINA DE ATENCION DE LA EXCEPCION DIVIDE BY 0 */
	setup_IDT_entry (&idt[0x00], 0x08, (dword)&div0_hand, ACS_INT, 0);
	/* CARGA DE IDT CON LA RUTINA DE ATENCION DE LA EXCEPCION INVALID OPCODE */
	setup_IDT_entry (&idt[0x06], 0x08, (dword)&invop_hand, ACS_INT, 0);	
	/* CARGA DE IDT CON LA RUTINA DE ATENCION DE LA EXCEPCION GENERAL PROTECTION FAULT */
	setup_IDT_entry (&idt[0x0D], 0x08, (dword)&gpf_hand, ACS_INT, 0);	
	/* CARGA DE IDT CON LA RUTINA DE ATENCION DE LA EXCEPCION PAGE FAULT */
	setup_IDT_entry (&idt[0x0E], 0x08, (dword)&pgf_hand, ACS_INT, 0);
	/* CARGA DE IDT CON LA RUTINA DE ATENCION DE LA EXCEPCION OUT OF BOUNDS */
	setup_IDT_entry (&idt[0x05], 0x08, (dword)&bounds_hand, ACS_INT, 0);

	/* Carga de IDTR    */
	idtr.base = 0;
	idtr.base +=(dword) &idt;
	idtr.limit = sizeof(idt)-1;
	
	_lidt (&idtr);	

	_Cli();

	/* Habilito interrupcion de timer tic, keyboard y puerto serial*/
	mascaraPIC1(0xEC);
	mascaraPIC2(0xFF);

	/* Seteo al usuario activo como user */
	active_user = U_KERNEL;

	/* inicializacion del fd */
	__init_fd();
	
	/* asignacion de fd's */
	/* TTY Video */
	set_fd(TTY, tty_init, tty_setByte, tty_getByte, tty_destroy);
	stdout = fd_open(TTY);
	
	/* Keyboard */
	set_fd(KEYBOARD, init_keyboard, NULL, keyboard_getChar, close_keyboard);
	stdin = fd_open(TTY);

	/* Serial */
	//set_fd(SERIAL, init_serial, serial_setChar, serial_getChar, close_serial);
	//stdser=fd_open(SERIAL);

	/* Muestra la informacion que entrega el grub  */
	set_multiBoot(infoStruct);
	//show_multiBoot();

	/******************** INICIALIZACION DE MEMORIA ********************/
 	void* memory;
 	int memory_size;

	/* Si puedo asignar los bloques - devuelve memory_size 0 si no puede */
 	getBlockMem(&memory,&memory_size);

 	//Inicializo la paginacion en 2mb
	__init_pagination((unsigned long **) KERNEL_PAGE_DIRECTORY, (unsigned long *) KERNEL_TABLE_DIRECTORY, KERNEL_MEM_SIZE, USER_MEM_SIZE);

	//Inicializo la zona de malloc del kernel
	__init_memory((void*)KERNEL_MALLOC_ADDRESS, KERNEL_MALLOC_SIZE);

	//Inicializo shared memory
	__init_ipcs();

	//Inicializo semaforos
	__init_sem();

	/******************** FIN CONFIGURACION DEL SO *************************/

	/* Pantalla de inicio */
	//init_presents(OS_PID, OS_PID+1, NULL);
	//showSplashScreen();

	/* Seteo al usuario activo como user */
	active_user=U_NORMAL;

	/******************** INICIO DE ZONA LIBRE *************************/

	// Proceso base
	init();
	
	_Sti();
	

	while(!shutdown_pc && !reboot_pc)
		asm volatile ("hlt");

	_Cli();

	tty_set_active(0);
	
	printf("\n\n\n\nSystem is shutting down... OK\n");
	
	/******************** FINALIZACION DEL SO *************************/

	//fd_close(SERIAL);
	fd_close(KEYBOARD);
	fd_close(TTY);

/*
	if (shutdown_pc)
		shutdown();
	if (reboot_pc)
		_reboot();
*/
}

