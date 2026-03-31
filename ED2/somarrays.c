#include <stdio.h>
#include <stdlib.h>

int somaArray(int vet[], int tam){
	
	if(tam == 0){
		return  0;
	}
	else{
		return vet[tam - 1] + somaArray(vet, tam - 1);
	}

}

int main(int argc, char **argv)
{
	int vet[3] = {10, 20, 30};
	
	printf("%d",somaArray(vet, 3));
	
	return 0;
}

