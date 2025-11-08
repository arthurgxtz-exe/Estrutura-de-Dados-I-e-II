#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    int aposta[5];
    int n_sorteados = 0;
    int candidato;
    int repetido;

    while(n_sorteados <  5){
        repetido = 0;
        candidato = rand() % 80 + 1;
        
        for( int i = 0; i < n_sorteados; i++)
        {   
            if(aposta[i] == candidato)
            {
                repetido = 1;
                break;
            }
        }
        
        if(!repetido){
            aposta[n_sorteados] = candidato;
            n_sorteados++;
        }
    }
        

    printf("Números sorteados:\n");
        for(int i = 0; i < 5; i++)
        {
            printf("%d ", aposta[i]);
        }
    return 0;
}