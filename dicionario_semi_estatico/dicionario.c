#include "dicionario.h"
#include "comparavel.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct dado {
    void** dado;

    int tam;
    int fatorCarga;
    int fatorAgrupamento;
} TDadoDicionario;

TDadoDicionario* criarDado(int tam, double fc)
{
    TDadoDicionario* d = (TDadoDicionario*)malloc(sizeof(TDadoDicionario));
    d->tam = tam * (2.0 - fc);
    d->fatorCarga = fc;
    d->fatorAgrupamento = 0.0;

    // armazena a informação
    d->dado = malloc(sizeof(void*) * d->tam);

    return d;
}

static int hash(int k, int m)
{
    return (k % m);
}

static short evaluation(TDicionario *d) {
    TDadoDicionario *dd = d->dado;
    int sumXi = 0;
    int amostras = sqrt(dd->tam);
    srand(time(NULL));
    do {
        int posi = rand() % dd->tam; // TODO: tem que resolver
        int i = 0;
        TComparavel *e;
        do {
            int posc = (posi + i)%dd->tam;
            i++;
            e = dd->dado[posc];
        }while(e!=NULL);
        int Xi = i - 1;
        sumXi = sumXi + Xi*Xi;
        amostras--;
    }while(amostras); // TODO: tem qeu resolverx
    double n = sqrt(dd->tam - 1);
    dd->fatorAgrupamento = (double) (sumXi)/(n - 1) - dd->fatorCarga;
}

static void* buscar(TDicionario* d, int k)
{
    TDadoDicionario* dd = d->dado;

    int posi = hash(k, dd->tam);
    int posc = posi;
    int i = 0;

    TComparavel* elemento;
    int encontrou = 0;
    do {
        elemento = dd->dado[posi];
        posc = (posi + i) % dd->tam;
        i++;
    } while ((elemento != NULL) && (elemento->compara(elemento, &k)));
    return elemento;
}

static void *inserir(TDicionario *d, int k, void *e)
{
    TDadoDicionario *dd = d->dado;
    int posi = hash(k, dd->tam);
    int posc = posi;
    int i = 0;

    while(dd->dado[posc] != NULL) {
        posc = (posi + i) % dd->tam;
        i++;
    }

	// dd->
}

TDicionario *criarDicionario(int tam)
{
    TDadoDicionario* d = criarDado(tam, 0.8);
    TDicionario *dict = malloc(sizeof(TDicionario));
    dict->buscar = buscar;
    dict->inserir = inserir;
}
