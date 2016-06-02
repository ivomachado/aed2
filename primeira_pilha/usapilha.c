#include <stdio.h>
#include "pilha.h"

int main() {
    TPilha *p = CriarPilha();
    for(int i = 0; i < 10; i++)
        p->empilhar(p,i);
    while(!p->vazia(p))
        printf("%d\n",p->desempilhar(p));
    return 0;
}
