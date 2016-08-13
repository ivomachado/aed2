#define DICIONARIO_H_

typedef struct dicionario TDicionario;

typedef void (*TInserirDicionario)(TDicionario*, int K, void*info);
typedef void* (*TBuscarDicionario)(TDicionario*, int K);
typedef void (*TAnalytiDicionario)(TDicionario*);

struct dicionario {
    void *dado;
    TInserirDicionario inserir;
    TBuscarDicionario buscar;
    TAnalytiDicionario analytic;
};
