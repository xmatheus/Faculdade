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

tipo_arvore* insereArvB(tipo_arvore *raiz, int valor);
tipo_arvore *insere (tipo_arvore *no, int valor, int *flag, int *valorRetorno);
void insereChave(tipo_arvore **arvore,int *valorRetorno, tipo_arvore *filhoDir);
int BuscaBinaria(tipo_arvore *arvore, int valor);

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
		pos = BuscaBinaria (no, valor); //verifica/busca a posição
		//pos--;
		//Identifica se a chave já está presente na árvore
		if ( (pos < no->contChaves) && (no->chaves[pos] == valor) ){
			printf("O valor da chave já está presente na Árvore B!\n");
			*flag = 0;
		} 
		else {

			//Desce na árvore, buscando pelo nó folha onde deve ocorrer a inserção
			if ( no->chaves[pos] < valor && no->chaves[pos] != 0){
				pos++;
			}

			filhoDir = insere(no->filhos[pos], valor, flag, valorRetorno); 	//Executa chamada recursiva

			if ( *flag ) { //Se ocorreu a descida como esperado, então insere o valor no nó 
				if ( no->contChaves < MAX_CHAVES) { //Verifica se há espaço no nó
					insereChave(&no, valorRetorno, filhoDir);
					*flag = 0;
				}
				else { //Então é preciso dividir o nó p/ poder inserir o valor
					noAux = (tipo_arvore*) malloc(sizeof(tipo_arvore));
					meio = no->chaves[MIN_CHAVES];
					//Insere metade das chaves no novo nó
					noAux->filhos[0] = no->filhos[MIN_CHAVES+1];
					for (i = MIN_CHAVES+1; i < MAX_CHAVES; i++){
						insereChave(&noAux,&no->chaves[i],no->filhos[i+1]);
					}
					//Atualiza o nó ("apaga" as chaves transferidas
					for (i = MIN_CHAVES; i < MAX_CHAVES; i++){
						no->chaves[i] = 0;
						no->filhos[i+1] = NULL;
						no->contChaves--;
					}
					//Verifica em qual dos novos nós o valor deve ser inserido e executa
					if ( pos <= MIN_CHAVES) {
						insereChave(&no, valorRetorno, filhoDir);
					}
					else {
						insereChave(&noAux, valorRetorno, filhoDir);
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
int BuscaBinaria(tipo_arvore *arvore, int valor){
	int i=0;
	while( (arvore->chaves[i] < valor) && (arvore->chaves[i] != 0) && (i != MAX_CHAVES)){
		i++;
	}
	return i;
}
void insereChave(tipo_arvore **arvore,int *valorRetorno, tipo_arvore *filhoDir){//insere o int meio e aponta o filho dele para o filhoDir
	tipo_arvore *auxFilho1,*auxFilho2;
	int aux=0,pos=0,i=0,trocas=0;
	if((*arvore)->contChaves == 0){
		(*arvore)->contChaves = 1;
		(*arvore)->chaves[0] = *valorRetorno;
		(*arvore)->filhos[1] = filhoDir;
		(*arvore)->folha = 1;
	}
	else{
		while((*arvore)->chaves[pos] != 0 || pos > MAX_CHAVES){
			pos++;
		}
		(*arvore)->chaves[pos] = *valorRetorno;
		(*arvore)->filhos[pos+1] = filhoDir;
		(*arvore)->contChaves++;
		while(trocas != 2 && i != MAX_CHAVES-1){
			if(((*arvore)->chaves[i] > (*arvore)->chaves[i+1])){
				if(i<MIN_CHAVES){
					aux = (*arvore)->chaves[i+1];
					auxFilho1 = (*arvore)->filhos[i+1];
					auxFilho2 = (*arvore)->filhos[i+2];
					(*arvore)->chaves[i+1] = (*arvore)->chaves[i];
					(*arvore)->chaves[i] = aux;
					(*arvore)->filhos[i+2] = (*arvore)->filhos[i];
					(*arvore)->filhos[i] = auxFilho1;
					(*arvore)->filhos[i+1] = auxFilho2;
					trocas++;
				}
				else if ((*arvore)->chaves[i+1] != 0){
					aux = (*arvore)->chaves[i+1];
					auxFilho1 = (*arvore)->filhos[i+1];
					(*arvore)->filhos[i+1] = (*arvore)->filhos[i+2];
					(*arvore)->chaves[i+1] = (*arvore)->chaves[i];
					(*arvore)->chaves[i] = aux;
					(*arvore)->filhos[i+2] = auxFilho1;
					trocas++;
				}
			}
			
			i++;
		}
	}
}

int altura(tipo_arvore *arvore) {

    int F0,F1,F2,F3;
    if (arvore == NULL){
    	return 0;	
    } 
    F0 = altura(arvore->filhos[0]);
    F1 = altura(arvore->filhos[1]);
    F2 = altura(arvore->filhos[2]);
    F3 = altura(arvore->filhos[3]);
    if((F0 >= F1) && (F0 >= F2) && (F0 >= F3)){
    	return F0+1;	
    } 
    if((F1 >= F0) && (F1 >= F2) && (F1 >= F3)){
    	return F1+1;	
    }
    if((F2 >= F0) && (F2 >= F1) && (F2 >= F3)){
    	return F2+1;	
    }
    if((F3 >= F0) && (F3 >= F1) && (F3 >= F2)){
    	return F3+1;	
    }
}

void imprime(tipo_arvore *p, int nivel){//parametro arvore e nivel
	int i;
	if(p == NULL){//case arvore/noh null retorna para a funcao
		return;
	}
	imprime(p->filhos[3], nivel+1);//chamada recursiva para a dir
	for(i=0;i<nivel;i++){//quando maior o nivel mais espacamentos
        printf("\t");
    }
	printf("%d-%d-%d-\n\n",p->chaves[0],p->chaves[1],p->chaves[2]);
	imprime(p->filhos[2],nivel+1);//chamada recursiva para a esq
	imprime(p->filhos[1],nivel+1);
	imprime(p->filhos[0],nivel+1);
     
}


int main(int argc, char *argv[ ]){
	tipo_arvore *arvore;
	int alt;
	arvore = insereArvB(arvore,20);
	arvore = insereArvB(arvore,5);
	arvore = insereArvB(arvore,10);
	arvore = insereArvB(arvore,15);
	arvore = insereArvB(arvore,30);
	arvore = insereArvB(arvore,35);
	arvore = insereArvB(arvore,6);
	arvore = insereArvB(arvore,40);
	arvore = insereArvB(arvore,50);
	arvore = insereArvB(arvore,17);
	arvore = insereArvB(arvore,18);
	arvore = insereArvB(arvore,19);
	printf("\n\t\t\t[OK]\n");
	return 0;
}	