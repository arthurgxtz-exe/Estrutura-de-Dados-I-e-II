#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Jogador{
    char nome[50];
    int num_camisa;
    struct Jogador *proximo;
}Jogador;

typedef struct Time{
    Jogador *head;
    Jogador *tail;
    int tam;
}Time;

void inicializar(Time *t){
    t->head = NULL;
    t->tail = NULL;
    t->tam = 0;
}

int menu(){
    int op;
    printf("\n -- ESCALAÇÃO --- \n");
    printf("1 - Cadastrar novo jogador na escalação\n");
    printf("2 - Mostrar escalaçao atual\n");
    printf("3 - Definir Capitão (topo)\n");
    printf("4 - Remover jogador da escalação\n");
    printf("0 - SAIR\n");
    scanf("%d", &op);
    return op;
}

void finalizar_lista(Time *t){
    Jogador *aux = t->head;
    Jogador *temp;

    while(aux != NULL){
        temp = aux->proximo;
        free(aux);
        aux = temp;
    }

    t->head = NULL;
    t->tail = NULL;
    t->tam = 0;
}

void cadastrar_jogador(Time *t, int camisa, char nome[]){
    Jogador *novo = malloc(sizeof(Jogador));

    if(novo){
        novo->num_camisa = camisa;
        strcpy(novo->nome, nome);
        novo->proximo = t->head;
        t->head = novo;

        if(t->tail == NULL){
            t->tail = novo;
        }
        
        t->tam++;
        
    }
    else{
        printf("Erro ao alocar memoria\n");
    }
}

void listar_escalacao(Time *t){
    if(t->head == NULL){
        printf("Não existe nenhum jogador escalado ainda\n");
        return;
    }

    Jogador *aux = t->head;
    printf("\n ESCALAÇAO DO TIME:\n ");
    printf("Nome\t\t | Camisa \n");
    printf("-------------------------------\n");

    while(aux != NULL){
        printf("%s\t\t | %d\n", aux->nome, aux->num_camisa);
        aux = aux->proximo;
    }
    printf("\n %d jogadores escalados até o momento\n", t->tam);
}

void remover_jogador(Time *t, int alvo){
    if(t->head == NULL){
        printf("Não existe nenhum jogado escalado para ser excluido\n");
        return;
    }
    Jogador *aux = t->head;
    Jogador *anterior = NULL;

    while (aux != NULL && aux->num_camisa != alvo){
        anterior = aux;
        aux = aux->proximo;        
    }
    
    if(aux == NULL){
        printf("Jogador camisa %d não encontrado\n", alvo);
        return;
    }

    if(anterior == NULL){
        t->head = aux->proximo;
    }
    else{
        anterior->proximo = aux->proximo;
    }
    if(aux == t->tail){
        t->tail = anterior;
    }

    free(aux);
    t->tam--;

    printf("Jogador removido da escalação com sucesso!\n");

}

void dar_prioridade(Time *t, int alvo){
    if(t->head == NULL){
        printf("Não existe jogadores escalados para tornarem o capitão\n");
        return;
    }

    Jogador *aux = t->head;
    Jogador *anterior = NULL;

    while(aux != NULL && aux->num_camisa != alvo){
        anterior = aux;
        aux = aux->proximo;

    }

    if(aux == NULL){
        printf("Jogador inexistente na escalação\n");
        return;
    }
    if(anterior == NULL){
        printf("Esse jogador já o capitão!\n");
        return;
    }
    else{
        anterior->proximo = aux->proximo;
    }
    if(aux == t->tail){
        t->tail = anterior;
    }
    aux->proximo = t->head;
    t->head = aux;

    printf("O Jogador camisa %d, agora é o capitão!\n");
}
int main() {
    Time meu_time;
    inicializar(&meu_time);
    int op, camisa;
    char nome[50];
    
    do{
        op = menu();
        switch(op){
            case 1:
                printf("Digite o nome do jagador: \n");
                scanf(" %[^\n]", nome);
                printf("Digite o numero da camisa: \n");
                scanf("%d", &camisa);
                cadastrar_jogador(&meu_time, camisa, nome);
                break;
            case 2:
                listar_escalacao(&meu_time);
                break;
            case 3:
                printf("Digite o numero da camisa do jogador que deseja tornar capitão: \n");
                scanf("%d", &camisa);
                dar_prioridade(&meu_time, camisa);
            case 4:
                printf("Digite o numero da camisa do jogador a ser removido: \n");
                scanf("%d", &camisa);
                remover_jogador(&meu_time, camisa);
                break;
            case 0:
                printf("Limpando memoria e encerrando programa...\n");
                finalizar_lista(&meu_time);
                break;
            default:
                printf("Opção invalida\n");
                break;                     

        }

    }while(op != 0);

    return 0;
}