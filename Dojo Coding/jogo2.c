#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h> 


int main() {
    srand(time(NULL));

    int num_secreto_pc, num_chute, chute_pc, tentativas_pc = 0, tentativas_hum = 0;
    char feedback;
    int min_valor = 0, max_valor = 99;
    num_secreto_pc = rand() % 100;

    printf("----------Adivinhe o número----------\n");
    printf("----------Humano vs Commputador----------\n");
    printf("O PC já escolheu um número entre 0 a 99.\n");
    printf("Tente adivinhar o mais breve possível!\n");
    printf("Pressione enter  quando estiver pronto...\n");
    fflush(stdin);
    getchar();
    system("cls");


    do{
        tentativas_hum++;
        printf("Digite um número entre 0 a 99:\n\n");
        scanf("%d", &num_chute);

        if(num_chute == num_secreto_pc)
        {

        }
        else if(num_chute < num_secreto_pc)
        {
            printf("O número sorteado  é MAIOR que %d\n\n", num_chute);
        }
        else
        {
            printf("O  número  sorteado é MENOR que %d\n\n", num_chute);
        }   

    }while (num_chute != num_secreto_pc);

    printf("Parabéns, você acertou o número após %d tentativas.\n\n", tentativas_hum);
    printf("\nChegou a hora do Pc competir contra você!\n");
    printf("Tecle enter para continuar...\n");
    fflush(stdin);
    getchar();
    system("cls");

    printf("----------A vez do computador ----------\n");
    printf("Agora você deve pensar em um número de 0 a 99.\n");
    printf("O PC tentará adivinhar. Responda com '>', '<' ou '='.\n");
    printf("Pressione enter quando estiver pronto...\n");
    fflush(stdin);
    getchar();
    system("cls");

    while(1){
        system("cls");

        chute_pc = (rand() % (max_valor - min_valor + 1)) + min_valor;
        tentativas_pc++;

              
        printf("O PC chutou %d\n\n", chute_pc);
        printf("DIGITE:\n");
        printf("'>' Se o seu numero for MAIOR\n");
        printf("'<' Se o seu numero for MENOR\n");
        printf("'=' Se o PC ACERTOU\n");
        printf("Sua resposta: ");
        scanf(" %c", &feedback);

        if(feedback == '=')
        {
            printf("\nO PC acertou  o  número escolhido!\n");
            printf("Foram nescessárias %d tentativas para o PC!\n", tentativas_pc);
            break;
        }
        else if(feedback ==  '>')
        {
            min_valor =  chute_pc + 1;
            printf("\nPc, o número que eu pensei é maior...\n");
        }
        else if(feedback == '<')
        {
            max_valor = chute_pc - 1;
            printf("\nPc, o  número que eu pensei é menor...\n");
        }
        else
        {
            printf("\nResposta inválida, por favor digite '>', '<' ou '='.\n");
            tentativas_pc--;
        }
        Sleep(1500);
    }
    printf("\n---------- Resultado Final ----------\n");
    printf("Humano %d  x  %d PC\n", tentativas_hum, tentativas_pc);

     if (tentativas_hum < tentativas_pc) {
        printf("Parabens, voce ganhou do PC! \\o/\n");
    } else if (tentativas_pc < tentativas_hum) {
        printf("A maquina te venceu! :(\n");
    } else {
        printf("Voce e a maquina empataram!\n");
    }

    return 0;
}