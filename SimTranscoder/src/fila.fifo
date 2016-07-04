/*
 * fila.c
 *
 *  Created on: 30/05/2016
 *      Author: cesar
 */
#include "fila.h"
#include "math.h"
#include "stdlib.h"
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
	int primeiro;
	int ultimo;
	void* fila[TAM];
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
	void *elemento=NULL;
	TDadoFila *d = f->dado;
	//printf("P:%d U:%d\n", d->primeiro, d->ultimo);
	if (d->primeiro == -1){
		elemento = NULL;
	}else{
		elemento  = d->fila[d->primeiro];
		if (d->primeiro == d->ultimo){
			d->primeiro = d->ultimo = -1;
		}else{
			for(int i=d->primeiro;i<d->ultimo;i++){
				d->fila[i] = d->fila[i+1];
			}
			d->ultimo--;
		}
		//atualiza estatísticas
		d->stats.removeu++;
		d->stats.movimentou += (d->ultimo-d->primeiro)+(d->primeiro==-1?0:1);
	}
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

	if (d->primeiro == -1){
		d->primeiro=d->ultimo=0;
		d->fila[d->primeiro] = elemento;
	}else if ((d->ultimo+1) < TAM){
		d->ultimo++;
		d->fila[d->ultimo] = elemento;
	}else{
		status = 0; //falso (deu errado)
	}
	// Atualiza estatística
	d->stats.inseriu += (status==1?1:0);
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

	if (d->primeiro == -1)
		return 1;

	return 0;
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
	d->primeiro=-1;
	d->ultimo=-1;

	f->dado = d;

	return f;
}

void destruirFila(TFila *f){
	free(f->dado);
	free(f);
}
