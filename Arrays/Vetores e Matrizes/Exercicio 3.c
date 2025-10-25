#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));

    int num;

    do{
        printf("Digite um número multiplo de 4:\n");
        scanf("%d", &num);
        int vet[num];
        int temp[num];
        if(num < 0 || num % 4 != 0)
        {
            printf("Pode não mmano, digita um número válido ai\n");
        }
       else
       {
           printf("\nLista normal:\n");
           for(int i = 0; i < num; i++)
           {
               vet[i] = rand() % num + 1;
               printf("|%d|", vet[i]);
           }

           printf("\nLista trocada (metade inicial pela final):\n");
           for(int i = 0; i < num /2 ; i++)
           {
                temp[i] = vet[i];
                vet[i] = vet [i + num/2];
                vet [i + num/2] = temp[i];
                
           }
           for(int i = 0; i < num; i++)
           {
               printf("|%d|", vet[i]);
           }
        }

    }while(num < 0 || num % 4 != 0);

    return 0;
}
     


