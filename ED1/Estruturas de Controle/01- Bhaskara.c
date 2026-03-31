#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    
    double a, b, c, delta, x1, x2;

    printf("Digite o valor de a:\n");
    scanf("%lf", &a);
    printf("Digite o valor de b:\n");
    scanf("%lf", &b);
    printf("Digite o valor de c:\n");
    scanf("%lf", &c);

    delta = pow(b, 2) - 4 * a * c;

    if(a == 0){
        
        printf("Essa não é uma equação de segundo grau\n");
    }
    else
    {
        if (delta < 0)
        {
            printf("Não existem raízes reais.\n");
        }
        else
        {
            if (delta == 0)
            {
                x1 = -b / (2 * a);
                printf("Existe apenas uma raiz real: %.2lf\n", x1);
            }
            else 
            {
                x1 = (-b + sqrt(delta)) / (2 * a); 
                x2 = (-b - sqrt(delta)) / (2 * a);
                printf("Raiz x1: %.2lf\n", x1);
                printf("Raiz x2: %.2lf\n", x2);
            }
        }
    }
    
    return 0;
}