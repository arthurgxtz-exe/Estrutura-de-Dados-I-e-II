//Feito por: Arthur Almeida e Carlos Felipe

#include <stdio.h>
#include <unistd.h>  
#define N 3   // numero de processos
#define R 1   // numero de tipos de recurso

int alocacao[N][R];
int maximo[N][R];
int necessidade[N][R];
int disponivel[R];

/*
 Como funciona o Algoritmo do Banqueiro:
 
 1) Calcula quanto cada processo ainda PRECISA de recursos para terminar
  (necessidade = maximo - alocacao)

 2) Vai testando processo por processo se os recursos disponiveis no
     momento sao suficientes para atender a necessidade dele.
 
 3) Se um processo consegue terminar, ele devolve tudo que tinha alocado,
    aumentando os recursos disponiveis para os proximos processos.
 
 4) Se em algum momento nenhum processo restante consegue ser atendido,
    o sistema esta em ESTADO INSEGURO (ha risco de deadlock).
 
 5) Se todos os processos conseguirem terminar, a ordem em que eles
    terminaram e a SEQUENCIA SEGURA.
 */

// calcula a necessidade de cada processo e mostra a conta sendo feita
void calcularNecessidade() {
    int i, j;

    printf("ETAPA 1 - Calculando a necessidade de cada processo\n");
    printf("(necessidade = maximo - alocacao)\n\n");

    for (i = 0; i < N; i++) {
        printf("  P%d: ", i + 1);
        for (j = 0; j < R; j++) {
            necessidade[i][j] = maximo[i][j] - alocacao[i][j];
            printf("%d - %d = %d   ", maximo[i][j], alocacao[i][j], necessidade[i][j]);
        }
        printf("\n");
        sleep(1);
    }
    printf("\n");
}

// imprime uma tabela resumindo os dados.
void mostrarTabela() {
    int i, j;

    printf("Resumo dos dados:\n\n");
    printf("Processo | Maximo | Alocacao | Necessidade\n");
    printf("---------------------------------------------\n");

    for (i = 0; i < N; i++) {
        printf("   P%-5d|", i + 1);
        for (j = 0; j < R; j++) printf("   %-5d|", maximo[i][j]);
        for (j = 0; j < R; j++) printf("    %-6d|", alocacao[i][j]);
        for (j = 0; j < R; j++) printf("     %-6d", necessidade[i][j]);
        printf("\n");
    }
    printf("---------------------------------------------\n\n");
}

// tenta montar uma sequencia segura de execucao.
void algoritmoBanqueiro() {
    int trabalho[R];      // recursos disponiveis durante a simulacao
    int finalizado[N];    // marca quais processos ja terminaram
    int sequencia[N];     // guarda a ordem em que os processos terminaram
    int contador = 0;
    int i, j, k;
    int rodada = 1;

    for (j = 0; j < R; j++) trabalho[j] = disponivel[j];
    for (i = 0; i < N; i++) finalizado[i] = 0;

    printf("ETAPA 2 - Verificando se existe uma sequencia segura\n\n");

    while (contador < N) {
        int encontrou = 0;

        printf("--- Rodada %d ---\n", rodada);
        printf("Recursos disponiveis no momento: ");
        for (j = 0; j < R; j++) printf("%d ", trabalho[j]);
        printf("\n");

        for (i = 0; i < N; i++) {
            if (finalizado[i] == 1) {
                continue;
            }

            printf("  Verificando P%d (necessidade: ", i + 1);
            for (j = 0; j < R; j++) printf("%d ", necessidade[i][j]);
            printf(")... ");

            int podeExecutar = 1;
            for (j = 0; j < R; j++) {
                if (necessidade[i][j] > trabalho[j]) {
                    podeExecutar = 0;
                    break;
                }
            }

            if (podeExecutar == 1) {
                printf("CONSEGUE executar!\n");
                printf("  P%d termina e devolve sua alocacao: ", i + 1);
                for (j = 0; j < R; j++) {
                    trabalho[j] += alocacao[i][j];
                    printf("%d ", alocacao[i][j]);
                }
                printf("\n");

                finalizado[i] = 1;
                sequencia[contador] = i;
                contador++;
                encontrou = 1;
            } else {
                printf("NAO consegue (precisa de mais recursos do que ha disponivel).\n");
            }

            sleep(1);
        }

        printf("\n");
        rodada++;

        // se ninguem conseguiu executar nesta rodada, nao tem como continuar
        if (encontrou == 0) {
            break;
        }
    }

    printf("ETAPA 3 - Resultado final\n\n");

    if (contador == N) {
        printf("O sistema esta em um ESTADO SEGURO.\n");
        printf("Sequencia segura encontrada: ");
        for (k = 0; k < N; k++) {
            printf("P%d", sequencia[k] + 1);
            if (k < N - 1) printf(" -> ");
        }
        printf("\n");
    } else {
        printf("O sistema esta em um ESTADO INSEGURO.\n");
        printf("Nao foi possivel encontrar uma sequencia que atenda a todos os processos.\n");
        printf("Ha risco de deadlock.\n");
    }
}

int main() {
    int i, j;

    // dados de entrada do exemplo da atividade
    int alocacaoEntrada[N][R] = { {2}, {3}, {1} };
    int maximoEntrada[N][R]   = { {4}, {5}, {3} };
    int disponivelEntrada[R]  = { 1 };

    for (i = 0; i < N; i++) {
        for (j = 0; j < R; j++) {
            alocacao[i][j] = alocacaoEntrada[i][j];
            maximo[i][j] = maximoEntrada[i][j];
        }
    }
    for (j = 0; j < R; j++) {
        disponivel[j] = disponivelEntrada[j];
    }

    printf("===========================================\n");
    printf("        ALGORITMO DO BANQUEIRO\n");
    printf("===========================================\n\n");

    calcularNecessidade();
    mostrarTabela();

    printf("Recursos disponiveis no sistema: ");
    for (j = 0; j < R; j++) printf("%d ", disponivel[j]);
    printf("\n\n");

    algoritmoBanqueiro();

    return 0;
}
