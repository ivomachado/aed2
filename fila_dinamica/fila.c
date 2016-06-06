#include "fila.h"
#include <stdlib.h>

#define NaN 0 / 0.
typedef struct {
    int primeiro;
    int ultimo;
    int *fila;
    int tam;
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
    TDado *d = (TDado *)f->dado;
    if (d->cont == 0) {
        elemento = NaN;
    } else {
        elemento = d->fila[d->primeiro];
        d->primeiro = (d->primeiro + 1) % d->tam;
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
static void Extender(TFila *f) {
    TDado *d = (TDado *)f->dado;
    int *v = (int *)malloc(sizeof(int) * d->tam * 2), i;
    for (i = 0; i < d->tam; i++) {
        v[i] = f->desenfileirar(f);
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
static short Enfileirar(TFila *f, int elemento) {
    short status = 1; // verdade (vai dar tudo certo)
    TDado *d = (TDado *)f->dado;

    if (d->cont == d->tam) {
        Extender(f);
    }
    d->ultimo = (d->ultimo + 1) % d->tam;
    d->fila[d->ultimo] = elemento;
    d->cont += status;
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
    dado->primeiro = 1;
    dado->ultimo = 0;
    dado->cont = 0;
    dado->fila = (int *)malloc(sizeof(int) * 2);
    dado->tam = 2;

    fila->desenfileirar = Desenfileirar;
    fila->vazia = Vazia;
    fila->enfileirar = Enfileirar;

    return fila;
}
