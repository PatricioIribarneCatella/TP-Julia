#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "tiposDeDatos.h"
#include "NumeroComplejo.h"

#define HEADER_IMAGEN "P2"
#define MAXIMA_INTENSIDAD_PIXEL 255

/* ******************************************************************
 *            Funciones para simular el conjunto de Julia
 * *****************************************************************/

static unsigned char calcularBrillo(NumeroComplejo numeroComplejo, NumeroComplejo c){
	
	NumeroComplejo iComplejo = numeroComplejo;
	unsigned char i = 0;

	while(i < 255 && moduloAlCuadrado(iComplejo) <= 4){
		iComplejo = sumar(multiplicar(iComplejo, iComplejo),c);
		i++;
	}

	return i;
}

static NumeroComplejo transformarPixel(int i, int j, NumeroComplejo zInicio, double anchoPixel, double altoPixel) {

	NumeroComplejo numero;

	/*Se incrementa el píxel teniendo en cuenta en cual se está*/

	numero.parteReal = zInicio.parteReal + j*anchoPixel;
	numero.parteImaginaria = zInicio.parteImaginaria - i*altoPixel;

	return numero;
}

static NumeroComplejo obtenerZInicio(NumeroComplejo centro, Dimension dimension, Resolucion resolucion) {

	NumeroComplejo zInicio;

	/*Calculo el ancho del píxel en función del tamaño de la imagen y la resolución*/

	double anchoPixel = dimension.ancho/resolucion.ancho;
	double altoPixel = dimension.alto/resolucion.alto;

	/*Me posiciono en la esquina superior izquierda con respecto al centro de la imagen*/

	zInicio.parteReal = centro.parteReal - dimension.ancho/2;
	zInicio.parteImaginaria = centro.parteImaginaria + dimension.alto/2;

	double deltaAnchoPixel = anchoPixel/2;
	double deltaAltoPixel = altoPixel/2;

	/*Me centro en punto medio del píxel*/

	zInicio.parteReal = zInicio.parteReal + deltaAnchoPixel;
	zInicio.parteImaginaria = zInicio.parteImaginaria - deltaAltoPixel;

	return zInicio;
}

void simularConjuntoJulia(Resolucion resolucion, Dimension dimension, NumeroComplejo centro, NumeroComplejo c, FILE* imagen) {

	int anchoRes = resolucion.ancho;
	int altoRes = resolucion.alto;

	fprintf(imagen, "%s\n", HEADER_IMAGEN);
	fprintf(imagen, "%d\n", anchoRes);
	fprintf(imagen, "%d\n", altoRes);
	fprintf(imagen, "%d\n", MAXIMA_INTENSIDAD_PIXEL);

	int brillo;
	NumeroComplejo complejoAsociadoAPixel;

	NumeroComplejo zInicio = obtenerZInicio(centro, dimension, resolucion);

	/*Calculo el ancho del píxel en función del tamaño de la imagen y la resolución*/

	double anchoPixel = dimension.ancho/resolucion.ancho;
	double altoPixel = dimension.alto/resolucion.alto;

	for (int i = 0; i < altoRes; i++) {

		for (int j = 0; j < anchoRes; j++) {

			complejoAsociadoAPixel = transformarPixel(i, j, zInicio, anchoPixel, altoPixel);
			brillo = calcularBrillo(complejoAsociadoAPixel, c);

			fprintf(imagen, "%d ", brillo);
		}

		fprintf(imagen, "%s\n", "");
	}

	fclose(imagen);
}
