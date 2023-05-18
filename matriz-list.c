#ifndef __MATRIZ_LIST_C__
#define __MATRIZ_LIST_C__
#include "matriz-list.h"

Matriz* createMatriz(dimensiones dimensionesMatriz, ...)
{
    // crea una matriz multidimensional
    va_list args;
    va_start(args, dimensionesMatriz);

    Matriz *my_matriz = newMatriz();
    my_matriz->dimensiones_matriz = dimensiones_matriz_va_list(dimensionesMatriz, args);
    // la matriz tiene un vector con las dimensiones de la matriz

    position totalElements = get_size_va_list(dimensionesMatriz, args);



    printf("totalElements: %d\n ", totalElements);

    /*for (int i = 0; i < totalElements; i++)
    {
        printf("%d ", my_matriz[i]);
    }*/

    va_end(args);

    return my_matriz;
}

dimensiones get_size_size_total(dimensiones dimensionesMatriz, ...)
{
    // obtiene la cantidad de elementos totales teoricos que puede tener una matriz:
    va_list args;
    va_start(args, dimensionesMatriz);
    position totalElements = get_size_va_list(dimensionesMatriz, args);
    va_end(args);
    return totalElements;
}

dimensiones get_size_va_list(dimensiones dimensionesMatriz, va_list args)
{
    // obtiene la cantidad de elementos totales teoricos que puede tener una matriz:
    position totalElements = 1;
    for (position i = 0; i < dimensionesMatriz; i++)
    {
        position num = va_arg(args, position);
        totalElements *= num;
        printf("(%d), ", num);
    }
    return totalElements;
}

LinkedList* dimensiones_matriz_va_list(dimensiones dimensionesMatriz, va_list args){
    LinkedList *my_dimension = createLinkedList();
    for(position i = 0; i < dimensionesMatriz; i++)
    {
        position *size = (position *)malloc(sizeof(position));
        *size = va_arg(args, position);

        push_back(my_dimension, size);
    }
    return my_dimension;
}

LinkedList* dimensiones_matriz(dimensiones dimensionesMatriz, ...){
    if (dimensionesMatriz == 0) return NULL;
    va_list args;
    va_start(args, dimensionesMatriz);
    LinkedList *my_dimension = dimensiones_matriz_va_list(dimensionesMatriz, args);
    va_end(args);
    return my_dimension;
}

Matriz* newMatriz()
{
    // crea un matrix vacia, vector(fila = row) para almacenar las columnas(columns)
    Matriz* my_matriz = (Matriz*)malloc(sizeof(Matriz));
    my_matriz->dimensiones_matriz = dimensiones_matriz(0);
    return my_matriz;
}

void createColumns(Matriz* matriz, position columns)
{
    // Crea una nueva columna en la matriz con el número de elementos especificado

    for (position i = 0; i < columns; i++)
    {
        LinkedList* column = createLinkedList();
        push_back(matriz->list, column);
    }
}

void createRow(Matriz* matriz, position row)
{
    // Crea una nueva fila en la matriz con el número de elementos especificado

    LinkedList* rowList = createLinkedList();

    for (position i = 0; i < row; i++)
    {
        LinkedList* column = get_element_v(matriz->list, i);
        push_back(rowList, column);
    }

    push_back(matriz->list, rowList);
}

void freeMatriz(Matriz* matriz)
{
    // Libera la memoria asignada para la matriz

    Node* current = matriz->list->head;

    while (current != NULL)
    {
        LinkedList* column = (LinkedList*)current->data;
        clear(column); // Limpia la columna
        current = current->next;
    }

    freeLinkedList(matriz->list); // Libera la lista principal
    freeLinkedList(matriz->dimensiones_matriz); // Libera la lista de dimensiones
    free(matriz); // Libera la estructura Matriz
}



#endif