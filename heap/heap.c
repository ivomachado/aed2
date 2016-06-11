#include "heap.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int ocupacao;
    int tamanho;
    int *vetor;
} TDado;

static void Inserir(THeap *h, int elemento) {
    TDado *d = (TDado *)h->dado;
    int i = d->ocupacao, aux, pai;
    if(i < d->tamanho) {
        d->vetor[i] = elemento;
        d->ocupacao++;
        pai = (i-1)/2;
        while(d->vetor[pai] < d->vetor[i]) {
            aux = d->vetor[pai];
            d->vetor[pai] = d->vetor[i];
            d->vetor[i] = aux;
            i = pai;
            pai = (i-1)/2;
        }
    }
}

static void Print(THeap *h) {
    TDado *d = (TDado *)h->dado;
    int i;
    for(i = 0; i < d->ocupacao; i++) {
        printf("%d ", d->vetor[i]);
    }
    printf("\n");
}

THeap *CriarHeap(int tam) {
    TDado *d = (TDado *)malloc(sizeof(TDado));
    THeap *heap = (THeap *)malloc(sizeof(THeap));

    d->ocupacao = 0;
    d->tamanho = tam;
    d->vetor = (int *) malloc(sizeof(tam));

    heap->dado = d;
    heap->inserir = Inserir;
    heap->print = Print;

    return heap;
}
