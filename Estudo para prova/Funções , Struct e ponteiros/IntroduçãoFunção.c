#include <stdio.h>
#include <stdlib.h>

void imprimirSaudaca(){
    printf("=====================================");
    printf("BEM VINDO !");
    printf("=====================================");
}

int somar(num1, num2){
    int resultado = num1 + num2;

    return resultado;
}

int main() {
    int v1, v2, resultado;

    printf("Digite dois numeros (separados por espaco): ");
    scanf("%d %d", &v1, &v2);
    printf("A soma deu: %d\n", somar(v1,v2));

   


    return 0;
}