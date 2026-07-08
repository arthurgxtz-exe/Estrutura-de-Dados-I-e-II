#ifndef HTABLE_H
#define HTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef new
#define new(Type, ...) new_##Type(__VA_ARGS__)
#endif

typedef struct _HashNode _HashNode;
typedef _HashNode* HashNode;

typedef struct _HashTable _HashTable;
typedef _HashTable* HashTable;

struct _HashNode {
    char key[100];
    char value[100];
    HashNode next;
};

struct _HashTable {
    HashNode* buckets;
    int capacity;
    int size;

    void (*insert)(HashTable self, const char* key, const char* value);
    const char* (*get)(HashTable self, const char* key);
    int (*contains)(HashTable self, const char* key);
    void (*remove)(HashTable self, const char* key);
    void (*print)(HashTable self);
    void (*clear)(HashTable self);
    void (*destroy)(HashTable self);
};

HashTable new_HashTable(int capacity);

unsigned int htable_Hash(HashTable self, const char* key);
void htable_Insert(HashTable self, const char* key, const char* value);
const char* htable_Get(HashTable self, const char* key);
int htable_Contains(HashTable self, const char* key);
void htable_Remove(HashTable self, const char* key);
void htable_Print(HashTable self);
void htable_Clear(HashTable self);
void htable_Destroy(HashTable self);

HashTable new_HashTable(int capacity) {
    HashTable table;

    if (capacity <= 0) {
        printf("Capacidade invalida.\n");
        return NULL;
    }

    table = malloc(sizeof(_HashTable));

    if (!table) {
        printf("Erro ao alocar HashTable.\n");
        exit(1);
    }

    table->buckets = calloc(capacity, sizeof(HashNode));

    if (!table->buckets) {
        printf("Erro ao alocar os buckets.\n");
        free(table);
        exit(1);
    }

    table->capacity = capacity;
    table->size = 0;

    table->insert = htable_Insert;
    table->get = htable_Get;
    table->contains = htable_Contains;
    table->remove = htable_Remove;
    table->print = htable_Print;
    table->clear = htable_Clear;
    table->destroy = htable_Destroy;

    return table;
}

unsigned int htable_Hash(HashTable self, const char* key) {
    unsigned long hash = 5381;
    int c;

    while ((c = (unsigned char) *key++) != 0)
        hash = ((hash << 5) + hash) + c;

    return (unsigned int) (hash % self->capacity);
}

void htable_Insert(HashTable self, const char* key, const char* value) {
    unsigned int index;
    HashNode current;
    HashNode novo;

    if (!self || !key || !value) return;

    index = htable_Hash(self, key);
    current = self->buckets[index];

    /* Se a chave ja existe, apenas atualiza o valor. */
    while (current) {
        if (strcmp(current->key, key) == 0) {
            snprintf(current->value, sizeof(current->value), "%s", value);
            return;
        }

        current = current->next;
    }

    novo = malloc(sizeof(_HashNode));

    if (!novo) {
        printf("Erro ao alocar elemento da tabela.\n");
        exit(1);
    }

    snprintf(novo->key, sizeof(novo->key), "%s", key);
    snprintf(novo->value, sizeof(novo->value), "%s", value);

    /* Insere no inicio da lista do bucket. */
    novo->next = self->buckets[index];
    self->buckets[index] = novo;
    self->size++;
}

const char* htable_Get(HashTable self, const char* key) {
    unsigned int index;
    HashNode current;

    if (!self || !key) return NULL;

    index = htable_Hash(self, key);
    current = self->buckets[index];

    while (current) {
        if (strcmp(current->key, key) == 0)
            return current->value;

        current = current->next;
    }

    return NULL;
}

int htable_Contains(HashTable self, const char* key) {
    return htable_Get(self, key) != NULL;
}

void htable_Remove(HashTable self, const char* key) {
    unsigned int index;
    HashNode current;
    HashNode previous = NULL;

    if (!self || !key) return;

    index = htable_Hash(self, key);
    current = self->buckets[index];

    while (current) {
        if (strcmp(current->key, key) == 0) {
            if (previous)
                previous->next = current->next;
            else
                self->buckets[index] = current->next;

            free(current);
            self->size--;
            return;
        }

        previous = current;
        current = current->next;
    }
}

void htable_Print(HashTable self) {
    int i;

    if (!self) return;

    printf("\n----- HASH TABLE | size: %d | capacity: %d -----\n",
           self->size, self->capacity);

    for (i = 0; i < self->capacity; i++) {
        HashNode current = self->buckets[i];

        printf("[%d] ", i);

        if (!current) {
            printf("vazio");
        }

        while (current) {
            printf("{%s: %s}", current->key, current->value);

            if (current->next)
                printf(" -> ");

            current = current->next;
        }

        printf("\n");
    }

    printf("-----------------------------------------------\n");
}

void htable_Clear(HashTable self) {
    int i;

    if (!self) return;

    for (i = 0; i < self->capacity; i++) {
        HashNode current = self->buckets[i];

        while (current) {
            HashNode next = current->next;
            free(current);
            current = next;
        }

        self->buckets[i] = NULL;
    }

    self->size = 0;
}

void htable_Destroy(HashTable self) {
    if (!self) return;

    htable_Clear(self);
    free(self->buckets);
    free(self);
}

#endif
