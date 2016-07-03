
typedef struct video TJob;
TJob *criarJob();
void destruirJob(TJob*);
short comparaJob(TJob*, TJob*);
typedef void (*TImprimirVideo)(TJob *v);
typedef int (*TGetDuracaoVideo)(TJob *v);
typedef int (*TGetPrioridadeVideo)(TJob *v);
typedef double (*TGetTempoChegadaVideo)(TJob *v);
typedef int (*TGetTempoTranscodingVideo)(TJob *v);
typedef void (*TSetTempoTranscodingVideo)(TJob *v, int);

struct video{
	void *dado;
	TImprimirVideo imprimir;
	TGetDuracaoVideo getDuracao;
	TGetPrioridadeVideo getPrioridade;
	TGetTempoChegadaVideo getTempoChegada;
	TSetTempoTranscodingVideo setTempoTranscoding;
	TGetTempoTranscodingVideo getTempoTranscoding;
};

// Atividades
