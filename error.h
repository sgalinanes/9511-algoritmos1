#ifndef ERROR__H
#define ERROR__H

#include "tipos.h"

/*ERRORES*/
#define ARCHIVO_ERRORES "err_log.txt"
#define MSJ_ERROR_CLA_CANT_ARG "La cantidad de argumentos ingresadas es menor a la requerida"
#define MSJ_ERROR_CLA_FLAG "Uno de los flags ingresados es incorrecto"
#define MSJ_ERROR_ABRIR_ARCHIVO "Error al abrir el archivo"
#define MSJ_ERROR_MEMORIA "Error al pedir memoria"
#define MSJ_ERROR_OBTENCION_USUARIO "Error al obtener el nombre de usuario"
#define MSJ_ERROR_OPCION_OUTPUT "Error en la opcion de output elegida. Verificar que sea single o multi"
#define MSJ_ERROR_OPCION_FILTRO "El filtro ingresado es incorrecto"
#define MSJ_USUARIO_EXISTENTE "El usuario ya existe"
#define MSJ_ERROR_USUARIO "Hubo un error en el usuario"
#define MSJ_ERROR_NULL "El puntero es nulo"
#define MSJ_ERROR_RED "Hubo un error en la red"
#define MSJ_ERROR_ELIMINAR_INEXISTENTE	"No existe el usuario en la red"

void imprimir_errores(status_t status);

#endif
