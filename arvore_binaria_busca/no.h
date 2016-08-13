typedef struct no TNo;
TNo * CriarNo(void * info, TNo * pai);

struct no {
    void* info;
    TNo* esq;
    TNo* dir;
    TNo* pai;
};
