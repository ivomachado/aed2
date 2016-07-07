/*
 * fila.c
 *
 *  Created on: 30/05/2016
 *      Author: cesar
 */
#include "fila.h"
#include "math.h"
#include "stdlib.h"
#include "heap.h"
#include "stdio.h"

#define NaN NULL
#define TAM 10

typedef struct{
	int inseriu;
	int removeu;
	int movimentou;
	int sobrecarregou;
} TStatsFila;

typedef struct {
	THeap *heap;
	TStatsFila stats;
} TDadoFila;

/** Remove o primeiro elemento da fila. Para a fila passada, o primeiro elemento será removido se ele existir.
 * No caso da fila vazia, a operação não é realizada e um NaN é retornado.
 *
 * Pré-cond: Fila criada.
 *
 * Pós-cond: Elemento removido, se fila não estiver vazia.
 */
static void* Desenfileirar(TFila *f){
	TDadoFila *d = f->dado;
	void *elemento = d->heap->topo(d->heap);
	int movs = d->heap->remover(d->heap);
	if(movs > 0) {
		d->stats.movimentou += movs;
		d->stats.removeu++;
	}
	//printf("P:%d U:%d\n", d->primeiro, d->ultimo)
	return elemento;
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
static short Enfileirar(TFila *f, void *elemento){
	short status = 1; // verdade (vai dar tudo certo)
	TDadoFila *d = f->dado;
	int movs = d->heap->inserir(d->heap, elemento);
	// Atualiza estatística
	if(movs < 0) {
		d->stats.sobrecarregou++;
		movs *= -1;
	}
	d->stats.movimentou += movs;
	d->stats.inseriu++;
	d->stats.sobrecarregou += (status==0?1:0);

	return status;
}

/**Verifica a ocupação da fila. Para uma fila criada, verifica se ela tem UM elemento, pelo menos. Caso haja elementos o status retornado é de que a fila NÃO está vazia, caso contrário tem-se a indicação de fila vazia.
 *
 *Pré-cond: Fila criada.
 *
 *Pós-cond: Fila inalterada.
 */
static short Vazia(TFila *f){
	TDadoFila *d = f->dado;

	return d->heap->vazia(d->heap);
}
/** Analisa e imprime estatísticas da fila. Para uma fila criada, imprime as estatísticas coletadas ao longo da execução do programa que usou a fila. São consideradas operações de inserção e remoção na fila e os custos de movimentação de elementos.
 *
 * Pré-cond: Fila criada
 *
 * Pós-cond: Estatísticas geradas e apresentadas.
 */
static void Analytics(TFila *f){
	TDadoFila *d = f->dado;

	printf("inserções:%d\n", d->stats.inseriu);
	printf("removeu:%d\n", d->stats.removeu);
	printf("movimentou:%d\n", d->stats.movimentou);
	printf("sobrecarga:%d\n", d->stats.sobrecarregou);
}


TFila* criarFila(){
	TFila *f = malloc(sizeof(TFila));

	// inicialização dos métodos
	f->desenfileirar = Desenfileirar;
	f->enfileirar = Enfileirar;
	f->vazia = Vazia;
	f->analytics = Analytics;

	TDadoFila *d = malloc(sizeof(TDadoFila));
	d->heap = CriarHeap();
	d->stats.movimentou = 0;
	d->stats.inseriu = 0;
	d->stats.removeu = 0;
	d->stats.sobrecarregou = 0;

	f->dado = d;

	return f;
}

void destruirFila(TFila *f){
	free(f->dado);
	free(f);
}
