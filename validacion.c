#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tipos.h"
#include "validacion.h"
#include "utilities.h"


status_t validacion_cla(int argc, char *argv[], int *cant_archivos, char ***archivos, output_t *output, char filtro[]) {
    int i;
    char *aux;
    char *ret;

    /*Deben haber por lo menos 6 argumentos ingresados al CLA*/
    if (argc < MIN_ARG)
    {
        return ERROR_CLA_CANT_ARG;
    }


    /*Validacion de flag eliminar*/
    if ((strcmp(argv[OPCION_ELIMINAR_POSICION], OPCION_ELIMINAR) != 0) && (strcmp(argv[OPCION_ELIMINAR_POSICION], OPCION_ELIMINAR_ABREV) != 0))
    {

        return ERROR_CLA_FLAG;
    }

    /*Validacion de flag output*/
    if ((strcmp(argv[OPCION_OUTPUT_POSICION], OPCION_OUTPUT) != 0) && (strcmp(argv[OPCION_OUTPUT_POSICION], OPCION_OUTPUT_ABREV) != 0))
    {
        return ERROR_CLA_FLAG;
    }

    /*Verificacion si se ingreso la opcion single o multi*/
    if ((strcmp(argv[POSICION_OUTPUT_FILE], OPCION_OUTPUT_1)) != 0 && (strcmp(argv[POSICION_OUTPUT_FILE], OPCION_OUTPUT_2)) != 0)
   	{

        return ERROR_OPCION_OUTPUT;
    }

    if(!strcmp(argv[POSICION_OUTPUT_FILE], OPCION_OUTPUT_1))
    {
    	*output = SINGLE;
    } 
    else 
    {
    	*output = MULTI;
    }

    if(es_filtro_correcto(argv[OPCION_FILTRO_POSICION]))
    {
    	strcpy(filtro, argv[OPCION_FILTRO_POSICION]);
    }
    else
    {
    	return ERROR_OPCION_FILTRO;
    }

    /*Validacion de archivos*/
    *cant_archivos = (argc - MIN_ARG) + INIT;

    *archivos = (char**) malloc(sizeof (char*));
    for (i = 0; i < *cant_archivos; i++) 
    {
        *archivos = (char**) realloc(*archivos, sizeof (char*)*(i + 1));
        (*archivos)[i] = (char*) malloc(sizeof (char)*MAX_STR);

        aux = strtok(argv[POSICION_PRIMER_ARCHIVO + i], INICIO_CARGA_ARCHIVO);


        /* Ultima posición */
        if(POSICION_PRIMER_ARCHIVO + i == (argc-1))
        {

        	/* Tendremos i corchetes + 1 para borrar */
        	ret = strchr(aux, FIN_CARGA_ARCHIVO);
        	*ret = '\0';

        }


        strcpy((*archivos)[i], aux);

    }

    return OK;
}

bool_t es_filtro_correcto(const char *filtro)
{

	char aux[MAX_STR] = {'\0'};
	char *token;
	char flag_usuario = FALSE;

	/* flag = FALSE => id else => usuario */

	/* buffer overflow */
	if(strlen(filtro) > MAX_STR)
	{
		return FALSE;
	}

	strcpy(aux, filtro);


	token = strtok(aux, OPCION_FILTRO_SEPARADOR);


	if(token == NULL)
	{
		return FALSE;
	}

	if(strcmp(token, OPCION_FILTRO_ID) && strcmp(token, OPCION_FILTRO_USUARIO))
	{
		return FALSE;
	} 

	if(!strcmp(token, OPCION_FILTRO_USUARIO))
	{
		flag_usuario = TRUE;
	}

	if( (token = strtok(NULL, OPCION_FILTRO_SEPARADOR)) == NULL)
	{
		return FALSE;
	}


	if(!flag_usuario)
	{
		if(!is_number(token))
		{
			return FALSE;
		}
	}

	return TRUE;
}

