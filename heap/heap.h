typedef struct heap THeap;

typedef void (*TInserir)(THeap *, int);
typedef void (*TPrint)(THeap *);

THeap *CriarHeap(int tam);

struct heap {
    void *dado;
    TInserir inserir;
    TPrint print;
};
