#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    int num, jogada;
    float porcento;
    int cont[6] = {0, 0, 0, 0, 0, 0};

    printf("Digite quantas vezes você quer girar o dado:\n");
    scanf("%d", &num);


    for (int i = 1; i <= num; i++)
    {
        jogada = rand() % 6 + 1;
        cont[jogada - 1]++;
        printf("%d° jogada: %d\n", i, jogada);

    }
   
    for (int j = 0; j < 6; j++)
    {    
        porcento = (float)(cont[j] * 100) / num;
        printf("A face %d teve %d ocorrências, que representa %.2f%% do total.\n", j+1, cont[j], porcento);
    }

    return 0;
}
  
