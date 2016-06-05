typedef struct fila TFila;

typedef short (*TEnfileirar)(TFila *, int);

typedef int (*TDesenfileirar)(TFila *);

typedef short (*TVazia)(TFila *);

TFila *CriarFila();

struct fila {
    void *dado;
    TEnfileirar enfileirar;
    TDesenfileirar desenfileirar;
    TVazia vazia;
};
