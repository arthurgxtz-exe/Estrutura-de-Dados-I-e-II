#include <stdio.h>
#include <stdlib.h>

// 1. Definição do Item
typedef struct {
    int valor;
    int peso;
} Item;

// 2. Função de Comparação para Ordenação
int comparar(const void *a, const void *b) {
    Item *itemA = (Item *)a;
    Item *itemB = (Item *)b;
    
    double razaoA = (double)itemA->valor / itemA->peso;
    double razaoB = (double)itemB->valor / itemB->peso;
    
    if (razaoA < razaoB) return 1;
    else if (razaoA > razaoB) return -1;
    else return 0;
}

// 3. Algoritmo da Mochila Fracionária
double mochilaFracionaria(int capacidade, Item itens[], int n) {
    qsort(itens, n, sizeof(Item), comparar);
    
    double valorTotal = 0.0;
    
    for (int i = 0; i < n; i++) {
        if (itens[i].peso <= capacidade) {
            capacidade -= itens[i].peso;
            valorTotal += itens[i].valor;
        } 
        else {
            valorTotal += itens[i].valor * ((double)capacidade / itens[i].peso);
            break; 
        }
    }
    return valorTotal;
}

// 4. Função Principal
int main() {
    Item itens[] = {{60, 10}, {100, 20}, {120, 30}};
    int capacidade = 50;
    int n = sizeof(itens) / sizeof(itens[0]);
    
    printf("Valor maximo na mochila fracionaria: %.2f\n", mochilaFracionaria(capacidade, itens, n));
    return 0;
}
