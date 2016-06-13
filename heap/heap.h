typedef struct heap THeap;

typedef void (*TInserir)(THeap *, int);
typedef void (*TPrint)(THeap *);
typedef void (*TRemover)(THeap *);
typedef int (*TTopo)(THeap *);

THeap *CriarHeap(int tam);

struct heap {
  void *dado;
  TInserir inserir;
  TPrint print;
  TRemover remover;
  TTopo topo;
};
