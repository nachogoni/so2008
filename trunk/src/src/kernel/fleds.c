#include "kernel.h"
#include <termios.h>
#include <sys/ioctl.h>
#include <minix/callnr.h>
#include <minix/com.h>
#include <sys/types.h>
#include "proc.h"
#include "fleds.h"

FORWARD _PROTOTYPE( void send_serial, (int data)		);
FORWARD _PROTOTYPE( void do_open, (void) );
FORWARD _PROTOTYPE( void do_close, (void) );
FORWARD _PROTOTYPE( void do_write, (message *m_ptr) );
FORWARD _PROTOTYPE( void do_read, (message *m_ptr) );
FORWARD _PROTOTYPE( void fleds_init, (void) );
FORWARD _PROTOTYPE( void reply, (int code, int replyee, int process,
		int status) );

FORWARD _PROTOTYPE( int setParity, (int parity, int odd) );
FORWARD _PROTOTYPE( int setInterrupt, (int on) );
FORWARD _PROTOTYPE( int setMCR, (void) );
FORWARD _PROTOTYPE( int setbps, (serialSpeedT speed) );
FORWARD _PROTOTYPE( int setStop, (int stopBit)  );
FORWARD _PROTOTYPE( int setBitCount, (int bitCount) );
FORWARD _PROTOTYPE( int doReset, (void) );
FORWARD _PROTOTYPE( int fleds_handler, (int irq) );
FORWARD _PROTOTYPE( int add_buffer,(int data) );
FORWARD _PROTOTYPE( char get_buffer,(void) );
FORWARD _PROTOTYPE( int bufferNotFull, (void) );
FORWARD _PROTOTYPE( int bufferNotEmpty, (void) );

typedef struct {
	unsigned char LCR;
	unsigned char DLL;
	unsigned char DLM;
	unsigned char MCR;
	unsigned char IER;
} serialStateT;

PRIVATE serialStateT serialState;

PRIVATE int initialized = 0;

PRIVATE int commBase = COMM1_BASE;

typedef struct 
{
	int buffer[FLEDS_BUFFER_SIZE];
	int write;
	int read;
	int qty;
}fledsBufferT;

fledsBufferT k_buffer;

PRIVATE int bufferNotEmpty () {
	return (k_buffer.qty != 0);
}

PRIVATE int bufferNotFull () {
	return (k_buffer.qty < FLEDS_BUFFER_SIZE);
}


PUBLIC void fleds_task()
{
	message mess;
	int status;

	/* inicializo el fleds */
	fleds_init();

	while(1) 
	{
		receive(ANY, &mess);
		switch(mess.m_type)
		{
			case DEV_OPEN:		
				do_open();
				reply(TASK_REPLY, mess.m_source, mess.PROC_NR, OK);
				break;
			case DEV_WRITE:		
				do_write(&mess); 
				break;
			case DEV_READ:		
				do_read(&mess);	 
				break;
			case DEV_CLOSE:
				do_close();	 
				reply(TASK_REPLY, mess.m_source, mess.PROC_NR, OK);
				break;
			case DEV_IOCTL:
				reply(TASK_REPLY, mess.m_source, mess.PROC_NR, OK);
				break;
			case HARD_INT:				 break;
		}
		
	}
		
}

/*===========================================================================*
 *				do_write				     *
 *===========================================================================*/

PRIVATE void do_write(m_ptr)
register message *m_ptr;	/* pointer to the newly arrived message */
{

	register int r;
	int i, count=0;
	char obuf[FLEDS_BUFFER_SIZE];
	phys_bytes user_phys;

	/* Reject command if last write is not finished, count not positive, or
	* user address bad.
	*/

	if (m_ptr->COUNT <= 0) 
	{
		r = EINVAL;
	} 
	else
		if (numap(m_ptr->PROC_NR, (vir_bytes) m_ptr->ADDRESS, m_ptr->COUNT) == 0) 
		{
			r = EFAULT;
		} 
		else 
		{
			#if FLEDS_PING_ENABLE
			disable_irq(RS232_IRQ);
			#endif
			/* cantidad de bytes a copiar */
			count = m_ptr->COUNT;
			/* obtengo  la direccion fisica del puntero enviado */
			user_phys = proc_vir2phys(proc_addr(m_ptr->PROC_NR), (vir_bytes) m_ptr->ADDRESS);
			/* copio los datos a una posicion local */
			phys_copy(user_phys, vir2phys(obuf), (phys_bytes) count);
			/* envio al serial */
			for (i=0; i < count; i++)
				send_serial(obuf[i]);
			#if FLEDS_PING_ENABLE
			enable_irq(RS232_IRQ);
			#endif
			r = OK;
		}

	reply(TASK_REPLY, m_ptr->m_source, m_ptr->PROC_NR,r);
}


