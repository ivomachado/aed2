typedef struct heap THeap;

typedef void (*TInserir)(THeap *, void *);
typedef void (*TRemover)(THeap *);
typedef void *(*TTopo)(THeap *);

THeap *CriarHeap();

struct heap {
  void *dado;
  TInserir inserir;
  TRemover remover;
  TTopo topo;
};
