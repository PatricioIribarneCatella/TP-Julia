#include <stdlib.h>
#include "NumeroComplejo.h"

NumeroComplejo sumar(NumeroComplejo z1, NumeroComplejo z2) {

	NumeroComplejo resultado;
	resultado.parteReal = z1.parteReal + z2.parteReal;
	resultado.parteImaginaria = z1.parteImaginaria + z2.parteImaginaria;
	return resultado;
}

NumeroComplejo multiplicar(NumeroComplejo z1, NumeroComplejo z2) {

	NumeroComplejo resultado;
	resultado.parteReal = z1.parteReal * z2.parteReal -
						  z1.parteImaginaria * z2.parteImaginaria;
	resultado.parteImaginaria = z1.parteReal * z2.parteImaginaria +
								z1.parteImaginaria * z2.parteReal;
	return resultado;
}

double moduloAlCuadrado(NumeroComplejo z1) {
	
	return z1.parteImaginaria * z1.parteImaginaria
			+ z1.parteReal * z1.parteReal;
}

