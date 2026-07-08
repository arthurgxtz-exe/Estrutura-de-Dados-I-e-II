#include <stdio.h>
#include "htable.h"

int menu(void) {
    int op;

    printf("\n--- MENU ---\n");
    printf("1 - Inserir ou atualizar\n");
    printf("2 - Buscar por chave\n");
    printf("3 - Remover por chave\n");
    printf("4 - Imprimir tabela\n");
    printf("5 - Mostrar quantidade\n");
    printf("0 - Sair\n");
    printf("Opcao: ");
    scanf("%d", &op);

    return op;
}

int main(void) {
    HashTable table = new(HashTable, 7);
    int op;

    if (!table)
        return 1;

    /* Alguns dados iniciais para demonstrar o uso da biblioteca. */
    table->insert(table, "A01", "Teclado");
    table->insert(table, "A02", "Mouse");
    table->insert(table, "A03", "Monitor");

    do {
        op = menu();

        switch (op) {
            case 1: {
                char key[100];
                char value[100];

                printf("Chave: ");
                scanf(" %99[^\n]", key);

                printf("Valor: ");
                scanf(" %99[^\n]", value);

                table->insert(table, key, value);
                printf("Elemento inserido ou atualizado.\n");
                break;
            }

            case 2: {
                char key[100];
                const char* value;

                printf("Chave para buscar: ");
                scanf(" %99[^\n]", key);

                value = table->get(table, key);

                if (value)
                    printf("Valor encontrado: %s\n", value);
                else
                    printf("Chave nao encontrada.\n");

                break;
            }

            case 3: {
                char key[100];

                printf("Chave para remover: ");
                scanf(" %99[^\n]", key);

                if (table->contains(table, key)) {
                    table->remove(table, key);
                    printf("Elemento removido.\n");
                } else {
                    printf("Chave nao encontrada.\n");
                }

                break;
            }

            case 4:
                table->print(table);
                break;

            case 5:
                printf("Quantidade de elementos: %d\n", table->size);
                break;

            case 0:
                printf("Encerrando programa...\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }

    } while (op != 0);

    table->destroy(table);

    return 0;
}
