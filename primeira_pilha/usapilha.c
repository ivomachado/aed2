#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    TPilha *p = CriarPilha();
    char vet[10] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
    for (int i = 0; i < 10; i++) {
        char *var = (char *)malloc(sizeof(char));
        *var = vet[i];
        p->empilhar(p, var);
    }
    while (!p->vazia(p))
        printf("%c\n", *(char *)p->desempilhar(p));
    return 0;
}
