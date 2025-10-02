#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));

    int n, x, resultado;

    printf("Quantos números aleatórios você quer gerar?\n");
    scanf("%d", &n);
    printf("Esses números serão gerados no intevalo entre 0 e ...:\n");
    scanf("%d", &x);

    for (int i = 1; i <= n; i++)
    {
        resultado = (rand() % (x + 1));
        printf("Número aleatório N° %d: %d\n", i, resultado);
    }


    return 0;
}