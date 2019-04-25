#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "tipos.h"
#include "utilities.h"
#include "array.h"
#include "lista.h"
#include "carga.h"
#include "error.h"


status_t cargar_red(char **archivos, int cant_archivos, red_t **red)
{
	size_t i;
	usuario_t *user = NULL;
	FILE *fp = NULL;
	retval_t rv;

	user = crear_usuario();
	if(user == NULL)
	{
		return ERROR_MEMORIA;
	}

	/* Creamos lista vacia */
	*red = crear_red();

	/* Para ver si la carga es correcta, recorro con temp */

	for(i = 0; i < cant_archivos; i++)
	{
		if( (fp = fopen(archivos[i], "rb")) == NULL)
		{
			return ERROR_ABRIR_ARCHIVO;
		}

		/* La carga procede mientras no lleguemos al final del archivo, y si no existen errores */
		while( ((rv = cargar_usuario_completo(fp, user)) != RV_ERROR_O_FIN_DE_ARCHIVO) && ((rv == RV_SUCCESS)) )
		{
			insertar_en_red(red, user);

			user = crear_usuario();
			if(user == NULL)
			{
				return ERROR_MEMORIA;
			}

		}

		if(rv != RV_ERROR_O_FIN_DE_ARCHIVO)
		{
			free(user);
			user = NULL;
			return ERROR_USUARIO;
		}


		fclose(fp);

	}

	return OK;
}

retval_t cargar_usuario_completo(FILE* f, usuario_t* user)
{
	cadena_t valor;
	retval_t retval;
	char campo;

	if(!f || !user)
	{			
		return RV_ILLEGAL;
	}


	if((retval=cargar_nombre_de_usuario(f, user))!=RV_SUCCESS)
	{
		return retval;
	}
	
	while(1)
	{
		if((retval = detectar_campo(f, &valor, &campo)) == RV_FIN_USUARIO)
		{
			return RV_SUCCESS;
		}

		switch(campo)
		{
			case SWITCH_CAMPO_NOMBRE:

				if((retval=cargar_nombre(valor, user))!=RV_SUCCESS)
				{
					return retval;
				}


				break;

			case SWITCH_CAMPO_ID:

				if((retval=cargar_id(valor, user))!=RV_SUCCESS)
				{
		
					return retval;
				}

				break;

			case SWITCH_CAMPO_AMIGOS:

				if((retval=cargar_amigos(valor, user))!=RV_SUCCESS)
				{
                	free(user->nombre);
                	user->nombre = NULL;
					return retval;
                }


				break;

			case SWITCH_CAMPO_MENSAJES:

				if((retval=cargar_mensaje(valor, user))!=RV_SUCCESS)
				{
					free(user->nombre);
					user->nombre = NULL;
					VECTOR_destruir(&(user->amigos), &(VECTOR_destructor));
					return retval;
				}

				break;


			default:
				
				return RV_ERROR_LECTURA;
				break;
		}

		free(valor);
		valor = NULL;
	}


    return RV_ILLEGAL;
}
retval_t cargar_nombre_de_usuario(FILE *f, usuario_t *user)
{
	cadena_t cadena=NULL, aux=NULL, aux2=NULL, sin_espacios=NULL;
	bool_t fin_de_archivo=FALSE;
	retval_t retval;

	if(!f || !user)
	{
		return RV_ILLEGAL;
	}

	while((retval=readline(f, &cadena, &fin_de_archivo))==RV_SUCCESS)
	{

		if(fin_de_archivo)
		{
			retval = RV_ERROR_O_FIN_DE_ARCHIVO;
			break;
		}

		if(linea_vacia(cadena))
		{
			continue;
		}

		break;
	}


	if(retval!=RV_SUCCESS)
	{
		free(cadena);
		return retval;
	}


	sin_espacios=full_trim(cadena); /*saca los espacios de los costados*/
	free(cadena); /*solo me quedo con sin_espacios*/
	cadena = NULL;


	/* Esto no saca el caracter fin nombre usuario */

	if( (aux=strchr(sin_espacios, CARACTER_FIN_NOMBRE_USUARIO))==NULL)
	{
		free(sin_espacios);
		return RV_ILLEGAL;
	}

	*aux='\0';

	if((aux2=strdup(sin_espacios+1))==NULL) /*si sin_espacios="[mariano" entonces aux2="mariano"*/
	{
		free(sin_espacios);
		return RV_NOMEM;
	}

	user->usuario=aux2;


	free(sin_espacios);
	sin_espacios = NULL;

	return RV_SUCCESS;
}


