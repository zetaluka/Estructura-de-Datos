/**
 * @file inventory.c
 * @brief Funciones relacionadas con inventarios de productos
*/
#include "inventory.h"


//==============================================================================
//        FUNCIONES RELACIONADAS CON LOS PRODUCTOS DEL INVENTARIO
//==============================================================================

Inventory inv_delete(InventoryElement Position, Inventory I)
{
    // Verifica que I, el puntero a la posicion sea NULL, ademas de comprobar que la posicion no es la del centinela
    if(I == NULL || Position == NULL || Position == I)
    {
        printf("\033[31m\nError\n\033[0m");
        return I;
    }

    prod_delete(Position->product);

    (Position->prev)->next = Position->next;
    (Position->next)->prev = Position->prev;

    free(Position);

    return I;
}

Inventory inv_insert_first(Product P, Inventory I)
{
    return inv_insert(P, I, I);
}

Inventory inv_insert_last(Product P, Inventory I)
{
    return inv_insert(P, I, inv_last(I));
}

Product* inv_retrieve(InventoryElement Position, Inventory I)
{
    // Verifica que I, el puntero a la posicion sea NULL, ademas de comprobar que la posicion no es la del centinela
    if(I == NULL || Position == NULL || Position == I)
    {
        printf("\033[31m\nError\n\033[0m");
        return NULL;
    }

    return &Position->product;
}


//==============================================================================
//        FUNCIONES RELACIONADAS CON LOS ÍNDICES DEL INVENTARIO
//==============================================================================

InventoryElement inv_first(Inventory I)
{
    if(I == NULL)
    {
        printf("\033[31m\nError: No existe inventario\n\033[0m");
        return NULL;
    }

    return inv_forward(I);
}

InventoryElement inv_header(Inventory I)
{
    return I;
}

InventoryElement inv_last(Inventory I)
{
    if(I == NULL)
    {
        printf("\033[31m\nError: No existe inventario\n\033[0m");
        return NULL;
    }

    return inv_backward(I);
}

InventoryElement inv_forward(InventoryElement Position)
{
    if(Position == NULL)
    {
        printf("\033[31m\nError: No existe una posicion siguiente\n\033[0m");
        return NULL;
    }

    return Position->next;
}

InventoryElement inv_backward(InventoryElement Position)
{
    if(Position == NULL)
    {
        printf("\033[31m\nError: No existe una posicion anterior\n\033[0m");
        return NULL;
    }

    return Position->prev;
}

//==============================================================================
//        FUNCIONES RELACIONADAS CON LA TOTALIDAD DEL INVENTARIO
//==============================================================================

Inventory inv_make_empty(Inventory I)
{
    if(I != NULL)
    {
        inv_destroy(I);
    }

    if((I = malloc(sizeof(struct Node))) == NULL)
    {
        printf("\033[31m\nError: No se pudo crear el nodo correctamente\n\033[0m");
        return NULL;
    }
    
    I->next = I;
    I->prev = I;

    return I;
}

Inventory inv_insert(Product P, Inventory I, InventoryElement Position)
{
    // Verifica que I o el puntero a la posicion o algun puntero de la estructura producto no sea NULL para evitar Errores
    if(I == NULL || Position == NULL || P.name == NULL || P.provider == NULL)
    {
        printf("\033[31m\nError\n\033[0m");
        return I;
    }

    InventoryElement aux = malloc(sizeof(struct Node));

    if (aux == NULL)
    {
        printf("\033[31m\nError\n\033[0m");

        return I;
    }

    aux->next = Position->next;
    aux->prev = Position;
    Position->next = aux;
    (aux->next)->prev = aux;
    aux->product = P;

    return I;
}

void inv_print(Inventory I)
{
    int num = 1;

    if(I == NULL)
    {   
        return;
    }

    if(inv_is_empty(I) == 1) return;

    InventoryElement aux = I->next;

    printf("\n\n\033[1;36m============= Productos ===============\n\033[0m");
    while(aux != I)
    {
        printf("\n\033[4;36mProducto %d: \n\033[0m", num);
        
        prod_print(aux->product);

        aux = inv_forward(aux);
        num++;
    }

    printf("\033[36m\n\nCantidad total de productos: %d\n\033[0m", num - 1);
}

//==============================================================================
//        FUNCIONES DE COMPROBACIÓN DE ESTADO
//==============================================================================

void inv_destroy(Inventory I)
{
    if (I == NULL){
        return;
    }
    
    InventoryElement aux = I->next; //Puntero al primer nodo despues del centinela

    while(aux != I) // Bucle mientras aux no apunte al centinela
    {
        InventoryElement nextNode = aux->next; // Puntero al siguiente nodo como auxiliar 

        prod_delete(aux->product);
        free(aux); 

        aux = nextNode;
    }
    
    free(I);
}

int inv_is_empty(Inventory I)
{
    if(I == NULL || I->next == I)
    {
        printf("\033[31m\nInventario vacio o no existente\n\033[0m");
        return 1;
    }

    return 0;
}

int inv_is_last(InventoryElement Position, Inventory I)
{
    if(I == NULL || Position == NULL || Position == I)
    {
        printf("\033[31m\nError\n\033[0m");
        return 0;
    }

    if(Position->next == I)
    {
        printf("\nElemento en la ultima posicion del inventario\n");
        return 1;
    }

    return 0;
}

//==============================================================================
//        FUNCIONES DE BUSQUEDA
//==============================================================================

Product* inv_find_by_name(char* name, Inventory I)
{
    if (name == NULL) // Verifica que el parametro nombre no sea NULL antes de seguir
    {
        printf("\033[31m\nError\n\033[0m");
        return NULL;
    }

    if (I == NULL || I->next == I)
    {
        printf("\033[31m\nProducto (%s) no encontrado\n\033[0m", name);
        return NULL;
    }

    InventoryElement pA = inv_forward(I), pR = inv_backward(I);
    int it = 0;

    while(1)
    {
        it++;

        if(pA == pR && strcmp(name, pA->product.name) == 0)
        {
            printf("\033[32m\nProducto (%s) encontrado por puntero de avance y puntero de retroceso en %d iteraciones\n\033[0m", name, it);
            return &pA->product;
        }
        else if(strcmp(name, pA->product.name) == 0)
        {
            printf("\033[32m\nProducto (%s) encontrado por puntero de avance en %d iteraciones\n\033[0m", name, it);
            return &pA->product;
        }
        else if(strcmp(name, pR->product.name) == 0)
        {
            printf("\033[32m\nProducto (%s) encontrado por puntero de retroceso en %d iteraciones\n\033[0m", name, it);
            return &pR->product;
        }
        
        if(pA == pR || pA->next == pR)
        {
            printf("\033[31m\nProducto (%s) no encontrado en %d iteraciones\n\033[0m", name, it);
            return NULL;
        }

        pA = inv_forward(pA);
        pR = inv_backward(pR);
    }

}
