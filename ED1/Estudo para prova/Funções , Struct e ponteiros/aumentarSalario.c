#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char nome[50];
    int idade;
    float salario;

}Funcionario;

void aplicarDesconto(float *salario){
    float desconto = *salario * (10.0/100);
    *salario = *salario - desconto;
}

void FichaDesconto(Funcionario *F, int i) {
    printf("\n--- Ficha do Funcionario %d---\n", i + 1);
    printf("Nome: %s\n", F->nome);
    printf("Idade: %d\n", F->idade);
    printf("Salário: R$ %.f\n", F->salario);
}
int main() {

    int n;

    printf("Quantos funcionarios deseja cadastrar:\n");
    scanf("%d", &n);

    Funcionario funcionarios[n];

    for(int i = 0; i < n; i++){
        while(getchar()!= '\n');
        printf("\n==== Ficha do funcionario %d: ====\n", i + 1);
        printf("Nome:\n");
        scanf("%[^\n]", funcionarios[i].nome);
        printf("Idade:\n");
        scanf("%d", &funcionarios[i].idade);
        printf("Salário:\n");
        scanf("%f", &funcionarios[i].salario);
    }

    printf("\nSalário de cada funcionario após o desconto de 10%%:\n");
    for(int i = 0; i < n; i++){
        aplicarDesconto(&funcionarios[i].salario);
        FichaDesconto(&funcionarios[i], i);
    }
    return 0;
}