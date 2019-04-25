#ifndef VALIDACION__H
#define VALIDACION__H

#include <stdio.h>
#include <stdlib.h>
#include "tipos.h"

/*CLA*/
#define MIN_ARG 6
#define INICIO_CARGA_ARCHIVO "["
#define FIN_CARGA_ARCHIVO ']'
#define OPCION_ELIMINAR_POSICION 1
#define OPCION_ELIMINAR "--eliminar"
#define OPCION_FILTRO_POSICION	2
#define OPCION_FILTRO_SEPARADOR	":"
#define OPCION_FILTRO_ID "i"
#define OPCION_FILTRO_USUARIO "u"
#define OPCION_ELIMINAR_ABREV "-e"
#define OPCION_OUTPUT_POSICION 3
#define OPCION_OUTPUT "--output"
#define OPCION_OUTPUT_ABREV "-o"
#define POSICION_PRIMER_ARCHIVO 5
#define POSICION_OUTPUT_FILE 4
#define OPCION_OUTPUT_1 "single"
#define OPCION_OUTPUT_2 "multi"


#define INIT 1
#define MAX_STR 300


status_t validacion_cla(int argc, char **argv, int *cant_archivos, char ***archivos, output_t *output, char filtro[]);
bool_t es_filtro_correcto(const char *filtro);


#endif