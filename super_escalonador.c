//ARTHUR ALMEIDA E CLARA MIRIAN
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PROCESSOS   25
#define INTERRUPCAO_MS  20
#define MAX_FILAS       3
#define MAX_SEQ         100000

#define PRONTO      0
#define EXECUTANDO  1
#define BLOQUEADO   2
#define FINALIZADO  3

typedef struct {
    int pid;
    int tempo_chegada;
    int burst_total;
    int burst_restante;
    int prioridade;
    int estado;
    int tempo_inicio;
    int tempo_fim;
    int tempo_espera;
    int turnaround;
    int fila_nivel;
} Processo;

Processo processos[MAX_PROCESSOS];
Processo processos_original[MAX_PROCESSOS];
int num_processos = 0;
int trocas_contexto = 0;
int sequencia[MAX_SEQ];
int tam_sequencia = 0;

void limpar_tela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void separador() {
    printf("============================================================\n");
}

void cabecalho() {
    limpar_tela();
    separador();
    printf("              SUPER ESCALONADOR\n");
    printf("       Simulador de Algoritmos de Escalonamento\n");
    separador();
}

void gerar_processos() {
    num_processos = 20;

    printf("\n  Gerando %d processos...\n\n", num_processos);
    printf("  PID | Chegada(ms) | Burst(ms) | Prioridade\n");
    printf("  ----|-------------|-----------|------------\n");

    for (int i = 0; i < num_processos; i++) {
        processos[i].pid            = i + 1;
        processos[i].tempo_chegada  = (rand() % 10) * 5;
        processos[i].burst_total    = (rand() % 40) + 5;
        processos[i].burst_restante = processos[i].burst_total;
        processos[i].prioridade     = (rand() % 5) + 1;
        processos[i].estado         = PRONTO;
        processos[i].tempo_inicio   = -1;
        processos[i].tempo_fim      = -1;
        processos[i].tempo_espera   = 0;
        processos[i].turnaround     = 0;
        processos[i].fila_nivel     = 0;

        printf("  P%02d |     %3dms    |   %3dms   |      %d\n",
               processos[i].pid,
               processos[i].tempo_chegada,
               processos[i].burst_total,
               processos[i].prioridade);
    }

    memcpy(processos_original, processos, sizeof(Processo) * num_processos);
    printf("\n");
}

void registrar_execucao(int pid, int duracao) {
    for (int t = 0; t < duracao; t++) {
        if (tam_sequencia < MAX_SEQ)
            sequencia[tam_sequencia++] = pid;
    }
}

void exibir_resultados(const char *nome_algoritmo) {
    separador();
    printf("  Algoritmo : %s\n", nome_algoritmo);
    separador();

    printf("Sequencia de execucao:\n  ");
    int anterior = -1;
    int interrupcoes = 0;
    int tempo_acumulado = 0;
    trocas_contexto = 0;

    for (int i = 0; i < tam_sequencia; i++) {
        if (sequencia[i] != anterior) {
            if (anterior != -1) {
                printf("-> ");
                if (sequencia[i] != 0 && anterior != 0)
                    trocas_contexto++;
            }
            if (sequencia[i] == 0)
                printf("[IDLE] ");
            else
                printf("[P%02d] ", sequencia[i]);
            anterior = sequencia[i];
        }
        tempo_acumulado++;
        if (tempo_acumulado % INTERRUPCAO_MS == 0)
            interrupcoes++;
    }
    printf("\n\n");

    double soma_espera = 0, soma_turnaround = 0;

    printf("  PID | Burst | Chegada | Inicio |  Fim  | Espera | Turnaround\n");
    printf("  ----|-------|---------|--------|-------|--------|------------\n");

    for (int i = 0; i < num_processos; i++) {
        if (processos[i].tempo_fim != -1) {
            processos[i].turnaround = processos[i].tempo_fim - processos[i].tempo_chegada;
            soma_espera     += processos[i].tempo_espera;
            soma_turnaround += processos[i].turnaround;

            printf("  P%02d | %3dms |  %3dms  | %3dms  | %3dms | %3dms  |   %3dms\n",
                   processos[i].pid,
                   processos[i].burst_total,
                   processos[i].tempo_chegada,
                   processos[i].tempo_inicio,
                   processos[i].tempo_fim,
                   processos[i].tempo_espera,
                   processos[i].turnaround);
        }
    }

    separador();
    printf("  Tempo medio de espera      : %.2f ms\n", soma_espera / num_processos);
    printf("  Turnaround medio           : %.2f ms\n", soma_turnaround / num_processos);
    printf("  Trocas de contexto         : %d\n", trocas_contexto);
    printf("  Interrupcoes de ciclo      : %d (a cada %dms)\n", interrupcoes, INTERRUPCAO_MS);
    separador();
}

