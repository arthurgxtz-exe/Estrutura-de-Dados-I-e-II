#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int main(void) {
    /* Criação da árvore vazia. */
    Tree tree = new_Tree();

    /*
     * Inserção dos valores.
     * O primeiro valor inserido se torna a raiz.
     */
    tree->insert(tree, 50);
    tree->insert(tree, 30);
    tree->insert(tree, 70);
    tree->insert(tree, 20);
    tree->insert(tree, 40);
    tree->insert(tree, 60);
    tree->insert(tree, 80);

    /* Mostra a estrutura da árvore. */
    tree->print(tree);

    /* Mostra os três percursos principais. */
    tree->inOrder(tree);
    tree->preOrder(tree);
    tree->postOrder(tree);

    /* Teste de busca. */
    int value = 40;
    TreeNode found = tree->search(tree, value);

    if (found)
        printf("\nValor %d encontrado na arvore.\n", value);
    else
        printf("\nValor %d nao encontrado.\n", value);

    /* Remove um nó e imprime novamente. */
    printf("\nRemovendo o valor 30...\n");
    tree->remove(tree, 30);
    tree->print(tree);
    tree->inOrder(tree);

    /* Libera os nós e depois a estrutura principal. */
    tree->clear(tree);
    free(tree);

    return 0;
}
