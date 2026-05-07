#include <stdio.h>
#include <stdlib.h>

typedef struct no{
int valor;
struct no *proximo;
}No;

typedef struct Lista{
    No *head;
    int tam;
}Lista;

void criar_lista(Lista *lista){
    lista->head = NULL;
    lista->tam = 0;
}


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
    No *aux;
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
            }
            aux->proximo = novo;
        }

    }
    else 
        printf("Erro ao alocar memoria.\n");
}

void inserir_meio(No **lista, int num, int ant){
     No *aux, *novo = malloc(sizeof(No));

     if(novo){
         novo->valor = num;
         
         if(*lista == NULL){
            novo->proximo = NULL;
            *lista = novo; 
         }
         else{
            aux = *lista;
            while( aux->valor != ant && aux->proximo != NULL){
                aux = aux->proximo;
            }
            novo->proximo = aux->proximo;
            aux->proximo = novo;
         }
    
     }
     else{
        printf("Erro ao alocar memoria!\n");
     }

     
}

void imprimir_lista(No *head){
    printf("\n\tLista de valores: ");

    No *atual = head;

    while(atual != NULL){
        printf("|%d|", atual->valor);
        atual = atual->proximo;
    }
}

int menu(){
    int op;
    printf("\nMENU\n");
    printf("1 - Inserir no inicio\n");
    printf("2 - Inserir no meio \n");
    printf("3 - Inserir no Final\n");
    printf("4 - Listar valores da lista\n");
    printf("0 - SAIR\n");
    scanf("%d", &op);
    return op;
}

int main() {

    No *lista = NULL;
    int op, valor, ant;

    do{
        op = menu();
        switch(op){
            case 1:
                printf("Digite um valor: \n");
                while(getchar() != '\n');
                scanf("%d", &valor);
                inserir_inicio(&lista, valor);
                break;
            case 2:
                printf("Digite um valor: \n");
                while(getchar() != '\n');
                scanf("%d", &valor);
                printf("Digite o valor de referencia: \n");
                scanf("%d", &ant);
                inserir_meio(&lista, valor, ant);
                break;
            case 3:
                printf("Digite um valor: \n");
                while(getchar() != '\n');
                scanf("%d", &valor);
                inserir_fim(&lista, valor);
                break;
            case 4:
                imprimir_lista(lista);
                break;
            case 0: 
                printf("Encerrando programa...\n");
                break;
            default:
                printf("Opção invalida!");
                break;
        }

    }while(op != 0);
    
    return 0;
}