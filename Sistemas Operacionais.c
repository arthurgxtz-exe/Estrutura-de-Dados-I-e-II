//Arthur Almeida e Clara Mirian :)

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
    int id;
} Processo;

int PcTaOn() {
    int on;
    printf("\n--- Computador Desligado ---\n");
    printf("Deseja ligar o computador:\n");
    printf ("1-LIGAR\n");
    printf("0-SAIR\n");
    scanf(" %d", &on);
    return on;
}

int menu() {
    int op;
    printf("\n--- SISTEMA OPERACIONAL ---\n");
    printf("1 - Processo de Kernel\n");
    printf("2 - Processo de Usuario\n");
    printf("0 - Desligar\n");
    printf("Opcao: ");
    scanf("%d", &op);
    return op;
}

Processo* ProcessoKernel(Processo *memoria, int *qtd, int id_gerador, int modo) {
    while(getchar() != '\n'); 

    printf("Aperte ENTER para alocar processo de Kernel...\n");
    getchar();

    systemcall(modo);

    /*
    sleep(1);
    printf("Mudando para Modo Kernel");
    fflush(stdout);
    sleep(1);
    printf(".");
    fflush(stdout);
    sleep(1);
    printf(".");
    fflush(stdout);
    sleep(1);  
    printf(".");
    fflush(stdout);
    sleep(2);
    system("clear");
    */
    
    (*qtd)++; 
    memoria = (Processo *) realloc(memoria, (*qtd) * sizeof(Processo));
    memoria[(*qtd) - 1].id = id_gerador;
    
    printf("[+] Processo %d alocado no Kernel com sucesso!\n", id_gerador);
    
    return memoria;
}

Processo* ProcessoUsuario(Processo *memoria, int *qtd, int id_gerador, int modo) {
    while(getchar() != '\n'); 

    printf("Aperte ENTER para alocar processo do Usuario...\n");
    getchar();

    systemcall(modo);

    /*sleep(1);
    printf("Mudando para Modo Kernel");
    fflush(stdout);
    sleep(1);
    printf(".");
    fflush(stdout);
    sleep(1);
    printf(".");
    fflush(stdout);
    sleep(1);  
    printf(".");
    fflush(stdout);
    sleep(2);
    system("clear");
    */

    (*qtd)++; 
    memoria = (Processo *) realloc(memoria, (*qtd) * sizeof(Processo));
    memoria[(*qtd) - 1].id = id_gerador;
    
    printf("[+] Processo %d alocado no Usuario com sucesso!\n", id_gerador);
    
    return memoria;
}

void systemcall(int modo){

    if(!modo){
        sleep(1);
        printf("Salvando o contexto dos registradores");
        fflush(stdout);
        sleep(1);
        printf(".");
        fflush(stdout);
        sleep(1);
        printf(".");
        fflush(stdout);
        sleep(1);  
        printf(".");
        fflush(stdout);
        sleep(2);
        system("clear");
        printf("\n");

        sleep(1);
        printf("Alterando modo de acesso do processador para Kernel");
        fflush(stdout);
        sleep(1);
         printf(".");
        fflush(stdout);
        sleep(1);
        printf(".");
        fflush(stdout);
        sleep(1);  
        printf(".");
        fflush(stdout);
        sleep(2);
        system("clear");

    }
    if(modo){
        sleep(1);
        printf("Alterando o modo de acesso do processador para usuário");
        fflush(stdout);
        sleep(1);
        printf(".");
        fflush(stdout);
        sleep(1);
        printf(".");
        fflush(stdout);
        sleep(1);  
        printf(".");
        fflush(stdout);
        sleep(2);
        system("clear");
        printf("\n");

        sleep(1);
        printf("Restaurando contexto dos registradores");
        fflush(stdout);
        sleep(1);
         printf(".");
        fflush(stdout);
        sleep(1);
        printf(".");
        fflush(stdout);
        sleep(1);  
        printf(".");
        fflush(stdout);
        sleep(2);
        system("clear");

    }
    
}

int main() {
    int computador_ligado = 0;
    int modo = 0;
    
    int qtd_kernel = 0;
    int qtd_usuario = 0;
    int id_global = 1; 
    
    Processo *memoria_kernel = NULL;
    Processo *memoria_usuario = NULL;
    
    system("clear");

    computador_ligado = PcTaOn();
   
    
    if (computador_ligado == 1) {
        sleep(1);
        printf("Computador ligando");
        fflush(stdout);
        
        sleep(1);
        printf(".");
        fflush(stdout);
        
        sleep(1);
        printf(".");
        fflush(stdout);
        
        sleep(1);  
        printf(".");
        fflush(stdout);
        
        sleep(2);
        system("clear");
        modo = 1;
    }

    while(computador_ligado) {
        
        int op = menu();
        
        switch (op) {
            case 1:
                modo = 0;
                memoria_kernel = ProcessoKernel(memoria_kernel, &qtd_kernel, id_global, modo);
                id_global++;
                break;
            case 2:
                modo = 1;
                memoria_usuario = ProcessoUsuario(memoria_usuario, &qtd_usuario, id_global, modo);
                id_global++;
                break;
            case 0:
                computador_ligado = 0;
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    }
    
    printf("\n=== COMPUTADOR DESLIGADO ===\n");
    printf("Relatorio Final de Processos:\n\n");
    
    printf("Total de processos recebidos: %d\n", qtd_kernel + qtd_usuario);
    printf("-----------------------------------\n\n");
    
    printf("-> Total no Kernel: %d\n", qtd_kernel);
    if (qtd_kernel > 0) {
        for (int i = 0; i < qtd_kernel; i++) {
            printf("   [ID: %d] alocado no endereco de memoria: %p\n", memoria_kernel[i].id, (void*)&memoria_kernel[i]);
        }
    }
    
    printf("\n-----------------------------------\n\n");
    
    printf("-> Total no Usuario: %d\n", qtd_usuario);
    if (qtd_usuario > 0) {
        for (int i = 0; i < qtd_usuario; i++) {
            printf("   [ID: %d] alocado no endereco de memoria: %p\n", memoria_usuario[i].id, (void*)&memoria_usuario[i]);
        }
    }
    printf("\n===================================\n");

    if (memoria_kernel != NULL) free(memoria_kernel);
    if (memoria_usuario != NULL) free(memoria_usuario);

    return 0;
}