#include <stdio.h>
#include <stdlib.h>

struct Lista{
	int valor;
	struct lista *prox;
};
typedef struct Lista lista;


lista* cria_lista();
int tamanho_lista(lista* li);
int insere_inicio(lista* li, int valor);

lista* cria_lista(){
	lista* li= (lista*) malloc(sizeof(lista));
	if (li != NULL){
		li = NULL;
	}
	return li;
}


int insere_inicio(lista* li, int valor){
	if(li==NULL){
		return 0;
	}
	lista *no=(lista*) malloc(sizeof(lista));
	if(no==NULL){
		return 0;
	}
	no->valor=valor;

	if((li)==NULL){
		li=no;
		no->prox=no;
	}
	else{
		lista *aux=li;

		while (aux->prox != (li)){
			aux=aux->prox;
		}
		aux->prox=no;
		no->prox=li;
		li=no;
	}
}



int main(){
	lista* li;
	li = cria_lista();
	int tamaho1=0;

	insere_inicio(li,10);
	insere_inicio(li,20);
	printf("Valor\n",li->valor);

	//tamanho1=tamanho_lista(li);



	return 0;
}