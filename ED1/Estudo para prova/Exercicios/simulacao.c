#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int n;             // Tamanho do vetor a ser gerado pelo usuário
    int cont;          // Contador de tentativas de vetores
    int porc;          // Contador de vetores válidos (sem números repetidos)
    
    srand(time(NULL)); // Inicializa o gerador de números aleatórios com a hora atual

    // Loop principal: permite testar múltiplos valores de n
    do {
        printf("Digite o tamanho do vetor (ou 0 para sair): ");
        scanf("%d", &n);

        if (n <= 0) break; // Encerra o programa se n <= 0

        int vet[n];    // Vetor que armazenará os números aleatórios
        cont = 0;      // Zera o contador de tentativas
        porc = 0;      // Zera o contador de vetores válidos

        // Simulação: gerar 100.000 vetores de tamanho n
        while (cont < 100000) {
            int valido = 1; // Assume que o vetor atual é válido (sem repetições)

            // Preencher o vetor com números aleatórios de 0 a 2*n - 1
            for (int i = 0; i < n; i++) {
                vet[i] = rand() % (2 * n);
            }

            // Verificar se há números repetidos no vetor
            for (int i = 0; i < n; i++) {
                for (int k = i + 1; k < n; k++) { // Começa de i+1 para não comparar consigo mesmo
                    if (vet[i] == vet[k]) {       // Se encontrar repetição
                        valido = 0;               // Vetor inválido
                        break;                    // Sai do laço interno
                    }
                }
                if (!valido) break; // Sai do laço externo se já encontrou repetição
            }

            // Se o vetor é válido, incrementa o contador
            if (valido) {
                porc++;
            }

            cont++; // Próxima tentativa
        }

        // Mostrar resultados para o usuário
        printf("Número de vetores válidos: %d\n", porc);
        printf("Porcentagem de vetores válidos: %.2f%%\n\n", ((float)porc / 100000) * 100);

    } while (1); // Continua pedindo novos valores de n

    return 0; // Fim do programa
}
