#include "fila.h"
#include <stdlib.h>
#include <stdio.h>
#include "comparavel.h"

#define NaN 0 / 0.

typedef struct{
	int inseriu;
	int removeu;
	int movimentou_insercao;
	int movimentou_remocao;
	int sobrecarregou;
} TStatsFila;

typedef struct {
	int primeiro;
	int ultimo;
	void **fila;
	int tam;
	int cont;
	TStatsFila stats;
} TDadoFila;
/** Remove o primeiro elemento da fila. Para a fila passada, o primeiro elemento
* será removido se ele existir.
* No caso da fila vazia, a operação não é realizada e um NaN é retornado.
*
* Pré-cond: Fila criada.
*
* Pós-cond: Elemento removido, se fila não estiver vazia.
*/
static void * Desenfileirar(TFila *f) {
	void * elemento;
	TDadoFila *d = (TDadoFila *)f->dado;
	if (d->cont == 0) {
		elemento = NULL;
	} else {
		elemento = d->fila[d->primeiro];
		d->primeiro = (d->primeiro + 1) % d->tam;
		d->stats.removeu++;
		d->cont--;
	}
	return elemento;
}

/**Aloca um novo vetor para a fila e transfere os elementos para este novo vetor
*
*Pré-cond: fila com ocupação máxima
*
*Pós-cond: fila com capacidade dobrada
*/
static void Estender(TFila *f) {
	TDadoFila *d = (TDadoFila *)f->dado;
	void **v = (void **)malloc(sizeof(void *) * d->tam * 2);
	int i;
	for (i = 0; i < d->tam; i++) {
		v[i] = d->fila[d->primeiro];
		d->primeiro = (d->primeiro + 1) % d->tam;
		d->stats.movimentou_insercao++;
	}
	free(d->fila);
	d->cont = d->tam;
	d->primeiro = 0;
	d->ultimo = d->tam - 1;
	d->tam *= 2;
	d->fila = v;
}

/** Insere um novo elemento na fila. Para uma fila criada
* a função irá inserir o elemento passado
* considerando a ocupação da fila. o retorno indica se a
* operação foi realizada com sucesso.
*
* Pré-cond: fila criada, e elemento a ser inserido.
*
* Pós-Cond: elemento inserido na fila, se houver espaço.
*/
static short Enfileirar(TFila *f, void * elemento) {
	short status = 1; // verdade (vai dar tudo certo)
	TDadoFila *d = (TDadoFila *)f->dado;
	int pos = d->ultimo;
	TComparavel *c1 = (TComparavel *)elemento;
	int i = 0;

	if (d->cont == d->tam) {
		Estender(f);
		d->stats.sobrecarregou++;
		pos = d->ultimo;
	}


	while(i < d->cont && c1->compara(elemento, d->fila[pos]) > 0) {
		d->fila[(pos+1)%d->tam] = d->fila[pos];
		pos = (pos-1+d->tam)%d->tam;
		d->stats.movimentou_insercao++;
		i++;
	}

	d->cont++;
	d->fila[(pos+1)%d->tam] = elemento;

	d->ultimo = (d->ultimo + 1) % d->tam;
	d->stats.movimentou_insercao++;
	d->stats.inseriu++;
	return status;
}

/**Verifica a ocupação da fila. Para uma fila criada, verifica se ela tem UM
*elemento, pelo menos. Caso haja elementos o status retornado é de que a fila
*NÃO está vazia, caso contrário tem-se a indicação de fila vazia.
*
*Pré-cond: Fila criada.
*
*Pós-cond: Fila inalterada.
*/
static short Vazia(TFila *f) {
	TDadoFila *d = (TDadoFila *)f->dado;
	return d->cont == 0;
}



static void Analytics(TFila *f){
	TDadoFila *d = f->dado;

	printf("inserções:%d\n", d->stats.inseriu);
	printf("removeu:%d\n", d->stats.removeu);
	printf("movimentou para inserir:%d\n", d->stats.movimentou_insercao);
	printf("movimentou para remover:%d\n", d->stats.movimentou_remocao);
	printf("sobrecarga:%d\n", d->stats.sobrecarregou);
}

/**Criar uma nova instância de fila
*
*Pré-cond: .
*
*Pós-cond: Instância de fila criada.
*/

TFila *criarFila() {
	TFila *fila = (TFila *)malloc(sizeof(TFila));
	TDadoFila *dado = (TDadoFila *)malloc(sizeof(TDadoFila));
	fila->dado = dado;
	dado->primeiro = 0;
	dado->ultimo = -1;
	dado->cont = 0;
	dado->fila = (void **)malloc(sizeof(void *) * 2);
	dado->tam = 2;

	dado->stats.movimentou_insercao = 0;
	dado->stats.movimentou_remocao = 0;
	dado->stats.inseriu = 0;
	dado->stats.removeu = 0;
	dado->stats.sobrecarregou = 0;

	fila->desenfileirar = Desenfileirar;
	fila->vazia = Vazia;
	fila->enfileirar = Enfileirar;
	fila->analytics = Analytics; 

	return fila;
}

void destruirFila(TFila * f) {
	free(f->dado);
	free(f);
}
