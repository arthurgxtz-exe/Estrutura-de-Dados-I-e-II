#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

int main() {
srand(time(NULL));
    int num[100];
    int resp[100];
    int rodada = 0;
    int i;

    printf("---Jogo da mémoria---\n");
    printf("Memorize o número que aparecer e a sequência\n");
    printf("Pronto? Tecle enter para começar!\n");
    getchar();

    while(rodada < 100){
        system("cls");
        
        num[rodada] = rand() % 100 + 1;
     
        printf("Númer0: %d\n", num[rodada]);
        Sleep(1000);
        system("cls");
        printf("Digite a sequência (%d numeros):\n", rodada + 1);
        for (i = 0; i <= rodada; i++)
        {
            scanf("%d", &resp[i]);
            
        }
        
        int correto = 1;
        for( i = 0; i <= rodada; i++)
        {
            if(resp[i] != num[i])
            {
                correto = 0;
                break;
                
            }   

        }
        if(!correto)
        {   
            printf("==FIM DE JOGO==\n");
            printf("Você errou a sequência, mais sorte na próxima!\n");
            printf("Sequência correta:\n");
            for( i = 0; i <= rodada; i++)
            {
                printf("%d ", num[i]);
            }
            break;
        }
        else
        {
            printf("Tecle enter para ir para próxima rodada!\n");
                while(getchar() != '\n');
                getchar();
        }

     rodada++;
    }
    

    return 0;
}