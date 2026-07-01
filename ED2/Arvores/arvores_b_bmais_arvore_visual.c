#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAVES 3
#define MAX_FILHOS 4

/* ============================================================
   ÁRVORE B
   Ordem 4: cada nó armazena no máximo 3 chaves e 4 filhos.
   ============================================================ */

typedef struct NoB {
    int chaves[MAX_CHAVES];
    struct NoB *filhos[MAX_FILHOS];
    int quantidade;
    int folha;
} NoB;

NoB *criarNoB(int folha) {
    NoB *no = (NoB *)malloc(sizeof(NoB));
    if (no == NULL) {
        fprintf(stderr, "Erro: memória insuficiente.\n");
        exit(EXIT_FAILURE);
    }

    no->quantidade = 0;
    no->folha = folha;

    for (int i = 0; i < MAX_FILHOS; i++) {
        no->filhos[i] = NULL;
    }

    return no;
}

int buscarB(NoB *no, int chave) {
    if (no == NULL) {
        return 0;
    }

    int i = 0;
    while (i < no->quantidade && chave > no->chaves[i]) {
        i++;
    }

    if (i < no->quantidade && chave == no->chaves[i]) {
        return 1;
    }

    if (no->folha) {
        return 0;
    }

    return buscarB(no->filhos[i], chave);
}

/*
   Divide um filho cheio da Árvore B.
   A chave central sobe para o pai e deixa de permanecer no filho.
*/
void dividirFilhoB(NoB *pai, int indice, NoB *filhoCheio) {
    NoB *novo = criarNoB(filhoCheio->folha);

    /* Para t = 2, a chave central é a de índice 1. */
    int chavePromovida = filhoCheio->chaves[1];

    /* O novo nó recebe a última chave. */
    novo->chaves[0] = filhoCheio->chaves[2];
    novo->quantidade = 1;

    /* Se não for folha, transfere os dois últimos filhos. */
    if (!filhoCheio->folha) {
        novo->filhos[0] = filhoCheio->filhos[2];
        novo->filhos[1] = filhoCheio->filhos[3];
    }

    /* O filho original permanece somente com a primeira chave. */
    filhoCheio->quantidade = 1;

    /* Abre espaço no vetor de filhos do pai. */
    for (int j = pai->quantidade; j >= indice + 1; j--) {
        pai->filhos[j + 1] = pai->filhos[j];
    }
    pai->filhos[indice + 1] = novo;

    /* Abre espaço para a chave promovida no pai. */
    for (int j = pai->quantidade - 1; j >= indice; j--) {
        pai->chaves[j + 1] = pai->chaves[j];
    }
    pai->chaves[indice] = chavePromovida;
    pai->quantidade++;

    printf("[B] Divisão: chave %d promovida para o nó pai.\n", chavePromovida);
}

void inserirNaoCheioB(NoB *no, int chave) {
    int i = no->quantidade - 1;

    if (no->folha) {
        while (i >= 0 && chave < no->chaves[i]) {
            no->chaves[i + 1] = no->chaves[i];
            i--;
        }

        no->chaves[i + 1] = chave;
        no->quantidade++;
        return;
    }

    while (i >= 0 && chave < no->chaves[i]) {
        i--;
    }
    i++;

    if (no->filhos[i]->quantidade == MAX_CHAVES) {
        dividirFilhoB(no, i, no->filhos[i]);

        if (chave > no->chaves[i]) {
            i++;
        }
    }

    inserirNaoCheioB(no->filhos[i], chave);
}

void inserirB(NoB **raiz, int chave) {
    if (buscarB(*raiz, chave)) {
        printf("[B] A chave %d já existe.\n", chave);
        return;
    }

    if (*raiz == NULL) {
        *raiz = criarNoB(1);
        (*raiz)->chaves[0] = chave;
        (*raiz)->quantidade = 1;
        return;
    }

    NoB *raizAtual = *raiz;

    if (raizAtual->quantidade == MAX_CHAVES) {
        NoB *novaRaiz = criarNoB(0);
        novaRaiz->filhos[0] = raizAtual;

        dividirFilhoB(novaRaiz, 0, raizAtual);

        int indice = (chave > novaRaiz->chaves[0]) ? 1 : 0;
        inserirNaoCheioB(novaRaiz->filhos[indice], chave);

        *raiz = novaRaiz;
    } else {
        inserirNaoCheioB(raizAtual, chave);
    }
}

