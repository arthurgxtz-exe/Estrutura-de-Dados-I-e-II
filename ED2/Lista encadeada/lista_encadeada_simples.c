#include <stdio.h>
#include <stdlib.h>

typedef struct no{
int valor;
struct no *proximo;
}No;

void inserir_inicio(No **lista, int num){
    No *novo = malloc(sizeof(No));

    if (novo){
        novo->valor = num;
        novo->proximo = *lista;
        *lista = novo;
    }
    else
        printf("Erro ao alocar memoria.\n");
}

void inserir_fim(No **lista, int num){
    No *novo = malloc(sizeof(No));
    No *aux = malloc(sizeof(No));
    if(novo){
        novo->valor = num;
        novo->proximo = NULL;
        //é o primeiro?
        if(*lista == NULL){
            *lista = novo;
        }
        else{
            aux = *lista;
             while(aux->proximo){
                aux = aux->proximo;
                aux->proximo = novo;
             }
        }

    }
    else 
        printf("Erro ao alocar memoria.\n");
}

void inserir_meio(No **lista, int num, int ant){
     No *aux, *novo = malloc(sizeof(No));

     if(novo){
         novo->valor = num;
         //novo é o primeiro?

         if(*lista == NULL){
            novo->proximo = NULL;
            *lista = novo; 
         }
         else{
            aux = *lista;
            while( aux->valor != ant){
                
            }
         }
    
     }
     else{
        printf("Erro ao alocar memoria!\n");
     }

     
}

int main() {

    No lista;

    
    return 0;
}