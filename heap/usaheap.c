#include "heap.h"
#include <stdio.h>

#define SIZE 10

int main() {
    THeap *f = CriarHeap(SIZE);
    int oi[SIZE];
    int i;
    for (i = 0; i < SIZE; i++) {
        f->inserir(f, i);
    }
    f->print(f);

    for (i = 0; i < SIZE; i++) {
        oi[SIZE - i - 1] = f->topo(f);
        f->remover(f);
    }
    for (i = 0; i < SIZE; i++) {
        printf("%d ", oi[i]);
    }
    return 0;
}
