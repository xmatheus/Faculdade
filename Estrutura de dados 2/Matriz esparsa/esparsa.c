/* Matriz esparsa
 * Estrutura de dados 2
 * UFMT
 * Prof: Ivairton 
 * Aluno: Matheus Felipe Teodoro Correia
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcao.h"

#ifndef tipo_mtx
#define tipo_mtx

struct mtz_esparsa{//0
	struct cabecalho *linha;
	struct cabecalho *coluna;
};
typedef struct mtz_esparsa tipo_esparsa;

struct cabecalho{//1
	int indice;
	struct cabecalho *cab_prox;
	struct noh *noh_prox;
};
typedef struct cabecalho tipo_cabecalho;

struct noh{//2
	int valor;
	int indice_linha;
	int indice_coluna;
	struct noh *prox_linha;
	struct noh *prox_coluna;
};
typedef struct noh tipo_noh;
#endif

/*
 * 0 - aponta para os cabecalhos
 * 1 - cabecalhos
 * 2 - nohs com informacoes
 *
 * 0-1-1-1-1-1
 * 1-2-2-2-2-2
 * 1-2-2-2-2-2
 * 1-2-2-2-2-2
 */
int main(){
	tipo_esparsa *esparsa=(tipo_esparsa*)malloc(sizeof(tipo_esparsa));
	

	opcao(esparsa);
	
	return 0;
}

