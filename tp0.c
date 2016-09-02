#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define COMANDO_R "-r"
#define COMANDO_C "-c"
#define COMANDO_PARAMETRO_C "-C"
#define COMANDO_W "-w"
#define COMANDO_H "-H"
#define COMANDO_OUTPUT "-o"
#define ERROR "e"

#define HEADER_IMAGEN "P2"
#define MAXIMA_INTENSIDAD_PIXEL 255

#define MAX_FILAS 480
#define MAX_COLUMNAS 640

/* ******************************************************************
 *                  Definición de los tipos de datos
 * *****************************************************************/

typedef struct Matriz {
	int cantidadFilas;
	int cantidadColumnas;
	int *intensidadPixeles[MAX_FILAS][MAX_COLUMNAS];
}Matriz;

typedef struct NumeroComplejo {
	double parteReal;
	double parteImaginaria;
}NumeroComplejo;

typedef struct Resolucion {
	int ancho;
	int alto;
}Resolucion;

typedef struct Dimension {
	float ancho;
	float alto;
}Dimension;

typedef struct Comando {
	char* tipo;
	char* dato;
}Comando;

typedef struct ConfiguracionConjunto {
	Resolucion resolucion; // Resolución de la imagen a generar
	Dimension dimension; // Tamaño de la porción de plano complejo
	NumeroComplejo centro;
	NumeroComplejo parametroC;
	bool salidaImagen;
}ConfiguracionConjunto;

typedef struct ConjuntoDeJulia {
	Matriz* pixeles;
	bool salidaImagen;
}ConjuntoDeJulia;


/* ******************************************************************
 *                        Función de Lectura
 * *****************************************************************/

Comando* *leerDatos(int argc, char const *argv[]) {


}

/* ******************************************************************
 *     Configuración de las dimensiones de la imagen a generar
 * *****************************************************************/

ConfiguracionConjunto* configurarConjunto(Comando* *comandos) {


}

/* ******************************************************************
 *                  Simula el Conjunto de Julia
 * *****************************************************************/

ConjuntoDeJulia* simularConjunto(ConfiguracionConjunto* configuracion) {
/*
	para cada pixel $p {
		$z = complejo asociado a $p;
		for ($i = 0; $i < $N - 1; ++$i) {
		if (abs($z) > 2)
			reak;
			$z = $z * $z + $c;
		}
		dibujar el punto p con brillo $i;
	}
*/
}

/* ******************************************************************
 *                 Genera la salida correspondiente
 * *****************************************************************/

void generarSalidaDeLaSimulacion(ConjuntoDeJulia* conjuntoJulia) {


}

/* ******************************************************************
 *                 Funciones de destrucción de datos
 * *****************************************************************/

void destruirComandos(Comando* *comandos) {


}

void destruirConfiguracionConjunto(ConfiguracionConjunto* configuracion) {


}

void destruirConjuntoDeJulia(ConjuntoDeJulia* conjuntoDeJulia) {


}

void destruirDatos(Comando* *comandos, ConfiguracionConjunto* configuracion, ConjuntoDeJulia* conjuntoDeJulia) {

	destruirComandos(comandos);
	destruirConfiguracionConjunto(configuracion);
	destruirConjuntoDeJulia(conjuntoDeJulia);
}

/* ******************************************************************
 *              TP0 - Simulación del Conjunto de Julia
 * *****************************************************************/

void simulacionJulia(int argc, char const *argv[]) {

	Comando* *comandos = leerDatos(argc, argv);

	if (strcmp(comandos[0]->tipo, ERROR) == 0) {

		printf("%s\n", comandos[0]->dato);
		destruirComandos(comandos);

	} else {

		ConfiguracionConjunto* configuracion = configurarConjunto(comandos);

		ConjuntoDeJulia* conjuntoDeJulia = simularConjunto(configuracion);

		generarSalidaDeLaSimulacion(conjuntoDeJulia);

		destruirDatos(comandos, configuracion, conjuntoDeJulia);
	}
}

int main(int argc, char const *argv[]) {
	
	simulacionJulia(argc, argv);

	return 0;
}
