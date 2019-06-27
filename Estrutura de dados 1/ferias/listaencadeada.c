#include <stdio.h>
#include <stdlib.h>


struct lista{
	int valor;
	struct lista *prox;
};

typedef struct lista tipo_lista;

void insert_end(tipo_lista **lista,int valor);//insere no final
void insert_start(tipo_lista **lista,int valor);//insere no inicio
void print(tipo_lista *lista);//mostra a lista encadeada
void remove_valor(tipo_lista **lista,int valor);
void clear_lista(tipo_lista **lista);
void opcao(tipo_lista *lista);



int check_null(tipo_lista *lista){
	if(lista==NULL){//se lista for vazia retorn 1
		return 1;
	}
	else{//se nao retorna 0
		return 0;
	}
}
void insert_end(tipo_lista **lista,int valor){
	tipo_lista *new_no=(tipo_lista*)malloc(sizeof(tipo_lista));//aloca memoria para o novo no
	new_no->valor=valor;//novo no recebe valor
	new_no->prox=NULL;//novo no prox aponta para NULL
	
	if(*lista==NULL){//se lista for vazia
		printf("lista vazia, inserindo no final!\n");//informa que a lista esta vazia
		*lista=(tipo_lista*)malloc(sizeof(tipo_lista));
		*lista=new_no;//a lista eh preenchida com o novo no
	}
	else{
		tipo_lista *tmp=(tipo_lista*)malloc(sizeof(tipo_lista));//aloca memoria para a lista temporaria
		tmp=*lista;//lista temporaria receeve a lista
		while(tmp->prox!=NULL){//enquanto a lista prox for diferente de NULL
			tmp=tmp->prox;//atualiza a lista para o proximo no ate achar o no vazio
		}
		tmp->prox=new_no;//aloca o novo no no final da lista/como eh ponteiro de ponteiro ele atualiza a lista original

	}
}
void insert_start(tipo_lista **lista,int valor){
	tipo_lista *new_no=(tipo_lista*)malloc(sizeof(tipo_lista));//aloca memoria para o novo no
	if(*lista==NULL){//testa para ver se esta vazia
		new_no->valor=valor;//novo no receve o valor
		new_no->prox=NULL;//novo no prox aponta para NULL
		*lista=new_no;//lista recebe o novo no
		//printf("lista vazia,inserindo no comeco\n");
	}
	else{//se nao 
		
		new_no->valor=valor;//novo no valor recebe valor
		new_no->prox=*lista;//novo no prox aponta para o comeco da lista
		*lista=new_no;// a lista recebe o novo no/como o novo no aponta para um lista quase identica com um novo valor entao a lista inteira e atualizada com o novo valor

	}

}
void print(tipo_lista *lista){
	tipo_lista *tmp=(tipo_lista*)malloc(sizeof(tipo_lista));//aloca memoria para a lista temporaria
	if(lista==NULL){//se a lista for vazia
		printf("lista vazia\n");
	}
	else{//caso esteja preenchida
		for(tmp=lista;tmp!=NULL;tmp=tmp->prox){//atualiza o temporario ate chegar no no vazio
			printf("%d->",tmp->valor);//mostra os valores presentes no temporario
		}
		printf("NULL\n");//print para quebrar linha e mostrar toda lista ate o no NULL
	}
}

void remove_valor(tipo_lista **lista,int valor){
	tipo_lista *tmp1=(tipo_lista*)malloc(sizeof(tipo_lista));
	tipo_lista *tmp2=(tipo_lista*)malloc(sizeof(tipo_lista));
	tmp1=*lista;
	int marcador=0;
	while(tmp1->valor != valor && tmp1!=NULL){
		tmp2=tmp1;
		tmp1=tmp1->prox;
		marcador=1;
	}
	if(marcador==1){
		tmp2->prox=tmp1->prox;
		printf("valor removido\n");
	}
	else if(marcador==0 && tmp1->prox ==NULL){
		free(tmp1);
		printf("lista completamente vazia\n");
	}
	else if(marcador==0 && tmp1->prox !=NULL){
		*lista=(*lista)->prox;
		//tmp1=tmp1->prox;
		printf("Valor removido\n");
	}
	
	
}
void clear_lista(tipo_lista **lista){
	tipo_lista *tmp=(tipo_lista *)malloc(sizeof(tipo_lista));
	tmp=*lista;
	while(tmp!=NULL){
		free(tmp);
		*lista=(*lista)->prox;
		tmp=(*lista)->prox;
	}
	*lista=NULL;

	
	printf("Lista limpa\n");
}
void insere_posicao(tipo_lista **lista, int valor,int posicao){
	tipo_lista *tmp=(tipo_lista *)malloc(sizeof(tipo_lista));
	tipo_lista *new_no=(tipo_lista *)malloc(sizeof(tipo_lista));
	tmp=*lista;
	while(tmp->valor!=posicao && tmp!=NULL){
		tmp=tmp->prox;
	}
	if(tmp!=NULL){
		new_no->valor=valor;
		new_no->prox=tmp->prox;
		tmp->prox=new_no;
	}
	else{
		printf("impossivel alocar\n");
	}

}
void opcao(tipo_lista *lista){
	int valor,numero,posicao;

	system("clear");
	do{
		
		printf("\nLista encadeada-opções:\n\n1-Inserir no inicio\t|\t2-Inserir no final \n3-Mostrar lista    \t|\t4-remove da lista  \n5-zerar lista      \t|\t6-Insere depois do valor\n7-Sair\n\nopcao: ");
		scanf("%d",&valor);
		switch(valor){
			system("clear");
			case 1:
				system("clear");
				printf("Digite o valor a ser inserido\n");scanf("%d",&numero);
				insert_start(&lista,numero);//insere os valores no comeco da lista
				break;
			case 2:
				system("clear");
				printf("Digite o valor a ser inserido\n");scanf("%d",&numero);
				insert_end(&lista,numero);//insere os valores
				break;
			case 3:
				system("clear");
				print(lista);
				break;
			case 4:
				system("clear");
				printf("Digite o valor a ser removido\n");scanf("%d",&numero);
				remove_valor(&lista,numero);
				break;
			case 5:
				system("clear");
				clear_lista(&lista);
				break;
			case 6:
				system("clear");
				printf("Digite o novo valor a ser alocado:\n");scanf("%d",&numero);
				printf("Depois de qual valor ele deve ser alocado: ");scanf("%d",&posicao);
				insere_posicao(&lista,numero,posicao);
				break;	
		}
	} while (valor!=7);
}

int main(){
	tipo_lista *lista=NULL;;//inicia o ponteiro apontando para vazio
	//insert_start(&lista,10);//insere os valores
	//insert_start(&lista,20);
	//insert_start(&lista,30);
	//print(lista);//mostra os valores inseridos
	//insert_end(&lista,5);//insere os valores no final
	//insert_end(&lista,2);
	//insert_end(&lista,1);
	//print(lista);
	opcao(lista);
	return 0;
}