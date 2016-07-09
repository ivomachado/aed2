
typedef struct job TJob;
TJob *criarJob();
void destruirJob(TJob*);
typedef void (*TImprimirJob)(TJob *v);
typedef int (*TGetDuracaoJob)(TJob *v);
typedef int (*TGetPrioridadeJob)(TJob *v);
typedef double (*TGetTempoChegadaJob)(TJob *v);
typedef int (*TGetTempoTranscodingJob)(TJob *v);
typedef void (*TSetTempoTranscodingJob)(TJob *v, int);
typedef short (*TComparaJob)(TJob*, TJob*);

struct job{
	void *dado;
	TComparaJob compara;
	TImprimirJob imprimir;
	TGetDuracaoJob getDuracao;
	TGetPrioridadeJob getPrioridade;
	TGetTempoChegadaJob getTempoChegada;
	TSetTempoTranscodingJob setTempoTranscoding;
	TGetTempoTranscodingJob getTempoTranscoding;
};

// Atividades
