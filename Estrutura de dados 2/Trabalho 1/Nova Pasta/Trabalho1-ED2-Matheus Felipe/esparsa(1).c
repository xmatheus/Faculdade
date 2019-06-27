/*
*	Trabalho 1
*	Estrutura de dados 2
*	Matheus Felipe Teodoro Correia
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcao.h"

#ifndef tipo_mtx
#define tipo_mtx
struct mtz_esparsa{
	struct cabecalho *linha;
	struct cabecalho *coluna;
};
typedef struct mtz_esparsa tipo_esparsa;

struct cabecalho{
	int indice;
	struct cabecalho *cab_prox;
	struct noh *noh_prox;
};
typedef struct cabecalho tipo_cabecalho;

struct noh{
	int valor;
	int indice_linha;
	int indice_coluna;
	struct noh *prox_linha;
	struct noh *prox_coluna;
};
typedef struct noh tipo_noh;
#endif

int main(){
	tipo_esparsa *esparsa=(tipo_esparsa*)malloc(sizeof(tipo_esparsa));
	

	opcao(esparsa);
	
	return 0;
}

