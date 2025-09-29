#include <stdio.h>

struct Aluno {
    float media;
    char nome[50];
    int numero;
};

int main() {
    struct Aluno a1 = {8.75, "João Silva", 1};
    
    printf("Média: %.2f\n", a1.media);
    printf("Nome: %s\n", a1.nome);
    printf("Número: %d\n", a1.numero);
    
    return 0;
}