#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tipos.h"
#include "validacion.h"
#include "error.h"
#include "carga.h" 
#include "eliminar.h"
#include "lista.h"


int main(int argc, char *argv[]) 
{

    int cant_archivos;
    status_t status; 
    char **archivos;
    output_t output;
    char filtro[MAX_STR];
    red_t *red = NULL;


    status = validacion_cla(argc, argv, &cant_archivos, &archivos, &output, filtro);
    if (status != OK) {
        imprimir_errores(status); 
        return EXIT_FAILURE;
    }

    status = cargar_red(archivos, cant_archivos, &red); 

    if(status != OK)
    {

        imprimir_errores(status);
        return EXIT_FAILURE;
    } 

    status = eliminar_usuario(&red, filtro, output);
    if(status != OK)
    {
        RED_destruir(&red);
        imprimir_errores(status);
        return EXIT_FAILURE;
    }


    RED_destruir(&red);

    return EXIT_SUCCESS;
}

