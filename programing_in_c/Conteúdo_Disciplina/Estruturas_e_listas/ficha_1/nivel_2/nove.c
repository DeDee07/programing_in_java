#include <stdio.h>

int main() {
    int largura = 20;
    int altura = 10;
    int* p1 = &largura;
    int* p2 = &altura;

    printf("Largura é: %d\n", largura);
    printf("Altura é: %d\n", altura);
    
    int area = largura * altura;
    printf("Área é: %d\n", area);
    
    int area_com_ponteiros = (*p1) * (*p2);
    printf("Área (usando ponteiros) é: %d\n", area_com_ponteiros);
    
    return 0;
}