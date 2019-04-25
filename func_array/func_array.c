#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "array.h"


int main(void)
{
	vector_s amigos = NULL;

	printf("Creamos un nuevo vector\n");
	VECTOR_crear(&amigos);

	if(VECTOR_vacio(amigos))
	{
		printf("El vector se encuentra vacio\n");
	}

	printf("Insertamos valores en el vector\n");
	VECTOR_insertar(amigos, 5);
	VECTOR_insertar(amigos, 4);

	
	printf("Impresion de los valores insertados\n");
	VECTOR_recorrer(amigos, &(funcion_imprimir));
	printf("\n");
	

	printf("Destruimos el vector");
	VECTOR_destruir(&amigos, &(destructor));


	return EXIT_SUCCESS;
}