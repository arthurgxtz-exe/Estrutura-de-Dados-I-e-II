#include <stdio.h>
#include<stdlib.h>

int main() {

    int num;

    do {
        printf("\n--- MENU DE OPCOES ---\n");
        printf("1 - Opcao UM\n");
        printf("2 - Opcao DOIS\n");
        printf("3 - Opcao TRES\n");
        printf("4 - Opcao QUATRO\n");
        printf("5 - Opcao CINCO\n");
        printf("0 - Sair do Programa\n");
        printf("Escolha uma opcao: \n");
        scanf("%d", &num);

        switch(num) {
        case 1:
            printf("Um");
            break;
        case 2: 
            printf("Dois");
            break;
        case 3:
            printf("Três");
            break;
        case 4:
            printf("Quatro");
            break;
        case 5:
            printf("Cinco");
            break;
        case 0:
            printf("Saindo do programa...");
            break;
        default:
            printf("Numero invalido, por favor escolha uma opcao valida.");
            break;
        }
    } while(num != 0);
        printf("Programa Finalizado com sucesso!");
        return 0;
    
     
}