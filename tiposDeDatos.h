#ifndef TIPOSDEDATOS_H
#define TIPOSDEDATOS_H

#include <stdlib.h>
#include "NumeroComplejo.h"

/* ******************************************************************
 *                  Definición de los tipos de datos
 * *****************************************************************/

typedef struct Resolucion {
	int ancho;
	int alto;
} Resolucion;

typedef struct Dimension {
	double ancho;
	double alto;
} Dimension;

typedef struct ConfiguracionConjunto {
	Resolucion resolucion; // Resolución de la imagen a generar
	Dimension dimension; // Tamaño de la porción de plano complejo
	NumeroComplejo centro;
	NumeroComplejo c;
	char* nombreImagen;
	bool salidaEstandar;
} ConfiguracionConjunto;

#endif //TIPOSDEDATOS_H

