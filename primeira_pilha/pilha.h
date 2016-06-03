

typedef struct pilha TPilha;

typedef char (*TEmpilhar)(TPilha *, int);
typedef int (*TDesempilhar)(TPilha *);
typedef char (*TVazia)(TPilha *);

TPilha *CriarPilha();

struct pilha {
    void *dado;
    TEmpilhar empilhar;
    TDesempilhar desempilhar;
    TVazia vazia;
};
