/*
============================ Ejercicio 1 ==============================
Crear un programa (con el esqueleto que se deja a continuacion) donde
se reciba por consola un numero entero positivo correspondiente a una
cantidad de notas que se van a generar aleatoriamente entre 1.0 y 7.0
(datos de tipo flotante).

A continuacion calcular el promedio  de  las  notas  y  mostrarlo  por
pantalla.

--------------------------- Tips -------------------------------------
1. En este caso se usa el paso de parametros no con scanf() sino di-
rectamente por consola escribiendo "./random.out <numero>", esto se
conoce como "Acceso a linea de comandos", puedes investigar mas al res-
pecto, pero en el esqueleto de este ejercicio se deja una pista de como
usarlo.

2. Es importante asegurar que todas las variables esten en rangos 
razonables: la cantidad de notas debe ser positiva, y los valores de
las notas deben estar entre 1.0 y 7.0.

3. Tip importante, al trabajar en C no usaremos tildes ni caracteres
especiales unicos en el espanhol (como la letra enhe que generalmente se
escribe como "nh") ¡Pregunta la razon en la clase!.
=======================================================================
*/

#include <stdio.h>   /* <-- Para usar printf     */
#include <stdlib.h>  /* <-- Para usar srand      */
#include <time.h>    /* <-- Para usar time(NULL) */

int main(int argc, char *argv[])
{
	int n = -1, i = 0;
    float result = 0;

    srand(time(0));

	if (argc == 2)
	{
		n = atoi(argv[1]);
	}

    if(n <= 0) 
    {
        printf("ERROR: Ingrese un numero positivo\n");
        return 1;
    }

    float notas[n];

	printf("Se recibio el numero %d por consola\n", n);

    for(i = 0; i < n; i++)
        notas[i] = (float)((rand()%61)+ 10) / 10;
    
    printf("Notas obtenidas (%d): [", n);

    for(i = 0; i < n; i++)
    {
        printf("%.1f", notas[i]);

        if(i < n - 1)
            printf(", ");
        else 
            printf("]\n");

        result += notas[i];
    }

    result /= n;
    
    printf("Promedio obtenido (%d): %.1f\n", n, result);

	return 0;
}


/*
========================== Salida Esperada ==========================
> gcc random.c -o random.out
> 
> ./random.out 5
> Notas obtenidas (5): [1.0, 5.3, 4.7, 3.2, 2.8]
> Promedio obtenido: 3.4

> ./random.out 3
> Notas obtenidas (10): [1.0, 5.0, 7.0]
> Promedio obtenido: 4.3
=====================================================================
*/