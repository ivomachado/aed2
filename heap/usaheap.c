#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

#define SIZE 6

void print(void* v)
{
    printf("%d____\n", *(int*)v);
}

int comparar(void* a, void* b)
{
    return *(int*)a - *(int*)b;
}

int main()
{
    THeap* f = CriarHeap(SIZE, print, comparar);
    int oi[SIZE];
    int i;
    int* var;
    for (i = 1; i <= SIZE; i++) {
        var = (int*)malloc(sizeof(int));
        *var = i;
        f->inserir(f, var);
        f->print(f);
    }

    for (i = 0; i < SIZE; i++) {
        oi[SIZE - i - 1] = *(int*)f->topo(f);
        f->remover(f);
    }
    for (i = 0; i < SIZE; i++) {
        printf("%d ", oi[i]);
    }
    return 0;
}
