#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h> 

int main() {
    
    int i, j, espaco;
    int h = 12; 
    
    char *cores[] = {"\033[1;31m", "\033[1;33m", "\033[1;32m", "\033[1;34m", "\033[1;35m"}; 

    srand(time(NULL));
    
    while (1) { 
        
        system("cls"); 

        printf("\n"); 
        
        for (i = 0; i < h; i++) { 
            
            for (espaco = i; espaco < h; espaco++) {
                printf(" ");
            }
            
            for (j = 0; j <= i * 2; j++) {
                
                if (rand() % 6 == 0) { 
                    printf("%s*\033[0m", cores[rand() % 5]); 
                } else {
                    printf("\033[1;32m^\033[0m"); 
                }
            }
            printf("\n");
        }

        for (i = 0; i < 3; i++) { 
            for (espaco = 0; espaco < h - 1; espaco++) {
                printf(" ");
            }
            printf("\033[0;33m|||\033[0m\n");
        }
        
        printf("\n\033[1;31mFeliz Natal e um próspero Ano Novo!\033[0m 🎅🎁🎄\n");
        
        Sleep(800); 
    }
    
    return 0; 
}