void imprimirChavesB(NoB *no) {
    printf("[");
    for (int i = 0; i < no->quantidade; i++) {
        printf("%d", no->chaves[i]);
        if (i < no->quantidade - 1) {
            printf(" | ");
        }
    }
    printf("]");
}

/* ============================================================
   VISUALIZAÇÃO DA ÁRVORE B EM FORMATO GRÁFICO NO TERMINAL

   Cada nó recebe uma posição horizontal. Em seguida, desenhamos
   linhas ligando o nó pai aos filhos, formando uma árvore de verdade.
   ============================================================ */

#define LARGURA_TELA 180
#define ALTURA_TELA 80
#define ESPACO_FOLHAS 22
#define ESPACO_NIVEIS 5
#define MAX_NOS_VISUAIS 256

typedef struct PosicaoB {
    NoB *no;
    int x;
    int y;
} PosicaoB;

static char telaB[ALTURA_TELA][LARGURA_TELA + 1];
static PosicaoB posicoesB[MAX_NOS_VISUAIS];
static int totalPosicoesB;

void limparTelaB(void) {
    for (int i = 0; i < ALTURA_TELA; i++) {
        for (int j = 0; j < LARGURA_TELA; j++) {
            telaB[i][j] = ' ';
        }
        telaB[i][LARGURA_TELA] = '\0';
    }
}

void colocarCaractereB(int y, int x, char c) {
    if (y < 0 || y >= ALTURA_TELA || x < 0 || x >= LARGURA_TELA) {
        return;
    }

    char atual = telaB[y][x];
    if (atual == ' ' || atual == c) {
        telaB[y][x] = c;
    } else if ((atual == '-' && c == '|') || (atual == '|' && c == '-')) {
        telaB[y][x] = '+';
    } else if (c == '+') {
        telaB[y][x] = '+';
    }
}

void escreverTextoB(int y, int centro, const char *texto) {
    int tamanho = (int)strlen(texto);
    int inicio = centro - tamanho / 2;

    for (int i = 0; i < tamanho; i++) {
        int x = inicio + i;
        if (y >= 0 && y < ALTURA_TELA && x >= 0 && x < LARGURA_TELA) {
            telaB[y][x] = texto[i];
        }
    }
}

int adicionarPosicaoB(NoB *no, int x, int y) {
    if (totalPosicoesB >= MAX_NOS_VISUAIS) {
        return -1;
    }

    posicoesB[totalPosicoesB].no = no;
    posicoesB[totalPosicoesB].x = x;
    posicoesB[totalPosicoesB].y = y;
    return totalPosicoesB++;
}

int posicionarNosB(NoB *no, int nivel, int *proximaFolha) {
    if (no == NULL) {
        return 0;
    }

    int x;

    if (no->folha) {
        x = 8 + (*proximaFolha) * ESPACO_FOLHAS;
        (*proximaFolha)++;
    } else {
        int primeiroX = posicionarNosB(no->filhos[0], nivel + 1, proximaFolha);
        int ultimoX = primeiroX;

        for (int i = 1; i <= no->quantidade; i++) {
            ultimoX = posicionarNosB(no->filhos[i], nivel + 1, proximaFolha);
        }

        x = (primeiroX + ultimoX) / 2;
    }

    adicionarPosicaoB(no, x, nivel * ESPACO_NIVEIS);
    return x;
}

PosicaoB *buscarPosicaoB(NoB *no) {
    for (int i = 0; i < totalPosicoesB; i++) {
        if (posicoesB[i].no == no) {
            return &posicoesB[i];
        }
    }
    return NULL;
}

