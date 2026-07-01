#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>

/*
 * Nó da árvore.
 * Cada nó guarda um valor inteiro e dois ponteiros:
 * um para o filho da esquerda e outro para o filho da direita.
 */
typedef struct _TreeNode _TreeNode;
typedef _TreeNode* TreeNode;

struct _TreeNode {
    int value;
    TreeNode left;
    TreeNode right;
};

/*
 * Estrutura principal da árvore.
 * root aponta para o primeiro nó da árvore.
 * size guarda a quantidade de valores armazenados.
 */
typedef struct _Tree _Tree;
typedef _Tree* Tree;

struct _Tree {
    TreeNode root;
    int size;

    void (*insert)(Tree self, int value);
    TreeNode (*search)(Tree self, int value);
    void (*print)(Tree self);
    void (*inOrder)(Tree self);
    void (*preOrder)(Tree self);
    void (*postOrder)(Tree self);
    void (*remove)(Tree self, int value);
    void (*clear)(Tree self);
};

/* Protótipos das funções principais. */
Tree new_Tree(void);
TreeNode new_TreeNode(int value);

void tree_Insert(Tree self, int value);
TreeNode tree_Search(Tree self, int value);
void tree_Print(Tree self);
void tree_InOrder(Tree self);
void tree_PreOrder(Tree self);
void tree_PostOrder(Tree self);
void tree_Remove(Tree self, int value);
void tree_Clear(Tree self);

/* Funções auxiliares usadas internamente pela biblioteca. */
TreeNode insert_Node(TreeNode node, int value, int* inserted);
TreeNode search_Node(TreeNode node, int value);
void print_Node(TreeNode node, int level);
void inOrder_Node(TreeNode node);
void preOrder_Node(TreeNode node);
void postOrder_Node(TreeNode node);
TreeNode smallest_Node(TreeNode node);
TreeNode remove_Node(TreeNode node, int value, int* removed);
void clear_Node(TreeNode node);

/*
 * Cria um novo nó.
 */
TreeNode new_TreeNode(int value) {
    TreeNode node = malloc(sizeof(_TreeNode));

    if (!node) {
        printf("Erro ao alocar no da arvore.\n");
        exit(1);
    }

    node->value = value;
    node->left = NULL;
    node->right = NULL;

    return node;
}

/*
 * Cria uma árvore vazia e liga os ponteiros de função.
 */
Tree new_Tree(void) {
    Tree tree = malloc(sizeof(_Tree));

    if (!tree) {
        printf("Erro ao alocar arvore.\n");
        exit(1);
    }

    tree->root = NULL;
    tree->size = 0;

    tree->insert = tree_Insert;
    tree->search = tree_Search;
    tree->print = tree_Print;
    tree->inOrder = tree_InOrder;
    tree->preOrder = tree_PreOrder;
    tree->postOrder = tree_PostOrder;
    tree->remove = tree_Remove;
    tree->clear = tree_Clear;

    return tree;
}

/*
 * Função recursiva que encontra a posição correta para inserir o valor.
 * Valores menores vão para a esquerda.
 * Valores maiores vão para a direita.
 * Valores repetidos não são inseridos.
 */
TreeNode insert_Node(TreeNode node, int value, int* inserted) {
    if (!node) {
        *inserted = 1;
        return new_TreeNode(value);
    }

    if (value < node->value)
        node->left = insert_Node(node->left, value, inserted);
    else if (value > node->value)
        node->right = insert_Node(node->right, value, inserted);

    return node;
}

/*
 * Insere um valor na árvore.
 */
void tree_Insert(Tree self, int value) {
    if (!self) return;

    int inserted = 0;

    self->root = insert_Node(self->root, value, &inserted);

    if (inserted)
        self->size++;
    else
        printf("O valor %d ja existe na arvore.\n", value);
}

/*
 * Busca recursiva.
 * A comparação permite escolher apenas um dos lados da árvore.
 */
TreeNode search_Node(TreeNode node, int value) {
    if (!node || node->value == value)
        return node;

    if (value < node->value)
        return search_Node(node->left, value);

    return search_Node(node->right, value);
}

TreeNode tree_Search(Tree self, int value) {
    if (!self) return NULL;

    return search_Node(self->root, value);
}

