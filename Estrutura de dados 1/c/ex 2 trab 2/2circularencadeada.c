#include <stdio.h>
#include <stdlib.h>




struct lista{
	int valor;
	struct lista* prox;
	
};

typedef struct lista lista;


void insere (lista *l,int i){
	lista *novoNo,*aux;
	
	if(l==NULL){
		lista* novoNo = (lista*) malloc(sizeof(lista));
		novoNo->valor=i;
		novoNo->prox = l;
		l=novoNo;

		
		
	}
	
	else{
		aux=l;
		while(aux->prox != l){
			aux=aux->prox;
		}
		lista* novoNo = (lista*) malloc(sizeof(lista));
		aux->prox=novoNo;
		aux=aux->prox;
		aux->valor=i;
		aux->prox=l;
		l=aux;
		printf("aux %d\n",aux->valor);
		
	}	
}
lista* inicializa (void){
   return NULL;
}

int imprime (lista* l){

	
	/*if(l == NULL){

		printf("Lista vazia!\n");

		return 1;
	}*/

	lista* loop=l;

	do{

		printf("{%d} ", loop->valor);

		loop = loop->prox;

	}while(loop != l);
	printf("\n");
	return 0;
}
void doc_insere (lista* l,char *texto){
	int i=0,j=0;
	FILE *file;
	file = fopen(texto,"rt");
	printf("Valores dentro do arquivo: \n");
	for(i=0; !feof(file);i++){
		fscanf(file,"%d\n",&j);
		insere(l,j);
		printf("[%d] ",j);
	}
	printf("\n");
	fclose(file);
	
	printf("quantidade de valores no arq: %d\n",i);		
}


int main(){
	char doc_nome[]="numero1.txt";
	lista* l;     /* declara uma lista não iniciada */
	//l=inicializa();
	//insere(l,1);
	l->valor=1;
	l->prox=NULL;
	printf("%d\n",l->valor );
	//doc_insere(l,doc_nome);
	//imprime(l);        


	return 0;
}