void montarRotuloB(NoB *no, char *rotulo, size_t tamanho) {
    size_t usados = 0;
    usados += (size_t)snprintf(rotulo + usados, tamanho - usados, "[");

    for (int i = 0; i < no->quantidade && usados < tamanho; i++) {
        usados += (size_t)snprintf(rotulo + usados, tamanho - usados,
                                   "%d%s", no->chaves[i],
                                   i < no->quantidade - 1 ? " | " : "");
    }

    if (usados < tamanho) {
        snprintf(rotulo + usados, tamanho - usados, "]");
    }
}

void desenharLigacoesB(NoB *no) {
    if (no == NULL || no->folha) {
        return;
    }

    PosicaoB *pai = buscarPosicaoB(no);
    if (pai == NULL) {
        return;
    }

    int linhaHorizontal = pai->y + 2;
    int menorX = LARGURA_TELA;
    int maiorX = 0;

    colocarCaractereB(pai->y + 1, pai->x, '|');

    for (int i = 0; i <= no->quantidade; i++) {
        PosicaoB *filho = buscarPosicaoB(no->filhos[i]);
        if (filho == NULL) {
            continue;
        }

        if (filho->x < menorX) menorX = filho->x;
        if (filho->x > maiorX) maiorX = filho->x;

        colocarCaractereB(linhaHorizontal, filho->x, '+');
        for (int y = linhaHorizontal + 1; y < filho->y; y++) {
            colocarCaractereB(y, filho->x, '|');
        }
    }

    for (int x = menorX; x <= maiorX; x++) {
        colocarCaractereB(linhaHorizontal, x, '-');
    }

    colocarCaractereB(linhaHorizontal, pai->x, '+');

    for (int i = 0; i <= no->quantidade; i++) {
        desenharLigacoesB(no->filhos[i]);
    }
}

void desenharNosB(void) {
    char rotulo[80];

    for (int i = 0; i < totalPosicoesB; i++) {
        montarRotuloB(posicoesB[i].no, rotulo, sizeof(rotulo));
        escreverTextoB(posicoesB[i].y, posicoesB[i].x, rotulo);
    }
}

void imprimirTelaB(void) {
    int ultimaLinha = 0;

    for (int i = 0; i < ALTURA_TELA; i++) {
        for (int j = LARGURA_TELA - 1; j >= 0; j--) {
            if (telaB[i][j] != ' ') {
                ultimaLinha = i;
                break;
            }
        }
    }

    for (int i = 0; i <= ultimaLinha; i++) {
        int ultimo = LARGURA_TELA - 1;
        while (ultimo >= 0 && telaB[i][ultimo] == ' ') {
            ultimo--;
        }
        telaB[i][ultimo + 1] = '\0';
        printf("%s\n", telaB[i]);
    }
}

/*
   Exibe a Árvore B como um diagrama hierárquico.
   Os símbolos ├── e └── deixam visível a ligação entre pai e filhos.
*/
void imprimirHierarquiaB(NoB *no, const char *prefixo, int ultimo, int raiz) {
    if (no == NULL) {
        return;
    }

    printf("%s", prefixo);
    if (!raiz) {
        printf("%s", ultimo ? "└── " : "├── ");
    }

    imprimirChavesB(no);
    printf(" %s\n", no->folha ? "(folha)" : "(nó interno)");

    if (!no->folha) {
        char novoPrefixo[512];
        snprintf(novoPrefixo, sizeof(novoPrefixo), "%s%s",
                 prefixo,
                 raiz ? "" : (ultimo ? "    " : "│   "));

        for (int i = 0; i <= no->quantidade; i++) {
            imprimirHierarquiaB(no->filhos[i], novoPrefixo,
                                i == no->quantidade, 0);
        }
    }
}

void imprimirB(NoB *no, int nivel) {
    (void)nivel;

    if (no == NULL) {
        printf("(árvore vazia)\n");
        return;
    }

    limparTelaB();
    totalPosicoesB = 0;
    int proximaFolha = 0;
    posicionarNosB(no, 0, &proximaFolha);
    desenharLigacoesB(no);
    desenharNosB();
    imprimirTelaB();
    printf("Legenda: os nós acima são ligados aos filhos pelas linhas.\n");
}