void reset_processos() {
    memcpy(processos, processos_original, sizeof(Processo) * num_processos);
    for (int i = 0; i < num_processos; i++) {
        processos[i].estado         = PRONTO;
        processos[i].burst_restante = processos[i].burst_total;
        processos[i].tempo_inicio   = -1;
        processos[i].tempo_fim      = -1;
        processos[i].tempo_espera   = 0;
        processos[i].turnaround     = 0;
        processos[i].fila_nivel     = 0;
    }
    trocas_contexto = 0;
    tam_sequencia   = 0;
}

void fifo() {
    Processo copia[MAX_PROCESSOS];
    memcpy(copia, processos, sizeof(Processo) * num_processos);

    for (int i = 0; i < num_processos - 1; i++)
        for (int j = i + 1; j < num_processos; j++)
            if (copia[j].tempo_chegada < copia[i].tempo_chegada) {
                Processo tmp = copia[i];
                copia[i] = copia[j];
                copia[j] = tmp;
            }

    int tempo = 0;

    for (int i = 0; i < num_processos; i++) {
        if (tempo < copia[i].tempo_chegada) {
            int idle = copia[i].tempo_chegada - tempo;
            for (int t = 0; t < idle && tam_sequencia < MAX_SEQ; t++)
                sequencia[tam_sequencia++] = 0;
            tempo = copia[i].tempo_chegada;
        }

        copia[i].tempo_inicio = tempo;
        copia[i].tempo_espera = tempo - copia[i].tempo_chegada;
        copia[i].estado = EXECUTANDO;

        registrar_execucao(copia[i].pid, copia[i].burst_total);
        tempo += copia[i].burst_total;

        copia[i].tempo_fim = tempo;
        copia[i].estado = FINALIZADO;

        for (int j = 0; j < num_processos; j++) {
            if (processos[j].pid == copia[i].pid) {
                processos[j].tempo_inicio = copia[i].tempo_inicio;
                processos[j].tempo_fim    = copia[i].tempo_fim;
                processos[j].tempo_espera = copia[i].tempo_espera;
                processos[j].estado       = FINALIZADO;
                break;
            }
        }
    }
}

void sjf() {
    printf("  Obs.: SJF pode causar starvation em processos longos.\n\n");

    int tempo = 0;
    int finalizados = 0;
    int executado[MAX_PROCESSOS] = {0};

    while (finalizados < num_processos) {
        int menor = -1;

        for (int i = 0; i < num_processos; i++)
            if (!executado[i] && processos[i].tempo_chegada <= tempo)
                if (menor == -1 || processos[i].burst_total < processos[menor].burst_total)
                    menor = i;

        if (menor == -1) {
            if (tam_sequencia < MAX_SEQ) sequencia[tam_sequencia++] = 0;
            tempo++;
            continue;
        }

        processos[menor].tempo_inicio = tempo;
        processos[menor].tempo_espera = tempo - processos[menor].tempo_chegada;
        processos[menor].estado = EXECUTANDO;

        registrar_execucao(processos[menor].pid, processos[menor].burst_total);
        tempo += processos[menor].burst_total;

        processos[menor].tempo_fim = tempo;
        processos[menor].estado = FINALIZADO;
        executado[menor] = 1;
        finalizados++;
    }
}

void srtf() {
    printf("  Obs.: SRTF pode causar starvation em processos longos.\n");
    printf("  Obs.: Nesta simulacao processos podem ser bloqueados por E/S (5ms).\n\n");

    int tempo = 0;
    int finalizados = 0;
    int tempo_desbloqueio[MAX_PROCESSOS];

    for (int i = 0; i < num_processos; i++)
        tempo_desbloqueio[i] = -1;

    while (finalizados < num_processos) {
        for (int i = 0; i < num_processos; i++)
            if (processos[i].estado == BLOQUEADO && tempo >= tempo_desbloqueio[i])
                processos[i].estado = PRONTO;

        int menor = -1;

        for (int i = 0; i < num_processos; i++)
            if (processos[i].estado == PRONTO && processos[i].tempo_chegada <= tempo)
                if (menor == -1 || processos[i].burst_restante < processos[menor].burst_restante)
                    menor = i;

        if (menor == -1) {
            if (tam_sequencia < MAX_SEQ) sequencia[tam_sequencia++] = 0;
            tempo++;
            continue;
        }

        if (processos[menor].tempo_inicio == -1)
            processos[menor].tempo_inicio = tempo;

        for (int i = 0; i < num_processos; i++)
            if (i != menor &&
                processos[i].estado != FINALIZADO &&
                processos[i].estado != BLOQUEADO &&
                processos[i].tempo_chegada <= tempo)
                processos[i].tempo_espera++;

        processos[menor].estado = EXECUTANDO;

        if (tam_sequencia < MAX_SEQ)
            sequencia[tam_sequencia++] = processos[menor].pid;

        processos[menor].burst_restante--;
        tempo++;

        if (processos[menor].burst_restante == 0) {
            processos[menor].tempo_fim = tempo;
            processos[menor].estado = FINALIZADO;
            finalizados++;
        } else if (rand() % 10 == 0) {
            processos[menor].estado = BLOQUEADO;
            tempo_desbloqueio[menor] = tempo + 5;
        } else {
            processos[menor].estado = PRONTO;
        }
    }
}

