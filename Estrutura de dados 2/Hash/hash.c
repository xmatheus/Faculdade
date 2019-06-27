#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct lista{
	char nome[50];
	int valor;
	struct lista *prox;
};
typedef struct lista tipo_lista;

struct aux{
	char nome[50];
	int valor;
};
typedef struct aux tipo_aux;


void insert_end(tipo_lista **lista,char *nome,int valor);//insere no final
void print(tipo_lista *lista);
int conta(tipo_lista *lista);
void clear_lista(tipo_lista **lista);
void opcao(tipo_lista *lista,tipo_lista *vetor_hash);
void pega_nome(tipo_lista *lista,tipo_aux *aux);
int funcao_hash(int quant,int valor);
void corrigeA(tipo_lista **lista);
void corrigeB(tipo_lista **lista);
int dispersa_hash(tipo_lista *lista,tipo_lista *vetor);
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
		//printf("Inome=%s Irga=%d\n",(*lista)->nome,(*lista)->valor);
	}
	else{
		tipo_lista *tmp=(tipo_lista*)malloc(sizeof(tipo_lista));//aloca memoria para a lista temporaria
		tmp=*lista;//lista temporaria recebe a lista encadeada
		while(tmp->prox!=NULL){//enquanto a lista prox for diferente de NULL
			tmp=tmp->prox;//atualiza a lista para o proximo no ate achar o no vazio
		}
		tmp->prox=new_no;//aloca o novo no no final da lista/como eh ponteiro de ponteiro ele atualiza a lista original
		//printf("Inome=%s Irga=%d\n",new_no->nome,new_no->valor);
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
	printf("Lista encadeada criada com o arquivo 'alunos.txt'\n");

	do{
		
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
int conta_linhas(){
	FILE *file;
	int linhas=0;
	char letra;
	file=fopen("alunos.txt","r");
	if(file == NULL){//teste  de erro
		printf("Erro na abertura do arquivo alunos.txt, ele deve ter o parametro NOME:RGA!\n");
		return 0;
	}
	while(fscanf(file,"%c",&letra)!=EOF){

		if(letra == '\n'){
			
			linhas++;
			
		}
	}
	
	fclose(file);
	return linhas;
}
void pega_nome(tipo_lista *lista,tipo_aux *aux){
	FILE *file;
	int i=0,valor=0,flag=0,numero=0,j=0;
	char letra,nome[100];


	file=fopen("alunos.txt","r");
	if(file == NULL){//teste  de erro
		printf("Erro na abertura do arquivo alunos.txt, ele deve ter o parametro NOME:RGA!\n");
	}
	while(fscanf(file,"%c",&letra)!=EOF){


		if(letra != ':' && letra != '\n' && flag==0){
			
			aux[j].nome[i] = letra;
			i++;
			
		}
		if(letra==':'&& letra != '\n'){
			
			flag=1;
			fscanf(file,"%d",&numero);
			
		}
		if(numero!=0){	
			aux[j].nome[i]='\0';
			aux[j].valor=numero;
			j++;
			numero=0;
		}
		if(letra=='\n'){
			i=0;
			flag=0;
		}
	}
	fclose(file);
}
int dispersa_hash(tipo_lista *lista,tipo_lista *vetor){
	int i=0,indice=0,linhas=0;
	linhas=conta_linhas();
	tipo_lista *tmp=(tipo_lista*)malloc(sizeof(tipo_lista));

	for(i=0;i<linhas;i++){
		strcpy(vetor[i].nome,"$");
		vetor[i].valor=0;
		vetor[i].prox=NULL;
	}
	for(tmp=lista;tmp!=NULL;tmp=tmp->prox){
		indice=funcao_hash(linhas,tmp->valor);

		if(vetor[indice].valor==0){
			strcpy(vetor[indice].nome,tmp->nome);
			vetor[indice].valor=tmp->valor;
			vetor[indice].prox=NULL;
		}
		else{
			tipo_lista *aux;
			if(vetor[indice].prox==NULL){
				aux=(tipo_lista*)malloc(sizeof(tipo_lista));
				strcpy(aux->nome,tmp->nome);
				aux->valor=tmp->valor;
				aux->prox=NULL;
				vetor[indice].prox=aux;
			}
			else{
				aux=vetor[indice].prox;
				while(aux->prox!=NULL){
					aux=aux->prox;
				}
				aux->prox=(tipo_lista*)malloc(sizeof(tipo_lista));
				strcpy(aux->prox->nome,tmp->nome);
				aux->prox->valor=tmp->valor;
				aux->prox->prox=NULL;
			}
		}
	}
	puts("Dispersão 100% concluida com sucesso");

	
	
}
void printa_vetor(tipo_lista *lista,tipo_lista *vetor){
	int cont,i;
	cont=conta_linhas();
	tipo_lista *aux;
	if(lista==NULL){
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
void abre_cria(tipo_aux *aux,tipo_lista *lista){
	int linhas;
	linhas=conta_linhas();
	for(int i=0;i<linhas;i++){
		insert_end(&lista,aux[i].nome,aux[i].valor);
	}
}

int main(){
	system("clear");
	int cont=0,linhas=0;

	tipo_lista *lista = NULL;
	linhas=conta_linhas();

	tipo_aux *aux=(tipo_aux*)malloc(sizeof(tipo_aux)*linhas);
	
	pega_nome(lista,aux);
	cont=conta(lista);
	
	tipo_lista *vetor_hash=(tipo_lista*)malloc(sizeof(tipo_lista)*linhas);	
	
	for(int i=0;i<linhas;i++){
		
		insert_end(&lista,aux[i].nome,aux[i].valor);
	}

	//abre_cria(aux,lista);
	opcao(lista,vetor_hash);

	return 0;
}