/*===========================================================================*
 *				do_read				     *
 *===========================================================================*/

PRIVATE void do_read(m_ptr)
register message *m_ptr;	/* pointer to the newly arrived message */
{

	register int r;
	int i, count=0;
	char orBuf[FLEDS_BUFFER_SIZE];
	phys_bytes user_phys;

	/* Reject command if last write is not finished, count not positive, or
	* user address bad.
	*/

	if (m_ptr->COUNT <= 0) 
	{
		r = EINVAL;
	} 
	else
		if (numap(m_ptr->PROC_NR, (vir_bytes) m_ptr->ADDRESS, m_ptr->COUNT) == 0) 
		{
			r = EFAULT;
		} 
		else 
		{
			#if FLEDS_PING_ENABLE
			disable_irq(RS232_IRQ);
			#endif
			/* cantidad de bytes a copiar */
			count = m_ptr->COUNT;
			/* obtengo  la direccion fisica del puntero enviado */
			user_phys = proc_vir2phys(proc_addr(m_ptr->PROC_NR), (vir_bytes) m_ptr->ADDRESS);
			/* copio  los datos del buffer a una variable local (por que el buffer es ciclico */
			for (i=0; i < count; i++)
				orBuf[i]=get_buffer();
			/* copio los datos a la posicion fisica del usuario */
			phys_copy(vir2phys(orBuf), user_phys, (phys_bytes) count);
			#if FLEDS_PING_ENABLE
			enable_irq(RS232_IRQ);
			#endif
			r = OK;
		}

	reply(TASK_REPLY, m_ptr->m_source, m_ptr->PROC_NR,r);
}


/*===========================================================================*
 *				setInterrupt 	 			     *
 *===========================================================================*/

PRIVATE int setInterrupt(on)
int on;
{
	unsigned char ie = 0;	
	
	if (on)
		ie = 0x01;

	out_byte(commBase + 3, serialState.LCR & 0x7F);
        out_byte(commBase + 1, ie); 
	out_byte(commBase + 3, serialState.LCR);
		 
	return 1;	 
}
/*===========================================================================*
 *				setParity 	 			     *
 *===========================================================================*/

PRIVATE int setParity(parity, odd)
int parity;
int odd;
{
	unsigned char p = 0;

	if (parity)
	{
		p |= 0x08;
		if (!odd)
			p |= 0x10;
	}	
	
	serialState.LCR = (serialState.LCR & 0xE7) | p;
	
	out_byte(commBase + 3, serialState.LCR);

	return 1;
}

/*===========================================================================*
 *				setMCR	 	 			     *
 *===========================================================================*/

PRIVATE int setMCR()
{
	out_byte(commBase + 4, 0x08);
	return 1; 
}

/*===========================================================================*
 *				setbps	 	 			     *
 *===========================================================================*/

PRIVATE int setbps(speed)
serialSpeedT speed;
{
	char speedReg[][2] = { {0x00, 0x09}, {0x80, 0x01}, {0x60, 0x00}, {0x30, 0x00},
	{0x18, 0x00}, {0x0C, 0x00}, {0x06, 0x00}, {0x03, 0x00}, {0x02, 0x00}, {0x01, 0x00}};
	
	out_byte(commBase + 3, serialState.LCR | 0x80);
	out_byte(commBase + 0, serialState.DLL = speedReg[speed][0]);
	out_byte(commBase + 1, serialState.DLM = speedReg[speed][1]);
	out_byte(commBase + 3, serialState.LCR);
		 
	return 1;	 
}

/*===========================================================================*
 *				setStop 	 			     *
 *===========================================================================*/

PRIVATE int setStop(stopBit)
int stopBit;
{
	unsigned char s = 0;
	
	if (stopBit)
		s = 0x04;
	
	serialState.LCR = (serialState.LCR & 0xFB) | s;
	
	out_byte(commBase + 3, serialState.LCR);

	return 1;
}