void liberarB(NoB *no) {
    if (no == NULL) {
        return;
    }

    if (!no->folha) {
        for (int i = 0; i <= no->quantidade; i++) {
            liberarB(no->filhos[i]);
        }
    }

    free(no);
}

/* ============================================================
   ÁRVORE B+
   Dados ficam apenas nas folhas.
   Nós internos armazenam somente chaves de separação.
   As folhas são ligadas pelo ponteiro "proximo".
   ============================================================ */

typedef struct NoBMais {
    int chaves[MAX_CHAVES];
    struct NoBMais *filhos[MAX_FILHOS];
    struct NoBMais *proximo;
    int quantidade;
    int folha;
} NoBMais;

typedef struct ResultadoDivisao {
    int houveDivisao;
    int chavePromovida;
    NoBMais *novoDireito;
} ResultadoDivisao;

NoBMais *criarNoBMais(int folha) {
    NoBMais *no = (NoBMais *)malloc(sizeof(NoBMais));
    if (no == NULL) {
        fprintf(stderr, "Erro: memória insuficiente.\n");
        exit(EXIT_FAILURE);
    }

    no->quantidade = 0;
    no->folha = folha;
    no->proximo = NULL;

    for (int i = 0; i < MAX_FILHOS; i++) {
        no->filhos[i] = NULL;
    }

    return no;
}

NoBMais *encontrarFolhaBMais(NoBMais *raiz, int chave) {
    NoBMais *atual = raiz;

    while (atual != NULL && !atual->folha) {
        int i = 0;

        /* Em B+, chaves iguais seguem para o filho da direita. */
        while (i < atual->quantidade && chave >= atual->chaves[i]) {
            i++;
        }

        atual = atual->filhos[i];
    }

    return atual;
}

int buscarBMais(NoBMais *raiz, int chave) {
    NoBMais *folha = encontrarFolhaBMais(raiz, chave);
    if (folha == NULL) {
        return 0;
    }

    for (int i = 0; i < folha->quantidade; i++) {
        if (folha->chaves[i] == chave) {
            return 1;
        }
    }

    return 0;
}

ResultadoDivisao semDivisao(void) {
    ResultadoDivisao resultado;
    resultado.houveDivisao = 0;
    resultado.chavePromovida = 0;
    resultado.novoDireito = NULL;
    return resultado;
}

