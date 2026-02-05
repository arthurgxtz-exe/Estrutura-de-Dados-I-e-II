#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int id;
    char descricao[50];
    float valor;
    int dia;
    char tipo;
    int status;
}Lancamento;
int gerarID(FILE *arq){
    fseek(arq, 0, SEEK_END);

    long totalbytes = ftell(arq);

    if(totalbytes == 0){
        return 1;
    }

    long qtdRegistros = totalbytes / sizeof(Lancamento);
    return qtdRegistros + 1;
}
int menu(){
    int op;
    printf("\n----MENU----\n");
    printf("1 - Cadastrar Receita\n");
    printf("2 - Cadastrar Despesa\n");
    printf("3 - Pagar Despesa\n");
    printf("4 Extrato Mensal\n");
    printf("0 - Sair\n");
    scanf("%d", &op);

    return op;

}
void cadastrar(FILE *arq, char tipo){
    Lancamento novo;

    novo.tipo = tipo;
    if(tipo == 'R'){
        novo.status = 1;
    }
    if(tipo == 'D'){
        novo.status = 0;
    }
    
    novo.id = gerarID(arq);
    printf("Gerando ID automatico... ID %d definido.\n", novo.id);
    printf("Descricao: ");
    scanf(" %[^\n]", novo.descricao);
    printf("Valor: ");
    scanf("%f", &novo.valor);
    printf("Dia: ");
    scanf("%d", &novo.dia);

    fseek(arq, 0, SEEK_END);
    fwrite(&novo, sizeof(Lancamento), 1, arq);
    fflush(arq);

    printf("Receita ID %d, cadastrada com sucesso!\n", novo.id);
}
void pagarDespesa(FILE *arq){
    int idBusca;
    Lancamento temp;
    int encontrou = 0;
    printf("\n---- Pagar Despesa ----\n");
    printf("Digite o ID da despesa a ser pega: \n");
    scanf("%d", &idBusca);
    fseek(arq, 0, SEEK_SET);

    while(fread(&temp, sizeof(Lancamento), 1, arq)){
        if(idBusca == temp.id){
            if(temp.tipo == 'R'){
                printf("Esse ID, pertence a uma receita, não uma despesa!\n");
                break;
            }
            if(temp.status == 1){
                printf("Essa despesa já foi paga!\n");
                break;
            }
            printf("Conta encontrada: %s\n", temp.descricao);
            encontrou = 1;
            temp.status = 1;
            fseek(arq, -sizeof(Lancamento), SEEK_CUR);
            fwrite(&temp, sizeof(Lancamento), 1, arq );
            fflush(arq);
            printf("Conta paga com sucesso! ✔ \n");
            break;
        }
    }
    if(!encontrou){
        printf("Conta não encontrada!\n");
    }

}
void extrato(FILE *arq){
    float totalReceitas = 0, despesasPagas = 0, despesasPendentes = 0;
    Lancamento temp;
    printf("\n--- EXTRATO MENSAL ---\n");
    printf("ID\t| TIPO\t| STATUS\t| VALOR\t        | DESCRICAO\n");
    printf("------------------------------------------------------------\n");
    fseek(arq, 0, SEEK_SET);
    while(fread(&temp, sizeof(Lancamento), 1, arq)){
        printf("%-4d\t| %c\t| %-10s\t| %9.2f\t| %-10s\n", temp.id, temp.tipo, (temp.status == 1) ? "PAGO" : "PENDENTE", temp.valor, temp.descricao);

        if(temp.tipo == 'R'){
            totalReceitas += temp.valor;
        }
        if(temp.tipo == 'D' && temp.status == 1){
            despesasPagas += temp.valor;        
        }
        if(temp.tipo == 'D' && temp.status == 0){
            despesasPendentes += temp.valor;
        }
    }
    printf("-----------------------------------------------------------\n");
    printf(" (+) Total Recebido:   R$ %.2f\n", totalReceitas);
    printf(" (-) Despesas Pagas:   R$ %.2f\n",despesasPagas);
    printf(" (!) Contas a Pagar:   R$ %.2f\n", despesasPendentes);
    printf("==========================================\n");
    printf(" SALDO ATUAL (liq):    R$ %.2f\n", totalReceitas - despesasPagas);
}

int main() {
    FILE *arquivo;
    arquivo = fopen("dados.dat", "rb+");
    if(arquivo == NULL){
        arquivo = fopen("dados.dat", "wb+");
    }
    if(arquivo == NULL){
        printf("Erro fatal\n");
        return 1;
    }
    printf("Arquivo aberto!\n");

    int op;
    char tipo;
    
    do{
        op = menu();
        switch(op){
            case 1:
                tipo = 'R';
                cadastrar(arquivo, tipo);
                break;
            case 2:
                tipo = 'D';
                cadastrar(arquivo, tipo);
                break;
            case 3:
                pagarDespesa(arquivo);
                break;
            case 4: 
                extrato(arquivo);
                break;
            case 0:
                printf("Fechando programa...\n");
                break;
            default:
                printf("Opção invalida.\n");
                break;
        }

    }while(op != 0);

    fclose(arquivo);
    
    return 0;
}