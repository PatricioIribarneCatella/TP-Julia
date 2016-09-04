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
 *                        Funciones de operacion con complejos
 * *****************************************************************/

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


/* ******************************************************************
 *                  Simula el Conjunto de Julia
 * *****************************************************************/

unsigned char calcularBrillo(NumeroComplejo numeroComplejo, NumeroComplejo c){
	NumeroComplejo iComplejo = numeroComplejo;
	unsigned char i = 0;
	while(i < 255 && moduloAlCuadrado(iComplejo) <= 4){
		iComplejo = sumar(multiplicar(iComplejo, iComplejo),c);
		i++;
	}
	return i;
}

/* Si la resolucion es un numero impar en ancho y alto,
 * el centro que se le da es el centro de un pixel y todo funciona adecuadamente.
 * Si es par, habria que hacer un ajuste de sumarle medio pixel en la coordenada
 * correcta. Por ahora lo dejo asi.
 * Por ahora no devuelve el conjunto
*/
ConjuntoDeJulia* simularConjunto(ConfiguracionConjunto* configuracion) {

	NumeroComplejo unNumero;
	NumeroComplejo centro = configuracion->centro;
	unsigned char brillo;
	double incrementoParteReal, incrementoParteImaginaria, altoPixel, anchoPixel;
	int anchoRes = configuracion->resolucion.ancho;
	int altoRes = configuracion->resolucion.alto;

	incrementoParteReal = configuracion->dimension.ancho / anchoRes;
	incrementoParteImaginaria = configuracion->dimension.alto / altoRes;

	for(int i = -anchoRes/2; i <= anchoRes/2; i++){
		for(int j = -altoRes/2; j <= altoRes/2; j++){
			unNumero.parteReal = centro.parteReal + i*incrementoParteReal;
			unNumero.parteImaginaria = centro.parteImaginaria + j*incrementoParteImaginaria;
			brillo = calcularBrillo(unNumero, configuracion->parametroC);
			//Aca ya podriamos guardar este punto en el archivo de imagen
		}
	}
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
