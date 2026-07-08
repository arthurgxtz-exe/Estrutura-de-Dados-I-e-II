#ifndef HTABLE_H
#define HTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include "object.h"
#include "list.h"

typedef struct __HTable __HTable;
typedef __HTable* HTable;

struct __HTable {
    List* buckets;
    int size;
    int count;

    void (*insert)(HTable self, int value);
    Object (*search)(HTable self, int value);
    void (*delete)(HTable self, int value);
    void (*print)(HTable self);
    void (*clear)(HTable self);
    void (*destroy)(HTable self);
};

HTable new_HTable(int size);
int htable_Hash(HTable self, int value);
void htable_Insert(HTable self, int value);
Object htable_Search(HTable self, int value);
void htable_Delete(HTable self, int value);
void htable_Print(HTable self);
void htable_Clear(HTable self);
void htable_Destroy(HTable self);

HTable new_HTable(int size) {
    HTable ht;
    int i;

    if (size <= 0) {
        printf("Tamanho invalido para a Hash Table.\n");
        return NULL;
    }

    ht = malloc(sizeof(__HTable));

    if (!ht) {
        printf("Erro ao alocar HTable.\n");
        exit(1);
    }

    ht->buckets = malloc(size * sizeof(List));

    if (!ht->buckets) {
        printf("Erro ao alocar os buckets.\n");
        free(ht);
        exit(1);
    }

    ht->size = size;
    ht->count = 0;

    for (i = 0; i < size; i++)
        ht->buckets[i] = new(List);

    ht->insert = htable_Insert;
    ht->search = htable_Search;
    ht->delete = htable_Delete;
    ht->print = htable_Print;
    ht->clear = htable_Clear;
    ht->destroy = htable_Destroy;

    return ht;
}

int htable_Hash(HTable self, int value) {
    int index;

    if (!self || self->size <= 0)
        return -1;

    index = value % self->size;

    if (index < 0)
        index += self->size;

    return index;
}

void htable_Insert(HTable self, int value) {
    int index;

    if (!self) return;

    if (htable_Search(self, value)) {
        printf("Valor %d ja existe na tabela.\n", value);
        return;
    }

    index = htable_Hash(self, value);

    self->buckets[index]->enqueue(
        self->buckets[index],
        new(TYPE1, "HTABLE", value)
    );

    self->count++;
    printf("Valor %d inserido no bucket %d.\n", value, index);
}

Object htable_Search(HTable self, int value) {
    int index;
    Object current;

    if (!self) return NULL;

    index = htable_Hash(self, value);
    current = self->buckets[index]->head;

    while (current) {
        if (current->type == TYPE1) {
            Type1* item = (Type1*) current->item;

            if (item && item->numero == value)
                return current;
        }

        current = current->next;
    }

    return NULL;
}

void htable_Delete(HTable self, int value) {
    int index;
    int position = 0;
    Object current;

    if (!self) return;

    index = htable_Hash(self, value);
    current = self->buckets[index]->head;

    while (current) {
        if (current->type == TYPE1) {
            Type1* item = (Type1*) current->item;

            if (item && item->numero == value) {
                self->buckets[index]->del(self->buckets[index], position);
                self->count--;
                printf("Valor %d removido.\n", value);
                return;
            }
        }

        current = current->next;
        position++;
    }

    printf("Valor %d nao encontrado.\n", value);
}

void htable_Print(HTable self) {
    int i;

    if (!self) return;

    printf("\n----- HASH TABLE | elementos: %d | buckets: %d -----\n",
           self->count, self->size);

    for (i = 0; i < self->size; i++) {
        Object current = self->buckets[i]->head;

        printf("[%d] ", i);

        if (!current)
            printf("vazio");

        while (current) {
            Type1* item = (Type1*) current->item;

            if (item)
                printf("%d", item->numero);

            if (current->next)
                printf(" -> ");

            current = current->next;
        }

        printf("\n");
    }

    printf("----------------------------------------------------\n");
}

void htable_Clear(HTable self) {
    int i;

    if (!self) return;

    for (i = 0; i < self->size; i++)
        self->buckets[i]->clear(self->buckets[i]);

    self->count = 0;
}

void htable_Destroy(HTable self) {
    int i;

    if (!self) return;

    htable_Clear(self);

    for (i = 0; i < self->size; i++)
        free(self->buckets[i]);

    free(self->buckets);
    free(self);
}

#endif
