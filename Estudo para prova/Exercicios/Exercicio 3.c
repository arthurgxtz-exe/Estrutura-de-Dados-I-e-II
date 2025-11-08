#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));

    int x, n;
    printf("Digite qual vai ser o tamanho do vetor:\n");
    scanf("%d", &x);
    printf("O intervalo de numeros sorteados seerá de 0 até...?\n");
    scanf("%d", &n);

    int vet[x];
    int contagem[n + 1];

    for(int i = 0; i <= n; i++)
    {
        contagem[i] = 0;
    }
    printf("Todos os números sorteados:\n");
    for(int i = 0; i < x; i++)
    {
        vet[i] = rand() % (n + 1); 
        contagem[vet[i]]++;
        printf("%d ", vet[i]);
    }
    int cont  = 0;
    for(int i = 0; i <= n; i++)
    {
        if(contagem[i] > 0)
        {
            cont++;
        }
    }
    printf("\nForam sorteados %d números distintos.\n", cont);
    int maior = vet[0];
    int menor = vet[0];
    int indice_maior = 0, indice_menor = 0;
    for(int i = 1; i < x; i++)
    {
        if(vet[i] > maior)
        {
            maior = vet[i];
            indice_maior = i;
        }
        if(vet[i] < menor)
        {
            menor = vet[i];
            indice_menor = i;
        }

    }
    printf("O menor valor é %d, e ele está no indice[%d]\n", menor, indice_menor);
    printf("O maior valor é %d, e ele está no indice[%d]\n", maior, indice_maior);
    int maior_contagem = contagem[0]; 
    int menor_contagem = x;
    int n_mais = 0;
    int n_menos = 0;
    for(int i = 1; i <= n; i++)
    {
        if(contagem[i] > maior_contagem)
        {
            maior_contagem = contagem[i];
            n_mais = i;
        }
        if(contagem[i] < menor_contagem && contagem[i] > 0)
        {
            menor_contagem = contagem[i];
            n_menos = i;
        }
    }

    printf("O numero mais vezes sorteado foi %d, que apareceu %d vezes\n", n_mais, maior_contagem);
    printf("O numero menos vezes sorteado foi %d, que apareceu %d vezes\n", n_menos, menor_contagem);
    return 0;
}