/*===========================================================================*
 *				setBitCount 	 			     *
 *===========================================================================*/

PRIVATE int setBitCount(bitCount)
int bitCount;
{
	if (bitCount >= 5 && bitCount <= 8)
		bitCount -= 5;
	
	serialState.LCR = (serialState.LCR & 0xFC) | bitCount;
	
	out_byte(commBase + 3, serialState.LCR);

	return 1;
}

PRIVATE int doReset()
{
	out_byte(commBase + 3, serialState.LCR & 0x7F);
        out_byte(commBase + 2, 0x06); 
	out_byte(commBase + 3, serialState.LCR);
		 
	return 1;	 
}



/*===========================================================================*
 *				fleds_init 	 			     *
 *===========================================================================*/

PRIVATE void fleds_init()
{
	doReset();

	/*  inicializo las variables a usar */
	serialState.LCR = 0;
	serialState.DLL = 0;
	serialState.DLM = 0;
	serialState.MCR = 0;
	serialState.IER = 0;
	/* Inicializo las variables del buffer */
	k_buffer.write = 0;
	k_buffer.read = 0;
	k_buffer.qty = 0;


	setInterrupt(SERIAL_INT_E_OFF);
	setParity(SERIAL_PARITY_OFF,SERIAL_PARITY_ODD);
	setMCR();
	setbps(SERIAL_S_115200);
	setStop(SERIAL_STOP_1);
	setBitCount(8);

	/* si esta habilitado el ping lo uso */
	#if FLEDS_PING_ENABLE
	put_irq_handler(RS232_IRQ, fleds_handler);
	enable_irq(RS232_IRQ);
	#endif

	doReset();

	setInterrupt(SERIAL_INT_E_ON);

}



/*===========================================================================*
 *				add_buffer	 			     *
 *===========================================================================*/

PRIVATE int add_buffer(data)
int data;
{
	if( bufferNotFull() ) {
		k_buffer.buffer[k_buffer.write] = data;
		k_buffer.qty++;
		if ( ++(k_buffer.write) == FLEDS_BUFFER_SIZE) 
			k_buffer.write = 0;
		return 1;
	}
	return 0;
}

/*===========================================================================*
 *				get_buffer	 			     *
 *===========================================================================*/

PRIVATE char get_buffer()
{
	char data;

	if ( bufferNotEmpty() ) {
		k_buffer.qty--;
		data = k_buffer.buffer[k_buffer.read];
		if ( ++(k_buffer.read) == FLEDS_BUFFER_SIZE) 
					k_buffer.read = 0;
		return data;
	}
	return 0;
}


/*===========================================================================*
 *				fleds_handler  	 			     *
 *===========================================================================*/

PRIVATE int fleds_handler(irq)
int irq;
{
	char data;

	switch (data = in_byte(commBase)) 
	{
		#if FLEDS_PING_ENABLE
		case FLEDS_PING:
			send_serial(FLEDS_PONG);
			break;
		#endif
		default:
			add_buffer(data);
	}
	return(1);	/* reenable serial interrupt */
}


/*===========================================================================*
 *				do_open    	 			     *
 *===========================================================================*/

PRIVATE void do_open()
{
	return;
}

/*===========================================================================*
 *				do_close    	 			     *
 *===========================================================================*/

PRIVATE void do_close()
{
	return;
}


/*===========================================================================*
 *				reply					     *
 *===========================================================================*/

PRIVATE void reply(code, replyee, process, status)
int code;			/* TASK_REPLY or REVIVE */
int replyee;			/* destination for message (normally FS) */
int process;			/* which user requested the printing */
int status;			/* number of  chars printed or error code */
{
/* Send a reply telling FS that printing has started or stopped. */

  message pr_mess;

  pr_mess.m_type = code;	/* TASK_REPLY or REVIVE */
  pr_mess.REP_STATUS = status;	/* count or EIO */
  pr_mess.REP_PROC_NR = process;	/* which user does this pertain to */
  if ((status = send(replyee, &pr_mess)) != OK)
	panic("reply failed, status\n", status);
}


/*===========================================================================*
 *				send_serial	 			     *
 *===========================================================================*/

PRIVATE void send_serial(data)
int data;
{
	out_byte(commBase, data);
}

