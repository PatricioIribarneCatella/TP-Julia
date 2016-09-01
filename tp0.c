#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* ******************************************************************
 *                  Definición de los tipos de datos
 * *****************************************************************/

typedef struct Comando {


}Comando;

typedef struct ConfiguracionConjunto {


}ConfiguracionConjunto;

typedef struct ConjuntoDeJulia {
	
	
}ConjuntoDeJulia;


/* ******************************************************************
 *                        Función de Lectura
 * *****************************************************************/

Comando* *leerDatos() {


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


}

/* ******************************************************************
 *                 Genera la salida correspondiente
 * *****************************************************************/

void generarSalidaDeLaSimulacion(ConjuntoDeJulia* conjuntoJulia, ConfiguracionConjunto* configuracion) {


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

/* ******************************************************************
 *              TP0 - Simulación del Conjunto de Julia
 * *****************************************************************/

void simulacionJulia() {

	Comando* *comandos = leerDatos();

	ConfiguracionConjunto* configuracion = configurarConjunto(comandos);

	ConjuntoDeJulia* conjuntoDeJulia = simularConjunto(configuracion);

	generarSalidaDeLaSimulacion(conjuntoDeJulia, configuracion);

	destruirComandos(comandos);
	destruirConfiguracionConjunto(configuracion);
	destruirConjuntoDeJulia(conjuntoDeJulia);
}

int main(int argc, char const *argv[]) {
	
	simulacionJulia();

	return 0;
}