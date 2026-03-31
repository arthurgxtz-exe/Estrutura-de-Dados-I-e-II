#include <stdio.h>

int main() {
    /*
     * EXPLICAÇÃO DO CONCEITO (EXERCÍCIO 5):
     *
     * Este programa demonstra como o C armazena caracteres. Em C, uma
     * variável do tipo 'char' não guarda o "desenho" de uma letra, mas
     * sim um NÚMERO INTEIRO que a representa.
     *
     * Esse número é o código do caractere na Tabela ASCII, que é um
     * padrão universal.
     *
     * - O formato %c no printf() pega o número e mostra o CARACTERE
     * correspondente na tabela.
     * - O formato %d no printf() pega o mesmo número e o mostra como um
     * NÚMERO decimal.
     *
     * Exemplo: Se o usuário digita 'A', a variável guarda o número 65.
     * - %c vai imprimir 'A'.
     * - %d vai imprimir 65.
    */

    char letra;

    printf("Digite um caractere:");
    scanf(" %c", &letra); // O espaço antes do %c é importante para ignorar 'Enters' anteriores

    printf("Saida com %%c e %%d: %c %d\n", letra, letra);
    
    return 0;
}