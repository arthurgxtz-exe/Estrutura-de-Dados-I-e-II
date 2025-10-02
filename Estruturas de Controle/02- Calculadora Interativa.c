#include <stdio.h>
#include <stdlib.h>

int main() {
    
    int num1, num2;
    char op;

    while(1)
    {
        printf("Digite sua operação: operações permitidas [+, -, /, *, %%, ^]\nExemplo: 1 + 1\n");
        scanf("%d %c %d", &num1, &op, &num2);

        switch(op){
            case '+':
                printf("%d + %d = %d\n", num1, num2, num1 + num2);
                break;
            case '-':
                printf("%d - %d = %d\n", num1, num2, num1 - num2);
                break;
            case '/':
                if(num2 == 0)
                {
                    printf("Divisão por zero é indefinida.\n");
                }
                else
                {
                    printf("%d / %d = %.2f\n", num1, num2, (float)num1 / num2);
                }
                break;
            case '*':
                printf("%d * %d = %d\n", num1, num2, num1 * num2);
                break;
            case '%':
            printf("%d %% de %d = %.2f\n", num1, num2, (num1 / 100.0) * num2);
                
                break;
            case '^':
                {
                    int resultado = 1; 
                    for(int i = 0; i < num2; i++) {
                        resultado *= num1;
                    }
                    printf("%d ^ %d = %d\n", num1, num2, resultado);
                }
                break;
            default:
                printf("Operação inválida, por favor digite uma operação permitida\n");
                break;                 
        }
    }

    return 0;
}
