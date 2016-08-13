#include "comparavel.h"

typedef struct elemento TElemento;

typedef void (*TImprimir)(void *);

struct elemento {
    struct comparavel;
    TImprimir imprimir;
};
