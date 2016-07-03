typedef struct comparavel TComparavel;

typedef int (*TCompara)(TComparavel *, TComparavel *);

struct comparavel{
    void * dados;
    TCompara compara;
};
