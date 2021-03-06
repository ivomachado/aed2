typedef struct heap THeap;

typedef int (*TInserir)(THeap *, void *);
typedef int (*TRemover)(THeap *);
typedef void *(*TTopo)(THeap *);
typedef short (*THeapVazio)(THeap *);

THeap *CriarHeap();

struct heap {
  void *dado;
  TInserir inserir;
  TRemover remover;
  TTopo topo;
  THeapVazio vazia;
};
