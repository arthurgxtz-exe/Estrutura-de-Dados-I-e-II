#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct{
    char nome[50];
    float preco;
    int estoque;

}Produto;
void estoqueProduto(Produto p){
    printf("\nFicha do Produto:\n");
    printf("Nome: %s\n", p.nome);
    printf("Preco: %.2f\n", p.preco);
    printf("Estoque: %d\n", p.estoque);

}
void realizarVenda(Produto *p, int qtd){
    if(p->estoque >= qtd){
        p->estoque = p->estoque - qtd;
        float total = p->preco * qtd;
        printf("\n[SUCESSO] Venda de %dx '%s' realizada!\n", qtd, p->nome);
        printf("Valor total a pagar: R$ %.2f\n", total);
    
    }
    else{
        printf("\n[ERRO] Estoque insuficiente! Restam apenas %d.\n", p->estoque);
    }
   
}

int main() {
    Produto camisa;
    strcpy(camisa.nome, "Camisa Oficial Cruzeiro 2024");
    camisa.preco = 349.90;
    camisa.estoque = 50;
    int n;
    estoqueProduto(camisa);
    printf("\nQuantas camisas você deseja comprar:\n");
    scanf("%d", &n);
    while(getchar()!= '\n');
    printf("\nPedido de %d camisas recebido, tecle enter para confirmar venda.\n", n);
    getchar();
    printf("Realizando venda de %d camisas...\n", n);
    Sleep(2000);
    system("cls");
    realizarVenda(&camisa, n);
    printf("\nTecle enter para ver o estoque atualizado:\n");
    getchar();
    system("cls");
    printf("\nEstoque atualizado:\n");
    estoqueProduto(camisa);


    return 0;
}