#ifndef ELIMINAR__H
#define ELIMINAR__H

#include <stdio.h>
#include "tipos.h"

#define OPCION_FILTRO_SEPARADOR	":"
#define OPCION_FILTRO_ID "i"

#define STRING_ID "id"
#define STRING_NOMBRE "nombre"



typedef struct filtro {
	cadena_t key;
	void *value;
} filtro_t;

typedef enum key
{
	ID,
	USUARIO

} key_t;


status_t eliminar_usuario(red_t **red, char filtro[], output_t output);
void eliminar(usuario_t **pusuario);
char* strdup(const char *sc);
void imprimir_single_output(red_t *red);
status_t imprimir_multi_output(red_t *red);
void RED_destruir(red_t **red);


#endif