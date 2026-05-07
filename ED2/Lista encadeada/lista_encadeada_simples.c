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

void imprimir_lista(No *head){
    printf("\nLista de valores\n");

    No *atual = head;

    while(atual != NULL){
        printf("%d \n", atual->valor);
        atual = atual->proximo;
    }
}

void menu(){
    int op;
    printf("1 - Inserir no inicio\n");
    printf("2 - Inserir no meio \n");
    printf("3 - Inserir no Final\n");
    printf("4 - Listar valores da lista\n");
    scanf("%d", &op);
    return op;
}

int main() {

    No lista;
    int op;
    do{
        op = menu();
        switch(op){
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            default:
                break;
        }

    }while(op != 0);
    
    return 0;
}