#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

#define SIZE 12

void print(void* v)
{
    printf("%d____\n", *(int*)v);
}

typedef struct Int TInt;

typedef int (*TCompara)(void*, void*);


struct Int {
    int value;
    TCompara compara;
};

int comparar(void* a, void* b)
{
    return ((TInt*)a)->value - ((TInt *)b)->value;
}

TInt * CriarInt(int value)
{
    TInt *elem = (TInt *)malloc(sizeof(TInt));
    elem->value = value;
    elem->compara = comparar;
    return elem;
}

int main()
{
    THeap* f = CriarHeap();
    int oi[SIZE];
    int i;
    TInt* var;
    for (i = 1; i <= SIZE; i++) {
        var = CriarInt(i);
        f->inserir(f, var);
    }

    for (i = 0; i < SIZE; i++) {
        oi[SIZE - i - 1] = ((TInt*)f->topo(f))->value;
        f->remover(f);
    }
    for (i = 0; i < SIZE; i++) {
        printf("%d ", oi[i]);
    }
    return 0;
}
