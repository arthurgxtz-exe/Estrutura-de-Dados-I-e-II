#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char string[100];
    char c1, c2;

    printf("Digite uma frase:\n");
    scanf(" %[^\n]s", string); 
    while (getchar() != '\n'); 

    printf("Digite o caractere que voce quer SUBSTITUIR:\n");
    scanf(" %c", &c1); 
    while (getchar() != '\n'); 

    printf("Digite o NOVO caractere:\n");
    scanf(" %c", &c2);
    while (getchar() != '\n'); 
    
    system("cls");

    int tamanho = strlen(string);
    for(int i = 0; i < tamanho; i++)
    {
        
        if(string[i] == c1)
        {
            string[i] = c2;
        }
    }

    printf("Frase modificada: %s\n", string);
    
    return 0;
}