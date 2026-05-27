#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "object.h"
#include "entidade.h"
#include "list.h"

Object new_Object(void* dado) {
    Object novo = (Object) malloc(sizeof(Node));
    if (novo) {
        novo->item = dado;
        novo->left = NULL;
        novo->right = NULL;
        return novo;
    }
    printf("Erro ao alocar memoria para o Objeto\n");
    return NULL;
}

void destroy(Object obj) {
    if (obj != NULL) {
        if (obj->item != NULL) {
            free(obj->item); 
        }
        free(obj); 
    }
}

Object new_Disciplina(char* nome, int creditos, int carga_horaria) {
    Disciplina* d = (Disciplina*) malloc(sizeof(Disciplina));
    if (d != NULL) {
        strcpy(d->nome, nome);
        d->creditos = creditos;
        d->carga_horaria = carga_horaria;
    }
    return new_Object(d); 
}

void printDisciplina(void* dado) {
    Disciplina* d = (Disciplina*) dado;
    printf("Disciplina: %-25s | Creditos: %d | Carga: %dh\n", d->nome, d->creditos, d->carga_horaria);
}

List new_List() {
    List l = (List) malloc(sizeof(_List));
    if (l) {
        l->head = NULL;
        l->tail = NULL;
        l->size = 0;
        return l;
    }
    printf("Erro ao alocar memoria para a Lista\n");
    return NULL;
}

void list_push(List l, Object obj) {
    if (l == NULL || obj == NULL) return;

    obj->right = l->head;
    obj->left = NULL; 

    if (l->head != NULL) {
        l->head->left = obj;
    } else {
        l->tail = obj;
    }

    l->head = obj;
    l->size++;
}

void list_enqueue(List l, Object obj) {
    if (l == NULL || obj == NULL) return;

    obj->left = l->tail;
    obj->right = NULL;

    if (l->tail != NULL) {
        l->tail->right = obj;
    } else {
        l->head = obj;
    }

    l->tail = obj;
    l->size++; 
}

Object list_pop(List l) {
    if (l == NULL || l->head == NULL) return NULL;

    Object removido = l->head;
    l->head = removido->right;

    if (l->head != NULL) {
        l->head->left = NULL; 
    } else {
        l->tail = NULL; 
    }

    removido->right = NULL;
    removido->left = NULL;
    
    l->size--;
    return removido; 
}

void list_print(List l, void (*funcao_imprimir)(void*)) {
    if (l == NULL || l->head == NULL) {
        printf("Lista Vazia.\n");
        return;
    }

    Object aux = l->head;
    while (aux != NULL) {
        funcao_imprimir(aux->item); 
        aux = aux->right; 
    }
}

void list_clear(List l) {
    if (l == NULL) return;

    Object aux = l->head;
    while (aux != NULL) {
        Object proximo = aux->right; 
        destroy(aux); 
        aux = proximo; 
    }

    l->head = NULL;
    l->tail = NULL;
    l->size = 0;
}

int main() {
    printf("--- INICIANDO SISTEMA ---\n");

    List minha_lista = new_List();

    Object d1 = new(Disciplina, "Estruturas de Dados 2", 4, 80);
    Object d2 = new(Disciplina, "Redes de Computadores", 4, 60);
    Object d3 = new(Disciplina, "Sistemas Distribuidos", 4, 60);

    printf("\n>>> Testando Insercao no Inicio (Push):\n");
    list_push(minha_lista, d1);
    list_push(minha_lista, d2);
    list_print(minha_lista, printDisciplina);

    printf("\n>>> Testando Insercao no Final (Enqueue):\n");
    list_enqueue(minha_lista, d3);
    list_print(minha_lista, printDisciplina);

    printf("\n>>> Testando Remocao do Inicio (Pop):\n");
    Object retirado = list_pop(minha_lista);
    printf("Item removido: ");
    printDisciplina(retirado->item);
    destroy(retirado);

    printf("\n>>> Lista Apos o Pop:\n");
    list_print(minha_lista, printDisciplina);

    list_clear(minha_lista);
    free(minha_lista);

    printf("\n--- SISTEMA ENCERRADO ---\n");
    return 0;
}