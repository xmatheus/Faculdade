#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct lista{
	char nome[50];
	int valor;
	struct lista *prox;
};
typedef struct lista tipo_lista;


void insert_end(tipo_lista **lista,char *nome,int valor);//insere no final
void print(tipo_lista *lista);
int conta(tipo_lista *lista);
void clear_lista(tipo_lista **lista);
void opcao(tipo_lista *lista,tipo_lista *vetor_hash);
int pega_nome(tipo_lista *lista);
int funcao_hash(int quant,int valor);
void corrigeA(tipo_lista **lista);
void corrigeB(tipo_lista **lista);
void dispersa_hash(tipo_lista *lista,tipo_lista *vetor);
void printa_vetor(tipo_lista *lista,tipo_lista *vetor);

void insert_end(tipo_lista **lista,char *nome,int valor){
	tipo_lista *new_no=(tipo_lista*)malloc(sizeof(tipo_lista));//aloca memoria para o novo no
	strcpy(new_no->nome,nome);
	new_no->valor=valor;//novo no recebe valor
	new_no->prox=NULL;//novo no prox aponta para NULL

	if(*lista==NULL){//se lista for vazia
		*lista=(tipo_lista*)malloc(sizeof(tipo_lista));
		printf("lista vazia, inserindo no final!\n");//informa que a lista esta vazia
		*lista=new_no;//a lista eh preenchida com o novo noh
	}
	else{
		tipo_lista *tmp=(tipo_lista*)malloc(sizeof(tipo_lista));//aloca memoria para a lista temporaria
		tmp=*lista;//lista temporaria recebe a lista encadeada
		while(tmp->prox!=NULL){//enquanto a lista prox for diferente de NULL
			tmp=tmp->prox;//atualiza a lista para o proximo no ate achar o no vazio
		}
		tmp->prox=new_no;//aloca o novo no no final da lista/como eh ponteiro de ponteiro ele atualiza a lista original
	}
}
void print(tipo_lista *lista){
	int cont,hash;
	cont=conta(lista);
	printf("conta printa=%d\n",cont);
	tipo_lista *tmp=(tipo_lista*)malloc(sizeof(tipo_lista));//aloca memoria para a lista temporaria
	if(lista==NULL){//se a lista for vazia
		printf("lista vazia\n");
	}
	else{//caso esteja preenchida
		for(tmp=lista;tmp!=NULL;tmp=tmp->prox){//atualiza o temporario ate chegar no no vazio
			hash=funcao_hash(cont,tmp->valor);	
			printf("Nome[%s]\nRGA[%d]\nHASH[%d]\n↓\n",tmp->nome,tmp->valor,hash);//mostra os valores presentes no temporario
		}
		printf("NULL\n");//print para quebrar linha e mostrar toda lista ate o no NULL
	}
}
int conta(tipo_lista *lista){
	tipo_lista *tmp=(tipo_lista*)malloc(sizeof(tipo_lista));//aloca memoria para a lista temporaria
	int cont=0;
	if(lista==NULL){//se a lista for vazia
		cont=0;
	}
	else{//caso esteja preenchida
		for(tmp=lista;tmp!=NULL;tmp=tmp->prox){//atualiza o temporario ate chegar no noh NULL
			cont++;
			//printf("%d\n",cont);
		}
		
	}
	return cont;
}
void clear_lista(tipo_lista **lista){
	tipo_lista *tmp=(tipo_lista *)malloc(sizeof(tipo_lista));
	tmp=*lista;
	while(tmp!=NULL){
		free(tmp);
		tmp=NULL;
		*lista=(*lista)->prox;
		tmp=(*lista)->prox;
			

	}
	*lista=NULL;

	
	printf("Lista limpa\n");
}
void opcao(tipo_lista *lista,tipo_lista *vetor_hash){
	int ra,valor,numero,posicao,cont=0;
	char palavra[100];
	
	system("clear");
	

	do{
		printf("Lista encadeada criada com o arquivo 'alunos.txt'\n");
		printf("\nLista encadeada-opções:\n\n1-Inserir no final\n2-Mostrar lista\n3-mostra a quantidade de valores na lista\n4-Limpar lista\n5-Hash vetor\n6-Mostrar vetor\n7-SAIR\n\nopcao: ");
		scanf("%d",&valor);
		switch(valor){
			system("clear");
			case 1:
				system("clear");
				printf("Nome aluno :");
				scanf(" %[^\n]s", &palavra);
				printf("RA :");
				scanf("%d", &ra);
				insert_end(&lista,palavra,ra);//insere os valores
				break;
			case 2:
				system("clear");
				print(lista);
				break;
			case 3:
				system("clear");
				cont=conta(lista);
				printf("quantidade de alunos na lista=%d\n",cont);
				break;
			case 4:
				system("clear");
				clear_lista(&lista);
				break;
			case 5:
				system("clear");
				dispersa_hash(lista,vetor_hash);
				break;
			case 6:
				system("clear");
				printa_vetor(lista,vetor_hash);

		}
	} while (valor!=7);
}
int funcao_hash(int quant,int valor){
	int indice;
	indice=valor%quant;
	return indice;

}
int pega_nome(tipo_lista *lista){
	FILE *file;
	int i=0,valor=0,flag=0,numero=0;
	char letra,nome[100];
	
	file=fopen("alunos.txt","r");
	if(file == NULL){//teste  de erro
		printf("Erro na abertura do arquivo alunos.txt, ele deve ter o parametro NOME:RGA!\n");
		return 0;
	}
	while(fscanf(file,"%c",&letra)!=EOF){

		if(letra != ':' && letra != '\n' && flag==0){
			
			nome[i] = letra;
			i++;
			
		}
		if(letra==':'&& letra != '\n'){
			
			flag=1;
			fscanf(file,"%d",&numero);
			
		}
		if(numero!=0){	
			valor=numero;
			char *frase=malloc(sizeof(char)*i);
			for(int k=0;k<i;k++){
				frase[k]=nome[k];
			}
			printf("%s\n",frase);
			insert_end(&lista,frase,valor);
			free(frase);
			frase=NULL;
			numero=0;
		}
		if(letra=='\n'){
			i=0;
			flag=0;
		}
	}
	fclose(file);
}
void dispersa_hash(tipo_lista *lista,tipo_lista *vetor){
	
	tipo_lista *tmp=(tipo_lista *)malloc(sizeof(tipo_lista));
	tmp=lista;
	int indice=0,cont,i=0;
	cont=conta(lista);
	tipo_lista *aux=NULL;
	for(i=0;i<cont;i++){
		vetor[i].nome[0]='$';
		vetor[i].valor=0;
		vetor[i].prox=NULL;
	}
	while(tmp!=NULL){

		indice=funcao_hash(cont,tmp->valor);
		printf("indice=%d ",indice);
		if(vetor[indice].valor==0){
			strcpy(vetor[indice].nome,tmp->nome);
			vetor[indice].valor=tmp->valor;
			vetor[indice].prox=NULL;
			printf("nome: %s rga: %d\n",vetor[indice].nome,vetor[indice].valor);
			tmp=tmp->prox;	
		}
		else{
			aux=vetor[indice].prox;
			while(aux!=NULL){
				aux=aux->prox;
			}
			aux=tmp;
			printf("Cnome: %s rga: %d\n",aux->nome,aux->valor);
			aux->prox=NULL;
			tmp=tmp->prox;
			vetor[indice].prox=aux;
			printf("Vnome: %s rga: %d\n",vetor[indice].nome,vetor[indice].valor);
		}
	}
}
void printa_vetor(tipo_lista *lista,tipo_lista *vetor){
	int cont,i;
	cont=conta(lista);
	printf("cont printa_vetor=%d\n",cont);
	tipo_lista *aux;
	if(lista!=NULL){
		printf("lista==NULL\n");
	}
	else{
		for(i=0;i<cont;i++){
			if(vetor[i].valor!=0){
				printf("NOME: %s ",vetor[i].nome);
				printf("RGA: %d",vetor[i].valor);
				if(vetor[i].prox!=NULL){
					aux=vetor[i].prox;
					while(aux!=NULL){
						printf(" -> ");
						printf("NOME: %s",aux->nome);
						printf(" RGA: %d",aux->valor);
						aux=aux->prox;
					}
				}
				printf("\n");
			}
		}
	}
}


int main(){
	system("clear");
	int cont=0;
	tipo_lista *lista = NULL;
	pega_nome(lista);
	cont=conta(lista);
	tipo_lista *vetor_hash=(tipo_lista*)malloc(sizeof(tipo_lista)*cont);	
	opcao(lista,vetor_hash);

	return 0;
}