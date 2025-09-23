#include <stdio.h>

int main() {
    int x = 10;
    int* p = &x;

    printf("O Endereço é: %d\n", *p);

    return 0;
}