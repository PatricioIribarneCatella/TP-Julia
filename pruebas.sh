#!/bin/bash

# Prueba 1: Imagen imposible (Hay cero píxeles de ancho)
./tp0 -c 0+0i -r 0x1 -o -

# Prueba 2: Archivo de salida imposible (El archivo no es válido)
./tp0 -o /tmp

# Prueba 3: Coordenadas complejas inválidas en el centro
./tp0 -c 1+3 -o -

# Prueba 4: Coordenadas complejas inválidas en el parámetro C
./tp0 -C 2+4 -o -

# Prueba 5: No se especifican las coordenadas del centro
./tp0 -c -o -

# Prueba 6: Ningún argumento ingresado
./tp0

# Prueba 7: Alto de la imagen inválido
./tp0 -H 3.0.0 -o -

# Prueba 8: Ancho de la imagen negativo
./tp0 -w -3.0

# Prueba 9: Imagen default
./tp0 -o imagenDefault.pgm
mv imagenDefault.pgm imagenes/

# Prueba 10: Imagen con parámetros [r: 1000x1000]
./tp0 -r 1000x1000 -o imagen1000x1000.pgm
mv imagen1000x1000.pgm imagenes/

# Prueba 11: Imagen con parámetros [r: 1000x1000, C: -0.75+0.0i, w(ancho): 3, H(alto): 3]
./tp0 -r 1000x1000 -C -0.75+0.0i -w 3.0 -H 3.0 -o imagen1.pgm
mv imagen1.pgm imagenes/

# Prueba 12: Imagen con parámetros [r: 1000x1000, C: -0.29799-0.65705i]
./tp0 -r 1000x1000 -C -0.29799-0.65705i -o imagen2.pgm
mv imagen2.pgm imagenes/

# Prueba 13: Imagen con parámetros [r: 1000x1000, C: -0.20722+0.64840i]
./tp0 -r 1000x1000 -C -0.20722+0.64840i -o imagen3.pgm
mv imagen3.pgm imagenes/

# Prueba 14: Imagen con parámetros [r: 1000x1000, C: -0.45793+0.52736i]
./tp0 -r 1000x1000 -C -0.45793+0.52736i -o imagen4.pgm
mv imagen4.pgm imagenes/

# Prueba 15: Imagen con parámetros [r: 1000x1000, C: -1.75473+0i]
./tp0 -r 1000x1000 -C -1.75473+0i -o imagen5.pgm
mv imagen5.pgm imagenes/
