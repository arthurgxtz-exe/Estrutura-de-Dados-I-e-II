#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

int main() {
    int cartas[10], estado[10];
    int i, a, b, pares = 0;
    srand(time(NULL));

    for (i = 0; i < 5; i++) {
        cartas[i*2] = i + 1;
        cartas[i*2 + 1] = i + 1;
    }

    for (i = 0; i < 10; i++) {
        int j = rand() % 10;
        int temp = cartas[i];
        cartas[i] = cartas[j];
        cartas[j] = temp;
    }

    for (i = 0; i < 10; i++) {
        estado[i] = 0;
    }

    printf("=== JOGO DA MEMORIA ===\n");
    printf("Encontre todos os pares!\n");
    printf("Pressione ENTER para comecar...");
    getchar();

    while (pares < 5) {
        system("cls");
        printf("\nPosicoes:\n");
        for (i = 0; i < 10; i++) {
            if (estado[i] == 0)
                printf("[%2d] *  ", i + 1);
            else
                printf("[%2d] %d  ", i + 1, cartas[i]);
        }

        printf("\n\nEscolha a primeira carta: ");
        scanf("%d", &a);
        a--;

        printf("Escolha a segunda carta: ");
        scanf("%d", &b);
        b--;

        estado[a] = 1;
        estado[b] = 1;

        system("cls");
        for (i = 0; i < 10; i++) {
            if (estado[i] == 0)
                printf("[%2d] *  ", i + 1);
            else
                printf("[%2d] %d  ", i + 1, cartas[i]);
        }

        if (cartas[a] == cartas[b]) {
            printf("\n\nPar encontrado!\n");
            pares++;
        } else {
            printf("\n\nNao foi par!\n");
            Sleep(1000);
            estado[a] = 0;
            estado[b] = 0;
        }

        printf("\nPares encontrados: %d/5\n", pares);
        printf("Pressione ENTER para continuar...");
        while (getchar() != '\n');
        getchar();
    }

    system("cls");
    printf("\nPARABENS! Voce encontrou todos os pares!\n");

    return 0;
}
