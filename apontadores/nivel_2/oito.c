#include <stdio.h>

int main() {
    int a = 5;
    int b = 7;
    int* p1 = &a;
    int* p2 = &b;

    printf("O Valor de A é: %d\n", *p1);
    printf("O Valor de B é: %d\n", *p2);

    return 0;
}