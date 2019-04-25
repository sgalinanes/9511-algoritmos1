#include <stdio.h>
#include <stdlib.h>

typedef enum{
	FALSE,
	TRUE
} bool_t;

typedef enum{
	RV_ILLEGAL,
	RV_SUCCESS,
	RV_NOMEM,
	RV_EMPTY
} retval_t;

struct amigo;
typedef struct amigo *vector_s;

typedef char* cadena_t;

retval_t VECTOR_crear(vector_s *vector);
retval_t VECTOR_vacio(vector_s vector);
retval_t VECTOR_insertar(vector_s vector, int dato);
retval_t VECTOR_destruir(vector_s *vector, void (*destructor)(void *));
retval_t VECTOR_recorrer(vector_s vector, void (*funcion_imprimir)(void *, void *));
 
void destructor(void* dato);
void funcion_imprimir(void *arg, void *dato);