#ifndef LISTA__H
#define LISTA__H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tipos.h"

#define STRING_MENSAJE "mensaje"

typedef struct dato_mensaje{
	size_t id_msj;
    time_t timestamp;
    size_t id_usuario_mensaje; /*Puede no existir en la red*/
    cadena_t texto;
} mensaje_s;

retval_t LISTA_crear(lista_s *pl);
bool_t LISTA_vacia(lista_s pl);
retval_t LISTA_crear_nodo(lista_s *nodo, void *dato);
retval_t LISTA_destruir_nodo(lista_s *pnodo, void (*destructor)(void*));
retval_t LISTA_destruir(lista_s *pl, void (*destructor)(void*));
retval_t LISTA_insertar_ppio(lista_s *pl, void *d);
retval_t LISTA_insertar_final(lista_s *pl, void *d);
retval_t LISTA_insertar_decreciente(lista_s *pl, void *d, int(*cmp)(void*, void*));
void* LISTA_buscar(lista_s l, void* t, bool_t (*cmp)(void*, void*));
retval_t LISTA_recorrer(lista_s l, void *arg, void (*pf)(void*, void*));

void LISTA_destructor(void* dato);
void LISTA_funcion_imprimir(void * arg, void * dato);
void RED_imprimir(red_t *red);

#endif

