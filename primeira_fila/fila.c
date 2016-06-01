#include "fila.h"
#include "stdlib.h"

#define NaN 0 / 0.
#define TAM 10
typedef struct {
    int primeiro;
    int ultimo;
    int fila[TAM];
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
    TDado *d = (TDado*)f->dado;
    if (d->primeiro == -1) {
        elemento = NaN;
    } else {
        elemento = d->fila[d->primeiro];
        if (d->primeiro == d->ultimo) {
            d->primeiro = d->ultimo = -1;
        } else {
            for (int i = d->primeiro; i < d->ultimo; i++) {
                d->fila[i] = d->fila[i + 1];
            }
            d->ultimo--;
        }
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
static short Enfileirar(TFila *f, int elemento) {
    short status = 1; // verdade (vai dar tudo certo)
    TDado *d = (TDado*)f->dado;

    if (d->primeiro == -1) {
        d->primeiro = d->ultimo = 0;
        d->fila[d->primeiro] = elemento;
    } else if ((d->ultimo + 1) < TAM) {
        d->ultimo++;
        d->fila[d->ultimo] = elemento;
    } else {
        status = 0; // falso (deu errado)
    }
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
    TDado *d = (TDado*)f->dado;

    if (d->primeiro == -1)
        return 1;

    return 0;
}

/**Verifica a ocupação da fila. Para uma fila criada, verifica se ela tem UM
*elemento, pelo menos. Caso haja elementos o status retornado é de que a fila
*NÃO está vazia, caso contrário tem-se a indicação de fila vazia.
*
*Pré-cond: Fila criada.
*
*Pós-cond: Fila inalterada.
*/

TFila* CriarFila() {
    TFila *fila = (TFila*)malloc(sizeof(TFila));
    TDado *dado = (TDado*)malloc(sizeof(TDado));
    fila->dado = dado;
    dado->primeiro = dado->ultimo = -1;

    fila->desenfileirar = Desenfileirar;
    fila->vazia = Vazia;
    fila->enfileirar = Enfileirar;

    return fila;
}
