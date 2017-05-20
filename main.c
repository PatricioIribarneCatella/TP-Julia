#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <limits.h>

#include "NumeroComplejo.h"
#include "SimulacionJulia.h"
#include "LecturaParametros.h"
#include "tiposDeDatos.h"

#define COMANDO_V "-v"

static void destruirConfiguracion(ConfiguracionConjunto* configuracion) {

	free(configuracion->nombreImagen);
	free(configuracion);
}

static void simularConjunto(ConfiguracionConjunto* configuracion) {

	Resolucion resolucion = configuracion->resolucion;
	Dimension dimension = configuracion->dimension;
	NumeroComplejo centro = configuracion->centro;
	NumeroComplejo c = configuracion->c;
	char* nombreImagen = configuracion->nombreImagen;

	FILE* imagen;

	if (!(configuracion->salidaEstandar)) {

		imagen = fopen(nombreImagen, "w");
        
	} else {

		imagen = stdout;
	}

	simularConjuntoJulia(resolucion, dimension, centro, c, imagen);
}

/* ******************************************************************
 *              TP0 - Simulación del Conjunto de Julia
 * *****************************************************************/

static void simulacionJulia(int argc, char const *argv[]) {
	
	if ((argc != 1) && strcmp(argv[1], COMANDO_V) == 0) {

		printf("%s\n", "Version: 1.0");
		printf("Integrantes:\n" 
			"\t Mauro Toscano Gonella\n"
			"\t Patricio Iribarne Catella\n"
			"\t Marcos Vrljicak\n");

	} else {

		ConfiguracionConjunto* configuracion = leerDatos(argc, argv);
	
		if (!configuracion) return;

		simularConjunto(configuracion);
		
		destruirConfiguracion(configuracion);
	}
}

int main(int argc, char const *argv[]) {

	simulacionJulia(argc, argv);
	return 0;
}
