#include <stdio.h>
#include <stdlib.h>

#define T 2	//Constante T que determina o tamanho da Arv.B
#define MAX_CHAVES ( 2 * T - 1 )	//Máximo de registros
#define MAX_FILHOS ( 2 * T )		//Máximo de filhos
#define MIN_CHAVES ( T - 1 )		//Mínimo de registros


// estrutura 'tipo_arvore'
struct arvore{
	int contChaves;
	int chaves[MAX_CHAVES];
	struct arvore *filhos[MAX_FILHOS];
	int folha;
};
typedef struct arvore tipo_arvore;


tipo_arvore* insereArvB(tipo_arvore *raiz, int valor) {
	int flag;
	char valorRetorno, i;
	tipo_arvore *filhoDir, *novaRaiz;

	filhoDir = insere(raiz, valor, &flag, &valorRetorno);

	//Verifica se ocorreu a descida na árvore adequadamente, se há a necessidade de um novo nó como raiz
	if (flag) {
		novaRaiz = alocaNovoNo();
		novaRaiz->contChaves = 1;
		novaRaiz->chaves[0] = valorRetorno;
		novaRaiz->filhos[0] = raiz;
		novaRaiz->filhos[1] = filhoDir;
		novaRaiz->folha = 0;
		return novaRaiz;
	} else {
		return raiz;
	}
}

//Função que busca pelo nó onde deve ser inserido o valor/chave e faz a quebra do nó, quando necessário
tipo_arvore *insere (tipo_arvore *no, int valor, int *flag, int *valorRetorno){
	int i, pos, meio;
	tipo_arvore *noAux, *filhoDir;

	if (no == NULL) {
		//Então o nó pai (anterior) é o nó onde deve ser feita a inserção, pois alcançou um nó folha
		*flag = 1;
		*valorRetorno = valor;
		return NULL;
	} 
	else {
		//Executa a busca pelo nó onde o valor deve ser inserido
		pos = buscaBinaria (no, valor); //verifica/busca a posição

		//Identifica se a chave já está presente na árvore
		if ( (pos < no->contChaves) && (no->chaves[pos] == valor) ){
			printf("O valor da chave já está presente na Árvore B!\n");
			*flag = 0;
		} 
		else {
			//Desce na árvore, buscando pelo nó folha onde deve ocorrer a inserção
			if ( no->chaves[pos] < valor){
				pos++;
			}
			filhoDir = insere(no->filhos[pos], valor, flag, valorRetorno); 	//Executa chamada recursiva

			if ( *flag ) { //Se ocorreu a descida como esperado, então insere o valor no nó
				if ( no->contChaves < MAX_CHAVES) { //Verifica se há espaço no nó
					insereChave(no, *valorRetorno, filhoDir);
					*flag = 0;
				} else { //Então é preciso dividir o nó p/ poder inserir o valor
					noAux = alocaNovoNo();
					meio = no->chaves[MIN_CHAVES];
					//Insere metade das chaves no novo nó
					noAux->filhos[0] = no->filhos[MIN_CHAVES+1];
					for (i = MIN_CHAVES+1; i < MAX_CHAVES; i++){
						insereChave( noAux, no->chaves[i], no->filhos[i+1] );
					}
					//Atualiza o nó ("apaga" as chaves transferidas
					for (i = MIN_CHAVES; i < MAX_CHAVES; i++) {
						no->chaves[i] = 0;
						no->filhos[i+1] = NULL;
						no->contChaves--;
					}
					//Verifica em qual dos novos nós o valor deve ser inserido e executa
					if ( pos <= MIN_CHAVES) {
						insereChave(no, *valorRetorno, filhoDir);
					} else {
						insereChave(noAux, *valorRetorno, filhoDir);
					}
					//Retorna o elemento do meio para ser inserido no nó pai e o filho direito da chave central
					*flag = 1;
					*valorRetorno = meio;
					return (noAux);
				}
			}
		}
	}
}


int main(int argc, char *argv[ ]){

}