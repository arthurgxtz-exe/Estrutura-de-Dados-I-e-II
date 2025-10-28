#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {

    char string[100];
    char c1, c2;

    printf("Digite uma frase:\n");
    scanf(" %[^\n]s", string);
    while (getchar() != '\n');
    printf("Digite o caractere que você quer incluir na frase:\n");
    scanf(" %c", &c1);
    while(getchar() != '\n');
    printf("Digite o caractere que você vai substituir pelo anterior na frase:\n");
    scanf(" %c", &c2);
    while(getchar() != '\n');
    system("cls");

    for(int i = 0; i <= strlen(string); i++)
    {
        if(string[i] == '\0')
        {
            break;
        }
        else if(string[i] == c2)
        {
            string[i] = c1;
        }
    }


    printf("%s", string);
   
    return 0;
}