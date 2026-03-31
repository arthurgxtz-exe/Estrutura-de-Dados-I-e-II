#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    int N_pessoas;

    int TOTAL_SIMULACOES = 100000;

    while (1) {
        printf("\n-------------------------------------------------");
        printf("\nDigite o N de pessoas (0 ou menos para sair): ");
        scanf("%d", &N_pessoas);

        if (N_pessoas <= 0) {
            break; 
        }

        int contador_de_colisoes = 0;

        for (int c = 0; c < TOTAL_SIMULACOES; c++) {
            
            int aniversarios[N_pessoas];
            for (int p = 0; p < N_pessoas; p++) {
                aniversarios[p] = (rand() % 365) + 1; 
            }

            for (int i = 0; i < N_pessoas - 1; i++) {
                for (int j = 0; j < N_pessoas - 1 - i; j++) {
                    if (aniversarios[j] > aniversarios[j + 1]) {
                        int temp = aniversarios[j];
                        aniversarios[j] = aniversarios[j + 1];
                        aniversarios[j + 1] = temp;
                    }
                }
            }

            int achou_colisao = 0;
            for (int p = 0; p < N_pessoas - 1; p++) {
                if (aniversarios[p] == aniversarios[p + 1]) {
                    achou_colisao = 1; 
                    break; 
                }
            }
            
            if (achou_colisao == 1) {
                contador_de_colisoes++;
            }
            
        } 

        float percentual = (float)contador_de_colisoes / TOTAL_SIMULACOES * 100.0;
        
        printf("Para um grupo de %d pessoas, em %.2f por cento dos 100K cenarios foram\n", N_pessoas, percentual);
        printf("encontrados aniversariantes na mesma data!\n");

    } 

    printf("\nPrograma encerrado.\n");
    return 0;
}