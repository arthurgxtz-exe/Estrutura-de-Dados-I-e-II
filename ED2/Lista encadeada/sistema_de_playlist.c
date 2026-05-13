#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Musica{ 
    char nome[50];
    char artista[50];
    struct Musica *proximo;
}Musica;

typedef struct{
    Musica *head;
    Musica *tail;
    int tam;
}Playlist;

void inicializar(Playlist *p){
    p->head = NULL;
    p->tail = NULL;
    p->tam = 0;
}

void limpar_buffer(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

int menu(){
    int op;
    printf("\n>>> SPOTIFY <<<\n");
    printf("1 - Adicionar musica na fila (Fim)\n");
    printf("2 - Tocar agora (Inicio)\n");
    printf("3 - Remover musica\n");
    printf("4 - Mostrar Playlist\n");
    printf("5 - Tocar a seguir (dar prioridade\n");
    printf("0 - SAIR\n");
    scanf("%d", &op);
    return op;
}

void adicionar_musica(Playlist *p, char nome_musica[], char nome_artista[]){
    Musica *novo = malloc(sizeof(Musica));

    if(novo){
        strcpy(novo->nome, nome_musica);
        strcpy(novo->artista, nome_artista);
        novo->proximo = NULL;
        if(p->head == NULL){
            p->head = novo;
            p->tail = novo;
        }
        else{
            p->tail->proximo = novo;
            p->tail = novo;
        }
        p->tam++;
    }
    else{
        printf("Erro ao alocar memoria\n");
    }

}

void tocar_agora(Playlist *p, char nome_musica[], char nome_artista[]){
    Musica *novo = malloc(sizeof(Musica));

    if(novo){
        strcpy(novo->nome, nome_musica);
        strcpy(novo->artista, nome_artista);
        if(p->head == NULL){
            novo->proximo = NULL;
            p->head = novo;
            p->tail = novo;
        }
        else{
            novo->proximo = p->head;
            p->head = novo;
        }
        p->tam++;
    }

    else{
        printf("Erro ao alocar memoria\n");
    }
}

void remover_musica(Playlist *p, char alvo[]){
    Musica *aux = p->head;
    Musica *anterior = NULL;

    while(aux != NULL && strcmp(aux->nome, alvo) != 0){
        anterior = aux;
        aux = aux->proximo;
    }

    if(aux == NULL){
        printf("Musica não encontrada.\n");
        return;
    }
    
    if(anterior == NULL){
        p->head = aux->proximo;
    }
    else{
        anterior->proximo = aux->proximo;
    }
    if(aux->proximo == NULL){
        p->tail = anterior;
    }

    free(aux);
    p->tam--;
    printf("Musica removida com sucesso!\n");
}

void listar_playlist(Playlist *p){
    Musica *aux = p->head;

    printf("\n --- MINHA PLAYLIST --- \n ");
    if(aux == NULL){
        printf("A playlist está vazia no momento.\n");
        return;
    }
    printf("Nome\t\t | Artista\n"); 
    printf("-----------------------------------\n");
    while(aux != NULL){
        printf("%s\t\t | %s\n", aux->nome, aux->artista);
        aux = aux->proximo;
    }

}

void limpar_playlist(Playlist *p){
    Musica *aux = p->head;
    Musica *temp;

    while(aux != NULL){
        temp = aux->proximo;
        free(aux);
        aux = temp;
    }
    p->head = NULL;
    p->tail = NULL;
    p->tam = 0;

    printf("Memoria limpa com sucesso. Encerrando...\n");

}

void dar_prioridade(Playlist *p, char alvo[]){

    if(p->head == NULL){
        printf("A playlist esta vazia\n");
        return;
    }
    Musica *aux = p->head;
    Musica *anterior;
    while(aux != NULL && strcmp(aux->nome, alvo) != 0){
        anterior = aux;
        aux = aux->proximo;
    }
    
    if(aux == p->head){
        printf("A musica %s já é a primeira a tocar\n", aux->nome);
        return;
    }

    if(aux == NULL){
        printf("Musica %s não encontrada\n");
        return;
    }

    anterior->proximo = aux->proximo;

    if(aux->proximo == NULL){
        p->tail = anterior;
    }

    aux->proximo = p->head;
    p->head = aux;
    
    printf("Sucesso, a musica %s é a proxima a tocar\n", alvo);

}

int main() {

    Playlist minha_lista;
    inicializar(&minha_lista);

    int op;
    char nome_musica[50], nome_artista[50];

    do{
        op = menu();
        switch(op){
            case 1:
                printf("Digite o nome da musica: \n");
                scanf(" %[^\n]", nome_musica);
                limpar_buffer();
                printf("Digite o nome do artista: \n");
                scanf(" %[^\n]", nome_artista);
                adicionar_musica(&minha_lista, nome_musica , nome_artista);
                break;
            case 2:
                printf("Digite o nome da musica: \n");
                scanf(" %[^\n]", nome_musica);
                limpar_buffer();
                printf("Digite o nome do artista: \n");
                scanf(" %[^\n]", nome_artista);
                tocar_agora(&minha_lista, nome_musica, nome_artista);
                break;
            case 3 :
                printf("Digite o nome da musica que deseja remover: \n");
                scanf(" %[^\n]", nome_musica);
                limpar_buffer();
                remover_musica(&minha_lista, nome_musica);
                break;
            case 4:
                listar_playlist(&minha_lista);
                break;
            case 5:
                printf("Qual musica você deseja tocar a seguir(dar prioridade): \n");
                scanf(" %[^\n]", nome_musica);
                limpar_buffer();
                dar_prioridade(&minha_lista, nome_musica);
                break;
            case 0: 
                printf("Limpando a memoria e saindo do programa..\n");
                limpar_playlist(&minha_lista);
                break;
            default:
                printf("Comando invalido\n");
                break;

        }
                
    }while(op != 0);

    

    return 0;
}