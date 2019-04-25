#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "lista.h"


int main(void)
{
	lista_s lista;

	mensaje_s *mensaje1;
	mensaje_s *mensaje2;
	mensaje_s *mensaje3;

	mensaje1 = malloc(sizeof(mensaje_s));
	mensaje1->id_msj=1234;
	mensaje1->timestamp = time(NULL);
	mensaje1->id_usuario_mensaje=654;
	(mensaje1->texto)=(char*)malloc(100);
	mensaje1->texto="Mensaje de prueba 1";

	mensaje2 = malloc(sizeof(mensaje_s));
	mensaje2->id_msj=1236;
	mensaje2->timestamp = time(NULL);
	mensaje2->id_usuario_mensaje=651;
	(mensaje2->texto)=(char*)malloc(100);
	mensaje2->texto="Mensaje de prueba 2";

	mensaje3 = malloc(sizeof(mensaje_s));
	mensaje3->id_msj=1237;
	mensaje3->timestamp = time(NULL);
	mensaje3->id_usuario_mensaje=621;
	(mensaje3->texto)=(char*)malloc(100);
	mensaje3->texto="Mensaje de prueba 3";

	LISTA_crear(&lista);
	puts("Lista creada");

	if(LISTA_vacia(lista))
		puts("Lista Vacia");

	LISTA_crear_nodo(&lista, mensaje1);
	puts("Agregado nodo");

	if(LISTA_vacia(lista))
		puts("Lista Vacia");
	else{
		puts("Lista no vacia");
	}

	puts("Recorremos la lista: ");
	LISTA_recorrer(lista, NULL, &(funcion_imprimir));

	puts("Insertamos al principio otro mensaje");
	LISTA_insertar_ppio(&lista, mensaje2);

	puts("Recorremos nuevamente la lista");
	LISTA_recorrer(lista, NULL, &(funcion_imprimir));

	puts("Insertamos al final otro mensaje");
	LISTA_insertar_final(&lista, mensaje3);

	puts("Recorremos nuevamente la lista");
	LISTA_recorrer(lista, NULL, &(funcion_imprimir));

	puts("Destruimos la lista entera");
	LISTA_destruir(&lista, &(destructor));

	if(LISTA_vacia(lista))
	{
		puts("Lista vacia\n");
	}

	return EXIT_SUCCESS;
}