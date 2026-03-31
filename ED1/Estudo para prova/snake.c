#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

// 🐍 Snake Game - Autor: Arthur Ferreira de Almeida

int main() {
    int width = 40, height = 20;
    int x, y, fruitX, fruitY, score;
    int tailX[100], tailY[100];
    int nTail;
    int gameOver, dir; // 0-stop, 1-left, 2-right, 3-up, 4-down
    char tecla;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.bVisible = 0;
    cursorInfo.dwSize = 1;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

inicio:
    system("cls");
    gameOver = 0;
    dir = 0;
    score = 0;
    nTail = 0;
    x = width / 2;
    y = height / 2;
    srand(time(0));
    fruitX = rand() % (width - 2) + 1;
    fruitY = rand() % (height - 2) + 1;

    // Desenha moldura inicial
    for (int i = 0; i < height + 2; i++) {
        for (int j = 0; j < width + 2; j++) {
            if (i == 0 || i == height + 1 || j == 0 || j == width + 1)
                printf("#");
            else
                printf(" ");
        }
        printf("\n");
    }

    while (!gameOver) {
        // --- Atualiza cursor ---
        COORD coord = {0, 0};
        SetConsoleCursorPosition(hConsole, coord);

        // --- Desenha ---
        for (int i = 0; i < height + 2; i++) {
            for (int j = 0; j < width + 2; j++) {
                if (i == 0 || i == height + 1 || j == 0 || j == width + 1)
                    printf("#");
                else if (i == y && j == x)
                    printf("O");
                else if (i == fruitY && j == fruitX)
                    printf("*");
                else {
                    int print = 0;
                    for (int k = 0; k < nTail; k++) {
                        if (tailX[k] == j && tailY[k] == i) {
                            printf("o");
                            print = 1;
                            break;
                        }
                    }
                    if (!print) printf(" ");
                }
            }
            printf("\n");
        }

        printf("Pontuação: %d\n", score);
        printf("Use WASD para mover, X para sair.\n");

        // --- Entrada ---
        if (_kbhit()) {
            tecla = _getch();
            if (tecla == 'a' && dir != 2) dir = 1;
            if (tecla == 'd' && dir != 1) dir = 2;
            if (tecla == 'w' && dir != 4) dir = 3;
            if (tecla == 's' && dir != 3) dir = 4;
            if (tecla == 'x') gameOver = 1;
        }

        // --- Movimento da cauda ---
        int prevX = tailX[0], prevY = tailY[0];
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

        // --- Movimento da cabeça ---
        switch (dir) {
            case 1: x--; break; // esquerda
            case 2: x++; break; // direita
            case 3: y--; break; // cima
            case 4: y++; break; // baixo
        }

        // --- Colisões ---
        if (x <= 0 || x >= width + 1 || y <= 0 || y >= height + 1)
            gameOver = 1;

        for (int i = 0; i < nTail; i++)
            if (tailX[i] == x && tailY[i] == y)
                gameOver = 1;

        // --- Comer fruta ---
        if (x == fruitX && y == fruitY) {
            score += 10;
            fruitX = rand() % (width - 2) + 1;
            fruitY = rand() % (height - 2) + 1;
            nTail++;
        }

        // --- Velocidade uniforme (compensação vertical) ---
        if (dir == 3 || dir == 4)
            Sleep(120); // mais tempo p/ compensar altura do caractere
        else
            Sleep(90);
    }

    system("cls");
    printf("\n########## GAME OVER ##########\n");
    printf("Pontuação final: %d\n", score);
    printf("\nPressione 'r' para recomeçar ou qualquer tecla para sair...\n");

    tecla = _getch();
    if (tecla == 'r' || tecla == 'R') goto inicio;

    return 0;
}
