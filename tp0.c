#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <limits.h>

#include "NumeroComplejo.h"
#include "SimulacionJulia.h"
#include "tiposDeDatos.h"

#define COMANDO_R "-r"
#define COMANDO_C "-c"
#define COMANDO_PARAMETRO_C "-C"
#define COMANDO_W "-w"
#define COMANDO_H "-H"
#define COMANDO_OUTPUT "-o"
#define COMANDO_V "-v"

#define PARAMETRO_DEF_LEN 15
#define COMPLEJO_MAX_LEN 200

#define RESOLUCION_ANCHO_DEFAULT 640
#define RESOLUCION_ALTO_DEFAULT 480
#define CENTRO_REAL_DEFAULT 0
#define CENTRO_IMAGINARIO_DEFAULT 0
#define DIMENSION_ANCHO_DEFAULT 4
#define DIMENSION_ALTO_DEFAULT 4

const double C_REAL_DEFAULT = 0.285;
const double C_IMAGINARIO_DEFAULT = -0.01;


/* ******************************************************************
 *                             Manual
 * *****************************************************************/

void printUso() {
	printf("Usage: ./tp0 [options]\n"
				   "-v [version]        shows the program's version (do not use it with the other options)\n"
				   "-r [resolution]     specify resolution\n"
				   "-c [complex number] specify center\n"
				   "-C [complex number] specify c parameter\n"
				   "-w [width]          specify width of output\n"
				   "-H [hight]          specify height of output\n"
				   "-o [filename]       specify file name, or type '-' for standard output\n");
}

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
		if (isdigit((int)str[idx])){
			canDig++;
		}
		else{
			if (str[idx] == '.'){
				//si no tiene números antes del punto, es inválido
				if (canDig == 0)
					return false;
				else{	//sino se cuenta la cantidad de números
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
    if (strcmp(nombre, "-") == 0){
    	return true;
    } else {
    	if (strcmp(nombre, "") == 0){
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

/* ******************************************************************
 *                            Lectura
 * *****************************************************************/

NumeroComplejo numeroComplejoInvalido() {
    NumeroComplejo invalido;
    invalido.parteReal = INT_MAX;
    return invalido;
}

NumeroComplejo stringANumeroComplejo(const char* complejoStr) {

	NumeroComplejo complejo;
    //Valido
    if (!(complejoStr && *complejoStr && complejoStr[strlen(complejoStr) - 1] == 'i')){
        return numeroComplejoInvalido();
    }

	//Homogeneizo entrada
	char str[COMPLEJO_MAX_LEN];
	if (complejoStr[0] != '+' && complejoStr[0] != '-') {
		strcpy(str, "+");
        strcat(str, complejoStr);
	} else {
        strcpy(str, complejoStr);
    }

	int signoReal = 1;
	int signoImaginario = 1;
	int i = 0, cuentaMas = 0, cuentaMenos = 0;

	for (i = 0; str[i]; i++) {
		cuentaMas += (str[i] == '+');
		cuentaMenos += (str[i] == '-');
	}

    if (cuentaMas + cuentaMenos != 2) {
        return numeroComplejoInvalido();
    }

	if (cuentaMas == 0) {
		signoImaginario = -1;
		signoReal = -1;
	} else if (cuentaMas == 1){
		if (str[0] == '+') signoImaginario = -1;
		else signoReal = -1;
	}

	//Parseo
	char* tmp;

	tmp = strtok(str, " +-i");
	if (!isFloatNumber(tmp, strlen(tmp))) return numeroComplejoInvalido();
	else {
        complejo.parteReal = signoReal*atof(tmp);
    }

	tmp = strtok(NULL, " +-i");
	if (!isFloatNumber(tmp, strlen(tmp))) return numeroComplejoInvalido();
	else {
        complejo.parteImaginaria = signoImaginario*atof(tmp);
    }

	return complejo;
}

ConfiguracionConjunto* leerDatos(int argc, char const *argv[]) {
	
	//Configuracion default
	ConfiguracionConjunto* configuracion = malloc(sizeof(ConfiguracionConjunto));
	configuracion->nombreImagen = malloc(sizeof(char)*PARAMETRO_DEF_LEN);
	strcpy(configuracion->nombreImagen, "");
	Resolucion resolucion;
	resolucion.ancho = RESOLUCION_ANCHO_DEFAULT;
	resolucion.alto = RESOLUCION_ALTO_DEFAULT;
	configuracion->resolucion = resolucion;
	NumeroComplejo centro;
	centro.parteReal = CENTRO_REAL_DEFAULT;
	centro.parteImaginaria = CENTRO_IMAGINARIO_DEFAULT;
	configuracion->centro = centro;
	NumeroComplejo c;
	c.parteReal = C_REAL_DEFAULT;
	c.parteImaginaria = C_IMAGINARIO_DEFAULT;
	configuracion->c = c;
	Dimension dimension;
	dimension.ancho = DIMENSION_ANCHO_DEFAULT;
	dimension.alto = DIMENSION_ALTO_DEFAULT;
	configuracion->dimension = dimension;
	configuracion->salidaEstandar = false;

	//Configuración custom
    int i;
	for (i = 1; i < argc; i++){
		if (strcmp(argv[i], COMANDO_R) == 0) {
			i++;
			if (i < argc) {
				char parametro[PARAMETRO_DEF_LEN];
				strcpy(parametro, argv[i]);
				char* valor;
				valor = strtok(parametro, "x");
				if (!isNumber(valor, strlen(valor))) {
					printErrorMessage("fatal: invalid width resolution. Must be a valid integer number");
					free(configuracion->nombreImagen);
					free(configuracion);
                    return NULL;
				}
				configuracion->resolucion.ancho = atoi(valor);
				valor = strtok(NULL, "x");
				if (!isNumber(valor, strlen(valor))) {
					printErrorMessage("fatal: invalid height resolution. Must be a valid integer number");
					free(configuracion->nombreImagen);
					free(configuracion);
					return NULL;
				}
				configuracion->resolucion.alto = atoi(valor);

				if (!resolucionValida(configuracion->resolucion)) {
					free(configuracion->nombreImagen);
					free(configuracion);
					return NULL;
				}
			}
		} else if (strcmp(argv[i], COMANDO_C) == 0) {
			i++;
			if (i < argc){
				configuracion->centro = stringANumeroComplejo(argv[i]);
                if (!complejoValido(configuracion->centro)) {
                	printErrorMessage("fatal: invalid center specification");
                	free(configuracion->nombreImagen);
                    free(configuracion);
                    return NULL;
                }
			}
		} else if (strcmp(argv[i], COMANDO_PARAMETRO_C) == 0) {
			i++;
			if (i < argc){
				configuracion->c = stringANumeroComplejo(argv[i]);
                if (!complejoValido(configuracion->c)) {
                	printErrorMessage("fatal: invalid c parameter specification");
                	free(configuracion->nombreImagen);
                    free(configuracion);
                    return NULL;
                }
			}
		} else if (strcmp(argv[i], COMANDO_W) == 0) {
			i++;
			if (i < argc){
				if (!isFloatNumber((char*)argv[i], strlen(argv[i]))) {
					printErrorMessage("fatal: invalid width specification. Must be a valid float number");
					free(configuracion->nombreImagen);
					free(configuracion);
					return NULL;
				} else {
					configuracion->dimension.ancho = atof(argv[i]);
				}

				if (configuracion->dimension.ancho < 0) {
					printErrorMessage("fatal: image width dimension must be a number greater than zero");
					free(configuracion->nombreImagen);
					free(configuracion);
					return NULL;
				}
			}
		} else if (strcmp(argv[i], COMANDO_H) == 0) {
			i++;
			if (i < argc){
				if (!isFloatNumber((char*)argv[i], strlen(argv[i]))) {
					printErrorMessage("fatal: invalid height specification. Must be a valid float number");
					free(configuracion->nombreImagen);
					free(configuracion);
					return NULL;
				} else {
					configuracion->dimension.alto = atof(argv[i]);
				}

				if (configuracion->dimension.alto < 0) {
					printErrorMessage("fatal: image height dimension must be a number greater than zero");
					free(configuracion->nombreImagen);
					free(configuracion);
					return NULL;
				}
			}
		} else if (strcmp(argv[i], COMANDO_OUTPUT) == 0) {
			i++;
			if (i < argc) {
				char* nombre = realloc(configuracion->nombreImagen, sizeof(char)*(strlen(argv[i]) + 1));
				configuracion->nombreImagen =  nombre;
				strcpy(configuracion->nombreImagen, argv[i]);
                if (!nombreValido(configuracion->nombreImagen)) {
                	free(configuracion->nombreImagen);
                    free(configuracion);
                    return NULL;
                }
			} else break;
		} else if (strcmp(argv[i], COMANDO_V) == 0) {
			printErrorMessage("To see the program's version, rerun only with the -v option");
		} else break;
	}

	if (strcmp(configuracion->nombreImagen,"-") == 0){
		configuracion->salidaEstandar = true;
	}

    //Errores de uso
	if (argc == 1 || argc != i) {
		free(configuracion->nombreImagen);
		free(configuracion);
		printUso();
		return NULL;
	}

	return configuracion;
}

/* ******************************************************************
 *                  Simula el Conjunto de Julia
 * *****************************************************************/

void simularConjunto(ConfiguracionConjunto* configuracion) {

	Resolucion resolucion = configuracion->resolucion;
	Dimension dimension = configuracion->dimension;
	NumeroComplejo centro = configuracion->centro;
	NumeroComplejo c = configuracion->c;
	char* nombreImagen = configuracion->nombreImagen;
	bool salidaEstandar = configuracion->salidaEstandar;

	simularConjuntoJulia(resolucion, dimension, centro, c, nombreImagen, salidaEstandar);
}

/* ******************************************************************
 *              TP0 - Simulación del Conjunto de Julia
 * *****************************************************************/

void simulacionJulia(int argc, char const *argv[]) {
	
	if ((argc != 1) && strcmp(argv[1], COMANDO_V) == 0) {

		printf("%s\n", "Version: 1.0");
		printf("Integrantes:\n" 
					"Mauro Toscano Gonella\n"
					"Patricio Iribarne Catella\n"
					"Marcos Vrljicak\n");

	} else {

		ConfiguracionConjunto* configuracion = leerDatos(argc, argv);
    
	    if (configuracion) {
	    	simularConjunto(configuracion);
	    	free(configuracion->nombreImagen);
	    }

	    free(configuracion);
	}
}

int main(int argc, char const *argv[]) {	
	simulacionJulia(argc, argv);
	return 0;
}

