#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

//definindo uma interface padrão para funções construtoras
#define new(TYPE,...) new_##TYPE(__VA_ARGS__)

typedef struct __Object{
	void* item;
	struct __Object* left;
	struct __Object* right;
}__Object;
typedef __Object* Object;

typedef struct{
	char nome[100];
	int power;
}__Item;
typedef __Item* Item;

typedef struct{
	char nome[100];
	int hp;
}__Player;
typedef __Player* Player;

Object new_Object(){
	Object obj = malloc(sizeof(__Object));
	return obj;
}

Object new_Player(char* nome, int hp){
	Object obj = new(Object);
	Player n = malloc(sizeof(__Player));
	obj->item = n;
	strcpy(n->nome,nome);
	n->hp = hp;
	return obj;
}

Object new_Item(char* nome, int power){
	Object obj = malloc(sizeof(__Object));
	Item n = malloc(sizeof(__Item));
	obj->item = n;
	strcpy(n->nome,nome);
	n->power = power;
	return obj;
}

int main(){
	List lst = new(List);
		
	Object arma = new(Item,"arma",50);
	
	lst.append(arma);
	
	lst.print();
	
	
}
