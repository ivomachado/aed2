#include "job.h"

#include "stdlib.h"
#include "stdio.h"

typedef struct {
	double tempoChegada;
	int prioridade;
	int duracao;
	int tempoTranscoding;
}TDadoJob;

static void *criarDado(){
    TDadoJob *d = malloc(sizeof(TDadoJob));

    scanf("%lf", &(d->tempoChegada));
    if (d->tempoChegada >= 0){
        scanf("%d%d", &(d->duracao), &(d->prioridade) );
        d->tempoTranscoding = 0;
    }else{
        free(d);
        d = NULL;
    }

    return d;
}

static void imprimirJob(TJob *v){
	TDadoJob *d = v->dado;
    printf("%lf %d %d\n", d->tempoChegada, d->duracao, d->prioridade);

}

static void setTempoTranscodingJob(TJob *v, int tempoTranscoding){
	TDadoJob *d = v->dado;

	d->tempoTranscoding = tempoTranscoding;
}

static int getTempoTranscodingJob(TJob *v){
	TDadoJob *d = v->dado;

	return d->tempoTranscoding;
}

static int getDuracaoJob(TJob *v){
	TDadoJob *d = v->dado;

	return d->duracao;
}

static int getPrioridadeJob(TJob *v){
	TDadoJob *d = v->dado;

	return d->prioridade;
}

static double getTempoChegadaJob(TJob *v){
	TDadoJob *d = v->dado;

	return d->tempoChegada;
}

short comparaJob(TJob *v, TJob *v2){
	if (v->getPrioridade(v) == v2->getPrioridade(v2)){
		return 0;
	}else if (v->getPrioridade(v) > v2->getPrioridade(v2)){
		return 1;
	}else{
		return -1;
	}
}


TJob * criarJob(){
    TJob *job;
    
    job = malloc(sizeof(TJob));
 
    job->dado = criarDado();
    if(job->dado!=NULL){
    		job->imprimir = imprimirJob;
    		job->getDuracao = getDuracaoJob;
    		job->getPrioridade = getPrioridadeJob;
    		job->getTempoChegada = getTempoChegadaJob;
    		job->getTempoTranscoding = getTempoTranscodingJob;
    		job->setTempoTranscoding = setTempoTranscodingJob;
			job->compara = comparaJob;
    }else{
    		free(job);
    		job=NULL;
    }

	return job;
}


void destruirJob(TJob *v){
	free(v->dado);
	free(v);
}
