#ifndef ARRAY__H
#define ARRAY__h

#include <stdio.h>
#include <stdlib.h>
#include "tipos.h"

retval_t VECTOR_crear(vector_s *vector);
retval_t VECTOR_vacio(vector_s vector);
retval_t VECTOR_insertar(vector_s vector, int dato);
retval_t VECTOR_destruir(vector_s *vector, void (*destructor)(void *));
retval_t VECTOR_recorrer(vector_s vector, void (*funcion_imprimir)(void *, void *));


void VECTOR_destructor(void* dato);
void VECTOR_funcion_imprimir(void * arg, void * dato);

#endif
 
