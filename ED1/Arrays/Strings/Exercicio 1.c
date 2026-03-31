#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
int main() {
    char senha[11];
    char caractere;
    int cont;

    for(int i = 0; i < 5; i++)
    {
        cont = 0;
        printf("Digite uma senha:(No maximo 10 caracteres)\n");
        while(1){
            caractere = getch();

            if(caractere == 13)
            {
                senha[cont] = '\0';
                break;
            }
            else if(caractere == 8 && cont > 0)
            {
                cont--;
                printf("\b \b");
            }
            else if(cont < 10)
            {
                senha[cont] = caractere;
                cont++;
                printf("*");
            }

        }
       
        printf("\nSenha gerada da tentativa %d:\n", i + 1);
        printf("Sua senha é:\n");
        printf("%s\n", senha);
        printf("Tamanho da senha: %d caracteres.\n", strlen(senha));
        
    }
    printf("Programa finalizado.\n");
    return 0;
}