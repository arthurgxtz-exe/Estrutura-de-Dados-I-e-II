#ifndef LIST_H
#define LIST_H

#include "object.h"

typedef struct _List{
    Object head;
    Object tail;
    int size;
}_List;

typedef _List* List;

List new_List();

void list_push(List l, Object obj);

void list_enqueue(List l, Object obj);

Object list_pop(List l);

void list_clear(List l);

void list_print(List l, void (*funcao_imprimir)(void*));

#endif
