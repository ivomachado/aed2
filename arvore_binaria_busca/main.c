#include "elemento.h"
#include "arvorebinariabusca.h"
#include <stdio.h>
#include <stdlib.h>

void printInteiro(void * i) {
    printf("%d\n", (int)(((TElemento*)i)->dados));
}

int compararInteiro(void *a, void *b) {
    return (int)(((TElemento*)a)->dados) - (int)(((TElemento*)b)->dados);
}

typedef struct integer TInteger;

struct integer {
    int value;
    TCompara compara;
    TImprimir imprimir;
};

TInteger * criarInteger(int value) {
    TInteger *integer = (TInteger*)malloc(sizeof(TInteger));
    integer->value = value;
    integer->compara = compararInteiro;
    integer->imprimir = printInteiro;
    return integer;
}

int main() {
    TArvoreBinariaBusca *tree = criarArvoreBinariaBusca();
    tree->inserir(tree, criarInteger(5));
    tree->inserir(tree, criarInteger(7));
    tree->inserir(tree, criarInteger(6));
    tree->inserir(tree, criarInteger(8));
    tree->inserir(tree, criarInteger(9));
    tree->inserir(tree, criarInteger(3));
    tree->inserir(tree, criarInteger(2));
    tree->inserir(tree, criarInteger(4));
    tree->inserir(tree, criarInteger(1));

    tree->imprimir(tree);
    tree->remover(tree, criarInteger(2));
    tree->imprimir(tree);
    tree->remover(tree, criarInteger(3));
    tree->imprimir(tree);

    return 0;
}
