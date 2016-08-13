#include "no.h"

typedef struct arvorebinariabusca TArvoreBinariaBusca;

typedef void (*TInserirABB)(TArvoreBinariaBusca *, void *);
typedef int (*TBuscarABB)(TArvoreBinariaBusca *, void *);
typedef void (*TRemoverABB)(TArvoreBinariaBusca *, void *);
typedef void (*TImprimirABB)(TArvoreBinariaBusca*);

TArvoreBinariaBusca * criarArvoreBinariaBusca();

struct arvorebinariabusca {
    void * dados;
    TInserirABB inserir;
    TBuscarABB buscar;
    TRemoverABB remover;
    TImprimirABB imprimir;
};
