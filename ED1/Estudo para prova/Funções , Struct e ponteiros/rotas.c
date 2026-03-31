#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
char origem[50];
char destino[50];
float distancia;
float tempo;
}Rota;

int menu(){
    int op;
    printf("Escolha uma opção:\n");
    printf("1- Cadastrar Rotas\n");
    printf("2- Consultar Entrega\n");
    printf("0 - Sair do programa\n");
    scanf("%d", &op);
    return op;
}

int BuscarRotas(Rota r[], int cont, char origem[]){
    for( int i = 0; i < cont; i++){
        if(strcmp(r[i].origem, origem) == 0){
            return i;
        }
    }
    return -1;
}

void CadastrarRotas(Rota r[], int cont){
    system("cls");
    printf("\nNova rota [%d]:\n", cont + 1);
    while(1){
        char origemTemp[50];
        printf("Cidade de origem:\n");
        scanf(" %[^\n]", origemTemp);
        if(BuscarRotas(r, cont, origemTemp) != -1 ){
            printf("Cidade: %s já foi cadastrada, tente novamente.\n", origemTemp);
        }
        else{
            strcpy(r[cont].origem, origemTemp);
                    
            break;
        }
   }
    printf("Cidade de destino:\n");
    scanf(" %[^\n]", r[cont].destino);
    printf("Distancia(km):\n");
    scanf("%f", &r[cont].distancia);
    printf("Tempo gasto(horas):\n");
    scanf("%f", &r[cont].tempo);
}

void ConsultaRotas(Rota r[], int qtd){
    char CidadeAtual[50];
    char CidadeFinal[50];
    float distTotal = 0;
    float tempoTotal = 0;
    int contViagem = 0;
    while(getchar() != '\n');
    printf("\n===Painel de Consultas===\n");
    printf("Digite a cidade inicial:\n");
    scanf(" %[^\n]", CidadeAtual);
    printf("Digite a cidade final:\n");
    scanf(" %[^\n]", CidadeFinal);
    while(1){
        if(contViagem > qtd){
            printf("Erro! Caminho Impossivel\n");
            return;
        }

        int indice = BuscarRotas(r, qtd, CidadeAtual);

        if(indice == -1){
            printf("Não existe estrada saindo de %s.\n", CidadeAtual);
            return;
        }

        printf("Viagem %d: Sai de %s indo para %s (%.1f km)\n", contViagem + 1, r[indice].origem, r[indice].destino, r[indice].distancia);
        distTotal += r[indice].distancia;
        tempoTotal += r[indice].tempo;
        contViagem++;

        if(strcmp(r[indice].destino, CidadeFinal) == 0){
            printf("\nRota encontrada\n");
            printf("Distancia Total: %.1f\n", distTotal);
            printf("Tempo Total: %.1f\n", tempoTotal);
            printf("Viagens nescessarias: %d\n", contViagem);
            return;
        }
        else{
            strcpy(CidadeAtual, r[indice].destino);

        }
    }
            
}

    

int main() {
    Rota minhasRotas[100];
    int cont = 0;
    int op;
    do{
        op = menu();
        switch (op){
        case 1:
            system("cls");
            CadastrarRotas(minhasRotas, cont);
            cont++;
            break;
        case 2:
            system("cls");
            ConsultaRotas(minhasRotas, cont);
            break;
        case 0: 
            printf("Saindo do programa..\n");
            break;
        default:
            break;
        }

    }while(op != 0);
    printf("Programa Finalizado com sucesso!\n");
    return 0;
}