void round_robin(int quantum) {
    printf("  Quantum: %dms\n\n", quantum);

    int fila[MAX_PROCESSOS * 200];
    int ini = 0, fim_fila = 0;
    int tempo = 0;
    int finalizados = 0;

    for (int i = 0; i < num_processos; i++)
        if (processos[i].tempo_chegada == 0)
            fila[fim_fila++] = i;

    while (finalizados < num_processos) {
        for (int i = 0; i < num_processos; i++)
            if (processos[i].tempo_chegada == tempo && processos[i].estado == PRONTO) {
                int ja_esta = 0;
                for (int k = ini; k < fim_fila; k++)
                    if (fila[k] == i) { ja_esta = 1; break; }
                if (!ja_esta) fila[fim_fila++] = i;
            }

        if (ini == fim_fila) {
            if (tam_sequencia < MAX_SEQ) sequencia[tam_sequencia++] = 0;
            tempo++;
            continue;
        }

        int atual = fila[ini++];
        if (processos[atual].estado == FINALIZADO) continue;

        if (processos[atual].tempo_inicio == -1)
            processos[atual].tempo_inicio = tempo;

        int exec = (processos[atual].burst_restante < quantum)
                    ? processos[atual].burst_restante : quantum;

        processos[atual].estado = EXECUTANDO;

        for (int t = 0; t < exec; t++) {
            if (tam_sequencia < MAX_SEQ)
                sequencia[tam_sequencia++] = processos[atual].pid;

            for (int i = 0; i < num_processos; i++) {
                if (i != atual &&
                    processos[i].estado != FINALIZADO &&
                    processos[i].tempo_chegada <= tempo + t)
                    processos[i].tempo_espera++;
            }
        }

        tempo += exec;
        processos[atual].burst_restante -= exec;

        for (int i = 0; i < num_processos; i++)
            if (processos[i].tempo_chegada > (tempo - exec) &&
                processos[i].tempo_chegada <= tempo &&
                processos[i].estado == PRONTO) {
                int ja_esta = 0;
                for (int k = ini; k < fim_fila; k++)
                    if (fila[k] == i) { ja_esta = 1; break; }
                if (!ja_esta) fila[fim_fila++] = i;
            }

        if (processos[atual].burst_restante == 0) {
            processos[atual].tempo_fim = tempo;
            processos[atual].estado = FINALIZADO;
            finalizados++;
        } else {
            processos[atual].estado = PRONTO;
            fila[fim_fila++] = atual;
        }
    }
}

void prioridade_nao_preemptivo() {
    int tempo = 0;
    int finalizados = 0;
    int executado[MAX_PROCESSOS] = {0};

    while (finalizados < num_processos) {
        int escolhido = -1;

        for (int i = 0; i < num_processos; i++)
            if (!executado[i] && processos[i].tempo_chegada <= tempo)
                if (escolhido == -1 || processos[i].prioridade < processos[escolhido].prioridade)
                    escolhido = i;

        if (escolhido == -1) {
            if (tam_sequencia < MAX_SEQ) sequencia[tam_sequencia++] = 0;
            tempo++;
            continue;
        }

        processos[escolhido].tempo_inicio = tempo;
        processos[escolhido].tempo_espera = tempo - processos[escolhido].tempo_chegada;
        processos[escolhido].estado = EXECUTANDO;

        registrar_execucao(processos[escolhido].pid, processos[escolhido].burst_total);
        tempo += processos[escolhido].burst_total;

        processos[escolhido].tempo_fim = tempo;
        processos[escolhido].estado = FINALIZADO;
        executado[escolhido] = 1;
        finalizados++;
    }
}

