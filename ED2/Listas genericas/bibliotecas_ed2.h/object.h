#ifndef OBJECT_H
#define OBJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define new(Type, ...) new_##Type(__VA_ARGS__)

typedef enum {
    TYPE1,
    TYPE2,
    PLAYER,
    ARMA,
    NPC
} TypeNode;

typedef struct Node {
    void* item;
    int owns_item;
    TypeNode type;

    struct Node* next;
    struct Node* prev;

    void (*set)();
    void (*print)(struct Node* self, int position);
    void (*destroy)(struct Node* self);
} Node;

typedef Node* Object;



Object new_Object(void);

void set_Object(Object self, void* item);
void print_Object(Object self, int position);
void destroy_Object(Object self);

Object view_Object(Object obj);
Object copy_Object(Object obj);
void destroy_View(Object self);

char* type_Name(TypeNode type);


Object new_Object(void) {
    Object novo = malloc(sizeof(Node));

    if (!novo) {
        printf("Erro ao alocar Object.\n");
        exit(1);
    }

    novo->item = NULL;
    novo->owns_item = 0;
    novo->type = TYPE1;

    novo->next = NULL;
    novo->prev = NULL;

    novo->set = set_Object;
    novo->print = print_Object;
    novo->destroy = destroy_Object;

    return novo;
}

void set_Object(Object self, void* item) {
    if (!self) return;

    self->item = item;
    self->owns_item = 0;
}

void print_Object(Object self, int position) {
    if (!self) return;

    printf("[%d] Object | tipo: %s | item: %p\n",
           position, type_Name(self->type), self->item);
}

void destroy_Object(Object self) {
    if (!self) return;

    if (self->owns_item && self->item)
        free(self->item);

    free(self);
}


Object view_Object(Object obj) {
    Object novo = new_Object();

    if (!obj) return novo;

    novo->item = obj->item;
    novo->owns_item = 0;
    novo->type = obj->type;

    novo->set = obj->set;
    novo->print = obj->print;
    novo->destroy = destroy_View;

    return novo;
}

void destroy_View(Object self) {
    if (!self) return;

    free(self);
}

char* type_Name(TypeNode type) {
    switch (type) {
        case TYPE1: return "TYPE1";
        case TYPE2: return "TYPE2";
        case PLAYER: return "PLAYER";
        case ARMA: return "ARMA";
        case NPC: return "NPC";
        default: return "UNKNOWN";
    }
}


typedef struct {
    char texto[100];
    int numero;
} Type1;

Object new_TYPE1(char* texto, int numero);
void print_TYPE1(Object self, int position);
void set_TYPE1(Object self, char* texto, int numero);

Object new_TYPE1(char* texto, int numero) {
    Object novo = new_Object();

    Type1* item = malloc(sizeof(Type1));

    if (!item) {
        printf("Erro ao alocar TYPE1.\n");
        exit(1);
    }

    snprintf(item->texto, sizeof(item->texto), "%s", texto);
    item->numero = numero;

    novo->item = item;
    novo->owns_item = 1;
    novo->type = TYPE1;

    novo->set = set_TYPE1;
    novo->print = print_TYPE1;
    novo->destroy = destroy_Object;

    return novo;
}

void print_TYPE1(Object self, int position) {
    if (!self || !self->item) return;

    Type1* item = (Type1*) self->item;

    printf("[%d] TYPE1 | texto: %s | numero: %d\n",
           position, item->texto, item->numero);
}

void set_TYPE1(Object self, char* texto, int numero) {
    if (!self || !self->item) return;

    Type1* item = (Type1*) self->item;

    snprintf(item->texto, sizeof(item->texto), "%s", texto);
    item->numero = numero;
}


typedef struct {
    char campo1[100];
    char campo2[100];
    char campo3[100];
} Type2;

Object new_TYPE2(char* campo1, char* campo2, char* campo3);
void print_TYPE2(Object self, int position);
void set_TYPE2(Object self, char* campo1, char* campo2, char* campo3);

Object new_TYPE2(char* campo1, char* campo2, char* campo3) {
    Object novo = new_Object();

    Type2* item = malloc(sizeof(Type2));

    if (!item) {
        printf("Erro ao alocar TYPE2.\n");
        exit(1);
    }

    snprintf(item->campo1, sizeof(item->campo1), "%s", campo1);
    snprintf(item->campo2, sizeof(item->campo2), "%s", campo2);
    snprintf(item->campo3, sizeof(item->campo3), "%s", campo3);

    novo->item = item;
    novo->owns_item = 1;
    novo->type = TYPE2;

    novo->set = set_TYPE2;
    novo->print = print_TYPE2;
    novo->destroy = destroy_Object;

    return novo;
}

void print_TYPE2(Object self, int position) {
    if (!self || !self->item) return;

    Type2* item = (Type2*) self->item;

    printf("[%d] TYPE2 | campo1: %s | campo2: %s | campo3: %s\n",
           position, item->campo1, item->campo2, item->campo3);
}

void set_TYPE2(Object self, char* campo1, char* campo2, char* campo3) {
    if (!self || !self->item) return;

    Type2* item = (Type2*) self->item;

    snprintf(item->campo1, sizeof(item->campo1), "%s", campo1);
    snprintf(item->campo2, sizeof(item->campo2), "%s", campo2);
    snprintf(item->campo3, sizeof(item->campo3), "%s", campo3);
}


Object copy_Object(Object obj) {
    if (!obj || !obj->item) return NULL;

    switch (obj->type) {
        case TYPE1: {
            Type1* item = (Type1*) obj->item;
            return new(TYPE1, item->texto, item->numero);
        }
        case TYPE2: {
            Type2* item = (Type2*) obj->item;
            return new(TYPE2, item->campo1, item->campo2, item->campo3);
        }
        default:
            return view_Object(obj);
    }
}

#endif
