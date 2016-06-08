#include "heap.h"
#include <stdio.h>

#define SIZE 15

int main() {
    THeap *f = CriarHeap(SIZE);
    int i;
    for (i = 0; i < SIZE; i++) {
        f->inserir(f, i);
    }
    f->print(f);
    return 0;
}
