#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#include "tiposDeDatos.h"
#include "NumeroComplejo.h"

/* ******************************************************************
 *                            Validación
 * *****************************************************************/

void printErrorMessage(const char* errorMessage) {

	printf("%s\n", errorMessage);
}

bool isNumber(char* str, size_t len) {
	
	int idx = 0;

	if (str[idx] == '-') {
		idx++;
	}

	while (idx < len) {

		if (!isdigit((int)str[idx])) {
			return false;
		}
		idx++;
	}

	return true;
}

bool isFloatNumber(char* str, size_t len) {

	int idx = 0;
	int canPoints = 0;
	int canDig = 0;
	int canNums = 0;

	if (str[idx] == '-') { // Si el número es negativo
		idx++;
	}

	while (idx < len) {

		if (isdigit((int)str[idx])) {

			canDig++;

		} else {

			if (str[idx] == '.') {
				//si no tiene números antes del punto, es inválido
				if (canDig == 0)
					return false;
				else {	//sino se cuenta la cantidad de números
					canNums++;
					canDig = 0;	//se inicializa el contador de dígitos
				}
				canPoints++;
			} else { //si no es un dígito ni un punto, es un caracter no admitido
				return false;
			}
		}
		
		idx++;
	}
	if (canDig > 0)
		canNums++;
	if (canNums > 2)	//si tiene más de 2 números es inválido
		return false;
	if (canPoints > 1)	//si tiene más de un punto es inválido
		return false;
	return true;
}

bool resolucionValida(Resolucion resolucion) {

	bool valido = resolucion.ancho > 0 && resolucion.alto > 0;

	if (!valido) {
		printErrorMessage("fatal: invalid resolution specification. Height and Width must be greater than zero");
	}

	return valido;
}

bool nombreValido(char* nombre) {

	if (strcmp(nombre, "-") == 0) {

		return true;

	} else {

		if (strcmp(nombre, "") == 0) {

			printErrorMessage("fatal: output file was not specified");
			return false;

		} else {

			FILE* f = fopen(nombre, "w");

			if (f == NULL) {
				char errorMessage[200] = "fatal: output file can not be open. The filepath: ";
				strcat(errorMessage, nombre);
				strcat(errorMessage, " ");
				strcat(errorMessage, "is invalid");
				printErrorMessage(errorMessage);
				return false;
			}

			fclose(f);
			return true;
		}
	}
}

bool complejoValido(NumeroComplejo complejo) {

	return complejo.parteReal != INT_MAX;
}

NumeroComplejo numeroComplejoInvalido() {

	NumeroComplejo invalido;
	invalido.parteReal = INT_MAX;
	return invalido;
}
