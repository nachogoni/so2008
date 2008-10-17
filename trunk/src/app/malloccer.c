#include "malloccer.h"
#include "../../include/strings.h"
#include "../../include/io.h"
#include "../../include/memory.h"

int malloccer(void) {
	void *aux;

	while((aux =malloc(400)) != NULL) {
		printf("Pedi 400 bytes y se me asigna la posicion %d\n", aux);
	}
	if(aux == NULL) {
		printf("Pedi 400 bytes y no se me asigna nada, no hay mas memoria\n");
	}
	return 0;
}

