#include <stdio.h>
#include <stdlib.h>

int main() {

    int n, primo;

    printf("Digite um numero:\n");
    scanf("%d", &n);

    int anterior = n - 1;
    int posterior = n + 1;

    primo = 0;
    
    while(!primo){
        primo = 1;
        if(anterior <= 1)
            {
                primo = 0;
                break;
            }
        for(int i = 2; i < anterior; i++)
        {
            
    
            if(anterior % i == 0 )
            {
                primo = 0;
                anterior--;
                break;
            }
                
        }

    }



    if(primo){
        printf("O número primo anterior mais proximo é %d\n", anterior);
    }
    else{
        printf("Não existe primo anterior mais proximo\n");
    }


    primo = 0;

    while(!primo){
        primo = 1;
        for(int i = 2; i < posterior; i++)
        if(posterior % i == 0 )
        {
            primo = 0;
            posterior++;
            break;
        }
        
    }

    printf("O número primo posterior mais proximo é %d\n", posterior);

    return 0;
}