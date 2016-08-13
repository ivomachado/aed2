#include "arvorebinariabusca.h"
#include "elemento.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    TNo * raiz;
    int tam;
}TDadoABB;

static TNo * _inserir(TNo *no, TNo *pai, void * info) {
    TElemento *c = (TElemento*)info;

    if(no == NULL) {
        no = CriarNo(info, pai);
    } else {
        if(c->compara(info, no->info) > 0) {
            no->dir = _inserir(no->dir, no, info);
        } else {
            no->esq = _inserir(no->esq, no, info);
        }
    }
    return no;
}

static void inserir(TArvoreBinariaBusca *tree, void *info) {
    TDadoABB *d = (TDadoABB*)tree->dados;
    d->raiz = _inserir(d->raiz, NULL, info);
}

static TNo * _buscar(TNo *no, TComparavel * chave) {
    if(no != NULL) {
        int comparacao = chave->compara(chave, no->info); 
        if(comparacao > 0) {
            no = _buscar(no->dir, chave);
        } else {
            if(comparacao < 0) {
                no = _buscar(no->esq, chave);
            }
        }
    }
    return no;
}

static int buscar(TArvoreBinariaBusca *tree, void *chave) {
    TDadoABB *d = (TDadoABB*)tree->dados;
    return !!_buscar(d->raiz, (TComparavel*)chave);
}

static void * _remover (TNo * no, TDadoABB *d, TComparavel *chave) {
    if(no != NULL) {
        int comparacao = chave->compara(chave, no->info); 
        if( comparacao > 0) {
            no->dir = _remover(no->dir, d, chave);
        } else {
            if(comparacao < 0) {
                no->esq = _remover(no->esq, d, chave);
            } else {
                if(!no->esq && !no->dir) {
                    free(no);
                    no = NULL;
                } else {
                    d->tam--;
                    if(no->dir && no->esq) {
                        TNo * replacement = no->esq;
                        TNo * paiReplacement = no->esq, * aux;
                        while(replacement->dir != NULL) {
                            paiReplacement = replacement;
                            replacement = replacement->dir;
                        }
                        aux = replacement->esq;
                        replacement->dir = no->dir;
                        replacement->esq = no->esq;
                        replacement->pai = no->pai;
                        no->esq = aux;
                        no->dir = NULL;
                        no->pai = paiReplacement;
                        d->tam++;
                        if(paiReplacement == replacement)
                            replacement->esq = _remover(no, d, no->info);
                        else
                            paiReplacement->dir = _remover(no, d, no->info);
                        no = replacement;
                    } else {
                        if(no->dir) {
                            no->dir->pai = no->pai;
                            no = no->dir;
                        } else {
                            no->esq->pai = no->pai;
                            no = no->esq;
                        }
                    }
                }
            }
        }
    }
    return no;
}

static void remover(TArvoreBinariaBusca *tree, void *chave) {
    TDadoABB *d = (TDadoABB*)tree->dados;
    d->raiz = _remover(d->raiz, d, (TComparavel*)chave);
}

static void _imprimir(TNo *no, int level) {
    if(no != NULL) {
        for(int i = 0; i < level*4; i++) {
            printf(" ");
        }
        ((TElemento*)no->info)->imprimir(no->info);
        _imprimir(no->esq, level + 1);
        _imprimir(no->dir, level + 1);
    } else {
        for(int i = 0; i < level*4; i++) {
            printf(" ");
        }
        printf("*\n");
    }
}

static void imprimir(TArvoreBinariaBusca *tree) {
    TDadoABB *d = (TDadoABB*)tree->dados;

    _imprimir(d->raiz, 0);
}


static TDadoABB * criarDado() {
    TDadoABB *d = (TDadoABB*)malloc(sizeof(TDadoABB));
    d->raiz = NULL;
    d->tam = 0;
    return d;
}

TArvoreBinariaBusca * criarArvoreBinariaBusca() {
    TArvoreBinariaBusca *tree = (TArvoreBinariaBusca*)malloc(sizeof(TArvoreBinariaBusca));
    tree->dados = criarDado();
    tree->inserir = inserir;
    tree->buscar = buscar;
    tree->remover = remover;
    tree->imprimir = imprimir;
    return tree;
}
