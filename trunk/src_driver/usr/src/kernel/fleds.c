#include "kernel.h"
#include <minix/com.h>

void
fleds_task()
{
	message mess;
	
	pritnf("soy el fleds");
	receive(ANY, &mess);
}
