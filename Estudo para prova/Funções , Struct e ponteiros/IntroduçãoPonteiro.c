#include <stdio.h>
#include <stdlib.h>

void depositarBonus(int *conta){

    *conta = *conta + 500;
}

int main() {
    int saldo = 1000;

    printf("Saldo inicial: %d\n", saldo);

    depositarBonus(&saldo);

    printf("Saldo depois do bônus: %d\n", saldo);

    
    return 0;
}
