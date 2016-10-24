#include <stdlib.h>
#include "NumeroComplejo.h"

NumeroComplejo sumar(NumeroComplejo unNumero, NumeroComplejo otroNumero){
	NumeroComplejo resultado;
	resultado.parteReal = unNumero.parteReal + otroNumero.parteReal;
	resultado.parteImaginaria = unNumero.parteImaginaria + otroNumero.parteImaginaria;
	return resultado;
}

NumeroComplejo multiplicar(NumeroComplejo unNumero, NumeroComplejo otroNumero){
	NumeroComplejo resultado;
	resultado.parteReal = unNumero.parteReal * otroNumero.parteReal -
						  unNumero.parteImaginaria * otroNumero.parteImaginaria;
	resultado.parteImaginaria = unNumero.parteReal * otroNumero.parteImaginaria +
								unNumero.parteImaginaria * otroNumero.parteReal;
	return resultado;
}

double moduloAlCuadrado(NumeroComplejo unNumero){
	return unNumero.parteImaginaria*unNumero.parteImaginaria
			+ unNumero.parteReal*unNumero.parteReal;
}

