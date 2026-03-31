#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char nome[30];
    int telefone;
} Contato;

void Cadastrar(FILE *arq){
    Contato novo;
        
    printf("\n---Novo Cadastro---\n");
    printf("Nome: \n");
    scanf(" %[^\n]", novo.nome);    
    printf("Telefone: \n");
    scanf("%d", &novo.telefone);
        
    fseek(arq, 0, SEEK_END);
    fwrite(&novo, sizeof(Contato), 1, arq);
    fflush(arq);

    printf("Sucesso! %s foi salvo na agenda.\n", novo.nome);
}
void alterarTelefone(FILE *arq){
    char nomeBusca[30];
    Contato temp;
    int encontrou = 0;

    printf("\n----Alterar Telefone----\n");
    printf("Digite o nome exato do contato:\n");
    scanf(" %[^\n]", nomeBusca);
    fseek(arq, 0, SEEK_SET);

    while(fread(&temp, sizeof(Contato), 1, arq)){

        if(strcmp(temp.nome, nomeBusca) == 0){
            printf("Encontrado! Telefone atual: %d\n", temp.telefone);
            printf("Digite o NOVO telefone:\n");
            scanf("%d", &temp.telefone);

            fseek(arq, -sizeof(Contato), SEEK_CUR);
            fwrite(&temp, sizeof(Contato), 1, arq);
            fflush(arq);
            printf("Telefone alterado com  sucesso!\n");
            encontrou = 1;
            break;
        }
    }
    if(!encontrou){
        printf("Contato não encontrado.\n");
    }
}

void ExcluirContato(){
    FILE *original = fopen("agenda.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    if(original == NULL || temp == NULL){
        printf("Erro ao abrir arquivos\n");
        return;
    }

    char nomeExcluir[30];
    Contato lido;
    int encontrou = 0;

    printf("\n---- Excluir Contato ----\n");
    printf("Digite o nome exato para apagar:\n");
    scanf(" %[^\n]", nomeExcluir);

    while(fread(&lido.nome, sizeof(Contato), 1, original)){
        if(strcmp(lido.nome, nomeExcluir) != 0){
            fwrite(&lido, sizeof(Contato), 1, temp);
        }
        else{
            encontrou = 1;
        }
    }
    fclose(original);
    fclose(temp);

    if(encontrou){
        remove("agenda.dat");
        rename("temp.dat", "agenda.dat");
        printf("Contato excluido!\n");
    }
    else{
        remove("temp.dat");
        printf("Nome não encontrado na agenda.\n");
    }

}

void listar(FILE *arq){
    Contato temp;

    printf("\n---- Lista de contatos ----\n");

    fseek(arq, 0, SEEK_SET);
    while(fread(&temp, sizeof(Contato), 1, arq)){
        printf("Nome: %-20s | Tel: %d\n", temp.nome, temp.telefone);
    }
}
int menu(){
    int op;
    printf("\n-----MENU-----\n");
    printf("1- Cadastrar Contrato\n");
    printf("2 - Ver Agenda Telefonica\n");
    printf("3- Alterar telefone\n");
    printf("4- Excluir\n");
    printf("0 - Sair\n");
    scanf("%d", &op);
    return op;
}
int main() {
    FILE *arquivo;
    arquivo = fopen("agenda.dat", "rb+");
    if (arquivo == NULL){
        arquivo = fopen("agenda.dat", "wb+");
    }

    if (arquivo == NULL) {
        printf("Erro fatal!\n");
        return 1;
    }
    printf("Sucesso! O sistema de arquivos está pronto.\n");

    int op;
    do{
        op = menu();
        switch(op){
            case 1:
                Cadastrar(arquivo);
                break;
            case 2:
                listar(arquivo);
                break;
            case 3:
                alterarTelefone(arquivo);
                break;
            case 4:
                fclose(arquivo);
                ExcluirContato();
                arquivo = fopen("agenda.dat", "rb+");
                break;
            case 0:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }

    }while(op != 0);
    fclose(arquivo);
    
    printf("Programa Finalizado.\n");

    
    return 0;
}