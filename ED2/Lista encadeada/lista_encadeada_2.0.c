#include <stdio.h>
#include <stdlib.h>

typedef struct no{
int valor;
struct no *proximo;
}No;

typedef struct Lista{
    No *head;
    No *tail;
    int tam;
}Lista;

void criar_lista(Lista *lista){
    lista->head = NULL;
    lista->tail = NULL;
    lista->tam = 0;
}


void inserir_inicio(Lista *l, int num){
    No *novo = malloc(sizeof(No));

    if (novo){
        novo->valor = num;
        novo->proximo = l->head;
        l->head = novo;
        
        if(l->tail == NULL){
            l->tail = novo;
        }
        
        l->tam++;
    }
        
    else
        printf("Erro ao alocar memoria.\n");
}

void inserir_fim(Lista *l, int num){
    No *novo = malloc(sizeof(No));
    
    if(novo){
        novo->valor = num;
        novo->proximo = NULL;
        //é o primeiro?
        if(l->head == NULL){
            l->head = novo;
            l->tail = novo;
        }
        else{
            l->tail->proximo = novo;
            l->tail = novo;
        }
    
        l->tam++;
    }
    else 
        printf("Erro ao alocar memoria.\n");
}

void inserir_meio(Lista *l, int num, int ant){
    if(l->head == NULL){
        inserir_inicio(l, num);
        return;
    }

    No *novo = malloc(sizeof(No));
    
    if(novo){
        novo->valor = num;
        No *aux = l->head;
        while(aux->valor != ant && aux->proximo != NULL){
            aux = aux->proximo;
        }

        if(aux->valor != ant){
            printf("Erro: valor %d não encontrado na lista.\n", ant);
            free(novo);
            return;
        }

        novo->proximo = aux->proximo;
        aux->proximo = novo;

        if(novo->proximo == NULL){
            l->tail = novo;
        }
        l->tam++;
    }
    else{
        printf("Erro ao alocar memoria.\n");
    }
}
 
void imprimir_lista(Lista *l){
    printf("\n\tLista de valores: ");

    No *atual = l->head;

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

    Lista lista;
    criar_lista(&lista);
    int op, valor, ant;

    do{
        op = menu();
        switch(op){
            case 1:
                printf("Digite um valor: \n");
                scanf("%d", &valor);
                inserir_inicio(&lista, valor);
                break;
            case 2:
                printf("Digite um valor: \n");
                scanf("%d", &valor);
                printf("Digite o valor de referencia: \n");
                scanf("%d", &ant);
                inserir_meio(&lista, valor, ant);
                break;
            case 3:
                printf("Digite um valor: \n");
                scanf("%d", &valor);
                inserir_fim(&lista, valor);
                break;
            case 4:
                imprimir_lista(&lista);
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