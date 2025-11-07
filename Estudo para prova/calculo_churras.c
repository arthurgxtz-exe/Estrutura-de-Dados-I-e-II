#include <stdio.h>

int main() {
    int pessoas;
    float precoCarne, precoLinguica, precoRefri;
    float totalCarne, totalLinguica, totalRefri, totalGeral, valorPorPessoa;

    
    printf("Quantas pessoas vao para o churrasco? ");
    scanf("%d", &pessoas);

    printf("Preco do kg da carne: R$ ");
    scanf("%f", &precoCarne);

    printf("Preco do kg da linguica: R$ ");
    scanf("%f", &precoLinguica);

    printf("Preco do refrigerante (por litro): R$ ");
    scanf("%f", &precoRefri);

    
    float carnePorPessoa = 0.4;     // kg
    float linguicaPorPessoa = 0.2;  // kg
    float refriPorPessoa = 1.0;     // litro

    
    totalCarne = pessoas * carnePorPessoa * precoCarne;
    totalLinguica = pessoas * linguicaPorPessoa * precoLinguica;
    totalRefri = pessoas * refriPorPessoa * precoRefri;

    totalGeral = totalCarne + totalLinguica + totalRefri;
    valorPorPessoa = totalGeral / pessoas;

    
    printf("\n===== RESULTADO =====\n");
    printf("Total gasto com carne: R$ %.2f\n", totalCarne);
    printf("Total gasto com linguica: R$ %.2f\n", totalLinguica);
    printf("Total gasto com refrigerante: R$ %.2f\n", totalRefri);
    printf("----------------------------\n");
    printf("Valor total do churrasco: R$ %.2f\n", totalGeral);
    printf("Cada pessoa deve contribuir com: R$ %.2f\n", valorPorPessoa);
    printf("OBS: Esse valor não leva em consideração bebidas alcólicas.")
    

    return 0;
}
