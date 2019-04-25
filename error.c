#include <stdio.h>

#include "tipos.h"
#include "error.h"


void imprimir_errores(status_t status) {

    FILE *fp;

    if ((fp = fopen(ARCHIVO_ERRORES, "a+")) == NULL)
        return;
    
    switch(status)
    {
        case ERROR_CLA_CANT_ARG:
            fprintf(stderr, "%s\n", MSJ_ERROR_CLA_CANT_ARG);
            break;

        case ERROR_CLA_FLAG:
            fprintf(stderr, "%s\n", MSJ_ERROR_CLA_FLAG);
            break;

        case ERROR_OPCION_OUTPUT:
            fprintf(stderr, "%s\n", MSJ_ERROR_OPCION_OUTPUT);
            break;

        case ERROR_ABRIR_ARCHIVO:
            fprintf(stderr, "%s\n", MSJ_ERROR_ABRIR_ARCHIVO);
            break;

        case ERROR_MEMORIA:
            fprintf(stderr, "%s\n", MSJ_ERROR_MEMORIA);
            break;

        case ERROR_OBTENCION_USUARIO:
            fprintf(stderr, "%s\n", MSJ_ERROR_OBTENCION_USUARIO);
            break;

        case ERROR_OPCION_FILTRO:
           fprintf(stderr, "%s\n", MSJ_ERROR_OPCION_FILTRO);
           break;

        case ERROR_USUARIO:
            fprintf(stderr, "%s\n", MSJ_ERROR_USUARIO);
            break;

        case ERROR_NULL:
            fprintf(stderr, "%s\n", MSJ_ERROR_NULL);
            break;

        case ERROR_RED:
            fprintf(stderr, "%s\n", MSJ_ERROR_RED);

        case ERROR_ELIMINAR_INEXISTENTE:
            fprintf(stderr, "%s\n", MSJ_ERROR_ELIMINAR_INEXISTENTE);

        default:
            break;
    }

    fclose(fp);
}