void prioridade_preemptivo() {
    int tempo = 0;
    int finalizados = 0;

    while (finalizados < num_processos) {
        int maior_prio = -1;

        for (int i = 0; i < num_processos; i++)
            if (processos[i].estado != FINALIZADO && processos[i].tempo_chegada <= tempo)
                if (maior_prio == -1 || processos[i].prioridade < processos[maior_prio].prioridade)
                    maior_prio = i;

        if (maior_prio == -1) {
            if (tam_sequencia < MAX_SEQ) sequencia[tam_sequencia++] = 0;
            tempo++;
            continue;
        }

        if (processos[maior_prio].tempo_inicio == -1)
            processos[maior_prio].tempo_inicio = tempo;

        for (int i = 0; i < num_processos; i++)
            if (i != maior_prio && processos[i].estado != FINALIZADO && processos[i].tempo_chegada <= tempo)
                processos[i].tempo_espera++;

        processos[maior_prio].estado = EXECUTANDO;

        if (tam_sequencia < MAX_SEQ)
            sequencia[tam_sequencia++] = processos[maior_prio].pid;

        processos[maior_prio].burst_restante--;
        tempo++;

        if (processos[maior_prio].burst_restante == 0) {
            processos[maior_prio].tempo_fim = tempo;
            processos[maior_prio].estado = FINALIZADO;
            finalizados++;
        } else {
            processos[maior_prio].estado = PRONTO;
        }
    }
}

void fila_multinivel(int quantum_fila0) {
    printf("  Fila 0 (alta prio , quantum=%dms): prioridades 1-2\n", quantum_fila0);
    printf("  Fila 1 (media prio, FIFO)        : prioridade 3\n");
    printf("  Fila 2 (baixa prio, FIFO)        : prioridades 4-5\n\n");

    for (int i = 0; i < num_processos; i++) {
        if      (processos[i].prioridade <= 2) processos[i].fila_nivel = 0;
        else if (processos[i].prioridade == 3) processos[i].fila_nivel = 1;
        else                                   processos[i].fila_nivel = 2;
    }

    int tempo = 0;
    int finalizados = 0;

    while (finalizados < num_processos) {
        int escolhido = -1;

        for (int nivel = 0; nivel < MAX_FILAS && escolhido == -1; nivel++)
            for (int i = 0; i < num_processos; i++)
                if (processos[i].estado != FINALIZADO &&
                    processos[i].fila_nivel == nivel &&
                    processos[i].tempo_chegada <= tempo)
                    if (escolhido == -1 || processos[i].tempo_chegada < processos[escolhido].tempo_chegada)
                        escolhido = i;

        if (escolhido == -1) {
            if (tam_sequencia < MAX_SEQ) sequencia[tam_sequencia++] = 0;
            tempo++;
            continue;
        }

        if (processos[escolhido].tempo_inicio == -1)
            processos[escolhido].tempo_inicio = tempo;

        int exec;
        if (processos[escolhido].fila_nivel == 0) {
            exec = (processos[escolhido].burst_restante < quantum_fila0)
                    ? processos[escolhido].burst_restante : quantum_fila0;
        } else {
            exec = processos[escolhido].burst_restante;
        }

        for (int i = 0; i < num_processos; i++)
            if (i != escolhido && processos[i].estado != FINALIZADO && processos[i].tempo_chegada <= tempo)
                processos[i].tempo_espera += exec;

        processos[escolhido].estado = EXECUTANDO;
        registrar_execucao(processos[escolhido].pid, exec);
        processos[escolhido].burst_restante -= exec;
        tempo += exec;

        if (processos[escolhido].burst_restante == 0) {
            processos[escolhido].tempo_fim = tempo;
            processos[escolhido].estado = FINALIZADO;
            finalizados++;
        } else {
            processos[escolhido].estado = PRONTO;
        }
    }
}

