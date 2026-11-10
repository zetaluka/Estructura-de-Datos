/**
 * @file abb.c
 * @brief Funciones de árboles binarios de búsqueda (ABB) de productos
 *
 * Cada nodo del árbol guarda un producto y sus dos hijos. El orden lo da el
 * precio: en el subárbol izquierdo de un nodo están los productos más baratos
 * y en el derecho los más caros, por lo que no puede haber dos productos con
 * el mismo precio.
 *
 * Un árbol vacío es un puntero nulo. Por eso las funciones que pueden cambiar
 * la raíz (abb_insert y abb_delete_tree) retornan el árbol resultante y se
 * usan siempre de la forma ABB = abb_insert(P, ABB).
*/

/*
 * EN CLASE:
 *  1. Define los atributos de `struct Node` en inc/abb.h.
 *  2. Implementa cada función de este archivo: reemplaza el `;` del final de
 *     su prototipo por el cuerpo de la función `{ ... }`.
 */
#include "abb.h"

static void error(const char *texto);

//==============================================================================
//        FUNCIONES DE INSERCIÓN
//==============================================================================

/**
 * @brief Inserta un producto en el ABB, según su precio
 *
 * Un producto más barato que el del nodo actual se inserta a la izquierda y
 * uno más caro a la derecha. El árbol pasa a ser el dueño de los strings del
 * producto, por lo que quien llama nunca debe liberarlo después de insertarlo.
 *
 * No se permiten precios repetidos: si ya existe un producto con ese precio se
 * imprime "Error" y se libera el producto entregado. Lo mismo ocurre si no hay
 * memoria para el nodo. Si el producto es inválido (name o provider en NULL,
 * es decir, un prod_create fallido) se imprime "Error" y el árbol queda
 * intacto.
 *
 * @param P Producto a insertar
 * @param T ABB donde se debe insertar el producto
 * @return SearchTree Referencia al ABB con el producto insertado
 */
SearchTree abb_insert(Product P, SearchTree T)
{
    if(P.name == NULL || P.provider == NULL)
    {
        error("Producto invalido");
        prod_delete(P);
        return T;
    }

    if(T == NULL)
    {
        Position aux = malloc(sizeof(struct Node));

        if(aux == NULL)
        {
            error("Memoria insuficiente");
            prod_delete(P);
            return NULL;
        }

        aux->product = P;
        aux->Left = NULL;
        aux->Right = NULL;

        return aux;
    }

    if(P.price < T->product.price)
        T->Left = abb_insert(P, T->Left);
    else if(P.price > T->product.price)
        T->Right = abb_insert(P, T->Right);
    else
    {
        error("Producto con precio ya existente");
        prod_delete(P);
    }

    return T;
}

//==============================================================================
//        FUNCIONES DE BÚSQUEDA
//==============================================================================

/**
 * @brief Busca en el ABB el producto que tiene un precio determinado
 *
 * En cada nodo se compara el precio buscado con el del nodo y se sigue por el
 * subárbol izquierdo (si es menor) o por el derecho (si es mayor), descartando
 * el otro. Se retorna el nodo que contiene el producto, no una copia.
 *
 * Si no existe un producto con ese precio, o el árbol está vacío, se imprime
 * un aviso con el precio buscado y se retorna un puntero nulo.
 *
 * @param price Precio del producto a buscar
 * @param T ABB donde se busca
 * @return Position Nodo que contiene el producto, o NULL si no se encuentra
 */
Position abb_find(float price, SearchTree T)
{
    if(T == NULL)
    {
        printf("\n\033[31mError: Precio %.1f no encontrado\n\033[0m", price);
        return NULL;
    }

    if(price < T->product.price)
        return abb_find(price, T->Left);
    else if(price > T->product.price)
        return abb_find(price, T->Right);

    return T;
}

/**
 * @brief Busca el producto más barato del ABB
 *
 * El más barato es siempre el nodo que queda más a la izquierda. Si el árbol
 * está vacío se imprime "Error" y se retorna un puntero nulo.
 *
 * @param T ABB donde se busca
 * @return Position Nodo con el producto más barato, o NULL si el árbol está vacío
 */
Position abb_find_min(SearchTree T)
{
    if(T == NULL)
    {
        error("ABB Vacío");
        return NULL;
    }

    if(T->Left != NULL)
    {
        return abb_find_min(T->Left);
    }

    return T;
}

/**
 * @brief Busca el producto más caro del ABB
 *
 * El más caro es siempre el nodo que queda más a la derecha. Si el árbol está
 * vacío se imprime "Error" y se retorna un puntero nulo.
 *
 * @param T ABB donde se busca
 * @return Position Nodo con el producto más caro, o NULL si el árbol está vacío
 */
Position abb_find_max(SearchTree T)
{
    if(T == NULL)
    {
        error("ABB Vacío");
        return NULL;
    }

    if(T->Right != NULL)
    {
        return abb_find_max(T->Right);
    }

    return T;
}

//==============================================================================
//        FUNCIONES DE RECORRIDO
//==============================================================================

