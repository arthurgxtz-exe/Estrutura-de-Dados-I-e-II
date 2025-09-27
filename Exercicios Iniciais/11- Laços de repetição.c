#include <stdio.h>
#include <stdlib.h>

int main(){

    int num;

    printf("\nDigite um numero inteiro:\n");
    scanf("%d", &num);

    for (int i = 0; i <= num; i++)
        {
            if(i % 2 == 0)
            {
                printf("Valores crescentes pares:%d\n", i);
            }
        }
    
    
    for (int i = num; i >= 0; i--)
        {
            if(i % 2 != 0)
            {
                printf("Valores descrescentes impares:%d\n", i);
            }
        }
    
     return 0;
}