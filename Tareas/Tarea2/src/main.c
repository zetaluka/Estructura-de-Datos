#include "commons.h"

int main(){

    int i = 0;
    Struct_Producto producto[MAXPRODUCTO] = {0};

    srand(time(NULL));

    genera_nombres(producto); //Asigna los nombres de los productos

    for(i = 0; i < MAXPRODUCTO; i++)
        genera_cantidad(&producto[i]); //Genera la cantidad de los productos

    for(i = 0; i < MAXPRODUCTO; i++)
        genera_precio(producto, i); //Genera el precio de los productos via usuario

    for(i = 0; i < MAXPRODUCTO; i++)
        genera_proveedor(&producto[i]); //Genera el proveedor del producto de manera aleatoria

    print_productos(producto); //Imprime todo el arreglo de estructuras producto 
    
    if(producto_to_csv(producto) == 0) //Guarda el arreglo de estructura producto en un archivo .csv
        printf("\nGuardando en producto.csv ...\n");
    else
        printf("\nError al guardar producto.csv\n");

    return 0;
}