#ifndef CARGA__H
#define CARGA__H

#include <stdio.h>
#include <string.h>
#include <time.h>

#define CARACTER_FIN_NOMBRE_USUARIO ']'
#define SEPARADOR '='

/*INI*/
#define DELIMITADOR_INI ','

#define CAMPO_NOMBRE	"nombre"
#define CAMPO_ID		"id"
#define CAMPO_MENSAJES	"mensaje"
#define CAMPO_AMIGOS		"amigos"
#define SWITCH_CAMPO_AMIGOS		'a'
#define SWITCH_CAMPO_NOMBRE		'n'
#define SWITCH_CAMPO_ID 		'i'
#define SWITCH_CAMPO_MENSAJES	'm'

#define POS_ID_MSJ 0
#define POS_TIMESTAMP 1
#define POS_ID_USUARIO_MENSAJE 2
#define POS_TERCER_DELIMITADOR 3


retval_t cargar_nombre_de_usuario(FILE *f, usuario_t *user);
retval_t detectar_campo(FILE* f, cadena_t *valor, char *campo);

status_t cargar_red(char **archivos, int cant_archivos, red_t **red);
/*la estructura de lo que se lee en el archivo (despues de leer el nombre de usuario) es */
/*nombre = valor, siendo valor la cadena que tiene los campos delimitados por comas*/
/*esta funcion devuelve el nombre del campo que esta leyendo, para asi despues hacer algo con la
cadena valor, pero mejor implmentarlo en otra funcion. conviene esta funcion ponerla en un switch
que elija distintas acciones según lo que devuelva esta funcion (el nombre del campo)*/
/*la variable valor es una cadena que se modifica en la funcion y que guardara 
el string que contenga el los amigos, mensajes, etc*/

retval_t cargar_usuario_completo(FILE* f, usuario_t* user);

retval_t cargar_nombre(cadena_t valor, usuario_t *user);
retval_t cargar_amigos(cadena_t valor, usuario_t *user);
retval_t cargar_mensaje(cadena_t valor, usuario_t *user);
retval_t cargar_id(cadena_t valor, usuario_t *user);

usuario_t *crear_usuario(void);
red_t *crear_red(void);
status_t crear_nodo_red(red_t **red, void *dato);
status_t insertar_en_red(red_t **red, usuario_t *user);

#endif