#ifndef NUMEROCOMPLEJO_H
#define NUMEROCOMPLEJO_H

#include <stdlib.h>
#include <stddef.h>

/* *****************************************************************
 *           DEFINICION DEL TIPO DE DATO NUMERO COMPLEJO
 * *****************************************************************/

typedef struct NumeroComplejo {
	double parteReal;
	double parteImaginaria;
} NumeroComplejo;

/* *****************************************************************
 *          FUNCIONES PARA OPERAR SOBRE NUMEROS COMPLEJOS
 * *****************************************************************/

NumeroComplejo sumar(NumeroComplejo c1, NumeroComplejo c2);

NumeroComplejo multiplicar(NumeroComplejo c1, NumeroComplejo c2);

double moduloAlCuadrado(NumeroComplejo c);

#endif //NUMEROCOMLEJO_H