void fila_multinivel_realimentacao() {
    printf("  Fila 0: quantum =  5ms\n");
    printf("  Fila 1: quantum = 10ms\n");
    printf("  Fila 2: FIFO\n\n");

    int quantuns[MAX_FILAS] = {5, 10, 9999};

    int tempo = 0;
    int finalizados = 0;

    while (finalizados < num_processos) {
        int escolhido = -1;

        for (int nivel = 0; nivel < MAX_FILAS && escolhido == -1; nivel++)
            for (int i = 0; i < num_processos; i++)
                if (processos[i].estado != FINALIZADO &&
                    processos[i].fila_nivel == nivel &&
                    processos[i].tempo_chegada <= tempo)
                    if (escolhido == -1 || processos[i].tempo_chegada < processos[escolhido].tempo_chegada)
                        escolhido = i;

        if (escolhido == -1) {
            if (tam_sequencia < MAX_SEQ) sequencia[tam_sequencia++] = 0;
            tempo++;
            continue;
        }

        if (processos[escolhido].tempo_inicio == -1)
            processos[escolhido].tempo_inicio = tempo;

        int nivel_atual = processos[escolhido].fila_nivel;
        int exec = (processos[escolhido].burst_restante < quantuns[nivel_atual])
                    ? processos[escolhido].burst_restante : quantuns[nivel_atual];

        for (int i = 0; i < num_processos; i++)
            if (i != escolhido && processos[i].estado != FINALIZADO && processos[i].tempo_chegada <= tempo)
                processos[i].tempo_espera += exec;

        processos[escolhido].estado = EXECUTANDO;
        registrar_execucao(processos[escolhido].pid, exec);
        processos[escolhido].burst_restante -= exec;
        tempo += exec;

        if (processos[escolhido].burst_restante == 0) {
            processos[escolhido].tempo_fim = tempo;
            processos[escolhido].estado = FINALIZADO;
            finalizados++;
        } else {
            if (processos[escolhido].fila_nivel < MAX_FILAS - 1)
                processos[escolhido].fila_nivel++;
            processos[escolhido].estado = PRONTO;
        }
    }
}

int menu_principal() {
    cabecalho();
    printf("\n  Escolha o algoritmo de escalonamento:\n\n");
    printf("    1. FIFO\n");
    printf("    2. SJF\n");
    printf("    3. SRTF\n");
    printf("    4. Round Robin\n");
    printf("    5. Prioridade Preemptivo\n");
    printf("    6. Prioridade Nao-Preemptivo\n");
    printf("    7. Fila Multinivel\n");
    printf("    8. Fila Multinivel com Realimentacao\n");
    printf("    0. Sair\n\n");
    separador();
    printf("  Opcao: ");

    int op;
    scanf("%d", &op);
    return op;
}

int main() {
    srand((unsigned int)time(NULL));

    int opcao, quantum;

    cabecalho();
    printf("\n  Bem-vindo ao Super Escalonador!\n");
    printf("  Pressione ENTER para continuar...");
    getchar();

    gerar_processos();

    do {
        opcao = menu_principal();

        if (opcao == 0) break;
        if (opcao < 1 || opcao > 8) {
            printf("\n  Opcao invalida. Tente novamente.\n");
            getchar(); getchar();
            continue;
        }

        reset_processos();

        cabecalho();

        switch (opcao) {
            case 1:
                printf("\n  [FIFO]\n\n");
                fifo();
                exibir_resultados("FIFO");
                break;
            case 2:
                printf("\n  [SJF]\n\n");
                sjf();
                exibir_resultados("SJF");
                break;
            case 3:
                printf("\n  [SRTF]\n\n");
                srtf();
                exibir_resultados("SRTF");
                break;
            case 4:
                printf("\n  [Round Robin]\n\n");
                printf("  Informe o quantum (ms): ");
                scanf("%d", &quantum);
                if (quantum <= 0) quantum = 5;
                reset_processos();
                round_robin(quantum);
                exibir_resultados("Round Robin");
                break;
            case 5:
                printf("\n  [Prioridade Preemptivo]\n\n");
                prioridade_preemptivo();
                exibir_resultados("Prioridade Preemptivo");
                break;
            case 6:
                printf("\n  [Prioridade Nao-Preemptivo]\n\n");
                prioridade_nao_preemptivo();
                exibir_resultados("Prioridade Nao-Preemptivo");
                break;
            case 7:
                printf("\n  [Fila Multinivel]\n\n");
                printf("  Informe o quantum da fila 0 (ms): ");
                scanf("%d", &quantum);
                if (quantum <= 0) quantum = 5;
                reset_processos();
                fila_multinivel(quantum);
                exibir_resultados("Fila Multinivel");
                break;
            case 8:
                printf("\n  [Fila Multinivel com Realimentacao]\n\n");
                fila_multinivel_realimentacao();
                exibir_resultados("Fila Multinivel com Realimentacao");
                break;
        }

        printf("\n  Deseja gerar novos processos? (1-Sim / 0-Nao): ");
        int nova;
        scanf("%d", &nova);
        if (nova == 1) gerar_processos();

        printf("  Pressione ENTER para voltar ao menu...");
        getchar(); getchar();

    } while (opcao != 0);

    cabecalho();
    printf("\n  Simulacao encerrada.\n\n");
    return 0;
}
