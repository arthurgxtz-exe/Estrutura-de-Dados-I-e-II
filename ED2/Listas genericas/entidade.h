#ifndef ENTIDADE_H
#define ENTIDADE_H

#include "object.h"

typedef struct Disciplina{
    char nome[50];
    int creditos;
    int carga_horaria;

}Disciplina;

#define new(TYPE,...) new_##TYPE(__VA_ARGS__)

Object new_Disciplina(char* nome, int creditos, int carga_horaria);

void printDisciplina(void* dado);

#endif

