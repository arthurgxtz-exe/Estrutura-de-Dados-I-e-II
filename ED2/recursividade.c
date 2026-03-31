#include <stdlib.h>
#include <stdio.h>


int potenciacao(int x, int y){
	if(y == 0){
		return 1;
		
	}
	else{
		return x * potenciacao(x,y -1);
	}
	
}



int main(){
	
	printf("%d\n", potenciacao(2, 3));
		
	return 0;
}

