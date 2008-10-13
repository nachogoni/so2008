#include "../include/kc.h"
#include "../include/io.h"

void
showSplashScreen()
{
	k_clear_screen();

	printf("                                                                                 ");
	printf("\n                                        xXXXXXXXXXx   xXXXXXXXXXx              ");
	printf("\n                                            XXX           XXX                  ");
	printf("\n                                             XXX         XXX                   ");
	printf("\n                                              XXX       XXX                    ");
	printf("\n   HHH    HHH  UUU    UUU  MMM    MMM  III     XXX     XXX                     ");
	printf("\n   HHH    HHH  UUU    UUU  MMM    MMM  III      XXX   XXX                      ");
	printf("\n   HHH    HHH  UUU    UUU  MMMM  MMMM  III       XXX XXX                       ");
	printf("\n   HHH    HHH  UUU    UUU  MMMMMMMMMM  III        XXXXX                        ");
	printf("\n   HHHHHHHHHH  UUU    UUU  MMM MM MMM  III         XXX                         ");
	printf("\n   HHHHHHHHHH  UUU    UUU  MMM    MMM  III        XXXXX                        ");
	printf("\n   HHH    HHH  UUU    UUU  MMM    MMM  III       XXX XXX                       ");
	printf("\n   HHH    HHH  UUU    UUU  MMM    MMM  III      XXX   XXX                      ");
	printf("\n   HHH    HHH  UUUUUUUUUU  MMM    MMM  III     XXX     XXX                     ");
	printf("\n   HHH    HHH  UUUUUUUUUU  MMM    MMM  III    XXX       XXX                    ");
	printf("\n                                             XXX         XXX    Milenium       ");
	printf("\n                                            XXX           XXX       Version    ");
	printf("\n                                           XXX             XXX                 ");
	printf("\n                                       xXXXXXXXXXx     xXXXXXXXXXx             ");
	printf("\n   Includes: 12 Vitamins & Minerals                                           \n");
}

void
wait(int time)
{
	int i;
	
	for(i=0;i<time*100000;i++)
	;

}

/***************************************************************
*k_clear_screen
*
* Borra la pantalla en modo texto color.
****************************************************************/

void k_clear_screen() 
{
	char *vidmem = (char *) 0xb8000;
	unsigned int i=0;
	while(i < (80*25*2))
	{
		vidmem[i]=' ';
		i++;
		vidmem[i]=WHITE_TXT;
		i++;
	};
}

/***************************************************************
*setup_IDT_entry
* Inicializa un descriptor de la IDT
*
*Recibe: Puntero a elemento de la IDT
*	 Selector a cargar en el descriptor de interrupcion
*	 Puntero a rutina de atencion de interrupcion	
*	 Derechos de acceso del segmento
*	 Cero
****************************************************************/

void setup_IDT_entry (DESCR_INT *item, byte selector, dword offset, byte access,
			byte cero)
{
	item->selector = selector;
	item->offset_l = offset & 0xFFFF;
	item->offset_h = offset >> 16;
	item->access = access;
	item->cero = cero;
}


