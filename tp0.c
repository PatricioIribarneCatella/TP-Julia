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

/* ******************************************************************
 *                  Definición de los tipos de datos
 * *****************************************************************/

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

typedef struct Commandos {
	Comando* *datos;
	int cantidadComandos;
}Comandos;

typedef struct ConfiguracionConjunto {
	Resolucion resolucion; // Resolución de la imagen a generar
	Dimension dimension; // Tamaño de la porción de plano complejo
	NumeroComplejo centro;
	NumeroComplejo parametroC;
	char* nombreImagen;
	bool salidaImagen;
}ConfiguracionConjunto;


/* ******************************************************************
 *                        Función de Lectura
 * *****************************************************************/

Comandos* leerDatos(int argc, char const *argv[]) {

	Comandos* comandos = malloc(sizeof(Comandos));

	if (!comandos) return NULL;

	/*Implementar la validación de los datos de entrada*/

	return NULL;
}

/* ******************************************************************
 *     Configuración de las dimensiones de la imagen a generar
 * *****************************************************************/

ConfiguracionConjunto* configurarConjunto(Comandos* comandos) {

	ConfiguracionConjunto* configuracion = malloc(sizeof(ConfiguracionConjunto));

	if (!configuracion) return NULL;

	for (int i = 0; i < comandos->cantidadComandos; i++) {

		/*A partir de los comandos ya guardados, obtener la información para la configuración*/
	}

	return configuracion;
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

void simularConjunto(ConfiguracionConjunto* configuracion) {

	FILE* imagen;

	int anchoRes = configuracion->resolucion.ancho;
	int altoRes = configuracion->resolucion.alto;

	if (configuracion->salidaImagen) {

		imagen = fopen(configuracion->nombreImagen, "w");

		fprintf(imagen, "%s\n", HEADER_IMAGEN);
		fprintf(imagen, "%d %d\n", anchoRes, altoRes);
		fprintf(imagen, "%d\n", MAXIMA_INTENSIDAD_PIXEL);

	} else {

		printf("%s\n", HEADER_IMAGEN);
		printf("%d %d\n", anchoRes, altoRes);
		printf("%d\n", MAXIMA_INTENSIDAD_PIXEL);
	}

	unsigned char brillo;
	NumeroComplejo unNumero;
	double incrementoParteReal, incrementoParteImaginaria, anchoPixel, altoPixel;

	NumeroComplejo centro = configuracion->centro;

	incrementoParteReal = configuracion->dimension.ancho / anchoRes;
	incrementoParteImaginaria = configuracion->dimension.alto / altoRes;
	anchoPixel = anchoRes/configuracion->dimension.ancho;
	altoPixel = altoRes/configuracion->dimension.alto;

	for(double i = -anchoRes/2; i <= anchoRes/2; i++){
		
		for(double j = -altoRes/2; j <= altoRes/2; j++){
			unNumero.parteReal = centro.parteReal + i*incrementoParteReal + anchoPixel;
			unNumero.parteImaginaria = centro.parteImaginaria + j*incrementoParteImaginaria + altoPixel;
			brillo = calcularBrillo(unNumero, configuracion->parametroC);
			
			if (configuracion->salidaImagen)
				fprintf(imagen, "%d ", brillo);
			else
				printf("%d ", brillo);
		}

		if (configuracion->salidaImagen)
			fprintf(imagen, "%s\n", "");
		else
			printf("\n");
	}

	if (configuracion->salidaImagen)
		fclose(imagen);
}

/* ******************************************************************
 *                 Funciones de destrucción de datos
 * *****************************************************************/

void destruirComandos(Comandos* comandos) {

	Comando* *datos = comandos->datos;

	for (int i = 0; i < comandos->cantidadComandos; i++) {

		Comando* comando = datos[i];
		free(comando->tipo);
		free(comando->dato);
		free(comando);
	}

	free(datos);

	free(comandos);
}

void destruirConfiguracionConjunto(ConfiguracionConjunto* configuracion) {

	free(configuracion->nombreImagen);

	free(configuracion);
}

void destruirDatos(Comandos* comandos, ConfiguracionConjunto* configuracion) {

	destruirComandos(comandos);
	destruirConfiguracionConjunto(configuracion);
}

/* ******************************************************************
 *              TP0 - Simulación del Conjunto de Julia
 * *****************************************************************/

void simulacionJulia(int argc, char const *argv[]) {

	Comandos* comandos = leerDatos(argc, argv);

	Comando* *datos = comandos->datos;

	Comando* comando = datos[0];

	if (strcmp(comando->tipo, ERROR) == 0) {

		printf("%s\n", comando->dato);
		destruirComandos(comandos);

	} else {

		ConfiguracionConjunto* configuracion = configurarConjunto(comandos);

		simularConjunto(configuracion);

		destruirDatos(comandos, configuracion);
	}
}

int main(int argc, char const *argv[]) {
	
	simulacionJulia(argc, argv);

	return 0;
}
