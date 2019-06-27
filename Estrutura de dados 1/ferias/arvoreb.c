#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//struct arvore
struct arvore{
	int valor;
	struct arvore *esq;
	struct arvore *dir;
};
typedef struct arvore tipo_arvore;

//prototipos das funcoes
void insere(tipo_arvore **arvore,int valor);//insere valores na arvore recebendo como paramentro um ponteiro de ponteiro e o valor a ser alocado
tipo_arvore *inicializa();//inicializa a arvore como NULL
void mostra_arvore(tipo_arvore *arvore);//printa a arvore em ordem so que do maior para o menos
int busca_arvore(tipo_arvore *arvore, int valor, int marcador);//funcao para buscar um valor na arvore

void insere(tipo_arvore **arvore,int valor){
	if((*arvore) == NULL){//se a arvore for vazia ele aloca o novo valor e aponta a esq e dir para NULL
		(*arvore)=(tipo_arvore *)malloc(sizeof(tipo_arvore));//alocando o novo noh
		(*arvore)->valor=valor;//alocando novo valor
		//printf("inseriu %d\n",(*arvore)->valor );//print para saber se o novo valor foi inserido corretamente
		(*arvore)->esq=NULL;//esq apontando para NULL
		(*arvore)->dir=NULL;//dir apontando para NULL
	}
	else{//se nao
		if(valor>=(*arvore)->valor){//se valor for maior que o ponteiro da arvore->valor ele chama a funcao recursivamente pela direita
			//printf("dir\n");
			insere(&(*arvore)->dir,valor);
		}
		else if(valor<=(*arvore)->valor){//se nao se, valor for menor que o ponteiro da arvore->valor ele chama a funcao recursivamente pela esquerda
			//printf("esq\n");
			insere(&(*arvore)->esq,valor);
		}
	}
	
}
void mostra_arvore(tipo_arvore *arvore){
	if(arvore!=NULL){//caso o noh seja diferente de vazio ele entra printando todos os nohs seguintes
		
		mostra_arvore(arvore->dir);//recursivamente pela direita
		printf("%d ",arvore->valor);//mostra o valor
		mostra_arvore(arvore->esq);//recursivamente pela esquerda
	}
	
}
tipo_arvore *inicializa(){//retorna NULL para a arvore
	return NULL;
}
int busca_arvore(tipo_arvore *arvore, int valor,int marcador){
	
	if(arvore!=NULL){
		if(arvore->valor==valor){
			marcador++;
		}
		marcador=busca_arvore(arvore->dir,valor,marcador);
		marcador=busca_arvore(arvore->esq,valor,marcador);
	}
	return marcador;
	
}

int main(){
	int marcador,numero,valor;;
	tipo_arvore* arvore=inicializa();//inicializando a arvore vazia
	/*
	insere(&arvore,10);//inserindo valor com a funcao

	mostra_arvore(arvore);//mostrando arvore do maior para o menor

	marcador=busca_arvore(arvore,6,marcador);
	printf("marcador %d\n",marcador );*/

	do{
		
		printf("1-insiria dez valores\n2-printar em ordem do maior para o menor\n3-Busca valor\n4-Sair\n");scanf("%d",&valor);
		switch(valor){
			system("clear");
			case 1:

				printf("Difite os 10 numeros: \n");
				for(int i=0;i<10;i++){
					scanf("%d",&numero);
					insere(&arvore,numero);
				}
				break;
			case 2:
				system("clear");
				mostra_arvore(arvore);
				printf("\n");
				break;
			case 3:
				printf("Digite o valor a ser buscado: ");
				scanf("%d",&numero);
				
				marcador=busca_arvore(arvore,numero,marcador);
				if(marcador!=0){
					system("clear");
					printf("valor encontrado %d vez(es)\n",marcador);
				}
				else if(marcador==0){
					system("clear");
					printf("valor não encontrado\n");
				}
				break;
		}
	} while (valor!=4);






	return 0;
}
