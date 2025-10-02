#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main() {
    system("chcp 65001");

    int n;
    int maior_menor_primo = 0, menor_maior_primo = 0;
    bool primo;


    printf("Digite um número inteiro:\n");
    scanf("%d", &n);

   
        for(int i = n - 1; i > 0; i--)
        {
            primo = true;
            for(int j = 2; j < i; j++)
            {
                if(i % j == 0)
                {
                    primo = false;
                    break;
                }
            }
            if(primo)
            {
                maior_menor_primo = i;
                break;
            }
        }
        
    
        for(int i = n + 1; i > n; i++)
        {
            primo = true;
            for(int j = 2; j < i; j++)
            {
                if(i % j == 0)
                {
                    primo = false;
                    break;
                }
            }
            if(primo)
            {
                menor_maior_primo = i;
                break;
            }
          
        }
 
    if(maior_menor_primo == 0)
    {
        printf("Não existe um número primo menor que %d.\n", n);
    }
    else
    {
        printf("O maior número primo menor que %d é: %d\n", n, maior_menor_primo);
    }

    printf("O menor número primo maior que %d é: %d\n", n, menor_maior_primo);   
    return 0;
}