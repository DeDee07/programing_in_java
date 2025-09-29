#include <stdio.h>

struct Data {
    int dia;
    int mes;
    int ano;
};

int main() {
    struct Data hoje = {1, 1, 2025};

    printf("Data é: %02d/%02d/%d\n", hoje.dia, hoje.mes, hoje.ano);

    return 0;
}