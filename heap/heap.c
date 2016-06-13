#include "heap.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int ocupacao;
    int tamanho;
    int *vetor;
} TDado;

static void Inserir(THeap *h, int elemento) {
    TDado *d = (TDado *)h->dado;
    int i = d->ocupacao, aux, pai;
    if (i < d->tamanho) {
        d->vetor[i] = elemento;
        d->ocupacao++;
        pai = (i - 1) / 2;
        while (d->vetor[pai] < d->vetor[i]) {
            aux = d->vetor[pai];
            d->vetor[pai] = d->vetor[i];
            d->vetor[i] = aux;
            i = pai;
            pai = (i - 1) / 2;
        }
    }
}

static void print(TDado *d, int level, int pos) {
    int i;
    for (i = 0; i < level; i++) {
        printf("     ");
    }
    if (d->ocupacao > pos) {
        printf("%d_(%d)_\n", d->vetor[pos], pos);
        print(d, level + 1, pos * 2 + 1);
        print(d, level + 1, pos * 2 + 2);
    } else {
        printf("*\n");
    }
}

static void Print(THeap *h) {
    TDado *d = (TDado *)h->dado;
    print(d, 0, 0);
}

static int Topo(THeap *h) {
    TDado *d = (TDado *)h->dado;
    return d->vetor[0];
}

static void Remover(THeap *h) {
    TDado *d = (TDado *)h->dado;
    int elemento = d->vetor[0];
    int pos = 0;
    int i = 0;
    d->ocupacao--;
    d->vetor[0] = d->vetor[d->ocupacao];
    d->vetor[d->ocupacao] = elemento;
    while ((i * 2 + 1) < d->ocupacao) {
        if(d->vetor[i] < d->vetor[i * 2 + 1]) {
            pos = i * 2 + 1;
        }
        if(i * 2 + 2 < d->ocupacao && d->vetor[pos] < d->vetor[i * 2 + 2]) {
            pos = i * 2 + 2;
        }

        if(pos != i) {
            elemento = d->vetor[i];
            d->vetor[i] = d->vetor[pos];
            d->vetor[pos] = elemento;
            i = pos;
        } else {
            i = d->tamanho;
        }
    }
}

THeap *CriarHeap(int tam) {
    TDado *d = (TDado *)malloc(sizeof(TDado));
    THeap *heap = (THeap *)malloc(sizeof(THeap));

    d->ocupacao = 0;
    d->tamanho = tam;
    d->vetor = (int *)malloc(sizeof(tam));

    heap->dado = d;
    heap->inserir = Inserir;
    heap->print = Print;
    heap->remover = Remover;
    heap->topo = Topo;
    return heap;
}
