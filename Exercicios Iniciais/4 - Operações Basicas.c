#include <stdio.h>
#include <stdlib.h>

int main() {

    float custo, taxa;
    int x, y;

    printf("Digite o custo de produção do produto:\n");
    scanf("%f", &custo);
    printf("Digite a porcentagem de imposto a ser acressido:\n");
    scanf("%d", &x);
    printf("Digite a porcentagem de custos do distribuidor:\n");
    scanf("%d", &y);
    
    taxa = (custo * (x / 100.0));
    custo = custo + taxa;
    taxa = (custo * (y / 100.0));
    custo = custo + taxa;
   

    printf("O custo final do produto é de %f\n", custo);

    return 0;

}
