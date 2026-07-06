#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "object.h"
#include "list.h"

typedef struct{
    char nome[100];
    int nivel;
    int hp;
}Player;

typedef struct{
    char nome[100];
    int dano;
    int durabilidade;
}Arma;

void print_PLAYER(Object self, int position){
    Player* player = (Player*) self->item;

    printf("[%d] PLAYER | nome: %s | nivel: %d | hp: %d\n",
           position,
           player->nome,
           player->nivel,
           player->hp);
}
Object new_PLAYER(char* nome, int nivel, int hp){
    Object obj = new_Object();
    
    Player* player = malloc(sizeof(Player));

    player->nivel = nivel;
    player->hp = hp;
    strcpy(player->nome, nome);

    obj->item = player;
    obj->owns_item = 1;
    obj->type = PLAYER;
    obj->print = print_PLAYER;
    obj->destroy = destroy_Object;

    return obj;
}

void print_ARMA(Object self, int position) {
    Arma* arma = (Arma*) self->item;

    printf("[%d] ARMA | nome: %s | dano: %d | durabilidade: %d\n",
           position,
           arma->nome,
           arma->dano,
           arma->durabilidade);
}

Object new_ARMA(char* nome, int dano, int durabilidade){
    Object obj = new_Object();

    Arma* arma = malloc(sizeof(Arma));

    arma->dano = dano;
    arma->durabilidade = durabilidade;
    strcpy(arma->nome, nome);

    obj->item = arma;
    obj->owns_item = 1;
    obj->type = ARMA;
    obj->print = print_ARMA;
    obj->destroy = destroy_Object;

    return obj;
}



int menu(){
    int op;
    printf("\n MENU \n");
    printf("1 - Cadastrar jogador\n");
    printf("2 - Cadastrar arma\n");
    printf("3 - Imprimir lista\n");
    printf("4 - Contar jogadores\n");
    printf("0 - Sair\n");
    printf("Escolha: ");
    scanf("%d", &op);

    return op;
}

int contar_PLAYER(List lista){
    int contador = 0;

    Object atual = lista->head;

    while(atual){
        if(atual->type == PLAYER){
            contador++;
        }

        atual = atual->next;
    }

    return contador;
}

int main() {

    List lista = new(List);
    int op;
    do{
        op = menu();
        char nome[100];
        int nivel, hp, dano, durabilidade;

        switch(op){
            case 1:
                
                printf("\nCadastrar jogador: \n");
                printf("NOME: \n");
                scanf(" %[^\n]", nome);
                printf("NIVEL: \n");
                scanf("%d", &nivel);
                printf("HP: \n");
                scanf("%d", &hp);

                lista->enqueue(lista, new(PLAYER, nome, nivel, hp));
                printf("Jogador Cadastrado com sucesso!\n");
                break;

            case 2:
            printf("\nCAdastrar Arma: \n");
            printf("NOME: \n");
            scanf(" %[^\n]", nome);
            printf("DANO: \n");
            scanf("%d", &dano);
            printf("DURABILIDADE: \n");
            scanf("%d", &durabilidade);

            lista->enqueue(lista, new(ARMA, nome, dano, durabilidade));
            printf("Arma cadastrada com sucesso!\n");
            break;
            
            case 3:
                lista->print(lista);
                break;
            case 4:
                printf("Quantidade de Playes cadastrados: %d \n", contar_PLAYER(lista));
                break;
            case 0:
                printf("Encerrando...\n");
                break;
            default:
                printf("Opção invalida.\n");
                break;

        }


    }while(op != 0);

    lista->clear(lista);
    free(lista);
    return 0;
}