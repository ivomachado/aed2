#include "fila.h"
#include <stdlib.h>

#define NaN 0 / 0.
typedef struct no {
    int value;
    struct no *prox;
} TNo;

typedef struct {
    TNo *primeiro;
    TNo *ultimo;
    int cont;
} TDado;

/** Remove o primeiro elemento da fila. Para a fila passada, o primeiro elemento
* será removido se ele existir.
* No caso da fila vazia, a operação não é realizada e um NaN é retornado.
*
* Pré-cond: Fila criada.
*
* Pós-cond: Elemento removido, se fila não estiver vazia.
*/
static int Desenfileirar(TFila *f) {
    int elemento;
    TNo *aux;
    TDado *d = (TDado *)f->dado;
    if (!d->cont) {
        elemento = NaN;
    } else {
        if(d->primeiro == d->ultimo) d->ultimo = NULL;
        elemento = d->primeiro->value;
        aux = d->primeiro;
        d->primeiro = d->primeiro->prox;
        aux->prox = NULL;
        free(aux);
        aux = NULL;
        d->cont--;
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
static void Enfileirar(TFila *f, int elemento) {
    TDado *d = (TDado *)f->dado;
    TNo *inserido = (TNo *)malloc(sizeof(TNo));
    inserido->value = elemento;
    inserido->prox = NULL;

    if(!d->cont) {
        d->primeiro = d->ultimo = inserido;
    } else {
        d->ultimo->prox = inserido;
        d->ultimo = inserido;
    }

    d->cont += 1;
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
    TDado *d = (TDado *)f->dado;
    return d->cont == 0;
}

/**Criar uma nova instância de fila
*
*Pré-cond: .
*
*Pós-cond: Instância de fila criada.
*/

TFila *CriarFila() {
    TFila *fila = (TFila *)malloc(sizeof(TFila));
    TDado *dado = (TDado *)malloc(sizeof(TDado));
    fila->dado = dado;
    dado->primeiro = NULL;
    dado->ultimo = NULL;
    dado->cont = 0;

    fila->desenfileirar = Desenfileirar;
    fila->vazia = Vazia;
    fila->enfileirar = Enfileirar;

    return fila;
}
