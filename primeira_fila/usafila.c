#include "fila.h"
#include <stdio.h>

int main() {
    TFila *f = CriarFila();
    for (int i = 0; i < 10; i++)
        f->enfileirar(f, i);
    while (!f->vazia(f))
        printf("%d\n", f->desenfileirar(f));
    return 0;
}
