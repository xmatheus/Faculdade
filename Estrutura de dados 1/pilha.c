#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct pilha{
	int numero;
	struct pilha *prox;
};
typedef struct pilha tipo_pilha;



tipo_pilha *inicializa(tipo_pilha *pilha){
	pilha=(tipo_pilha *)malloc(sizeof(tipo_pilha));
	
	pilha->prox=NULL;
	//printf("OK\n");
	return pilha;
}
tipo_pilha *empilha(tipo_pilha *pilha,int valor){
	tipo_pilha *novo_no=inicializa(novo_no);
	//printf("valor %d\n",valor);
	if(pilha->prox==NULL){
		pilha->numero=valor;
		pilha->prox=NULL;
		novo_no->prox=pilha;
		printf("pilha->numero %d\n",pilha->numero );
		return novo_no;
	}

	
	novo_no->numero=valor;
	printf("novo_no->numero %d\n",novo_no->numero );
	novo_no->prox=pilha;
	return novo_no;

}
tipo_pilha *desempilha(tipo_pilha *pilha){
	printf("começou desempilha\n");
	tipo_pilha *proximo=inicializa(proximo);
	int i=0;
	proximo=pilha->prox;

	while(proximo!=NULL){
		free(pilha);
		pilha=proximo;
		proximo=pilha->prox;
		i++;
		printf("\tsem %d\n",i );
	}
	return proximo;

}
tipo_pilha *exibe(tipo_pilha *pilha){
	printf("começou a exibir\n");
	if(pilha==NULL){
		printf("Pilha vazia, impossivel exibir\n");
		return 0;
	}
	tipo_pilha *mostra;
	mostra=pilha;
	printf("topo->");
	while(mostra->prox!=NULL){
		printf("\t%d\n",mostra->numero);
		mostra=mostra->prox;
	}
	
}

int main(){
	tipo_pilha *pilha;
	pilha=inicializa(pilha);
	//printf("OK mainss\n");
	
	int i=0;
	for(i=0;i<10;i++){
		pilha=empilha(pilha,i);
		
	}

	exibe(pilha);
	pilha=desempilha(pilha);
	if(pilha==NULL){
		printf("vazia\n");
	}















	return 0;
}
