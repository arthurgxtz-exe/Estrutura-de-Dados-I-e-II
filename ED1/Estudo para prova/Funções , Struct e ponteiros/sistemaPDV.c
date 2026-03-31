#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//sistema pdv (ponto de venda)
/* REQUISITOS DA APLICAÇÃO

1- DEVE SER POSSÍVEL CADASTRAR ATÉ 100 PRODUTOS.
2- TODO PRODUTO DEVE TER CODIGO ÚNICO (GARANTIDO PELO SW).
3- SAÍDA DO CADASTRO DE PRODUTOS SERÁ CODIGO <= 0;

FASE DE VENDAS!
1- SOLICITAR CODIGO DE ITEM PARA VENDA:
	1.1- VERIFICAR SE ITEM EXISTE
		1.1.1- IMPRIMIR TODOS OS DADOS DO PRODUTO, OU
		1.1.2- CODIGO NÃO EXISTENTE! TENTAR NOVAMENTE.

	1.2. SOLICITAR QUANTIDADE DESTE MESMO ITEM NO CARRINHO
		1.2.1- VERIFICAR SE A QTDE. ESTÁ DISPONÍVEL
		1.2.2- ATUALIZAR ESTOQUE DO ITEM
		
2. REPETIR TODO PROCESSO DE VENDA DO CARRINHO ATÉ CÓDIGO <=0

3. INFORMAR TOTAL DA VENDA
4. INFORMAR VALOR PAGO
5. INFORMAR TROCO DA VENDA

6. PERGUNTAR SE HÁ NOVO CARRINHO DE COMPRAS
	6.1. REPETIR TODO PROCESSO PARA NOVO CARRINHO.

7. NÃO HAVENDO...
	7.1 RELATÓRIO ATUALIZADO DE TODOS OS PRODUTOS
	7.2 FATURAMENTO DO DIA (TOTAL DE VENDAS)
*/

typedef struct{
	int codigo;   //chave
	char descricao[100];
	float valor;
	int estoque;
}Produto;

int  menu(){
	int op;
	printf("Menu de opções:\n");
	printf("1- Cadastrar Produtos\n");
	printf("2 - Realizar Vendas\n");
	printf("3 - Relátorio e Faturamento\n");
	printf("0 - Sair do programa\n");
	scanf("%d", &op);
	return op;

}
int BuscarProduto(Produto p[], int cont, int cod){
	for(int i = 0; i < cont; i++){
		if(p[i].codigo == cod){
			return i;
		}
	}
				
	return -1;
}
int CadastrarProduto(Produto p[], int cont){

	if(cont >= 100){
		printf("Limite de cadastro excedido\n");
		return 0;
	}
	else{
		printf("\n====== Cadastro do produto %d\n", cont + 1);
		do{
			printf("Código: (<= 0 pra voltar) \n");
			scanf("%d", &p[cont].codigo);
			if(p[cont].codigo <= 0){
				return 0;
			}
			if(BuscarProduto(p, cont, p[cont].codigo) >= 0){
				printf("Esse código já existe! Digite outro.\n");
			}
			else{
				break;
			}
		}while(1);	
		printf("Descrição:\n");
		scanf(" %[^\n]", p[cont].descricao);
		printf("Valor:\n");
		scanf("%f", &p[cont].valor);
		printf("Estoque:\n");
		scanf("%d", &p[cont].estoque);
		printf("Sucesso!\n");

	}
	
	return 1;
}

void realizarvenda(Produto p[], int qtd, float *faturamento){
	int codTemp;
	int qtdTemp;
	float valorPago, totalCarrinho = 0;
	printf("\nNova venda iniciada:\n");
	while(1){
		printf("Digite o código do item para venda (cod <= 0 para voltar):\n");
		scanf("%d", &codTemp);
		if(codTemp <= 0){
			break;
		}
		int indice = BuscarProduto(p, qtd, codTemp);
		if(indice < 0){
			printf("Esse item não existe! Digite um código valido.\n");
		}
		else{
			printf("\nProduto código %d Encontrado:\n", codTemp);
			printf("Descrição: %s\n", p[indice].descricao);
			printf("Valor: %.2f\n", p[indice].valor);
			printf("Estoque: %d\n", p[indice].estoque);
			while(1){
				printf("\nDigite quantidade que será vendida do produto:\n");
				scanf("%d", &qtdTemp);
				if(qtdTemp > p[indice].estoque){
					printf("O pedido é maior que o estoque! Faça um novo pedido.\n");
				}
				else{
					printf("Venda de %d unidades feita com sucesso!\n", qtdTemp);
					p[indice].estoque -= qtdTemp;
					float subTotal = p[indice].valor * qtdTemp;
					totalCarrinho += subTotal;
					printf("Adicionado! SubTotal do item: %.2f\n", subTotal);
					printf("Total parcial do carrinho: %.2f\n", totalCarrinho);
					break;
				}
			}
			char resp;
			printf("Deseja iniciar uma nova venda? ( s/n )\n");
			scanf(" %c", &resp);
			if(resp == 'n'){

				break;
			}
			
		}
		
	}

	if(totalCarrinho > 0){
		printf("\nFechamento de caixa\n");
		printf("TOTAL DA VENDA: %.2f\n", totalCarrinho);

		while(1){
			printf("Informe o valor pago:\n");
			scanf("%f", &valorPago);

			if(valorPago < totalCarrinho){
				printf("Valor insuficiente! Faltam R$ %.2f\n", totalCarrinho - valorPago);

			}
			else{
				printf("Venda Concluida! Troco: R$ %.2f\n", valorPago - totalCarrinho);
				*faturamento += totalCarrinho;
				break;
			}
		}
	}
	else{
		printf("\nVenda cancelada ou carrinho vazio.\n");
	}
	
}

void RelatorioProdutos(Produto p[], int qtd, float faturamento){
	printf("\nRELATORIO ATUALIZADO DOS PRODUTOS:\n");
	for(int i = 0; i < qtd; i++){
		printf("\nProduto Código: %d\n", p[i].codigo);
		printf("Descrição: %s\n", p[i].descricao);
		printf("Valor: %.2f\n", p[i].valor);
		printf("ESTOQUE: %d\n", p[i].estoque);
	}

	printf("\nFaturamento do dia: %.2f\n", faturamento);

}

int main(){
	Produto p[100];
	int cont = 0;
	int op;
	float faturamento = 0;
	
	do{
		op = menu();
		switch(op){
		case 1:
			do{
			if(CadastrarProduto(p, cont) == 1){
				cont++;
			}
			else{
				break;
			}
	
			}while(cont <= 100);
		
			printf("Total de Produtos Cadastrados: %d\n", cont);
			break;
		
		case 2:
			realizarvenda(p, cont, &faturamento);
			break;
		case 3:
			RelatorioProdutos(p, cont, faturamento);
		case 0:
			printf("Encerrando..\n");
			break;
		}

	}while(op != 0);
	printf("Programa Finalizado.");
		
	return 0;
}

	


