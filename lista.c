#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "tipos.h"
#include "lista.h"



typedef struct nodo
{
	struct nodo *sig;
	void *dato;
} nodo_t;


retval_t LISTA_crear(lista_s *pl)
{
	if(!pl)
		return RV_ILLEGAL;
	*pl=NULL;
	return RV_SUCCESS;
}

bool_t LISTA_vacia(lista_s pl)
{
	return pl==NULL;
}

retval_t LISTA_crear_nodo(lista_s *nodo, void *dato)
{
	if(!nodo) 
	{

		return RV_ILLEGAL;
	}

	if((*nodo=(nodo_t*)calloc(1, sizeof(nodo_t)))==NULL)
	{

		return RV_NOMEM;
	}

	(*nodo)->sig=NULL;
	(*nodo)->dato=dato;
	return RV_SUCCESS;
}

retval_t LISTA_destruir_nodo(lista_s *pnodo, void (*LISTA_destructor)(void*))
{
	if(!pnodo) return RV_ILLEGAL;
	if(!(*pnodo)) return RV_SUCCESS; /*ya esta destruido*/

	if(LISTA_destructor!=NULL)
		(*LISTA_destructor)((*pnodo)->dato);

	(*pnodo)->dato=NULL;
	(*pnodo)->sig=NULL;
	free(*pnodo);
	*pnodo=NULL;
	return RV_SUCCESS;
}

retval_t LISTA_destruir(lista_s *pl, void (*LISTA_destructor)(void*))
{
	nodo_t *siguiente;

	if(!pl) return RV_ILLEGAL;

	if(LISTA_vacia(*pl)) 
	{

		return RV_SUCCESS;
	}
	siguiente=(*pl)->sig;

	LISTA_destruir_nodo(pl, LISTA_destructor);

	return LISTA_destruir(&siguiente, LISTA_destructor);
}


retval_t LISTA_insertar_ppio(lista_s *pl, void *d)
{
	retval_t rv;
	nodo_t *nodo;

	if(!pl) return RV_ILLEGAL;

	if((rv=LISTA_crear_nodo(&nodo, d))!=RV_SUCCESS)
	{
		return rv;
	}

	nodo->sig=*pl;
	*pl=nodo;
	return RV_SUCCESS;
}

retval_t LISTA_insertar_final(lista_s *pl, void *d)
{
	if(!pl) return RV_ILLEGAL;

	if(LISTA_vacia(*pl)) return LISTA_insertar_ppio(pl, d);

	return LISTA_insertar_final(&((*pl)->sig), d);
}

retval_t LISTA_insertar_decreciente(lista_s *pl, void *d, int(*cmp)(void*, void*))
{
	retval_t rv;
	nodo_t *nodo;

	if(!pl) return RV_ILLEGAL;

	if(LISTA_vacia(*pl) || (*cmp)((*pl)->dato, d)<0)
	{
		if((rv=LISTA_crear_nodo(&nodo, d))!=RV_SUCCESS)
		{
			return rv;
		}
		nodo->sig=*pl;
		*pl=nodo;
	}
	return LISTA_insertar_decreciente(&(*pl)->sig, d, cmp);
}

void* LISTA_buscar(lista_s l, void* t, bool_t (*cmp)(void*, void*))
{
	if(!l) return NULL;

	if((*cmp)(l->dato, t)) return l->dato;

	return LISTA_buscar(l->sig, t, cmp);
}

retval_t LISTA_recorrer(lista_s l, void *arg, void (*pf)(void*, void*))
{
	if(!l) return RV_SUCCESS;

	(*pf)(arg, l->dato); /*se podria validar lo que devuelve*/

	return LISTA_recorrer(l->sig, arg, pf);
}

void LISTA_destructor(void* dato)
{
	free(dato);
	dato=NULL;
}

void LISTA_funcion_imprimir(void * arg, void * dato)
{
	mensaje_s *mensaje = dato;
	output_t *output = arg;

	if(arg==NULL)
	{
		printf("Id mensaje: %i\n", (mensaje->id_msj));
		printf("Timestamp: %d\n", (mensaje->timestamp));
		printf("Id usuario mensaje: %i\n", (mensaje->id_usuario_mensaje));
		printf("Texto: %s\n", (mensaje->texto));
		return;
	}

	if((*output) == SINGLE)
	{
		printf("%s = %i,%i,%i,%s\n", STRING_MENSAJE, mensaje->id_msj, mensaje->timestamp, mensaje->id_usuario_mensaje, mensaje->texto);

	}


}


void RED_imprimir(red_t *red)
{
	red_t *red_aux=red;
	while(red_aux!=NULL)
	{
		LISTA_recorrer(*(red_aux->dato->mensajes), NULL, &(LISTA_funcion_imprimir));
		red_aux=red_aux->sig;
	}
}