/* Insere recursivamente e devolve uma promoção quando ocorre divisão. */
ResultadoDivisao inserirRecBMais(NoBMais *no, int chave) {
    if (no->folha) {
        int temporarias[MAX_CHAVES + 1];
        int i = 0;
        int j = 0;

        while (i < no->quantidade && no->chaves[i] < chave) {
            temporarias[j++] = no->chaves[i++];
        }

        temporarias[j++] = chave;

        while (i < no->quantidade) {
            temporarias[j++] = no->chaves[i++];
        }

        if (no->quantidade < MAX_CHAVES) {
            no->quantidade++;
            for (i = 0; i < no->quantidade; i++) {
                no->chaves[i] = temporarias[i];
            }
            return semDivisao();
        }

        /* Overflow: quatro chaves são divididas em duas folhas de duas. */
        NoBMais *novaFolha = criarNoBMais(1);
        int total = MAX_CHAVES + 1;
        int esquerda = total / 2;
        int direita = total - esquerda;

        no->quantidade = esquerda;
        for (i = 0; i < esquerda; i++) {
            no->chaves[i] = temporarias[i];
        }

        novaFolha->quantidade = direita;
        for (i = 0; i < direita; i++) {
            novaFolha->chaves[i] = temporarias[esquerda + i];
        }

        novaFolha->proximo = no->proximo;
        no->proximo = novaFolha;

        ResultadoDivisao resultado;
        resultado.houveDivisao = 1;
        resultado.chavePromovida = novaFolha->chaves[0];
        resultado.novoDireito = novaFolha;

        printf("[B+] Divisão de folha: chave %d copiada para o pai.\n",
               resultado.chavePromovida);

        return resultado;
    }

    int indice = 0;
    while (indice < no->quantidade && chave >= no->chaves[indice]) {
        indice++;
    }

    ResultadoDivisao filho = inserirRecBMais(no->filhos[indice], chave);

    if (!filho.houveDivisao) {
        return semDivisao();
    }

    int tempChaves[MAX_CHAVES + 1];
    NoBMais *tempFilhos[MAX_FILHOS + 1];

    int i;
    for (i = 0; i < indice; i++) {
        tempChaves[i] = no->chaves[i];
    }
    tempChaves[indice] = filho.chavePromovida;
    for (i = indice; i < no->quantidade; i++) {
        tempChaves[i + 1] = no->chaves[i];
    }

    for (i = 0; i <= indice; i++) {
        tempFilhos[i] = no->filhos[i];
    }
    tempFilhos[indice + 1] = filho.novoDireito;
    for (i = indice + 1; i <= no->quantidade; i++) {
        tempFilhos[i + 1] = no->filhos[i];
    }

    int totalChaves = no->quantidade + 1;

    if (totalChaves <= MAX_CHAVES) {
        no->quantidade = totalChaves;

        for (i = 0; i < totalChaves; i++) {
            no->chaves[i] = tempChaves[i];
        }
        for (i = 0; i <= totalChaves; i++) {
            no->filhos[i] = tempFilhos[i];
        }

        return semDivisao();
    }

    /* Overflow interno: promove a chave central. */
    int meio = totalChaves / 2;
    int promovida = tempChaves[meio];
    NoBMais *novoInterno = criarNoBMais(0);

    no->quantidade = meio;
    for (i = 0; i < meio; i++) {
        no->chaves[i] = tempChaves[i];
    }
    for (i = 0; i <= meio; i++) {
        no->filhos[i] = tempFilhos[i];
    }

    novoInterno->quantidade = totalChaves - meio - 1;
    for (i = 0; i < novoInterno->quantidade; i++) {
        novoInterno->chaves[i] = tempChaves[meio + 1 + i];
    }
    for (i = 0; i <= novoInterno->quantidade; i++) {
        novoInterno->filhos[i] = tempFilhos[meio + 1 + i];
    }

    ResultadoDivisao resultado;
    resultado.houveDivisao = 1;
    resultado.chavePromovida = promovida;
    resultado.novoDireito = novoInterno;

    printf("[B+] Divisão de nó interno: chave %d promovida.\n", promovida);

    return resultado;
}

void inserirBMais(NoBMais **raiz, int chave) {
    if (buscarBMais(*raiz, chave)) {
        printf("[B+] A chave %d já existe.\n", chave);
        return;
    }

    if (*raiz == NULL) {
        *raiz = criarNoBMais(1);
        (*raiz)->chaves[0] = chave;
        (*raiz)->quantidade = 1;
        return;
    }

    ResultadoDivisao resultado = inserirRecBMais(*raiz, chave);

    if (resultado.houveDivisao) {
        NoBMais *novaRaiz = criarNoBMais(0);
        novaRaiz->chaves[0] = resultado.chavePromovida;
        novaRaiz->filhos[0] = *raiz;
        novaRaiz->filhos[1] = resultado.novoDireito;
        novaRaiz->quantidade = 1;
        *raiz = novaRaiz;
    }
}

void imprimirChavesBMais(NoBMais *no) {
    printf("[");
    for (int i = 0; i < no->quantidade; i++) {
        printf("%d", no->chaves[i]);
        if (i < no->quantidade - 1) {
            printf(" | ");
        }
    }
    printf("]");
}

/* ============================================================
   VISUALIZAÇÃO DA ÁRVORE B+ EM FORMATO GRÁFICO NO TERMINAL
   ============================================================ */

typedef struct PosicaoBMais {
    NoBMais *no;
    int x;
    int y;
} PosicaoBMais;

static char telaBMais[ALTURA_TELA][LARGURA_TELA + 1];
static PosicaoBMais posicoesBMais[MAX_NOS_VISUAIS];
static int totalPosicoesBMais;