/**
 * @brief Imprime el ABB en inorder (izquierda, raíz, derecha)
 *
 * Los productos salen ordenados de menor a mayor precio. Se imprime una línea
 * por producto, con el formato "nombre [precio]". Si el árbol está vacío no se
 * imprime nada.
 *
 * @param T ABB a imprimir
 */
void abb_print_inorder(SearchTree T)
{
    if(T != NULL)
    {
        abb_print_inorder(T->Left);
        printf("%s [%.1f]\n", T->product.name, T->product.price);
        abb_print_inorder(T->Right);
    }
}

/**
 * @brief Imprime el ABB en preorder (raiz, izquierda, derecha).
 *
 * Recorre primero la raiz, luego el subarbol izquierdo
 * y finalmente el derecho. No imprime nada si el arbol
 * esta vacio.
 *
 * @param T ABB a imprimir
 */
void abb_print_preorder(SearchTree T)
{
    if(T != NULL)
    {
        printf("%s [%.1f]\n", T->product.name, T->product.price);
        abb_print_preorder(T->Left);
        abb_print_preorder(T->Right);
    }
}

/**
 * @brief Imprime el ABB en postorder (izquierda, derecha, raiz).
 *
 * Recorre primero el subarbol izquierdo, luego el subarbol derecho
 * y finalmente la raiz. No imprime nada si el arbol
 * esta vacio.
 *
 * @param T ABB a imprimir
 */
void abb_print_postorder(SearchTree T)
{
    if(T != NULL)
    {
        abb_print_postorder(T->Left);
        abb_print_postorder(T->Right);
        printf("%s [%.1f]\n", T->product.name, T->product.price);
    }
}

//==============================================================================
//        FUNCIONES DE ELIMINACIÓN
//==============================================================================

/**
 * @brief Elimina todos los nodos del ABB
 *
 * Se libera la memoria de todos los productos y nodos. Los nodos se liberan
 * en postorder (primero los dos subárboles y al final la raíz), porque si se
 * liberara la raíz primero se perdería el acceso a sus hijos. Después de
 * llamarla, T deja de ser válido, por lo que se debe asignar el valor
 * retornado: ABB = abb_delete_tree(ABB).
 *
 * @param T ABB a eliminar
 * @return SearchTree Siempre NULL (el árbol vacío)
 */
SearchTree abb_delete_tree(SearchTree T)
{
    if(T == NULL)
        return NULL;

    abb_delete_tree(T->Left);
    abb_delete_tree(T->Right);

    prod_delete(T->product);
    free(T);

    return NULL;
}

/**
 * @brief Elimina un producto del ABB segun su precio
 * 
 * Elimina el producto considerando 3 casos, sin hijos, con 1 hijo o con 2 hijos.
 * Sin hijos: Elimina el producto liberando su memoria.
 * 1 hijo: Guarda un puntero auxiliar al hijo, libera el producto y retorna el puntero auxiliar
 * 2 hijos: Se busca el precio menor del subarbol derecho para intercambiar sus productos
 * y elimina el producto original.
 * 
 * @param price Precio del producto a eliminar
 * @param T ABB
 * @return SearchTree Arbol resultante
 */
SearchTree abb_delete_price(float price, SearchTree T)
{
    if(T == NULL)
    {
        printf("\n\033[31mError: Precio %.1f no encontrado\n\033[0m", price);
        return NULL;
    }

    if(price < T->product.price)
    {
        T->Left = abb_delete_price(price, T->Left);
        return T;
    }
    else if(price > T->product.price)
    {
        T->Right = abb_delete_price(price, T->Right);
        return T;
    }

    // Caso 1: Sin hijos
    if(T->Left == NULL && T->Right == NULL)
    {
        prod_delete(T->product);
        free(T);
        return NULL;
    }

    // Caso 2: Un hijo
    if(T->Left == NULL)
    {
        Position aux = T->Right;
        prod_delete(T->product);
        free(T);
        return aux;
    }

    if(T->Right == NULL)
    {
        Position aux = T->Left;
        prod_delete(T->product);
        free(T);
        return aux;
    }

    // Caso 3: 2 Hijos
    Position aux;

    aux = abb_find_min(T->Right);

    Product temp = T->product;
    T->product = aux->product;
    aux->product = temp;

    T->Right = abb_delete_price(price, T->Right);

    return T;
}

//==============================================================================
//        FUNCIONES AUXILIARES
//==============================================================================

/**
 * @brief Devuelve el precio del producto que está en una posición del ABB
 *
 * Si la posición es nula se imprime "Error" y se retorna -1.
 *
 * @param P Posición (nodo) del ABB
 * @return float Precio del producto, o -1 si la posición es nula
 */
float abb_position_get_price(Position P)
{
    if(P == NULL)
    {
        error("Posicion invalida");
        return -1;
    }

    return P->product.price;
}

/**
 * @brief Mensaje de error
 * 
 * @param texto mensaje a mostrar
 */
static void error(const char *texto)
{
    printf("\n\033[31mError: %s\n\033[0m", texto);
}
