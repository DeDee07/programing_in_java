#include <stdio.h>

struct aluno {
    char nome[50];
    int idade;
    float media;
};

int main() {
    char *nome = "André Andrade Gomes";
    int idade = 16;
    float media = 15.6f;

    printf("O Seu Nome é: %s\n", nome);
    printf("A Sua Idade é: %d\n", idade);
    printf("E a Sua Média é: %f\n", media);

    return 0;
}