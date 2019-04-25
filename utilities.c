#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "tipos.h"
#include "utilities.h"

bool_t linea_vacia(cadena_t cadena)
{
	if(!cadena)
		return FALSE;

	for(; cadena; cadena++)
	{
		if(!(isspace(*cadena)))
			break;
	}

	if(*cadena=='\n' || *cadena=='\0')
		return TRUE;

	return FALSE;
}

retval_t readline(FILE *f, cadena_t *linea, bool_t *fin_archivo)
{
	char *aux;
	size_t start;
	
	if(fin_archivo == NULL)
	{
		return RV_ILLEGAL;
	}
	
	if((*linea = (char *)calloc(1, (CHOP_SIZE +1) * sizeof(char))) == NULL)
	{
		return RV_NOMEM;
	}
	
	*fin_archivo = FALSE;
	start = 0;

	while((fgets(*linea + start, CHOP_SIZE + 1, f)) != NULL)
	{
		if((*linea + start)[strlen(*linea + start) - 1] == '\n')
		{
			/* SE termino de leer una linea */
			return RV_SUCCESS;
		}
		
		start += CHOP_SIZE;
		if((aux = (char *)realloc(*linea, (start +1 +CHOP_SIZE) * sizeof(char))) == NULL)
		{
			free(*linea);
			return RV_NOMEM;
		}
		
		*linea = aux;
	}
	
	if(ferror(f))
	{
		/* fgets() devolvia NULL porque fallo */
		free(*linea);
		return RV_ERROR_FILE;
	}
	
	*fin_archivo = TRUE;
	return RV_SUCCESS;
}
retval_t split(const cadena_t cadena, char delimitador, char*** arreglo, size_t* l)
{
	char** campos;
	size_t n, i;
	char *aux, *q, *linea, delim[2];

	if(cadena==NULL || l==NULL)
	{
		return RV_ILLEGAL;
	}

	for (i = 0, n=1; cadena[i]; i++)
	{
		if(cadena[i]==delimitador)
			n++;
	}

	if((campos=(char**)malloc(sizeof(char*)*n))==NULL)
	{
		*arreglo=NULL;
		*l=0;
		return RV_NOMEM;
	}

	if((linea=strdup(cadena))==NULL)
	{
		free(campos);
		*arreglo=NULL;
		*l=0;
		return RV_NOMEM;
	}

	delim[0]=delimitador;
	delim[1]='\0';

	for ( i = 0, q = linea; (aux=strtok(q, delim))!=NULL; i++, q=NULL)
	{
		if( (campos[i] = strdup(aux)) == NULL)
		{
			destruir_arreglo_cadenas(&campos, i);
			*arreglo=NULL;
			*l=0;
			return RV_NOMEM;
		}
	}

	free(linea);
	*l=i;
	*arreglo = campos;
	return RV_SUCCESS;
}
char* strdup(const char *sc)
{

    char *s;
    
    if(sc==NULL)
    	return NULL;

    s=(char*)calloc(1, sizeof(char*)*(strlen(sc)+1));

    if(s)
    	strcpy(s, sc);

    return s;
}

char* left_trim(const char *sc)
{
	char *p, *aux;

	if(!sc)
		return NULL;

	for(p=sc; isspace(*p) && *p; p++)
		;

	if((aux=strdup(p))==NULL)
		return NULL;

	return aux;
}

char* right_trim(const char *sc)
{
	char *p;
	char *s;

	if(!sc)
		return NULL;

	if((s=strdup(sc))==NULL)
		return NULL;

	for(p=s+strlen(s)-1; isspace(*p) && p>s; p--)
		;

	*(p+1)='\0';

	return s;
}

char* full_trim(const char* sc)
{
	char *s, *p;

	if(!sc)
		return NULL;

	p=right_trim(sc);
	s=left_trim(p);
	free(p);

	return s;
}


void destruir_arreglo_cadenas(char*** arreglo_de_cadenas, size_t cant_de_cadenas)
{
	size_t i;

	for ( i = 0; i < cant_de_cadenas; i++)
	{
		free(arreglo_de_cadenas[i]);
	}
}

bool_t is_number(char *number)
{

	char *endptr = NULL;

	strtol(number, &endptr, 10);

	if(*endptr == '\0')
	{
		return TRUE;
	}

	return FALSE;

}