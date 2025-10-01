#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

int main() {
    system("chcp 65001");

    int n;
    bool primo = true;

    printf("Digite um valor inteiro:\n");
    scanf("%d", &n);

    if(n <= 1)
    {
        primo = false;
    }
    else 
    {
        for (int i = 2; i < n / 2; i++)
        {
            if (n % i == 0)
            {
                primo = false;
            break;
            }

        }
    }
            
    if(primo)
    {
        printf("%d é um número primo !\n", n);
    }
    else
    {
        printf("%d não é um número primo !\n", n);
    }

    return 0;
}