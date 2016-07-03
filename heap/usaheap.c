#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

#define SIZE 12

typedef struct Int TInt;

typedef int (*TCompara)(void*, void*);
typedef void (*TPrint)(void*);


struct Int {
    int value;
    TCompara compara;
    TPrint print;
};

void print(void * value)
{
    printf("%d", *(int*)value);
}

int comparar(void* a, void* b)
{
    return ((TInt*)a)->value - ((TInt *)b)->value;
}

TInt * CriarInt(int value)
{
    TInt *elem = (TInt *)malloc(sizeof(TInt));
    elem->value = value;
    elem->compara = comparar;
    elem->print = print;
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
