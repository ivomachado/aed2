typedef struct heap THeap;

typedef void (*TInserir)(THeap *, void *);
typedef void (*TPrint)(THeap *);
typedef void (*TRemover)(THeap *);
typedef int (*TComparar)(void *, void *);
typedef void (*TPrintInterno)(void *);
typedef void *(*TTopo)(THeap *);

THeap *CriarHeap(int tam, TPrintInterno _print, TComparar comparar);

struct heap {
  void *dado;
  TInserir inserir;
  TPrint print;
  TRemover remover;
  TTopo topo;
};
