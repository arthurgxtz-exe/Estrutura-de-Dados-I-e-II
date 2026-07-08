#ifndef LIST_H
#define LIST_H

#include "object.h"


typedef struct _List _List;
typedef _List* List;

struct _List {
    Object head;
    Object tail;
    int size;

    void (*enqueue)(List self, Object novo);
    void (*push)(List self, Object novo);
    Object (*pop)(List self);
    void (*print)(List self);
    void (*clear)(List self);
    void (*del)(List self, int pos);
    Object (*get)(List self, int pos);
};



List new_List(void);

void list_Enqueue(List self, Object novo);
void list_Push(List self, Object novo);
Object list_Pop(List self);
void list_Print(List self);
void list_Clear(List self);
void list_Delete(List self, int pos);
Object list_Get(List self, int pos);



List filter(List self, TypeNode type);
List join(List first, List second);

int count_Type(List self, TypeNode type);
Object find_Type(List self, TypeNode type);
void remove_Type(List self, TypeNode type);


List new_List(void) {
    List list = malloc(sizeof(_List));

    if (!list) {
        printf("Erro ao alocar List.\n");
        exit(1);
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    list->enqueue = list_Enqueue;
    list->push = list_Push;
    list->pop = list_Pop;
    list->print = list_Print;
    list->clear = list_Clear;
    list->del = list_Delete;
    list->get = list_Get;

    return list;
}


void list_Enqueue(List self, Object novo) {
    if (!self || !novo) return;

    novo->next = NULL;
    novo->prev = NULL;

    if (!self->head) {
        self->head = novo;
        self->tail = novo;
    } else {
        self->tail->next = novo;
        novo->prev = self->tail;
        self->tail = novo;
    }

    self->size++;
}


void list_Push(List self, Object novo) {
    if (!self || !novo) return;

    novo->next = NULL;
    novo->prev = NULL;

    if (!self->head) {
        self->head = novo;
        self->tail = novo;
    } else {
        self->head->prev = novo;
        novo->next = self->head;
        self->head = novo;
    }

    self->size++;
}


Object list_Pop(List self) {
    if (!self || !self->head) return NULL;

    Object current = self->head;

    self->head = current->next;

    if (!self->head)
        self->tail = NULL;
    else
        self->head->prev = NULL;

    current->next = NULL;
    current->prev = NULL;

    self->size--;

    return current;
}


void list_Print(List self) {
    if (!self || !self->head) {
        printf("Lista vazia.\n");
        return;
    }

    Object current = self->head;
    int position = 0;

    printf("----- LISTA | size: %d -----\n", self->size);

    while (current) {
        current->print(current, position);
        current = current->next;
        position++;
    }

    printf("----------------------------\n");
}


void list_Clear(List self) {
    if (!self) return;

    Object current = self->head;

    while (current) {
        Object next = current->next;

        current->next = NULL;
        current->prev = NULL;

        current->destroy(current);

        current = next;
    }

    self->head = NULL;
    self->tail = NULL;
    self->size = 0;
}


Object list_Get(List self, int pos) {
    if (!self || pos < 0 || pos >= self->size)
        return NULL;

    Object current = self->head;

    for (int i = 0; i < pos; i++)
        current = current->next;

    return current;
}


void list_Delete(List self, int pos) {
    if (!self || pos < 0 || pos >= self->size)
        return;

    Object current = list_Get(self, pos);

    if (!current) return;

    if (current == self->head)
        self->head = current->next;

    if (current == self->tail)
        self->tail = current->prev;

    if (current->prev)
        current->prev->next = current->next;

    if (current->next)
        current->next->prev = current->prev;

    current->next = NULL;
    current->prev = NULL;

    current->destroy(current);

    self->size--;
}


List filter(List self, TypeNode type) {
    List result = new_List();

    if (!self) return result;

    Object current = self->head;

    while (current) {
        if (current->type == type)
            result->enqueue(result, copy_Object(current));

        current = current->next;
    }

    return result;
}


List join(List first, List second) {
    List result = new_List();

    Object current;

    if (first) {
        current = first->head;

        while (current) {
            result->enqueue(result, copy_Object(current));
            current = current->next;
        }
    }

    if (second) {
        current = second->head;

        while (current) {
            result->enqueue(result, copy_Object(current));
            current = current->next;
        }
    }

    return result;
}


int count_Type(List self, TypeNode type) {
    if (!self) return 0;

    int count = 0;
    Object current = self->head;

    while (current) {
        if (current->type == type)
            count++;

        current = current->next;
    }

    return count;
}


Object find_Type(List self, TypeNode type) {
    if (!self) return NULL;

    Object current = self->head;

    while (current) {
        if (current->type == type)
            return current;

        current = current->next;
    }

    return NULL;
}


void remove_Type(List self, TypeNode type) {
    if (!self) return;

    Object current = self->head;
    int pos = 0;

    while (current) {
        if (current->type == type) {
            list_Delete(self, pos);
            return;
        }

        current = current->next;
        pos++;
    }
}

#endif
