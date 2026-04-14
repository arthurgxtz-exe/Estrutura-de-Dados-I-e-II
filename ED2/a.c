#include <stdio.h>
#include <stdlib.h>

typedef struct Veiculo
{
   char tipo[50];
   int ano;
   char modelo[50];
   float km;
   float valor;
   struct Veiculo *next;
}Veiculo;

Veiculo* cadastrar(Veiculo *head, int ano_novo){

    Veiculo *novo_carro = (Veiculo*) malloc(sizeof(Veiculo));
    novo_carro->ano = ano_novo;
    novo_carro->next = head;

    return novo_carro;
}

void listar(Veiculo *head){

    printf("\n--- Lista de veiculos ---\n");

    Veiculo *atual = head;

    while(atual != NULL){

        printf("Ano do Veiculo: %d\n", atual->ano);

        atual = atual->next;
    }
}

void buscar(Veiculo *head, int alvo){

    Veiculo *atual = head;
    int encontrou = 0;

    while(atual != NULL){

        if(atual->ano == alvo){
            printf("Encontrado um veiculo no ano: %d\n", atual->ano);
            encontrou = 1;
        }

        atual = atual->next;

    }

    if(!encontrou){
        printf("Nenhum veiculo desse ano foi encontrado na lista.\n");
    }
}

int main() {

    Veiculo *lista = NULL;

    lista = cadastrar(lista, 2010);
    lista = cadastrar(lista, 2015);
    lista = cadastrar(lista, 2024);

    listar(lista);

    buscar(lista, 2015); // Vai achar!
    buscar(lista, 1999); // Não vai achar!
    
    return 0;
}