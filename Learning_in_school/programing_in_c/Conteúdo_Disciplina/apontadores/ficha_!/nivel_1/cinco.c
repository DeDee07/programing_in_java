#include <stdio.h>

int main() {
    char c = 'A';
    char* pc = &c;

    printf("O Endereço é: %c\n", *pc);

    return 0;
}