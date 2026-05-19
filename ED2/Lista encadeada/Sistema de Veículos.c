#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Veiculo
{
   char tipo[50];
   int ano;
   char modelo[50];
   float km;
   float valor;
   struct Veiculo *next;
}Veiculo;

Veiculo* cadastrar(Veiculo *head){

    Veiculo *novo_carro = (Veiculo*) malloc(sizeof(Veiculo));


    printf("-- Cadastro de novo veículo ---\n");
    printf("Tipo:\n");
    scanf(" %[^\n]",novo_carro->tipo);
    printf("Ano:\n");
    scanf("%d", &novo_carro->ano);
    printf("Modelo:\n");
    scanf(" %[^\n]", novo_carro->modelo);
    printf("Km:\n");
    scanf("%f", &novo_carro->km);
    printf("Valor: \n");
    scanf("%f", &novo_carro->valor);
    
    
    novo_carro->next = head;

    return novo_carro;
}

void listar(Veiculo *head){

    printf("\n--- Lista de veiculos ---\n");

    Veiculo *atual = head;

    printf("%-10s | %-15s | %-6s | %-8s | %-15s\n", "TIPO", "MODELO", "ANO", "KM", "VALOR");
    printf("-------------------------------------------------------\n");

    while(atual != NULL){

        printf("%-10s | %-15s | %-6d | %-8.3f | R$ %-12.3f\n", atual->tipo, atual->modelo, atual->ano, atual->km, atual->valor);
        atual = atual->next;
    }
}

void buscarEmedia(Veiculo *head){

    Veiculo *atual = head;
    int cont = 0;
    char alvo[50];
    float total_valor = 0;
    printf("Digite o tipo do veiculo que deseja encontrar: \n");
    scanf(" %[^\n]", alvo);
    printf("\n--- Resultados da busca do tipo %s ---\n", alvo);
        

    while(atual != NULL){

        if(strcmp(alvo, atual->tipo) == 0){
             printf("%-10s | %-15s | %-6d | %-8.3f | R$ %-12.3f\n", atual->tipo, atual->modelo, atual->ano, atual->km, atual->valor);
             cont++;
             total_valor += atual->valor; 
        }

        atual = atual->next;

    }

    if(!cont){
        printf("Nenhum veiculo desse tipo foi encontrado na lista.\n");
    }

    if(cont > 0){
        float media = total_valor / cont;
        printf("Quantidade de veiculos encontrada: %d\n", cont);
        printf("Média de valor dos veiculos desse tipo: %.3f R$\n", media);

    }
    else{
        printf("Não foi achado veiculos suficientes para ter uma média\n");
    }
}

int menu(){
    int op;
    printf(" 1 - Cadastrar novo veiculo\n");
    printf(" 2 - Listar Veiculos\n");
    printf(" 3 - Procurar Veiculos\n");
    printf(" 0 - Sair\n");
    scanf("%d", &op);
    return op;
}

int main() {

    Veiculo *lista = NULL;

    int op;
    do{
        op = menu();
        switch(op){
            case 1:
                lista = cadastrar(lista);
                break;
            case 2:
                listar(lista);
                break;
            case 3:
                buscarEmedia(lista);
                break;
            case 0:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opção Invalida, por favor digite uma valida\n");
                break;
        }

    }while(op != 0);

       
    return 0;
}