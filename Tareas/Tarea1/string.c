/*
============================ Ejercicio 2 ==============================
Crear un programa (con el esqueleto que se deja a continuacion) donde
se generen cadenas de caracteres aleatorias de 5, 10, 15 y 20 caracteres
de largo, y se muestren por pantalla.

--------------------------- Tips -------------------------------------
1. En C, los caracteres son en el fondo numeros: cada letra tiene un
codigo asociado en la tabla ASCII. Investiga en que rango de numeros
se encuentran las letras mayusculas y en cual las minusculas.

2. Si guardas la cadena en un arreglo de char, no olvides dejar espacio
para el caracter nulo '\0' al final, que es el que le indica a C donde
termina la cadena.
=======================================================================
*/

#include <stdio.h>   /* <-- Para usar printf      */
#include <stdlib.h>  /* <-- Para usar rand y srand */
#include <time.h>    /* <-- Para usar time(NULL)   */

#define MAXFIL 4
#define MAXCOL 21

int main(void)
{
    int i = 0, j = 0, cant = 0;
    char letra[MAXFIL][MAXCOL];
    srand(time(NULL));

    for(i = 0; i < 4; i++)
    {
        cant += 5;
        printf("Cadena de %d caracteres: ", cant);

        for(j = 0; j < cant; j++)
            letra[i][j] = (rand()%26) + 65;
        
        letra[i][cant] = '\0';

        printf("%s\n", letra[i]);
    }

	return 0;
}


/*
========================== Salida Esperada ==========================
> gcc string.c -o string.out
> ./string.out
> Cadena de 5 caracteres:  JQXTR
> Cadena de 10 caracteres: MZKPLQARWY
> Cadena de 15 caracteres: BHNOPXQZTYVCLEK
> Cadena de 20 caracteres: DFGHJKLMNPQRSTVWXYZA
=====================================================================
*/