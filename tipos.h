#ifndef TIPOS__h
#define TIPOS__h

typedef char* cadena_t;

struct amigo;
typedef struct amigo *vector_s;

struct nodo;
typedef struct nodo *lista_s;

typedef struct usuario{
	size_t id;
	cadena_t nombre;
	cadena_t usuario;
	vector_s amigos;
	lista_s *mensajes;
} usuario_t;

typedef struct red {
	struct red *sig;
	usuario_t *dato;
} red_t;


typedef enum {
    ERROR_CLA_VALIDACION,
    ERROR_CLA_CANT_ARG,
    ERROR_CLA_FLAG,
    ERROR_OPCION_OUTPUT,
    ERROR_ABRIR_ARCHIVO,
    ERROR_MEMORIA,
    ERROR_OBTENCION_USUARIO,
    ERROR_OPCION_FILTRO,
    ERROR_USUARIO,
    ERROR_NULL,
    ERROR_RED,
    ERROR_ELIMINAR_INEXISTENTE,
    OK
} status_t;

typedef enum{
	FALSE,
	TRUE
} bool_t;

typedef enum {
	SINGLE,
	MULTI
} output_t;

typedef enum{
	RV_ILLEGAL,
	RV_SUCCESS,
	RV_NOMEM,
	RV_EMPTY,
	RV_ERROR_O_FIN_DE_ARCHIVO,
	RV_ERROR_FILE,
	RV_ERROR_LECTURA,
	RV_FIN_USUARIO
} retval_t;

#endif