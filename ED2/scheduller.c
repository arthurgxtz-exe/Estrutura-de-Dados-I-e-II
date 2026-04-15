#include <stdio.h>
#include <stdlib.h>
#include "gconio.h"

int main(){
	
	//loop principal da aplicação
	do{
		char opcao;
		int num = 1;
		while(!kbhit(&opcao)){
			//fazer algo eterno!
			printf("%d\n",num);
			num++;
			system("sleep 1");
		}
		
		system("clear");
		printf("voce apertou a tecla %c\n",opcao);
		
	}while(1);
	
	return 0;
}

