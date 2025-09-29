#include <stdio.h>

struct Aluno {
    float media;
    char* nome;
    int numero;
};

int main() {
    struct Aluno a1 = {8.75, "João Silva", 1};
    struct Aluno a2 = {10.95, "Leandro Oliveira", 2};

    printf("O nome é %s e número é %d e a sua média é %.2f\n", a1.nome, a1.numero, a1.media);
    printf("O nome é %s e número é %d e a sua média é %.2f\n", a2.nome, a2.numero, a2.media);

    a1.media = 17.5;
    
    printf("O nome é %s e a sua média é %.2f\n", a1.nome, a1.media);

    return 0;
}