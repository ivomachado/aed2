#include "pilha.h"
#include <stdlib.h>

#define TAM 10
#define NaN 0 / 0.

typedef struct {
    int topo;
    int pilha[TAM];
} TDado;

/** Insere um novo elemento na pilha. Para uma pilha criada
* a função irá inserir o elemento passado
* considerando a ocupação da pilha. o retorno indica se a
* operação foi realizada com sucesso.
*
* Pré-cond: pilha criada, e elemento a ser inserido.
*
* Pós-Cond: elemento inserido na pilha, se houver espaço.
*/

static char Empilhar(TPilha *p, int v) {
    TDado *d = (TDado *)p->dado;

    if (d->topo < TAM) {
        d->topo++;
        d->pilha[d->topo] = v;
        return 1;
    } else
        return 0;
}

/** Remove o primeiro elemento da pilha. Para a pilha passada, o último elemento
* será removido se ele existir.
* No caso da pilha vazia, a operação não é realizada e um NaN é retornado.
*
* Pré-cond: pilha criada.
*
* Pós-cond: Elemento removido, se pilha não estiver vazia.
*/

static int Desempilhar(TPilha *p) {
    TDado *d = (TDado *)p->dado;

    if (d->topo >= 0)
        return d->pilha[d->topo--];
    return NaN;
}

/**Verifica a ocupação da pilha. Para uma pilha criada, verifica se ela tem UM
*elemento, pelo menos. Caso haja elementos o status retornado é de que a pilha
*NÃO está vazia, caso contrário tem-se a indicação de pilha vazia.
*
*Pré-cond: pilha criada.
*
*Pós-cond: pilha inalterada.
*/

static char Vazia(TPilha *p) {
    TDado *d = (TDado *)p->dado;

    if (d->topo == -1)
        return 1;

    return 0;
}

TPilha *CriarPilha() {
    TPilha *f = (TPilha *)malloc(sizeof(TPilha));
    TDado *d = (TDado *)malloc(sizeof(TDado));

    d->topo = -1;

    f->dado = d;
    f->desempilhar = Desempilhar;
    f->empilhar = Empilhar;
    f->vazia = Vazia;

    return f;
}
