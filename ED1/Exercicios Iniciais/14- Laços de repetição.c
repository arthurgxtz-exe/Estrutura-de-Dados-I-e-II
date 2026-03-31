#include <stdio.h>
#include <stdlib.h>

int main(){

    int n;

    printf("Digite o numero inicial de * : ");
    scanf("%d", &n);

for (int i = n; i >= 1; i--)
    {
        for(int j = 1; j <= i; j++)
        {
            printf("*");
        }
        printf("\n");
    }

    return 0;

}
