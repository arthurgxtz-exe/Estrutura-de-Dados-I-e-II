#include <stdio.h>
#include <stdlib.h>
#include "htable.h"

int menu() {
    int option;

    printf("\n--- MENU ---\n");
    printf("1 - Inserir valor\n");
    printf("2 - Buscar valor\n");
    printf("3 - Excluir valor\n");
    printf("4 - Imprimir tabela\n");
    printf("5 - Mostrar quantidade\n");
    printf("0 - Sair\n");
    printf("Opcao: ");
    scanf("%d", &option);

    return option;
}

int buckets(){
    int quant_buckets;

    do{
        printf("Quantidade de buckets da tabela: ");
        scanf("%d", &quant_buckets);

        if(quant_buckets <= 0){
            printf("A quantidade deve ser maior que zero.\n");
        }

    }while(quant_buckets <= 0);

    return quant_buckets;
}

int main() {
   
    HTable ht = new(HTable, buckets());
    int option;

    if (!ht)
        return 1;
      

    do {
        option = menu();

        switch (option) {
            case 1: {
                int value;

                printf("Valor: ");
                scanf("%d", &value);

                ht->insert(ht, value);
                break;
            }

            case 2: {
                int value;
                Object found;

                printf("Valor para buscar: ");
                scanf("%d", &value);

                found = ht->search(ht, value);

                if (found)
                    printf("Valor %d encontrado.\n", value);
                else
                    printf("Valor %d nao encontrado.\n", value);

                break;
            }

            case 3: {
                int value;

                printf("Valor para excluir: ");
                scanf("%d", &value);

                ht->delete(ht, value);
                break;
            }

            case 4:
                ht->print(ht);
                break;

            case 5:
                printf("Quantidade de elementos: %d\n", ht->count);
                break;

            case 0:
                printf("Encerrando programa...\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }

    } while (option != 0);

    ht->destroy(ht);

    return 0;
}
