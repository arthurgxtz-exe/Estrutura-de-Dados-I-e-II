#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int sorteados[15];
    int aposta[15];
    int i, j, num, repetido, acertos = 0;

    // Inicializa a semente para geração de números aleatórios
    srand(time(NULL));

    // Sorteia 15 numeros sem repetição
    for (i = 0; i < 15; i++) {
        do {
            num = rand() % 25 + 1;  // Gera número entre 1 e 25
            repetido = 0;

            // Verifica se o número já foi sorteado
            for (j = 0; j < i; j++) {
                if (sorteados[j] == num) {
                    repetido = 1;
                    break;
                }
            }
        } while (repetido);

        sorteados[i] = num;
    }

    printf("Numeros sorteados: ");
    for (i = 0; i < 15; i++) {
        printf("%d ", sorteados[i]);
    }
    printf("\n");

    

    return 0;
}
