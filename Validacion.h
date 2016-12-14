#ifndef VALIDACION_H
#define VALIDACION_H

#include <stdlib.h>
#include "tiposDeDatos.h"

void printErrorMessage(const char* errorMessage);

bool isNumber(char* str, size_t len);

bool isFloatNumber(char* str, size_t len);

bool resolucionValida(Resolucion resolucion);

bool nombreValido(char* nombre);

bool complejoValido(NumeroComplejo complejo);

NumeroComplejo numeroComplejoInvalido();

#endif // VALIDACION_H