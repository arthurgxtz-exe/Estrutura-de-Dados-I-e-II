#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "object.h"
#include "list.h"

typedef struct{
   char nome[50];
   int matricula;
   int nota;
}Aluno;

typedef struct{
    char titulo[50];
    char autor[50];
    int num_paginas;
}Livro;


void print_LIVRO(Object self, int position){
    Livro* livro = (Livro*) self->item;

    printf("[%d] LIVRO | titulo: %s | autor: %s | n° de paginas: %d\n", 
    position,
    livro->titulo, 
    livro->autor,
    livro->num_paginas);
}

Object new_LIVRO(char titulo[], char autor[], int num_paginas){
    Object obj = new_Object();

    Livro* livro = malloc(sizeof(Livro));

    strcpy(livro->titulo, titulo);
    strcpy(livro->autor, autor);
    livro->num_paginas = num_paginas;

    obj->item = livro;
    obj->owns_item = 1;
    obj->type = LIVRO;
    obj->print = print_LIVRO;
    obj->destroy = destroy_Object;

    return obj;
}
void print_ALUNO(Object self, int position){
    Aluno* aluno = (Aluno*) self->item;

    printf("[%d] ALUNO | nome: %s | matricula: %d | nota: %d\n", position, aluno->nome, aluno->matricula, aluno->nota);
}

Object new_ALUNO(char nome[], int matricula, int nota){
    Object obj = new_Object();

    Aluno* aluno = malloc(sizeof(Aluno));

    strcpy(aluno->nome, nome);
    aluno->matricula = matricula;
    aluno->nota = nota;

    obj->item = aluno;
    obj->owns_item = 1;
    obj->type = ALUNO;
    obj->print = print_ALUNO;
    obj->destroy = destroy_Object;
    
    return obj;
}


int menu(){
    int op;
    printf("--- MENU ---\n");
    printf("1 - Cadastrar aluno no final\n");
    printf("2 - Cadastrtar livro no inicio\n");
    printf("3 - Imprimir lista\n");
    printf("4 - Inverter a lista\n");
    printf("5 - Imprimir alunos por nota minima\n");
    printf("6 - Mostrar objeto por posicao\n");
    printf("7 - Excluir objeto por posicao\n");
    printf("0 - Sair\n");
    scanf("%d", &op);

    return op;
}

void reverse(List lista) {
    if (!lista || lista->size <= 1) {
        return;
    }

    List temporaria = new(List);
    int tamanho = lista->size;

    for (int i = 0; i < tamanho; i++) {
        Object removido = lista->pop(lista);
        temporaria->push(temporaria, removido);
    }

    lista->head = temporaria->head;
    lista->tail = temporaria->tail;
    lista->size = temporaria->size;

    temporaria->head = NULL;
    temporaria->tail = NULL;
    temporaria->size = 0;

    free(temporaria);
}
void print_Alunos_Nota_min(List lista, int nota_minima){
    Object atual = lista->head;

    int position = 0;

    while(atual){
        if(atual->type == ALUNO){
            Aluno* aluno = (Aluno*) atual->item;

            if(aluno->nota >= nota_minima){
                atual->print(atual, position);
            }
        }
        atual = atual->next;
        position++;
    }

}
int main() {

    List lista = new(List);
    int op;

    do{
        op = menu();

        switch(op){
            case 1:{
                char nome[50];
                int matricula;
                int nota;
                printf("\nCadastrar aluno\n");
                printf("Nome: \n");
                scanf(" %[^\n]", nome);
                printf("Matricula: \n");
                scanf("%d", &matricula);
                printf("Nota: \n");
                scanf("%d", &nota);
                lista->enqueue(lista, new(ALUNO, nome, matricula, nota));
                printf("Aluno cadastrado com sucesso!\n");
                break;
            }
            case 2:{
                char titulo[50];
                char autor[50];
                int num_pag;
                printf("\nCadastrar livro\n");
                printf("Titulo: \n");
                scanf(" %[^\n]", titulo);
                printf("Autor: \n");
                scanf(" %[^\n]", autor);
                printf("N° de paginas: \n");
                scanf("%d", &num_pag);
                lista->push(lista, new(LIVRO, titulo, autor, num_pag));

                break;
            }
            case 3: 
                lista->print(lista);
                break;
            case 4:
                reverse(lista);
                printf("Lista invertida com sucesso!\n");
                break;
            case 5:{
                int nota_min;
                printf("Nota Minima: \n");
                scanf("%d", &nota_min);
                print_Alunos_Nota_min(lista, nota_min);
                break;
            }
            case 6:{
                int pos;

                printf("Posição: \n");
                scanf("%d", &pos);

                Object obj = lista->get(lista, pos);
                if(obj){
                    obj->print(obj, pos);

                }
                else{

                    printf("Posição invalida.\n");
                }
                break;
            }
            case 7: {
                int pos;

                printf("Posicao para excluir: ");
                scanf("%d", &pos);

                Object obj = lista->get(lista, pos);

                if (obj) {
                lista->del(lista, pos);
                printf("Objeto excluido com sucesso!\n");
                } else 
                {
                printf("Posicao invalida.\n");
                }

                break;
            }
            case 0:
                printf("Encerrando programa...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }

    }while(op != 0);

    lista->clear(lista);
    free(lista);

    return 0;
}