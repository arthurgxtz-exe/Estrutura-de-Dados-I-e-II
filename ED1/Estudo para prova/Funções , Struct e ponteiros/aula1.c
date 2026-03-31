#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
//FAÇA UM PROGRAMA QUE LEIA OS DADOS DE ATÉ 10 PESSOAS
//FINALIZE COM O NOME "EXIT".
//APÓS A FASE DE CADASTRO, REALIZE A IMPRESSAO
//DE TODAS AS PESSOAS CADASTRADAS ORDENADAS PELO NOME.

typedef	struct{
	char rua[100];
	int numero;
	char bairro[100];
	char cidade[100];
}Endereco;

typedef	struct{
	char nome[100];
	char cpf[12];
	int idade;
	float altura,peso;
	Endereco residencia;
}Pessoa;


void cadastrarPessoa(Pessoa *p){
		printf("CPF: \n");
		scanf(" %[^\n]", p->cpf);
		while(getchar()!= '\n');
		printf("Idade: \n");
		scanf("%d", &p->idade);
		while(getchar()!= '\n');
		printf("Altura: \n");
		scanf("%f", &p->altura);
		while(getchar()!= '\n');
		printf("Peso: \n");
		scanf("%f", &p->peso);
		while(getchar()!= '\n');
		printf("Rua: \n");
		scanf(" %[^\n]", p->residencia.rua);
		while(getchar()!= '\n');
		printf("Numero: \n");
		scanf("%d", &p->residencia.numero);
		while(getchar()!= '\n');
		printf("Bairro: \n");
		scanf("%[^\n]", p->residencia.bairro);
		while(getchar()!= '\n');
		printf("Cidade: \n");
		scanf(" %[^\n]", p->residencia.cidade);
		while(getchar()!= '\n');

}

void impressaoCadastro(Pessoa p, int id){

	printf("\nPessoa numero %d\n", id);
	printf("Nome: %s\n", p.nome);
	printf("CPF: %s \n", p.cpf);
	printf("Idade: %d\n", p.idade);
	printf("Altura: %.2f\n", p.altura);
	printf("Peso: %.2f \n", p.peso);
	printf("Rua: %s \n", p.residencia.rua);
	printf("Numero: %d \n", p.residencia.numero);
	printf("Bairro: %s \n", p.residencia.bairro);
	printf("Cidade: %s \n", p.residencia.cidade);
}
int main(){
	Pessoa cadastro[10];
	int cont = 0;
	for(int i = 0; i < 10; i++){
		cont = i + 1;
		printf("\n===== Cadastro da pessoa %d =====\n", cont);
		printf("Nome: \n");
		scanf("%[^\n]", cadastro[i].nome);
		while(getchar()!= '\n');

		if(strcmp(cadastro[i].nome, "EXIT") == 0){
			cont--;
			break;
		}
		else
		cadastrarPessoa(&cadastro[i]);	
		
	}
	system("cls");

	printf("\n===== Todas as pessoas cadastradas: =====\n");

	for(int i = 0; i < cont - 1; i++){
		for(int j = i + 1; j < cont; j++){
			if(strcmp(cadastro[i].nome, cadastro[j].nome) > 0){
				Pessoa temp = cadastro[i];
				cadastro[i] = cadastro[j];
				cadastro[j] = temp;
			}
		}
	}
	for(int i = 0; i < cont; i++){
		
		impressaoCadastro(cadastro[i], i + 1);
	}

}