/*
 * Imprime a árvore de lado.
 * A subárvore da direita aparece em cima e a esquerda embaixo.
 */
void print_Node(TreeNode node, int level) {
    if (!node) return;

    print_Node(node->right, level + 1);

    for (int i = 0; i < level; i++)
        printf("    ");

    printf("%d\n", node->value);

    print_Node(node->left, level + 1);
}

void tree_Print(Tree self) {
    if (!self || !self->root) {
        printf("Arvore vazia.\n");
        return;
    }

    printf("\n----- ARVORE | size: %d -----\n", self->size);
    print_Node(self->root, 0);
    printf("------------------------------\n");
}

/*
 * Percurso em ordem: esquerda, raiz, direita.
 * Em uma árvore binária de busca, mostra os valores em ordem crescente.
 */
void inOrder_Node(TreeNode node) {
    if (!node) return;

    inOrder_Node(node->left);
    printf("%d ", node->value);
    inOrder_Node(node->right);
}

void tree_InOrder(Tree self) {
    if (!self) return;

    printf("Em ordem: ");
    inOrder_Node(self->root);
    printf("\n");
}

/* Percurso pré-ordem: raiz, esquerda, direita. */
void preOrder_Node(TreeNode node) {
    if (!node) return;

    printf("%d ", node->value);
    preOrder_Node(node->left);
    preOrder_Node(node->right);
}

void tree_PreOrder(Tree self) {
    if (!self) return;

    printf("Pre-ordem: ");
    preOrder_Node(self->root);
    printf("\n");
}

/* Percurso pós-ordem: esquerda, direita, raiz. */
void postOrder_Node(TreeNode node) {
    if (!node) return;

    postOrder_Node(node->left);
    postOrder_Node(node->right);
    printf("%d ", node->value);
}

void tree_PostOrder(Tree self) {
    if (!self) return;

    printf("Pos-ordem: ");
    postOrder_Node(self->root);
    printf("\n");
}

/*
 * Retorna o menor nó de uma subárvore.
 * O menor valor sempre está o mais à esquerda possível.
 */
TreeNode smallest_Node(TreeNode node) {
    TreeNode current = node;

    while (current && current->left)
        current = current->left;

    return current;
}

/*
 * Remove um valor da árvore.
 * Existem três casos:
 * 1. Nó sem filhos.
 * 2. Nó com apenas um filho.
 * 3. Nó com dois filhos.
 */
TreeNode remove_Node(TreeNode node, int value, int* removed) {
    if (!node)
        return NULL;

    if (value < node->value) {
        node->left = remove_Node(node->left, value, removed);
    }
    else if (value > node->value) {
        node->right = remove_Node(node->right, value, removed);
    }
    else {
        *removed = 1;

        /* Caso 1 e caso 2: não existe filho esquerdo. */
        if (!node->left) {
            TreeNode rightChild = node->right;
            free(node);
            return rightChild;
        }

        /* Caso 2: não existe filho direito. */
        if (!node->right) {
            TreeNode leftChild = node->left;
            free(node);
            return leftChild;
        }

        /*
         * Caso 3: o nó tem dois filhos.
         * Copiamos o menor valor da subárvore direita para o nó atual.
         * Depois removemos o nó que possuía esse valor.
         */
        TreeNode smallest = smallest_Node(node->right);
        node->value = smallest->value;

        int auxiliary = 0;
        node->right = remove_Node(node->right, smallest->value, &auxiliary);
    }

    return node;
}

void tree_Remove(Tree self, int value) {
    if (!self) return;

    int removed = 0;

    self->root = remove_Node(self->root, value, &removed);

    if (removed)
        self->size--;
    else
        printf("O valor %d nao foi encontrado.\n", value);
}

/*
 * Libera todos os nós usando percurso pós-ordem.
 * Os filhos são liberados antes do nó pai.
 */
void clear_Node(TreeNode node) {
    if (!node) return;

    clear_Node(node->left);
    clear_Node(node->right);
    free(node);
}

void tree_Clear(Tree self) {
    if (!self) return;

    clear_Node(self->root);

    self->root = NULL;
    self->size = 0;
}

#endif
