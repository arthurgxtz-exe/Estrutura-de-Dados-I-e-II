#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
    int id;
} Processo;

void systemcall(int modo) {
    if (!modo) {
        printf("\n[SISTEMA] Interrupcao de Software: Chamada de Sistema detectada!\n");
        printf("[SISTEMA] Tipo da Chamada: ALOCACAO DE MEMORIA (Rotina de Kernel)\n");
        
        sleep(1);
        printf("1. Salvando o contexto dos registradores (Modo Usuario)");
        for(int i = 0; i < 3; i++) { sleep(1); printf("."); fflush(stdout); }
        
        sleep(1);
        printf("\n2. Mudando processador para MODO KERNEL (Bit de privilegio: 0)");
        for(int i = 0; i < 3; i++) { sleep(1); printf("."); fflush(stdout); }
        
        sleep(2);
        system("clear");
    } else {
        printf("\n[SISTEMA] Finalizando rotina do SO...\n");
        
        sleep(1);
        printf("3. Alterando o modo de acesso do processador para USUARIO (Bit: 1)");
        for(int i = 0; i < 3; i++) { sleep(1); printf("."); fflush(stdout); }
        
        sleep(1);
        printf("\n4. Resgatando contexto dos registradores e retomando execucao");
        for(int i = 0; i < 3; i++) { sleep(1); printf("."); fflush(stdout); }
        
        sleep(2);
        system("clear");
    }
}

int PcTaOn() {
    int on;
    printf("\n--- Computador Desligado ---\n");
    printf("Deseja ligar o computador:\n1-LIGAR\n0-SAIR\nOpcao: ");
    scanf(" %d", &on);
    return on;
}

int menu() {
    int op;
    printf("\n--- SISTEMA OPERACIONAL ---\n");
    printf("1 - Solicitar Processo de Kernel\n");
    printf("2 - Solicitar Processo de Usuario\n");
    printf("0 - Desligar\n");
    printf("Opcao: ");
    scanf("%d", &op);
    return op;
}

Processo* ProcessoKernel(Processo *memoria, int *qtd, int id_gerador, int modo) {
    while(getchar() != '\n'); 
    printf("\nAperte ENTER para disparar a System Call (Kernel)...\n");
    getchar();

    systemcall(0);

    (*qtd)++; 
    memoria = (Processo *) realloc(memoria, (*qtd) * sizeof(Processo));
    memoria[(*qtd) - 1].id = id_gerador;
    
    systemcall(1);

    printf("[+] Sucesso: Processo %d alocado no Kernel!\n", id_gerador);
    return memoria;
}

Processo* ProcessoUsuario(Processo *memoria, int *qtd, int id_gerador, int modo) {
    while(getchar() != '\n'); 
    printf("\nAperte ENTER para disparar a System Call (Usuario)...\n");
    getchar();

    systemcall(0);

    (*qtd)++; 
    memoria = (Processo *) realloc(memoria, (*qtd) * sizeof(Processo));
    memoria[(*qtd) - 1].id = id_gerador;
    
    systemcall(1);

    printf("[+] Sucesso: Processo %d alocado no Usuario!\n", id_gerador);
    return memoria;
}

int main() {
    int computador_ligado = 0, modo = 0, qtd_kernel = 0, qtd_usuario = 0, id_global = 1; 
    Processo *memoria_kernel = NULL, *memoria_usuario = NULL;
    
    system("clear");
    computador_ligado = PcTaOn();
   
    if (computador_ligado == 1) {
        printf("\nComputador ligando");
        for(int i = 0; i < 3; i++) { sleep(1); printf("."); fflush(stdout); }
        sleep(1);
        system("clear");
        modo = 1;
    }

    while(computador_ligado) {
        int op = menu();
        switch (op) {
            case 1:
                modo = 0;
                memoria_kernel = ProcessoKernel(memoria_kernel, &qtd_kernel, id_global++, modo);
                break;
            case 2:
                modo = 1;
                memoria_usuario = ProcessoUsuario(memoria_usuario, &qtd_usuario, id_global++, modo);
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
    printf("Relatorio Final de Processos:\n\nTotal Geral Executado: %d\n", qtd_kernel + qtd_usuario);
    
    printf("\n-> [MODO KERNEL]: %d processos\n", qtd_kernel);
    for (int i = 0; i < qtd_kernel; i++) 
        printf("   ID: %d | Endereco: %p\n", memoria_kernel[i].id, (void*)&memoria_kernel[i]);
    
    printf("\n-> [MODO USUARIO]: %d processos\n", qtd_usuario);
    for (int i = 0; i < qtd_usuario; i++) 
        printf("   ID: %d | Endereco: %p\n", memoria_usuario[i].id, (void*)&memoria_usuario[i]);

    if (memoria_kernel) free(memoria_kernel);
    if (memoria_usuario) free(memoria_usuario);

    return 0;
}