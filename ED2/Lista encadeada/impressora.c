#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "Document.h" 

int interface(){
	printf("1 - Criar Documento\n");
	printf("2 - Fila de Impressão\n");
	printf("3 - Imprimir Documento\n");
	printf("4 - Excluir Documento\n");
	printf("5 - Priorizar Documento\n");
	int opt;
	scanf(" %d",&opt);
	return opt;
}

void cadastrar_documento(List lst){
	char nome[100];
	int id, pgs, size;
	id = rand()%1000;
	printf("Nome do Documento: ");
	scanf(" %[^\n]s",nome);
	printf("Páginas do Documento: ");
	scanf(" %d",&pgs);
	size = rand()%200;
	new_Document(lst,id,nome,pgs,size);
}

void imprimir(List lst){
	if(lst->head == NULL){
		printf("A fila de impressão está vazia.\n");
		return;
	}

	Document doc = lst->head;
	printf("\nImprimindo primeiro da fila..\n");
	print_Document(doc);

	if(lst->head != NULL){
		lst->head->ant = NULL;

	}
	else{
		lst->tail = NULL;
	}

	lst->size--;

	free(doc);
	printf("Documento removido da fila com sucesso!\n");
}
void excluir_documento(List lst){

	if(lst->head == NULL){
	printf(" A fila está vazia, nada para excluir.\n");
	}

	int alvo;
	printf("Digite o ID do documento que deseja excluir: \n");
	scanf("%d", &alvo);

	Document atual = lst->head;
	int encontrou = 0;
	while(atual != NULL){

		if(atual->id == alvo){
			encontrou = 1;

			if(atual == lst->head){
				lst->head = atual->prox;
				if(lst->head != NULL){
					lst->head->ant = NULL;
				}
				else{
					lst->tail = NULL;
				}
			}
			else if(atual == lst->tail){
				lst->tail = atual->ant;
				lst->tail->prox = NULL;
				
			}
			else{
				atual->ant->prox = atual->prox;
				atual->prox->ant = atual->ant;
			}	

			lst->size--;
			free(atual);
			printf("Documento %d excluido com sucesso!\n", alvo);
			break;
		}
		atual = atual->prox;
		if(!encontrou){
			printf("Documento com %d não encontrado na fila.\n", alvo);
		}
			
	}
}
void priorizar(List lst){
	
}
int main(){
	List lst = new_List();
	
	do{
		switch(interface()){
			case 1: cadastrar_documento(lst);
					break;
			case 2: print_List(lst);
					break;
			case 3: imprimir(lst);
					break;
			case 4: excluir_documento(lst);
					break;
			case 5: 
					break;
			case 0: return 0;
		}
		
	}while(1);
}
