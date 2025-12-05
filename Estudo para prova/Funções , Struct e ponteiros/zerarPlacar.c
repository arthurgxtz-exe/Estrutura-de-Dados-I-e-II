#include <stdio.h>
#include <stdlib.h>

void anularGols(int *placar){
    *placar = 0;
}

int main() {
    int placar_adv = 3;
    
    printf("Valor do placar antes de ser anulado: %d\n", placar_adv);
    anularGols(&placar_adv);
    printf("Valor do placar depois de ser anulado: %d\n", placar_adv);

    return 0;
}