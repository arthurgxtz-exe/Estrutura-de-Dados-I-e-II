#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Cache{
	char nome_arquivo[50]; // CORREÇÃO: Corrigido o erro de digitação (estava aquivo)
	int hit_rate;
	struct Cache *proximo;	
} Cache;

typedef struct{
	Cache *head;
	Cache *tail;
	int tam;
} Proxy;

void inicializar(Proxy *p){
	p->head = NULL;
	p->tail = NULL;
	p->tam = 0;
}

void limpar_buffer(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

void liberar_sistema(Proxy *p) {
    Cache *aux = p->head;
    Cache *temp = NULL;
    
    while (aux != NULL) {
        temp = aux->proximo;
        free(aux);
        aux = temp;    
    }
    
    p->head = NULL;
	p->tail = NULL;
	p->tam = 0;
}

void inserir_fim(Proxy *p, char nome_buscado[]){
    Cache *novo = malloc(sizeof(Cache));
    
    if(novo){
        strcpy(novo->nome_arquivo, nome_buscado);
        
        // CORREÇÃO: O hit_rate precisa começar com 1, senão ele imprime lixo de memória
        novo->hit_rate = 1; 
        novo->proximo = NULL;
        
        if(p->head == NULL){
            p->head = novo;
            p->tail = novo;
        }
        else{
            p->tail->proximo = novo;
            p->tail = novo;
        }
    
        p->tam++;
    }
    else {
        printf("Erro ao alocar memoria.\n");
    }
}

void dar_prioridade(Proxy *p, char alvo[]){
    if(p->head == NULL){
        printf("Não existe arquivo para dar prioridade\n");
        return;
    }
    
    Cache *aux = p->head;
    Cache *anterior = NULL;
    
    
    while(aux != NULL && strcmp(aux->nome_arquivo, alvo) != 0){
        anterior = aux;
        aux = aux->proximo;
    }
    
    if(aux == NULL){
        printf("Arquivo não encontrado\n");
        return;
    }

    if(aux == p->head){
        // Como o buscar_arquivo já avisa do Hit, a gente só encerra silenciosamente aqui
        return;
    }

    
    anterior->proximo = aux->proximo;

    if(aux->proximo == NULL){
        p->tail = anterior;
    }

    aux->proximo = p->head;
    p->head = aux;
}

void listar_arquivos(Proxy *p){
    Cache *atual = p->head;

    if(atual == NULL){
        printf("Nenhum arquivo no Proxy\n");
        return;
    }
    
    while(atual != NULL){
        printf("-> %s |%d| ", atual->nome_arquivo, atual->hit_rate);
        atual = atual->proximo;
    }
	printf("\n");
}


void buscar_arquivo(Proxy *p, char arquivo_buscado[]){
	Cache *aux = p->head;
    Cache *anterior = NULL; // CORREÇÃO: Variáveis de ponteiro precisam iniciar em NULL
	
	printf("\nArquivo Buscado: %s\n", arquivo_buscado);
	
	if(p->head == NULL){
		printf("Cache Miss!\n");
		// CORREÇÃO: Eu passei '&aux', mas a função precisa do Gerente 'p'
        inserir_fim(p, arquivo_buscado); 
        return;        
    }
    
    // CORREÇÃO: Substituído o '!=' pelo strcmp para comparar o texto da string
    while (aux != NULL && strcmp(aux->nome_arquivo, arquivo_buscado) != 0){
        anterior = aux;
        aux = aux->proximo;
    }
    
    if(aux == NULL){
        printf("Cache Miss!\n");
        // CORREÇÃO: Passando 'p' em vez de '&aux'
        inserir_fim(p, arquivo_buscado);
        return;
    }

    if(anterior == NULL){
        printf("Cache Hit!\n");
        aux->hit_rate++;
    }
    else{
        printf("Cache Hit!\n");
        aux->hit_rate++;
        // CORREÇÃO: Passando 'p' em vez de '&aux'
        dar_prioridade(p, aux->nome_arquivo);
    }
    
    // CORREÇÃO: Removi a linha "if(aux->proximo == NULL){ p->tail = anterior; }" que estava aqui no final.
    // A  função "dar_prioridade" já é inteligente o suficiente para atualizar o tail sozinha!
}

int main(){
	Proxy minha_lista;
	inicializar(&minha_lista);
	
	// CORREÇÃO: Unifiquei o nome da variável para não dar erro no scanf
	char nome_arquivo[50]; 
	
	while(1){
		printf("\nDigite o arquivo a ser buscado (ou 'exit' para sair): ");
		scanf(" %[^\n]", nome_arquivo);
		limpar_buffer();
		
		if(strcmp(nome_arquivo, "exit") == 0){
			printf("Apagando memoria e encerrando aplicacao...\n");
			liberar_sistema(&minha_lista);
			break;		
		}
		else {		
		    buscar_arquivo(&minha_lista, nome_arquivo);
		    listar_arquivos(&minha_lista);
		}
	}
	
	return 0;
}