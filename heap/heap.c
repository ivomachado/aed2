#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int ocupacao;
    int tamanho;
    void** vetor;
    TComparar comparar;
    TPrintInterno print;
} TDado;

static void Inserir(THeap* h, void* elemento)
{
    TDado* d = (TDado*)h->dado;
    int i = d->ocupacao, pai;
    void* aux;
    if (i < d->tamanho) {
        printf("%d\n", i);
        d->vetor[i] = elemento;
        d->ocupacao++;
        pai = (i - 1) / 2;
        while (d->comparar(d->vetor[pai], d->vetor[i]) < 0) {
            printf("%d %d %d %d\n", *(int*)d->vetor[pai], *(int*)d->vetor[i], pai, i);
            aux = d->vetor[pai];
            d->vetor[pai] = d->vetor[i];
            d->vetor[i] = aux;
            i = pai;
            pai = (i - 1) / 2;
        }
    }
}

static void _print(TDado* d, int level, int pos)
{
    int i;
    for (i = 0; i < level; i++) {
        printf("     ");
    }
    if (d->ocupacao > pos) {
        d->print(d->vetor[pos]);
        // printf("%d_(%d)_\n", d->vetor[pos], pos);
        _print(d, level + 1, pos * 2 + 1);
        _print(d, level + 1, pos * 2 + 2);
    } else {
        printf("*\n");
    }
}

static void Print(THeap* h)
{
    TDado* d = (TDado*)h->dado;
    _print(d, 0, 0);
}

static void* Topo(THeap* h)
{
    TDado* d = (TDado*)h->dado;
    return d->vetor[0];
}

static void Remover(THeap* h)
{
    TDado* d = (TDado*)h->dado;
    void* elemento = d->vetor[0];
    int pos = 0;
    int i = 0;
    d->ocupacao--;
    d->vetor[0] = d->vetor[d->ocupacao];
    d->vetor[d->ocupacao] = elemento;
    while ((i * 2 + 1) < d->ocupacao) {
        if (d->comparar(d->vetor[i], d->vetor[i * 2 + 1]) < 0) {
            pos = i * 2 + 1;
        }
        if (i * 2 + 2 < d->ocupacao && d->comparar(d->vetor[pos], d->vetor[i * 2 + 2]) < 0) {
            pos = i * 2 + 2;
        }

        if (pos != i) {
            elemento = d->vetor[i];
            d->vetor[i] = d->vetor[pos];
            d->vetor[pos] = elemento;
            i = pos;
        } else {
            i = d->tamanho;
        }
    }
}

THeap* CriarHeap(int tam, TPrintInterno _print, TComparar comparar)
{
    TDado* d = (TDado*)malloc(sizeof(TDado));
    THeap* heap = (THeap*)malloc(sizeof(THeap));

    d->ocupacao = 0;
    d->tamanho = tam;
    d->vetor = (void**)malloc(sizeof(void*) * tam);
    d->print = _print;
    d->comparar = comparar;

    heap->dado = d;
    heap->inserir = Inserir;
    heap->print = Print;
    heap->remover = Remover;
    heap->topo = Topo;
    return heap;
}