void limparTelaBMais(void) {
    for (int i = 0; i < ALTURA_TELA; i++) {
        for (int j = 0; j < LARGURA_TELA; j++) {
            telaBMais[i][j] = ' ';
        }
        telaBMais[i][LARGURA_TELA] = '\0';
    }
}

void colocarCaractereBMais(int y, int x, char c) {
    if (y < 0 || y >= ALTURA_TELA || x < 0 || x >= LARGURA_TELA) {
        return;
    }

    char atual = telaBMais[y][x];
    if (atual == ' ' || atual == c) {
        telaBMais[y][x] = c;
    } else if ((atual == '-' && c == '|') || (atual == '|' && c == '-')) {
        telaBMais[y][x] = '+';
    } else if (c == '+') {
        telaBMais[y][x] = '+';
    }
}

void escreverTextoBMais(int y, int centro, const char *texto) {
    int tamanho = (int)strlen(texto);
    int inicio = centro - tamanho / 2;

    for (int i = 0; i < tamanho; i++) {
        int x = inicio + i;
        if (y >= 0 && y < ALTURA_TELA && x >= 0 && x < LARGURA_TELA) {
            telaBMais[y][x] = texto[i];
        }
    }
}

int adicionarPosicaoBMais(NoBMais *no, int x, int y) {
    if (totalPosicoesBMais >= MAX_NOS_VISUAIS) {
        return -1;
    }

    posicoesBMais[totalPosicoesBMais].no = no;
    posicoesBMais[totalPosicoesBMais].x = x;
    posicoesBMais[totalPosicoesBMais].y = y;
    return totalPosicoesBMais++;
}

int posicionarNosBMais(NoBMais *no, int nivel, int *proximaFolha) {
    if (no == NULL) {
        return 0;
    }

    int x;

    if (no->folha) {
        x = 8 + (*proximaFolha) * ESPACO_FOLHAS;
        (*proximaFolha)++;
    } else {
        int primeiroX = posicionarNosBMais(no->filhos[0], nivel + 1, proximaFolha);
        int ultimoX = primeiroX;

        for (int i = 1; i <= no->quantidade; i++) {
            ultimoX = posicionarNosBMais(no->filhos[i], nivel + 1, proximaFolha);
        }

        x = (primeiroX + ultimoX) / 2;
    }

    adicionarPosicaoBMais(no, x, nivel * ESPACO_NIVEIS);
    return x;
}

PosicaoBMais *buscarPosicaoBMais(NoBMais *no) {
    for (int i = 0; i < totalPosicoesBMais; i++) {
        if (posicoesBMais[i].no == no) {
            return &posicoesBMais[i];
        }
    }
    return NULL;
}

void montarRotuloBMais(NoBMais *no, char *rotulo, size_t tamanho) {
    size_t usados = 0;

    usados += (size_t)snprintf(rotulo + usados, tamanho - usados,
                               no->folha ? "F[" : "I[");

    for (int i = 0; i < no->quantidade && usados < tamanho; i++) {
        usados += (size_t)snprintf(rotulo + usados, tamanho - usados,
                                   "%d%s", no->chaves[i],
                                   i < no->quantidade - 1 ? " | " : "");
    }

    if (usados < tamanho) {
        snprintf(rotulo + usados, tamanho - usados, "]");
    }
}

void desenharLigacoesBMais(NoBMais *no) {
    if (no == NULL || no->folha) {
        return;
    }

    PosicaoBMais *pai = buscarPosicaoBMais(no);
    if (pai == NULL) {
        return;
    }

    int linhaHorizontal = pai->y + 2;
    int menorX = LARGURA_TELA;
    int maiorX = 0;

    colocarCaractereBMais(pai->y + 1, pai->x, '|');

    for (int i = 0; i <= no->quantidade; i++) {
        PosicaoBMais *filho = buscarPosicaoBMais(no->filhos[i]);
        if (filho == NULL) {
            continue;
        }

        if (filho->x < menorX) menorX = filho->x;
        if (filho->x > maiorX) maiorX = filho->x;

        colocarCaractereBMais(linhaHorizontal, filho->x, '+');
        for (int y = linhaHorizontal + 1; y < filho->y; y++) {
            colocarCaractereBMais(y, filho->x, '|');
        }
    }

    for (int x = menorX; x <= maiorX; x++) {
        colocarCaractereBMais(linhaHorizontal, x, '-');
    }

    colocarCaractereBMais(linhaHorizontal, pai->x, '+');

    for (int i = 0; i <= no->quantidade; i++) {
        desenharLigacoesBMais(no->filhos[i]);
    }
}

