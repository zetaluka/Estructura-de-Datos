#ifndef COMMONS
#define COMMONS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAXPRODUCTO 5

/**
 * @brief Estructura de un producto de una tienda
 */

typedef struct 
{
    int cantidad; //Cantidad del producto
    int precio; //Precio del producto
    char nombre[20]; //Arreglo de strings que almacena el nombre del producto
    char proveedor[6]; //Arreglo de strings que almacena el proveedor del producto
} Struct_Producto;

void genera_nombres(Struct_Producto *producto);
void genera_cantidad(Struct_Producto *producto);
void genera_proveedor(Struct_Producto *producto);
void genera_precio(Struct_Producto *producto, int i);
void print_productos(Struct_Producto *producto);
int producto_to_csv(Struct_Producto *producto);

#endif