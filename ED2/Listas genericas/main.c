#include <stdio.h>
#include <stdlib.h>
#include "object.h"
#include "list.h"

Object new_Object(void* dado){
    Object novo = malloc(sizeof(Node));
    if(novo){
        novo->item = dado; 
        novo->left = NULL;
        novo->right = NULL;
        return novo;
    }
    else{
        printf("Erro ao alocar memoria\n");
        return NULL;
    }
}
List new_List(){
    List l = malloc(sizeof(_List));
    if(l){
        l->head = NULL;
        l->tail = NULL;
        l->size = 0;
        return l;
    }
    else{
        printf("Erro ao alocar memoria\n");
        return NULL;
    }
}

void list_push(List l, Object obj){
    
}
int main() {

    

    return 0;
}