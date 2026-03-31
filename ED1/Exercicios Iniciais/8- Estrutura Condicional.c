#include <stdio.h>
#include <stdlib.h>

int main() {
    
    int a, b, c, temp;

    printf("Digite 3 valores inteiros separados por espaço:");
    scanf("%d %d %d", &a, &b, &c);

    //Usando uma cadeia de If/Else para testar todas as 6 combinações possíveis(jeito mais brutoe menos eficiente).
    {
    if(a > b && b > c)
    {
        printf("Ordem Decrescente: %d, %d, %d\n", a, b, c);
    }
    else 
    if(a > c && c > b)
    {
        printf("Ordem Decrescente: %d, %d, %d\n", a, c, b);
    }
    else 
    if(b > a && a > c)
    {
        printf("Ordem Decrescente: %d, %d, %d\n", b, a, c);

    }
    else
    if(b > c && c > a)
    {
        printf("Ordem Decrescente: %d, %d, %d\n", b, c, a);
    }
    else 
    if(c > b && b > a)
    {
        printf("Ordem Decrescente: %d, %d, %d\n", c, b, a);
    }
    else 
        printf("Ordem Decrescente: %d, %d, %d\n", c, a, b);
    if(a < b && b < c)
    {
        printf("Ordem Crescente: %d, %d, %d\n", a, b, c);
    }
    else 
    if(a < c && c < b)
    {
        printf("Ordem Crescente: %d, %d, %d\n", a, c, b);
    }
    else 
    if(b < a && a < c)
    {
        printf("Ordem Crescente: %d, %d, %d\n", b, a, c);

    }
    else
    if(b < c && c < a)
    {
        printf("Ordem Crescente: %d, %d, %d\n", b, c, a);
    }
    else 
    if(c < b && b < a)
    {
        printf("Ordem Crescente: %d, %d, %d\n", c, b, a);
    }
    else 
        printf("Ordem Crescente: %d, %d, %d\n", c, a, b);
}

    //Método usando a Lógica de Ordenação com "Swap ou trocas". Com essa técnica, podemos ordenar a, b e c com apenas 3 verificações if simples.
    if(a > b)
    {
        temp = a;
        a = b; 
        b = temp;
    }
    if(a > c)
    {
        temp = a;
        a = c;
        c = temp;
    }
    if(b > c)   
    {
        temp = b;
        b = c;
        c = temp;
    }

    printf("\nUsando método de trocas:\n");
    printf("Ordem Crescente: %d, %d, %d\n", a, b, c);
    printf("Ordem Derescente: %d, %d, %d\n", c, b, a);
      
return 0;
}