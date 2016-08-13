#include "no.h"
#include <stdlib.h>

TNo * CriarNo(void * info, TNo * pai) {
    TNo *no = malloc(sizeof(TNo));
    no->dir = NULL;
    no->esq = NULL;
    no->pai = pai;
    no->info = info;
    return no;
}
