#include "commons.h"

/**
 * @brief Funcion que asigna los nombres del producto
 * 
 * @param producto Puntero al arreglo completo de estructuras producto
 */
void genera_nombres(Struct_Producto *producto)
{
    char nombres[5][20] = {"Queso", "Jamon", "Pan", "Fideos", "Salsa"}; //Arreglo de strings que almacenan los nombres de algunos productos

    for(int i = 0; i < MAXPRODUCTO; i++)
    {
        if(i < 5) strcpy(producto[i].nombre, nombres[i]); //Copia el nombre del producto desde el arreglo de strings de nombres al campo nombre de la struct producto
        else strcpy(producto[i].nombre, "Desconocido"); //En caso de cambiar MAXPRODUCTO a un valor diferente a 5, si sobrepasa la cantidad de 5 productos lo deja como Desconocido
    }

}

/**
 * @brief Funcion que genera el proveedor de manera aleatoria
 * 
 * @param producto Puntero a un elemento del arreglo de estructuras producto
 */
void genera_proveedor(Struct_Producto *producto)
{
    int i = 0;

    for(i = 0; i < 5; i++)
        producto->proveedor[i] = (rand()%26) + 65; //Genera el nombre de un proveedor con 5 letras aleatorias
    
    producto->proveedor[i] = '\0';

}

/**
 * @brief Funcion que guarda el arreglo de estructuras producto en un archivo .csv
 * 
 * @param producto Puntero al arreglo completo de estructuras producto
 */
int producto_to_csv(Struct_Producto *producto)
{
    FILE *fdata;

    if((fdata = fopen("build/producto.csv","w")) == NULL)
        return 1;

    fprintf(fdata, "Nombre,Cantidad,Proveedor,Precio\n"); 

	for(int i = 0; i < MAXPRODUCTO; i++)
        fprintf(fdata, "%s,%d,%s,%d\n", producto[i].nombre, producto[i].cantidad, producto[i].proveedor, producto[i].precio); //Guarda los datos en el archivo .csv

    fclose(fdata);

    return 0;
}

/**
 * @brief Funcion que genera las cantidades de un producto de manera aleatoria
 * 
 * @param producto Puntero a un elemento del arreglo de estructuras producto
 */
void genera_cantidad(Struct_Producto *producto)
{
    producto->cantidad = ((rand()%10) + 1);
}

/**
 * @brief Funcion que asigna los precios de un producto via scanf
 * 
 * @param producto Puntero a un elemento del arreglo de estructuras producto
 * @param i indice del elemento del arreglo de estructuras producto
 */
void genera_precio(Struct_Producto *producto, int i)
{
    bool precioAsignado = false;

    printf("\nEscoja el precio del producto %d (%s): ", i+1, producto[i].nombre);
    do
    {
        if(precioAsignado)
            printf("ERROR: Ingrese una cantidad positiva: ");
        scanf("%d", &producto[i].precio);
        precioAsignado = true;
    } while (producto[i].precio <= 0);

}

/**
 * @brief Funcion que imprime todo el arreglo de estructuras producto
 * 
 * @param producto Puntero al arreglo completo de estructuras producto
 */
void print_productos(Struct_Producto *producto)
{
    printf("\n========Productos=========\n");

    for(int i = 0; i < MAXPRODUCTO; i++)
        printf("\nNombre: %s\nCantidad: %d\nProveedor: %s\nPrecio: %d\n", producto[i].nombre, producto[i].cantidad, producto[i].proveedor, producto[i].precio);
}