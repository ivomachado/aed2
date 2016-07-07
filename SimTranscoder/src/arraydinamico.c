#include "arraydinamico.h"
#include <math.h>
#include <stdlib.h>

typedef struct{
	void **_dado;
	int tamanho;
} TDado;

static void** ajustar(void *_add, int novoTamanho){
	TDado *d=_add;
	void **novo = malloc(sizeof(void*)*novoTamanho);
	int i;
	for (i=0;i< d->tamanho;i++)
        novo[i] = d->_dado[i];
	free(d->_dado);
	return novo;
}
static void* acessar(TArrayDinamico* ad, int pos){
	TDado *dado = ad->dado;
	return dado->_dado[pos];
}
static int atualizar(TArrayDinamico* ad, int pos, void* elemento){
	TDado *d = ad->dado;
	int k, novoTamanho = 0;
	if (pos >= d->tamanho){
		k = floor(log2(pos)) + 1;
		novoTamanho = (int)pow(2,k);
		d->_dado = ajustar(d, novoTamanho);
		d->tamanho = novoTamanho;
	}
	d->_dado[pos] = elemento;
	return novoTamanho;
}
static int tamanho(TArrayDinamico *ad){
	TDado *d = ad->dado;
	return d->tamanho;
}
static void *criarDado(){
	TDado *d = malloc(sizeof(TDado));
	d->tamanho=2;
	d->_dado = malloc(sizeof(void*)*d->tamanho);
	return d;
}

TArrayDinamico* criarArrayDinamico(){
	TArrayDinamico *ad = malloc(sizeof(TArrayDinamico));
	ad->dado = criarDado();
	ad->acessar = acessar;
	ad->atualizar = atualizar;
	ad->tamanho = tamanho;
	return ad;
}
