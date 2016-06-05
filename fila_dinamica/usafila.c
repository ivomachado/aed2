#include "fila.h"
#include <stdio.h>

int main() {
    TFila *f = CriarFila();
    int i;
    for (i = 0; i < 1024; i++) {
        f->enfileirar(f, i);
    }
    for(i = 0; i < 1024; i++)
        printf("%d ", f->desenfileirar(f));
    return 0;
}
