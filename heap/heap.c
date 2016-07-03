#include "heap.h"
#include "arraydinamico.h"
#include "comparavel.h"
#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int ocupacao;
    TArrayDinamico* vetor;
} TDado;

static int Inserir(THeap* h, void* elemento)
{
    TDado* d = (TDado*)h->dado;
    int i = d->ocupacao, pai;
    void* aux;
    int movs = 0;
    TComparavel* comparavel = (TComparavel*)elemento;
    printf("%d\n", i);
    d->vetor->atualizar(d->vetor, i, elemento);
    d->ocupacao++;
    pai = (i - 1) / 2;
    while (comparavel->compara(d->vetor->acessar(d->vetor, pai), d->vetor->acessar(d->vetor, i)) < 0) {
        aux = d->vetor->acessar(d->vetor, pai);
        d->vetor->atualizar(d->vetor, pai, d->vetor->acessar(d->vetor, i));
        d->vetor->atualizar(d->vetor, i, aux);
        i = pai;
        pai = (i - 1) / 2;
    }
    return movs;
}

static void* Topo(THeap* h)
{
    TDado* d = (TDado*)h->dado;
    return d->vetor->acessar(d->vetor, 0);
}

static int Remover(THeap* h)
{
    TDado* d = (TDado*)h->dado;
    TComparavel* comparavel = d->vetor->acessar(d->vetor, 0);
    void *aux;
    int pos = 0;
    int i = 0;
    void movs = 0;
    d->ocupacao--;
    d->vetor->atualizar(d->vetor, 0, d->vetor->acessar(d->vetor, d->ocupacao));
    d->vetor->atualizar(d->vetor, d->ocupacao, comparavel);
    while ((i * 2 + 1) < d->ocupacao) {
        if (comparavel->compara(d->vetor->acessar(d->vetor, i), d->vetor->acessar(d->vetor, i * 2 + 1)) < 0) {
            pos = i * 2 + 1;
        }
        if (i * 2 + 2 < d->ocupacao && comparavel->compara(d->vetor->acessar(d->vetor, pos), d->vetor->acessar(d->vetor, i * 2 + 2)) < 0) {
            pos = i * 2 + 2;
        }

        if (pos != i) {
            aux = d->vetor->acessar(d->vetor, i);
            d->vetor->atualizar(d->vetor, i, d->vetor->acessar(d->vetor, pos));
            d->vetor->atualizar(d->vetor, pos, aux);
            i = pos;
        } else {
            i = d->ocupacao;
        }
    }
    return movs;
}

THeap *CriarHeap()
{
    TDado* d = (TDado*)malloc(sizeof(TDado));
    THeap* heap = (THeap*)malloc(sizeof(THeap));

    d->ocupacao = 0;
    d->vetor = criarArrayDinamico();

    heap->dado = d;
    heap->inserir = Inserir;
    heap->remover = Remover;
    heap->topo = Topo;
    return heap;
}
