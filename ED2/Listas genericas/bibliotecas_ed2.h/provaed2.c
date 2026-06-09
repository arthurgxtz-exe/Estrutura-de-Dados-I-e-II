#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "list.h"

enum { REGISTRAR, TIPOS, POR, ENUM };

void exercicio1(void) {
    List lst = new_List();

    lst->enqueue(lst, new(TYPE1, "primeiro", 113));
    lst->enqueue(lst, new(TYPE2, "a", "b", "c"));
    lst->push(lst, new(TYPE1, "inicio", 654));
    lst->push(lst, new(TYPE2, "x", "y", "z"));

    lst->print(lst);

    List lst_temp = filter(lst, TYPE1);

    printf("\nApenas TYPE1:\n");
    lst_temp->print(lst_temp);

    lst_temp->clear(lst_temp);
    free(lst_temp);

    lst->clear(lst);
    free(lst);
}

void exercicio2(void) {
    List lst_type1 = new_List();
    List lst_type2 = new_List();

    lst_type1->enqueue(lst_type1, new(TYPE1, "um", 1));
    lst_type1->enqueue(lst_type1, new(TYPE1, "dois", 2));

    lst_type2->enqueue(lst_type2, new(TYPE2, "a", "b", "c"));
    lst_type2->enqueue(lst_type2, new(TYPE2, "d", "e", "f"));

    List lst = join(lst_type1, lst_type2);

    printf("\nJoin TYPE1 + TYPE2:\n");
    lst->print(lst);

    lst->clear(lst);
    free(lst);

    lst_type1->clear(lst_type1);
    free(lst_type1);

    lst_type2->clear(lst_type2);
    free(lst_type2);
}

int main(void) {
    exercicio1();
    exercicio2();

    return 0;
}
