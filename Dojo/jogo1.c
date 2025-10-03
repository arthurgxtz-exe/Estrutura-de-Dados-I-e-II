#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h> 

int main() {
    srand(time(NULL));

    int tentativa;
    int pontuacao = 0;
    int palpite;
    
    system("cls"); 
    printf("--- ENCONTRE O NUMERO ---\n\n");
    printf("Objetivo: Encontre o numero diferente no painel.\n");
    printf("Voce tera 3 segundos para memorizar.\n");
    printf("O jogo tem 10 tentativas.\n\n");
    printf("Pressione ENTER para comecar...");
    getchar(); 

    
    for (tentativa = 1; tentativa <= 10; tentativa++) {
        system("cls");

        int num_comum = rand() % 9 + 1;
        int num_diferente = rand() % 9 + 1;
        while (num_diferente == num_comum) {
            num_diferente = rand() % 9 + 1;
        }
        int pos_diferente = rand() % 700; 

        printf("--- TENTATIVA %d / 10 ---\n\n", tentativa);
        printf("Memorize em 3 segundos!\n\n");

        
        for (int i = 0; i < 700; i++) {
            if (i == pos_diferente) {
                printf("%d ", num_diferente);
            } else {
                printf("%d ", num_comum);
            }
            if ((i + 1) % 35 == 0) { 
                printf("\n");
            }
        }

        Sleep(3000); 

        system("cls");
        printf("QUAL ERA O VALOR DIFERENTE >>> ");
        scanf("%d", &palpite);

        
        if (palpite == num_diferente) {
            printf("\nAcertou! \\o/\n");
            pontuacao++;
        } else {
            printf("\nChute pra fora :( Era o %d\n", num_diferente);
        }
        
        printf("\nTecle ENTER para continuar para a proxima tentativa...");
        while (getchar() != '\n');
        getchar();
    }

    system("cls");
    printf("--- FIM DE JOGO ---\n\n");
    printf("Voce obteve %d/%d acertos!\n", pontuacao, 10);
    system("pause");
    return 0;
}