void desenharNosBMais(void) {
    char rotulo[80];

    for (int i = 0; i < totalPosicoesBMais; i++) {
        montarRotuloBMais(posicoesBMais[i].no, rotulo, sizeof(rotulo));
        escreverTextoBMais(posicoesBMais[i].y, posicoesBMais[i].x, rotulo);
    }
}

void imprimirTelaBMais(void) {
    int ultimaLinha = 0;

    for (int i = 0; i < ALTURA_TELA; i++) {
        for (int j = LARGURA_TELA - 1; j >= 0; j--) {
            if (telaBMais[i][j] != ' ') {
                ultimaLinha = i;
                break;
            }
        }
    }

    for (int i = 0; i <= ultimaLinha; i++) {
        int ultimo = LARGURA_TELA - 1;
        while (ultimo >= 0 && telaBMais[i][ultimo] == ' ') {
            ultimo--;
        }
        telaBMais[i][ultimo + 1] = '\0';
        printf("%s\n", telaBMais[i]);
    }
}

/* Exibe a B+ com nós de índice e folhas bem identificados. */
void imprimirHierarquiaBMais(NoBMais *no, const char *prefixo, int ultimo, int raiz) {
    if (no == NULL) {
        return;
    }

    printf("%s", prefixo);
    if (!raiz) {
        printf("%s", ultimo ? "└── " : "├── ");
    }

    if (no->folha) {
        printf("FOLHA ");
    } else {
        printf("ÍNDICE ");
    }
    imprimirChavesBMais(no);
    printf("\n");

    if (!no->folha) {
        char novoPrefixo[512];
        snprintf(novoPrefixo, sizeof(novoPrefixo), "%s%s",
                 prefixo,
                 raiz ? "" : (ultimo ? "    " : "│   "));

        for (int i = 0; i <= no->quantidade; i++) {
            imprimirHierarquiaBMais(no->filhos[i], novoPrefixo,
                                    i == no->quantidade, 0);
        }
    }
}

void imprimirBMais(NoBMais *no, int nivel) {
    (void)nivel;

    if (no == NULL) {
        printf("(árvore vazia)\n");
        return;
    }

    limparTelaBMais();
    totalPosicoesBMais = 0;
    int proximaFolha = 0;
    posicionarNosBMais(no, 0, &proximaFolha);
    desenharLigacoesBMais(no);
    desenharNosBMais();
    imprimirTelaBMais();
    printf("Legenda: I = índice | F = folha com os dados.\n");
}

void imprimirFolhasBMais(NoBMais *raiz) {
    if (raiz == NULL) {
        printf("(árvore vazia)\n");
        return;
    }

    NoBMais *folha = raiz;
    while (!folha->folha) {
        folha = folha->filhos[0];
    }

    while (folha != NULL) {
        printf("[");
        for (int i = 0; i < folha->quantidade; i++) {
            printf("%d", folha->chaves[i]);
            if (i < folha->quantidade - 1) {
                printf(" | ");
            }
        }
        printf("]");

        if (folha->proximo != NULL) {
            printf(" -> ");
        }

        folha = folha->proximo;
    }

    printf(" -> NULL\n");
}

void liberarBMais(NoBMais *no) {
    if (no == NULL) {
        return;
    }

    if (!no->folha) {
        for (int i = 0; i <= no->quantidade; i++) {
            liberarBMais(no->filhos[i]);
        }
    }

    free(no);
}

