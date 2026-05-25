#ifndef OBJECT_H
#define OBJECT_H

typedef struct Node{
    void* item;
    struct Node* left;
    struct Node* right;

}Node;
typedef Node* Object;

Object new_Object(void* dado);
void destroy(Object obj);

#endif