retval_t detectar_campo(FILE* f, cadena_t *valor, char *campo)
{

	cadena_t cadena=NULL, p=NULL, nombre=NULL;
	bool_t fin_de_archivo = FALSE;


	if(!f || !valor)
	{
		return RV_ILLEGAL;
	}
        

	if(readline(f, &cadena, &fin_de_archivo)!=RV_SUCCESS)
	{

		return RV_ERROR_LECTURA;
	}

	p = strchr(cadena, SEPARADOR);

	if(!p) /*si no encuentra el SEPARADOR (que es el '=')*/
	{
		free(cadena);
		cadena = NULL;
		return RV_FIN_USUARIO;
	}

	*p='\0'; /*pone un '\0' en el lugar del '='*/


	nombre=full_trim(cadena);

	*valor = full_trim(p+1);


	free(cadena);
	cadena = NULL;

	if(!strcmp(nombre, CAMPO_NOMBRE))
	{
		*campo = SWITCH_CAMPO_NOMBRE;

	} else if(!strcmp(nombre, CAMPO_ID))
	{
		*campo = SWITCH_CAMPO_ID;

	} else if(!strcmp(nombre, CAMPO_AMIGOS))
	{
		*campo = SWITCH_CAMPO_AMIGOS;
		
	} else if(!strcmp(nombre, CAMPO_MENSAJES))
	{
		*campo = SWITCH_CAMPO_MENSAJES;
	}

	return OK;

}


retval_t cargar_id(cadena_t valor, usuario_t *user)
{
	if(!user)
	{
		return RV_ILLEGAL;
	}

	user->id=(size_t)atoi(valor);
	return RV_SUCCESS;
}

retval_t cargar_nombre(cadena_t valor, usuario_t *user)
{
	if(!user) 
	{
		return RV_ILLEGAL;
	}

	if(!(user->nombre=strdup(valor)))
	{
		return RV_NOMEM;
	}

	return RV_SUCCESS;
}

retval_t cargar_amigos(cadena_t valor, usuario_t *user) /* CON FUNCIONES DE ARRAY.C */
{
	cadena_t *arreglo_de_cadenas;
	size_t cant_de_cadenas, i;
	retval_t retval;

	if(!user) 
	{
		return RV_ILLEGAL;
	}

	split(valor, DELIMITADOR_INI, &arreglo_de_cadenas, &cant_de_cadenas);

	
	if((retval=VECTOR_crear(&(user->amigos)))!=RV_SUCCESS)
	{
		for (i = 0; i < cant_de_cadenas; i++) /*LIBERA EL ARREGLO DE CADENAS*/
		{
			free(arreglo_de_cadenas[i]);
		}
		return RV_NOMEM;
	}


	for(i=0; i<cant_de_cadenas; i++)
	{	
		if((retval=VECTOR_insertar((user->amigos), atoi(arreglo_de_cadenas[i])))!=RV_SUCCESS)
		{
			for (i = 0; i < cant_de_cadenas; i++) /*LIBERA EL ARREGLO DE CADENAS*/
			{
				free(arreglo_de_cadenas[i]);
				VECTOR_destruir(&(user->amigos), &(VECTOR_destructor) );
				return retval;
			}
		}
	}

	return RV_SUCCESS;
}

