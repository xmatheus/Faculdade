#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*fazer uma funcao que arruma os fatores de balaceamentos de cada noh*/
//struct arvore
struct arvore{
	int valor;
	int fb;
	struct arvore *esq;
	struct arvore *dir;
};
typedef struct arvore tipo_arvore;

//prototipos das funcoes
void insere(tipo_arvore **arvore,int valor);//insere valores na arvore recebendo como paramentro um ponteiro de ponteiro e o valor a ser alocado
tipo_arvore *inicializa();//inicializa a arvore como NULL
void mostra_arvore(tipo_arvore *arvore);//printa a arvore em ordem so que do maior para o menos
int busca_arvore(tipo_arvore *arvore, int valor, int marcador);//funcao para buscar um valor na arvore
void pega_numero(tipo_arvore **arvore);
int fator(tipo_arvore **arvore);
void verifica_altura(tipo_arvore **arvore);
void rotacaoEsquerda(tipo_arvore **arvore);
void rotacaoDireita(tipo_arvore **arvore);
void duplarotacaoEsq(tipo_arvore **arvore);
void duplarotacaoDir(tipo_arvore **arvore);

void verifica_altura(tipo_arvore **arvore){
	if(*arvore!=NULL){
		(*arvore)->fb=fator(arvore);
		verifica_altura(&(*arvore)->esq);
		verifica_altura(&(*arvore)->dir);
	}
}
int altura(tipo_arvore *arvore) {

    int esq, dir;
    if (arvore == NULL){
    	return 0;	
    } 
    esq = altura(arvore->esq);
    dir = altura(arvore->dir);
    if (esq > dir){
    	return esq+1;	
    } 
    else{
    	return dir+1;	
    } 
}
int fator(tipo_arvore **arvore){
	int esq,dir,total;
	
	esq=altura((*arvore)->esq);
	dir=altura((*arvore)->dir);
	total=esq-dir;
	printf("esq %d dir %d\n",esq,dir );
	return total;
}
void pega_numero(tipo_arvore **arvore){//funcao que pega os valores do arquivo para inserir na matriz
	FILE *file;
	int i=0,j=0,numero=0;


	file=fopen("1000-arq01.txt","r");
	if(file == NULL){//teste  de erro
		printf("Erro na abertura do arquivo alunos.txt, ele deve ter o parametro NOME:RGA!\n");
	}
	while(fscanf(file,"%d",&numero)!=EOF){
		printf("%d\n",numero );
		insere(arvore,numero);
		verifica_altura(arvore);
		//fscanf(file,"%d",&numero);		
	}
	fclose(file);
}
void insere(tipo_arvore **arvore,int valor){
	int flag=0,total=0;
	if((*arvore) == NULL){//se a arvore for vazia ele aloca o novo valor e aponta a esq e dir para NULL
		(*arvore)=(tipo_arvore *)malloc(sizeof(tipo_arvore));//alocando o novo noh
		(*arvore)->valor=valor;//alocando novo valor
		(*arvore)->esq=NULL;//esq apontando para NULL
		(*arvore)->dir=NULL;//dir apontando para NULL
		(*arvore)->fb=0;
	}
	else{		
		if(valor>=(*arvore)->valor){//se valor for maior que o ponteiro da arvore->valor ele chama a funcao recursivamente pela direita
			insere(&(*arvore)->dir,valor);			
		}
		else if(valor<=(*arvore)->valor){//se nao se, valor for menor que o ponteiro da arvore->valor ele chama a funcao recursivamente pela esquerda
			insere(&(*arvore)->esq,valor);
		}
		verifica_altura(arvore);		
		if(((*arvore)->fb == -2) && ((*arvore)->dir !=NULL) &&((*arvore)->dir->fb > 0)){//rotacao dupla para a esquerda
			printf("Rotacao dupla para a esquerda\n");
			duplarotacaoEsq(arvore);
			flag=1;
		}
		if(((*arvore)->fb == 2) && ((*arvore)->esq) &&((*arvore)->esq->fb < 0)){//rotacao dupla para direita
			printf("Rotacao dupla para a direita\n");
			duplarotacaoDir(arvore);
			flag=1;
		}

		if(flag==0){
			if((*arvore)->fb == -2 ){//se fb neagtivo entao desbalanceado pra direita
				printf("Deslabalanceado pra direita\n");
				rotacaoEsquerda(arvore);
				
			}
			(*arvore)->fb=fator(arvore);
			 if((*arvore)->fb == 2){//se fb positivo entao desbalanceado pra esquerda
				printf("Deslabalanceado pra esquerda\n");
				rotacaoDireita(arvore);
				
			}
		}
	}
}

void rotacaoEsquerda(tipo_arvore **arvore){
	tipo_arvore *aux;
	aux=(*arvore)->dir;
	(*arvore)->dir=aux->esq;
	aux->esq=*arvore;
	*arvore=aux;
}
void rotacaoDireita(tipo_arvore **arvore){
	tipo_arvore *aux;
	aux=(*arvore)->esq;
	(*arvore)->esq=aux->dir;
	aux->dir=*arvore;
	*arvore=aux;
}
void duplarotacaoEsq(tipo_arvore **arvore){
	rotacaoDireita(&(*arvore)->dir);
	rotacaoEsquerda(arvore);
}
void duplarotacaoDir(tipo_arvore **arvore){
	rotacaoEsquerda(&(*arvore)->esq);
	rotacaoDireita(arvore);
}
void mostra_arvore(tipo_arvore *arvore){
	if(arvore!=NULL){//caso o noh seja diferente de vazio ele entra printando todos os nohs seguintes
		//printf("Valor=%d FB=%d\n",arvore->valor,arvore->fb);//mostra o valor
		if(arvore->esq != NULL){
			printf("esq ");
			mostra_arvore(arvore->esq);//recursivamente pela esquerda
		}
		else{
			printf("esq NULL\n");
		}
		if(arvore->dir!=NULL){
			printf("dir ");
			mostra_arvore(arvore->dir);//recursivamente pela direita
		}
		else{
			printf("dir NULL\n");
		}
	}
	
}
tipo_arvore *inicializa(){//retorna NULL para a arvore
	return NULL;
}
int main(){
	int marcador,numero,valor;
	tipo_arvore *arvore=inicializa();//inicializando a arvore vazia
	FILE *file;
	int i=0,j=0;
	do{
		
		printf("1-Ler arquivo e inserir valores\n2-Mostrar arvore\n3-Buscar valor\n4-Insere valores manualmente\n5-Sair\n");scanf("%d",&valor);
		switch(valor){
			system("clear");
			case 1:
				pega_numero(&arvore);
				
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
			case 4:
				printf("Quantidade de valores a ser inserida: ");
				scanf("%d",&valor);
				for(i=0;i<valor;i++){
					scanf("%d",&numero);
					insere(&arvore,numero);	
				}
				break;
		}	

	} while (valor!=5);
	return 0;
}
