/*
    🐍 JOGO DA COBRINHA - VERSÃO LINUX
    Autor: Arthur Ferreira de Almeida
    Linguagem: C (compatível com GCC/Linux)
    Controles:
      W - Cima
      S - Baixo
      A - Esquerda
      D - Direita
      X - Sair
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <time.h>

#define WIDTH 30
#define HEIGHT 15

int main() {
    int x, y, fruitX, fruitY, score;
    int tailX[100], tailY[100];
    int nTail;
    int gameOver;
    enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
    enum eDirection dir = STOP;

    struct termios oldt, newt;
    int kbhit(void) {
        struct termios oldt, newt;
        int ch;
        int oldf;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return ch;
    }

inicio_jogo:
    gameOver = 0;
    dir = STOP;
    x = WIDTH / 2;
    y = HEIGHT / 2;
    fruitX = rand() % (WIDTH - 2) + 1;
    fruitY = rand() % (HEIGHT - 2) + 1;
    score = 0;
    nTail = 0;

    while (!gameOver) {
        printf("\033[H\033[J");

        printf("╔");
        for (int i = 0; i < WIDTH; i++) printf("═");
        printf("╗\n");

       for (int i = 0; i < HEIGHT; i++) {
            printf("║");
            for (int j = 0; j < WIDTH; j++) {
                if (i == y && j == x)
                    printf("O"); 
                else if (i == fruitY && j == fruitX)
                    printf("@");
                else {
                    int printTail = 0;
                    for (int k = 0; k < nTail; k++) {
                        if (tailX[k] == j && tailY[k] == i) {
                            printf("o"); 
                            printTail = 1;
                        }
                    }
                    if (!printTail) printf(" ");
                }
            }
            printf("║\n");
        }

        printf("╚");
        for (int i = 0; i < WIDTH; i++) printf("═");
        printf("╝\n");
        printf("Pontuação: %d\n", score);
        printf("Use W, A, S, D para mover. X para sair.\n");

        struct termios oldt, newt;
        int ch;
        int oldf;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        usleep(100000);
        if (fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK) == 0) {}
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

        if (ch != EOF) {
            switch (ch) {
                case 'a': dir = LEFT; break;
                case 'd': dir = RIGHT; break;
                case 'w': dir = UP; break;
                case 's': dir = DOWN; break;
                case 'x': gameOver = 1; break;
            }
        }

        int prevX = tailX[0];
        int prevY = tailY[0];
        int prev2X, prev2Y;
        tailX[0] = x;
        tailY[0] = y;
        for (int i = 1; i < nTail; i++) {
            prev2X = tailX[i];
            prev2Y = tailY[i];
            tailX[i] = prevX;
            tailY[i] = prevY;
            prevX = prev2X;
            prevY = prev2Y;
        }

        switch (dir) {
            case LEFT: x--; break;
            case RIGHT: x++; break;
            case UP: y--; break;
            case DOWN: y++; break;
            default: break;
        }

        if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
            gameOver = 1;

       for (int i = 0; i < nTail; i++)
            if (tailX[i] == x && tailY[i] == y)
                gameOver = 1;

        if (x == fruitX && y == fruitY) {
            score += 10;
            fruitX = rand() % (WIDTH - 2) + 1;
            fruitY = rand() % (HEIGHT - 2) + 1;
            nTail++;
        }
    }

    
    printf("\033[H\033[J");
    printf("\n💀 Fim de jogo! Pontuação final: %d\n", score);
    printf("\nDeseja jogar novamente? (s/n): ");
    char op;
    scanf(" %c", &op);
    if (op == 's' || op == 'S')
        goto inicio_jogo;

    printf("\nAté a próxima, jogador!\n");
    return 0;
}