retval_t cargar_mensaje(cadena_t valor, usuario_t *user) /* SIN TERMINAR. HAY QUE USAR FUNCIONES DE LISTA.C*/
{
	cadena_t *arreglo_de_cadenas;
	size_t cant_de_cadenas, i;
	retval_t retval;
	char *pchar, *msj;
	mensaje_s *estructura_mensaje=NULL;
	struct tm s_tm = {0, 0, 0, 0, 0, 0, 0, 0, 0};


	if(!user) 
	{
		return RV_ILLEGAL;
	}
	
	pchar=valor;

	for(i=0; i<POS_TERCER_DELIMITADOR; i++)
	{
		pchar=strchr(pchar, DELIMITADOR_INI);
		pchar++;
	}

	(*(pchar-1))='\0';

	msj=pchar;


	if((retval=split(valor, DELIMITADOR_INI, &arreglo_de_cadenas, &cant_de_cadenas))!=RV_SUCCESS)
	{
		free(valor);
		return retval;
	}

	if(cant_de_cadenas!=3)
	{
		free(valor);
		return RV_ERROR_LECTURA;
	}


	if((estructura_mensaje=(mensaje_s*)malloc(sizeof(mensaje_s)))==NULL)
	{
		free(valor);
		return RV_NOMEM;
	}


	(estructura_mensaje->id_msj)=(size_t)atoi(arreglo_de_cadenas[POS_ID_MSJ]);

	/* HACER ALGO PARA CARGAR EL TIEMPO DEL MENSAJE EN estructura_mensaje->timestamp */
	sscanf(arreglo_de_cadenas[POS_TIMESTAMP], "%i-%i-%i", &(s_tm.tm_year), &(s_tm.tm_mon), &(s_tm.tm_mday));
	s_tm.tm_year = s_tm.tm_year - 1900;
	s_tm.tm_mon = s_tm.tm_mon - 1;
	(estructura_mensaje->timestamp) = mktime(&s_tm);

	estructura_mensaje->id_usuario_mensaje=(size_t)atoi(arreglo_de_cadenas[POS_ID_USUARIO_MENSAJE]);

	if((estructura_mensaje->texto = strdup(msj))==NULL)
	{
		free(valor);
		return RV_NOMEM;
	}



	if(user->mensajes == NULL)
	{
		if( (user->mensajes = (lista_s *)malloc(sizeof(lista_s))) == NULL)
		{
        	free(valor);
			return RV_NOMEM;
		}


		LISTA_crear(user->mensajes);

		if((retval=LISTA_crear_nodo(user->mensajes, estructura_mensaje))!=RV_SUCCESS)
		{
			free(valor);
			return RV_ILLEGAL;
		}


	} else {

		LISTA_insertar_ppio(user->mensajes, estructura_mensaje);


	}


	return RV_SUCCESS;
}


usuario_t *crear_usuario(void)
{
	usuario_t *ret_usr;

	if( (ret_usr = (usuario_t *)malloc(sizeof(usuario_t))) == NULL)
	{
		return NULL;
	}

	ret_usr->id = 0;
	ret_usr->nombre = NULL;
	ret_usr->usuario = NULL;
	ret_usr->amigos = NULL;
	ret_usr->mensajes = NULL;

	return ret_usr;
}

red_t *crear_red(void)
{

	red_t *ret_red;

	ret_red = NULL;

	return ret_red;
}

status_t crear_nodo_red(red_t **red, void *dato)
{

	if(red == NULL)
	{
		return ERROR_NULL;
	}

	if( (*red = (red_t *)calloc(1, sizeof(red_t))) == NULL)
	{
		return ERROR_MEMORIA;
	}

	(*red)->sig = NULL;
	(*red)->dato = dato;

	return OK;

}

status_t insertar_en_red(red_t **red, usuario_t *user)
{	
	red_t *temp;
	status_t st;

	if(red == NULL || user == NULL)
	{
		return ERROR_NULL;
	}

	if((st = crear_nodo_red(&temp, user)) != OK)
	{
		return st;
	}
	
	temp->sig = *red;
	*red = temp;

	return OK;

}

