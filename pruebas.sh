#!/bin/bash

# Prueba 1: Imagen imposible (Hay cero pixeles de ancho)
./tp0 -c 0+0i -r 0x1 -o -

# Prueba 2: Archivo de salida imposible (El archivo no es válido)
./tp0 -o /tmp

# Prueba 3: Coordenadas complejas inválidas
./tp0 -c 1+3 -o -

# Prueba 4: Argumentos de lı́nea de comando vacı́os
./tp0 -c -o -