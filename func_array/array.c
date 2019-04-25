#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "array.h"

struct amigo
{
	size_t *amigos;
	size_t cant_amigos;
};


retval_t VECTOR_crear(vector_s *vector)
{
   
    if(vector == NULL)
    {
        return RV_ILLEGAL;
    }
   
    if((*vector = malloc(sizeof(struct amigo))) == NULL)
    {
        return RV_NOMEM;
    }
   
    (*vector)->amigos = NULL;
    (*vector)->cant_amigos = 0;
   
    return RV_SUCCESS;
}
 
retval_t VECTOR_vacio(vector_s vector)
{
    if(!vector->cant_amigos)
    {
        return RV_SUCCESS;
    }
   
    return RV_EMPTY;
}
 
retval_t VECTOR_insertar(vector_s vector, int dato)
{
    size_t *ptr;
   
    if(vector == NULL)
    {
        return RV_ILLEGAL;
    }
   
    if(!vector->cant_amigos)
    {
        if((vector->amigos = malloc(sizeof(size_t))) == NULL)
        {
            return RV_NOMEM;
        }
    } else {
       
        if((ptr = realloc(vector->amigos, sizeof(size_t) + 1)) == NULL)
        {
            return RV_NOMEM;
        }
       
        vector->amigos = ptr;
 
    }
   
    vector->amigos[vector->cant_amigos] = dato;
    vector->cant_amigos++;

    return RV_SUCCESS;
       
}
 
retval_t VECTOR_destruir(vector_s *vector, void (*destructor)(void *))
{
    if(vector == NULL)
    {
        return RV_ILLEGAL;
    }
   
    destructor(*vector);
   
    free(*vector);
    *vector = NULL;

    return RV_SUCCESS;
}

retval_t VECTOR_recorrer(vector_s vector, void (*funcion_imprimir)(void *, void *))
{

    size_t i;

    for(i = 0; i < vector->cant_amigos; i++)
    {

        funcion_imprimir(NULL, &(vector->amigos[i]));

    }

    return RV_SUCCESS;

}


void destructor(void* dato)
{
	free(dato);
	dato=NULL;
}

void funcion_imprimir(void * arg, void *dato)
{

    if(arg == NULL)
    {
        printf("%d ",*((size_t *)dato));
    }

}