#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TOTA

int main() {
    srand(time(NULL));
    int N_pessoas;

    // Constante da Q2 [cite: 13]
    int TOTAL_SIMULACOES_Q2 = 300;
    int TOTAL_EXPERIMENTOS = 10; // [cite: 14]

    // --- Loop 1: Loop Principal (pede N) ---
    // Roda até o usuário digitar N <= 0 [cite: 15]
    while (1) {
        printf("\n-------------------------------------------------");
        printf("\nDigite o N de pessoas (0 ou menos para sair): ");
        scanf("%d", &N_pessoas);

        if (N_pessoas <= 0) {
            break; // Para o Loop 1
        }

        printf("Iniciando %d experimentos para N = %d...\n", TOTAL_EXPERIMENTOS, N_pessoas);

        // --- Loop 2: 10 Experimentos --- [cite: 14]
        for (int exp = 0; exp < TOTAL_EXPERIMENTOS; exp++) {
            
            // O "Caçador": Começa a "adivinhar" o número de dias.
            // (Começar com N é um palpite inicial razoável)
            int dias_necessarios = N_pessoas; 

            // --- Loop 3: "Caçador" de Dias ---
            // Este loop incrementa 'dias_necessarios' até que a
            // probabilidade de colisão seja < 10% [cite: 12]
            while (1) {
                
                int contador_de_colisoes = 0;

                // --- Loop 4: 300 Cenários --- [cite: 13]
                // Roda a simulação 300x para o N e 'dias_necessarios' atuais
                for (int c = 0; c < TOTAL_SIMULACOES_Q2; c++) {
                    
                    // ----- INÍCIO DA LÓGICA "simularCenario" -----
                    
                    int aniversarios[N_pessoas];

                    // 1. Sorteia N aniversários (de 0 a 'dias_necessarios' - 1)
                    for (int p = 0; p < N_pessoas; p++) {
                        aniversarios[p] = rand() % dias_necessarios;
                    }

                    // 2. Ordena os aniversários (Sua lógica da Q1)
                    for (int i = 0; i < N_pessoas - 1; i++) {
                        for (int j = 0; j < N_pessoas - 1 - i; j++) {
                            if (aniversarios[j] > aniversarios[j + 1]) {
                                int temp = aniversarios[j];
                                aniversarios[j] = aniversarios[j + 1];
                                aniversarios[j + 1] = temp;
                            }
                        }
                    }

                    // 3. Verifica se há vizinhos iguais (colisão)
                    int achou_colisao = 0;
                    for (int p = 0; p < N_pessoas - 1; p++) {
                        if (aniversarios[p] == aniversarios[p + 1]) {
                            achou_colisao = 1; // Achou colisão!
                            break; // Para o loop 'p'
                        }
                    }
                    
                    if (achou_colisao == 1) {
                        contador_de_colisoes++;
                    }
                    
                    // ----- FIM DA LÓGICA "simularCenario" -----

                } // Fim do Loop 4 (300 Cenários)

                // Calcula a probabilidade (ex: 45 / 300 = 0.15 ou 15%)
                float prob_colisao = (float)contador_de_colisoes / TOTAL_SIMULACOES_Q2;

                // Verifica a condição da Q2 (probabilidade INFERIOR A 10%) [cite: 12]
                if (prob_colisao < 0.10) {
                    // SUCESSO! Achamos o número de dias.
                    printf("  Exp %d: Dias = %d (Prob: %.2f%%)\n", 
                           exp + 1, dias_necessarios, prob_colisao * 100.0);
                    
                    // Quebra o Loop 3 (Caçador) e vai para o próximo Experimento
                    break; 
                } else {
                    // FALHA. A probabilidade (ex: 15%) ainda é >= 10%.
                    // Tenta de novo com mais dias.
                    dias_necessarios++;
                }
            } // Fim do Loop 3 (Caçador)
        } // Fim do Loop 2 (10 Experimentos)
    } // Fim do Loop 1 (Principal)

    printf("\nPrograma encerrado.\n");
    return 0;
}