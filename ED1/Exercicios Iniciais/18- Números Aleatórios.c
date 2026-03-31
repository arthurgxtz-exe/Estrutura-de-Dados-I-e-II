#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    
    int n, x, y, resultado;

    printf("Quantos números aleatórios você quer gerar?\n");
    scanf("%d", &n);

    printf("Digite o limite inferior do intervalo:\n");
    scanf("%d", &x);
    printf("Digite o limite superior do intervalo:\n");
    scanf("%d", &y);

    for (int i = 1; i <= n; i++)
    {
        resultado = (rand() % (y - x + 1)) + x; 
        printf("Número aleatório N° %d: %d\n", i, resultado);
    }


    return 0;
}