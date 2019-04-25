#ifndef UTILITIES__H
#define UTILITIES__H

#include <stdio.h>
#include <stdlib.h>

#include "tipos.h"

#define CHOP_SIZE 256

bool_t linea_vacia(cadena_t cadena);
retval_t readline(FILE *f, cadena_t *linea, bool_t *fin_archivo);
retval_t split(const cadena_t cadena, char delimitador, char*** arreglo, size_t* l);
char* strdup(const char *sc);
char* left_trim(const char *sc);
char* right_trim(const char *sc);
char* full_trim(const char* sc);
void destruir_arreglo_cadenas(char*** arreglo_de_cadenas, size_t cant_de_cadenas);
bool_t is_number(char *number);

#endif