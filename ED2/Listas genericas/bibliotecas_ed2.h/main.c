#include <stdio.h>
#include <stdlib.h>
#include "object.h"
#include "list.h"

int main() {

    List lst = new(List);

    lst->enqueue(lst, new(TYPE1, "A", 113));
    lst->enqueue(lst, new(TYPE2, "B1", "B2", "B3"));

    lst->push(lst, new(TYPE1, "C", 654));
    lst->push(lst, new(TYPE2, "D1", "D2", "D3"));

    lst->print(lst);
    lst->clear(lst);
    free(lst);

    return 0;
}

