#include <stdio.h>
#include <stdlib.h>

#define T 2						//Constante T que determina o tamanho da Arv.B
#define MAX_CHAVES ( 2 * T - 1 )//Máximo de registros
#define MAX_FILHOS ( 2 * T )	//Máximo de filhos
#define MIN_CHAVES ( T - 1 )	//Mínimo de registros


// estrutura 'tipo_arvore'
struct arvore{
	int contChaves;
	int chaves[MAX_CHAVES];
	struct arvore *filhos[MAX_FILHOS];
	int folha;
};
typedef struct arvore tipo_arvore;

tipo_arvore* insereArvB(tipo_arvore *raiz, int valor);

tipo_arvore* insereArvB(tipo_arvore *raiz, int valor){
	int flag;
	int valorRetorno;
	tipo_arvore *filhoDir, *novaRaiz;

	filhoDir = insere(raiz, valor, &flag, &valorRetorno);

	//Verifica se ocorreu a descida na árvore adequadamente, se há a necessidade de um novo nó como raiz
	if (flag){
		novaRaiz = (tipo_arvore*) malloc(sizeof(tipo_arvore));
		novaRaiz->contChaves = 1;
		novaRaiz->chaves[0] = valorRetorno;
		novaRaiz->filhos[0] = raiz;
		novaRaiz->filhos[1] = filhoDir;
		novaRaiz->folha = 0;
		return novaRaiz;
	}
	else {
		return raiz;
	}
}


int main(int argc, char *argv[ ]){
	tipo_arvore *arvore;
	
	return 0;
}	