/* ============================================================
   FUNÇÕES DA DEMONSTRAÇÃO
   ============================================================ */

void mostrarComparacao(NoB *raizB, NoBMais *raizBMais) {
    printf("\n================ ÁRVORE B ================\n");
    imprimirB(raizB, 0);

    printf("\n=============== ÁRVORE B+ ================\n");
    imprimirBMais(raizBMais, 0);

    printf("\nFolhas encadeadas da B+:\n");
    imprimirFolhasBMais(raizBMais);
}

void demonstracaoAutomatica(NoB **raizB, NoBMais **raizBMais) {
    int valores[] = {10, 20, 5, 6, 12, 30, 7, 17};
    int quantidade = (int)(sizeof(valores) / sizeof(valores[0]));

    liberarB(*raizB);
    liberarBMais(*raizBMais);
    *raizB = NULL;
    *raizBMais = NULL;

    printf("\nDemonstração automática\n");
    printf("Sequência: 10, 20, 5, 6, 12, 30, 7, 17\n\n");

    for (int i = 0; i < quantidade; i++) {
        printf("---------- Inserindo %d ----------\n", valores[i]);
        inserirB(raizB, valores[i]);
        inserirBMais(raizBMais, valores[i]);
        printf("\n");
    }

    mostrarComparacao(*raizB, *raizBMais);
}

void limparEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* descarta caracteres inválidos */
    }
}

int lerInteiro(const char *mensagem, int *valor) {
    printf("%s", mensagem);

    if (scanf("%d", valor) != 1) {
        limparEntrada();
        printf("Entrada inválida. Digite um número inteiro.\n");
        return 0;
    }

    limparEntrada();
    return 1;
}

int main(void) {
    NoB *raizB = NULL;
    NoBMais *raizBMais = NULL;
    int opcao;
    int valor;

    do {
        printf("\n=============================================\n");
        printf("       DEMONSTRAÇÃO: ÁRVORE B E B+\n");
        printf("=============================================\n");
        printf("1 - Inserir valor nas duas árvores\n");
        printf("2 - Buscar valor nas duas árvores\n");
        printf("3 - Mostrar Árvore B\n");
        printf("4 - Mostrar Árvore B+\n");
        printf("5 - Mostrar folhas encadeadas da B+\n");
        printf("6 - Executar demonstração automática\n");
        printf("7 - Limpar as duas árvores\n");
        printf("0 - Sair\n");
        printf("=============================================\n");

        if (!lerInteiro("Escolha uma opção: ", &opcao)) {
            continue;
        }

        switch (opcao) {
            case 1:
                if (lerInteiro("Digite o valor: ", &valor)) {
                    printf("\nInserindo %d...\n", valor);
                    inserirB(&raizB, valor);
                    inserirBMais(&raizBMais, valor);
                    mostrarComparacao(raizB, raizBMais);
                }
                break;

            case 2:
                if (lerInteiro("Digite o valor procurado: ", &valor)) {
                    printf("\nÁrvore B : %s\n",
                           buscarB(raizB, valor) ? "valor encontrado" : "valor não encontrado");
                    printf("Árvore B+: %s\n",
                           buscarBMais(raizBMais, valor) ? "valor encontrado na folha" : "valor não encontrado");
                }
                break;

            case 3:
                printf("\nÁRVORE B:\n");
                imprimirB(raizB, 0);
                break;

            case 4:
                printf("\nÁRVORE B+:\n");
                imprimirBMais(raizBMais, 0);
                break;

            case 5:
                printf("\nFOLHAS ENCADEADAS DA B+:\n");
                imprimirFolhasBMais(raizBMais);
                break;

            case 6:
                demonstracaoAutomatica(&raizB, &raizBMais);
                break;

            case 7:
                liberarB(raizB);
                liberarBMais(raizBMais);
                raizB = NULL;
                raizBMais = NULL;
                printf("As duas árvores foram limpas.\n");
                break;

            case 0:
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("Opção inválida.\n");
        }

    } while (opcao != 0);

    liberarB(raizB);
    liberarBMais(raizBMais);

    return 0;
}
