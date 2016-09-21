# TP0-Julia

Simulación de los conjuntos de Julia

**Compilación (Linux/NetBSD)**

$ make

**Generar código Assembly-MIPS en NetBSD**

$ gcc -Wall -std=c99 -O0 -S -mrnames tp0.c

**Ejecución**

$ ./tp0 -r ANCHOxALTO -c a+bi -C c+di -w AnchoRegionPlanoComplejo -H AltoRegionPlanoComplejo -o nombreImagen.pgm

**Pruebas**

$ bash pruebas.sh