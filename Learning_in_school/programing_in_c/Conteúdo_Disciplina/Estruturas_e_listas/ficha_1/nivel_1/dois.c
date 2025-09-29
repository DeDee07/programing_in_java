#include <stdio.h>

int main() {
    int x = 3;
    int y = 4;
    int* p1 = &x;
    int* p2 = &y;

    printf("O valor de X é: %d\n", *p1);
    printf("O valor de Y é: %d\n", *p2);

    return 0;
}