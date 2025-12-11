#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- ESTRUTURAS (Base de Dados) ---
typedef struct {
    int matricula;      // Auto-incremento
    char nome[50];
} Aluno;

typedef struct {
    int codigo;         // Auto-incremento
    char nome[50];
    int periodo;
    
    // O VETOR DENTRO DA STRUCT (Lista de Chamada)
    int ids_alunos[50]; 
    int qtd_matriculados; // Quantos alunos tem nessa disciplina
} Disciplina;

// --- FUNÇÃO AUXILIAR DE REMOVER (Já veio na sua prova) ---
// Remove o 'alvo' do vetor 'v' e puxa a fila
void RemoverAluno(int alvo, int v[], int tam){
    for(int i = 0; i < tam; i++){
        if(v[i] == alvo){
            for(int j = i; j < tam - 1; j++){

                v[j] = v[j + 1];
            }
            return;
        }
    }

}

// --- FUNÇÃO DE BUSCA (Para facilitar sua vida) ---
int BuscarAluno(Aluno a[], int qtd, char nomeBusca[]){
    for(int i=0; i<qtd; i++){
        if(strcmp(a[i].nome, nomeBusca) == 0) return i;
    }
    return -1;
}

int BuscarDisciplina(Disciplina d[], int qtd, char nomeBusca[]){
    for(int i=0; i<qtd; i++){
        if(strcmp(d[i].nome, nomeBusca) == 0) return i;
    }
    return -1;
}

// =============================================================
//      AQUI COMEÇA O SEU TREINO - PREENCHA AS LACUNAS
// =============================================================

// 1. CADASTRAR ALUNO (Auto-incremento)
void CadastrarAluno(Aluno a[], int cont){
    printf("Nome do Aluno: ");
    scanf(" %[^\n]", a[cont].nome);

    // TAREFA 1: Gere a matrícula automaticamente baseada no 'cont'.
    // Se é o primeiro (0), matricula é 1.
    /* --- COMPLETE ABAIXO --- */
    a[cont].matricula = cont + 1; 

    printf("Aluno cadastrado! Matricula gerada: %d\n", a[cont].matricula);
}

// 2. CADASTRAR DISCIPLINA (Inicialização)
void CadastrarDisciplina(Disciplina d[], int cont){
    printf("Nome da Disciplina: ");
    scanf(" %[^\n]", d[cont].nome);
    printf("Periodo: ");
    scanf("%d", &d[cont].periodo);

    // TAREFA 2: Gere o código auto-incremento E inicie o contador de alunos dela com 0
    /* --- COMPLETE ABAIXO --- */
    d[cont].codigo = cont + 1;
    d[cont].qtd_matriculados = 0; // Começa vazia
}

// 3. MATRICULAR (Relacionamento)
void Matricular(Aluno a[], int qtdA, Disciplina d[], int qtdD){
    char nomeAlu[50], nomeDisc[50];
    
    printf("Nome do Aluno: ");
    scanf(" %[^\n]", nomeAlu);
    printf("Nome da Disciplina: ");
    scanf(" %[^\n]", nomeDisc);

    int posA = BuscarAluno(a, qtdA, nomeAlu);
    int posD = BuscarDisciplina(d, qtdD, nomeDisc);

    if(posA == -1 || posD == -1) {
        printf("Erro: Aluno ou Disciplina nao encontrados.\n");
        return;
    }

    // TAREFA 3: Pegue o ID do aluno encontrado e grave no vetor da disciplina encontrada.
    // Dica: Use d[posD].qtd_matriculados para saber a posição vaga no vetor ids_alunos.
    
    int vaga = d[posD].qtd_matriculados;
    
    /* --- COMPLETE AQUI: O vetor 'ids_alunos' na posição 'vaga' recebe a matricula do aluno --- */
    d[posD].ids_alunos[vaga] = _____________________________ ;
    
    // Incrementa a quantidade de alunos nessa disciplina
    d[posD].qtd_matriculados++;
    printf("Matricula realizada!\n");
}

// 4. CHAMADA (Ordenação Bubble Sort)
void FazerChamada(Aluno a[], int qtdA, Disciplina d[], int qtdD){
    // (Simplificação: Vamos listar TODOS os alunos do sistema em ordem alfabética
    // para treinar a ordenação, conforme Requisito 5)
    
    // Cópia temporária para não bagunçar o cadastro original
    Aluno lista[50];
    for(int i=0; i<qtdA; i++) lista[i] = a[i];

    printf("\n--- Lista Geral em Ordem Alfabetica ---\n");
    
    Aluno aux;
    
    for(int i=0; i<qtdA - 1; i++){
        for(int j= i + 1; j < qtdA; j++){
            
            
            if ( strcmp(lista[i].nome, lista[j].nome) > 0){
                aux = lista[j];
                lista[j] = lista[i];
                lista[i] = aux;
            }
        }
    }

    for(int i=0; i<qtdA; i++) printf("- %s\n", lista[i].nome);
}

// =============================================================
//           FIM DO TREINO - O RESTO ESTÁ PRONTO
// =============================================================

int menu(){
    int op;
    printf("\n1-Cadastrar Aluno | 2-Cadastrar Disc | 3-Matricular | 4-Chamada | 0-Sair\nOpcao: ");
    scanf("%d", &op);
    return op;
}

int main(){
    Aluno alunos[100];
    Disciplina disciplinas[50];
    int contA = 0, contD = 0, op;

    do {
        op = menu();
        switch(op){
            case 1: CadastrarAluno(alunos, contA); contA++; break;
            case 2: CadastrarDisciplina(disciplinas, contD); contD++; break;
            case 3: Matricular(alunos, contA, disciplinas, contD); break;
            case 4: FazerChamada(alunos, contA, disciplinas, contD); break;
        }
    } while(op != 0);
    return 0;
}