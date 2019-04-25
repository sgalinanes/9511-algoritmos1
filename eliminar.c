#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "tipos.h"
#include "utilities.h"
#include "eliminar.h"
#include "array.h"
#include "lista.h"

status_t eliminar_usuario(red_t **red, char filtro[], output_t output)
{
	
	filtro_t s_filtro;
	key_t key;
	char *token;
	int id;
	red_t *aux=NULL, *aux2;
	bool_t eliminado = FALSE;


	aux2 = *red;
	/* No hace falta validar el filtro, pues ya esta validado */
	token = strtok(filtro, OPCION_FILTRO_SEPARADOR);

	s_filtro.key = strdup(token);

	token = strtok(NULL, OPCION_FILTRO_SEPARADOR);


	if(is_number(token))
	{
		id = atoi(token);
		s_filtro.value = &id;
	}
	else
	{
		s_filtro.value = token;
	}

	if(!strcmp(s_filtro.key, OPCION_FILTRO_ID))
	{
		key = ID;
	} else {
		key = USUARIO;
	}

	for( ;(*red) != NULL; (*red) = (*red)->sig)
	{

	
		if(key == ID)
		{
			if( ((*red)->dato->id != *((int *)s_filtro.value)))
			{

				aux = *red;
				continue;

			}

		} else if(key == USUARIO)

		{
			if(strcmp((*red)->dato->usuario, (cadena_t)s_filtro.value))	 
			{
				aux = *red;
				continue;
				
			}
		}
		if((*red)->sig != NULL)
		{
		}

		
		if(output == SINGLE)
		{
			imprimir_single_output(*red);			
		}

		

		eliminar(&( (*red)->dato));

		eliminado = TRUE;

		if(aux == NULL && (*red)->sig == NULL)
		{
			aux2 = NULL;
		}
		else if(aux == NULL)
		{
			aux = (*red)->sig;
			(*red)->sig = NULL;
			aux2 = aux;

		} 
		else if (aux != NULL)
		{
			aux->sig = (*red)->sig;
			(*red)->sig = NULL;
		}

		free(*red);

		*red = aux2;

		if(output == MULTI)
		{
			imprimir_multi_output(*red);
		}

		break;

	}

	if(!eliminado)
	{
		return ERROR_ELIMINAR_INEXISTENTE;
	}
	return OK;


}

void eliminar(usuario_t **pusuario)
{

	free((*pusuario)->usuario);
	(*pusuario)->usuario = NULL;

	free((*pusuario)->nombre);
	(*pusuario)->nombre = NULL;

	VECTOR_destruir(&((*pusuario)->amigos), &VECTOR_destructor);
	LISTA_destruir((*pusuario)->mensajes, &LISTA_destructor);

	free(*pusuario);
	*pusuario = NULL;


}

void imprimir_single_output(red_t *red)
{
	output_t output = SINGLE;
	output_t *p_output = &output;

	if(red != NULL);
	{
		printf("[%s]\n", red->dato->usuario);
		printf("%s = %i\n", STRING_ID, red->dato->id);
		printf("%s = %s\n", STRING_NOMBRE, red->dato->nombre);
		LISTA_recorrer(*(red->dato->mensajes), p_output, &(LISTA_funcion_imprimir));
		printf("\n\n");

	}

}

status_t imprimir_multi_output(red_t *red)
{
	FILE *fp;


	while(red != NULL)
	{

		if((fp = fopen(red->dato->usuario, "wb+")) == NULL)
		{
			return ERROR_ABRIR_ARCHIVO;
		}

		printf("Creado archivo con nombre: %s\n", red->dato->usuario);

		fprintf(fp, "%i - %s\n", red->dato->id, red->dato->usuario);

		red = red->sig;
	}

	return OK;

}

void RED_destruir(red_t **red)
{

	red_t *aux = *red;
	while(*red != NULL)
	{
		eliminar(&((*red)->dato));
		
		*red = (*red)->sig;
	}

	free(aux);
	aux = NULL;


}
