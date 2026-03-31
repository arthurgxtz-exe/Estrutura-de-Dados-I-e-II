#include <stdio.h>
#include <stdlib.h>

long long fibonacci_rec(int n){
	if( n <= 2) return 1;
	else
	return fibonacci_rec(n -1 ) + fibonacci_rec(n - 2);
		
}
long long fibonacci_dinamico(int n, long long *memoria){
	
	if(n <= 2){
		return 1;
	}
	
	if(memoria[n] != 0){
		return memoria[n];
	}
	
	memoria[n] = fibonacci_dinamico(n -1, memoria) + fibonacci_dinamico(n -2, memoria);
	
	return memoria[n];
		
}
long long fibonacci_iterativo(int n){
	
	if( n <= 2){
		return 1;
		
	}
	else{
		
		long long anterior = 1;
		long long atual = 1;
		long long proximo = 0;
	
		for(int i = 3; i <= n; i++){
			proximo = anterior + atual; 
			anterior = atual;
			anterior = atual;
			atual = proximo;
		}
	
		return atual;
	}
}

int main(){
	
	int n;
	
	printf("Digite o n do termo:\n");
	scanf("%d", &n);
	
	long long *memoria = (long long *) malloc((n + 1) * sizeof(long long));
	
	if(memoria == NULL){
		printf("Erro ao alocar a memoria!\n");
	}
	
	for(int i = 0; i <= n; i++){
		
		memoria[i] = 0;
	}
	
	printf("Alocação Dinamica: %lld\n", fibonacci_dinamico(n, memoria));
	printf("Iterativo: %lld \n", fibonacci_iterativo(n));
	printf("Recursivo: %lld \n", fibonacci_rec(n));

	
	free(memoria);
	
	
	return 0;
}

