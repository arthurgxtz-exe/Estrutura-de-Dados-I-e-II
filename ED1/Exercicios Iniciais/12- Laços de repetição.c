#include <stdio.h>
#include <stdlib.h>

int main(){

    int num1, num2;
    
    do{
        printf("Digite dois numeros inteiros (um par e um impar):\n");
        scanf("%d %d", &num1, &num2);

        if( (num1 % 2 == 0 && num2 % 2 == 0) || (num1 % 2 != 0 && num2 % 2 != 0) )
        {
            printf("\nEntrada invalida! Um numero deve ser par e o outro impar. Tente novamente.\n");
        }
        
    } while( (num1 % 2 == 0 && num2 % 2 == 0) || (num1 % 2 != 0 && num2 % 2 != 0) );
    
    printf("\nNumeros validos inseridos: %d e %d\n", num1, num2);

    if(num1 > num2)
    {
        for (int i = num2 + 1; i < num1; i++)
        printf("%d\n", i);
    }
    else 
    {
        for (int i = num1 + 1; i < num2; i++)
        printf("%d\n", i);
    }


    return 0;
}