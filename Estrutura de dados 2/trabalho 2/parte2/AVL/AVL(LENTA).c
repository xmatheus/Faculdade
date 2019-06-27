#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//struct arvore
struct arvore{
	long int valor;
	int fb;
	struct arvore *esq;
	struct arvore *dir;
};
typedef struct arvore tipo_arvore;
struct conta{
	int cont;
};
typedef struct conta tipo_conta;


//prototipos das funcoes
void insere(tipo_arvore **arvore,long int valor,tipo_conta *rotacao);//insere valores na arvore recebendo como paramentro um ponteiro de ponteiro e o valor a ser alocado
tipo_arvore *inicializa();//inicializa a arvore como NULL
void mostra_arvore(tipo_arvore *arvore);//printa a arvore em ordem so que do maior para o menos
void pega_numero(tipo_arvore **arvore,tipo_conta *rotacao,char *argv);
int fator(tipo_arvore **arvore);
void verifica_altura(tipo_arvore **arvore);
void rotacaoEsquerda(tipo_arvore **arvore);
void rotacaoDireita(tipo_arvore **arvore);
void duplarotacaoEsq(tipo_arvore **arvore);
void duplarotacaoDir(tipo_arvore **arvore);
void gravar(int altura,tipo_conta *rotacao);
void imprime(tipo_arvore *p, int nivel);

void verifica_altura(tipo_arvore **arvore){//verifica altura de toda a arvore
	if(*arvore!=NULL){
		(*arvore)->fb=fator(arvore);
		verifica_altura(&(*arvore)->esq);
		verifica_altura(&(*arvore)->dir);
	}
}
int altura(tipo_arvore *arvore){//verifica a altura do noh
    int esq, dir;

    if (arvore == NULL){
    	return -1;	
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
int fator(tipo_arvore **arvore){//calcula o fator de balanceamento
	int esq,dir,total;
	dir=altura((*arvore)->dir);
	esq=altura((*arvore)->esq);
	
	total=dir-esq;
	return total;
}
void pega_numero(tipo_arvore **arvore,tipo_conta *rotacao,char *argv){//funcao que pega os valores do arquivo para inserir na matriz
	FILE *file;
	int i=0,j=0;
	long int numero=0;
	char nomearq[100];

	strcpy(nomearq,argv);
	file=fopen(nomearq,"r");
	if(file == NULL){//teste  de erro
		printf("Erro na abertura do arquivo %s!\n",nomearq);
	}
	while(fscanf(file,"%ld",&numero)!=EOF){
		//printf("%ld\n",numero );
		insere(arvore,numero,rotacao);
	}
	
	verifica_altura(arvore);//checa todo fator de balanceamento de cada noh da arvore
	fclose(file);
	printf("[x]Valores inseridos\n");
}
void insere(tipo_arvore **arvore,long int valor,tipo_conta *rotacao){//funcao de insercao
	int flag=0,total=0;
	if((*arvore) == NULL){//se a arvore for vazia ele aloca o novo valor e aponta a esq e dir para NULL
		(*arvore)=(tipo_arvore *)malloc(sizeof(tipo_arvore));
		(*arvore)->valor=valor;
		(*arvore)->esq=NULL;
		(*arvore)->dir=NULL;
		(*arvore)->fb=0;
	}
	else{		
		if(valor>=(*arvore)->valor){//se valor for maior que o ponteiro da arvore->valor ele chama a funcao recursivamente pela direita			
			insere(&(*arvore)->dir,valor,rotacao);			
			(*arvore)->fb=fator(arvore);
		}
		else if(valor<=(*arvore)->valor){//se nao se, valor for menor que o ponteiro da arvore->valor ele chama a funcao recursivamente pela esquerda
			insere(&(*arvore)->esq,valor,rotacao);
			(*arvore)->fb=fator(arvore);	
		}
		if(((*arvore)->fb <= -2 ) && ((*arvore)->dir->fb < 0)){//se fb neagtivo entao desbalanceado pra direita
			//printf("Deslabalanceado pra direita\n");
			rotacaoEsquerda(arvore);
			rotacao->cont++;
			flag=1;
			
		}
		 if(((*arvore)->fb >= 2) && ((*arvore)->esq->fb > 0)){//se fb positivo entao desbalanceado pra esquerda
			//printf("Deslabalanceado pra esquerda\n");
			rotacaoDireita(arvore);
			rotacao->cont++;
			flag=1;
		}
		if(flag==0){	
			if(((*arvore)->fb == -2) && ((*arvore)->dir !=NULL) && ((*arvore)->dir->fb > 0)){//rotacao dupla para a esquerda
				//printf("Rotacao dupla para a esquerda\n");
				duplarotacaoEsq(arvore);
				(*arvore)->fb=fator(arvore);
				flag=1;
				rotacao->cont=rotacao->cont+2;
				
			}
			if(((*arvore)->fb == 2) && ((*arvore)->esq != NULL) && ((*arvore)->esq->fb < 0)){//rotacao dupla para direita
				//printf("Rotacao dupla para a direita\n");
				duplarotacaoDir(arvore);
				(*arvore)->fb=fator(arvore);
				flag=1;
				rotacao->cont=rotacao->cont+2;
				
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
	//(*arvore)->fb=fator(arvore);
	(*arvore)->fb=0;
	(*arvore)->esq->fb=0;	
}
void rotacaoDireita(tipo_arvore **arvore){
	tipo_arvore *aux;
	aux=(*arvore)->esq;
	(*arvore)->esq=aux->dir;
	aux->dir=*arvore;
	*arvore=aux;
	//(*arvore)->fb=fator(arvore);
	(*arvore)->fb=0;
	(*arvore)->dir->fb=0;
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
		printf("Valor=%ld FB=%d\n",arvore->valor,arvore->fb);//mostra o valor
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
void imprime(tipo_arvore *p, int nivel){
	int i;
	
	if(p == NULL){
		return;
	}
	
	imprime(p->dir, nivel+1);
	
	for(i=0;i<nivel;i++){
        printf("\t");
    }
	printf("%d(%d)\n\n",p->valor,p->fb);
	imprime(p->esq,nivel+1);
     
}
void gravar(int altura,tipo_conta *rotacao){
	FILE *file;

	if(!(file=fopen("info-ARVORES.txt","a"))){
		printf("Falha na abertura do arquivo 'info-ARVORES.txt'\n");
	}
	fprintf(file, "\nArvore AVL:\nAltura=%d\nRotacoes=%d\n",altura,rotacao->cont);
	fclose(file);
	printf("[x]Informacoes gravadas\n");
}
int main(int argc, char *argv[ ]){
	int marcador,numero,valor,alt,i,j,cmp;
	
	if(argc==1){
		system("clear");
		printf("\t[x]Utilize %s 'nome do arquivo'\n\t[x]O arquivo deve estar na mesma pasta do algoritmo, o conteudo do arquivo deve ser de numeros inteiros.\n\t[x]para gravar a altura e rotacoes no arquivo Utilize %s 'nome do arquivo' -G, o menu de opcoes sera ignorado\n\n",argv[0],argv[0]);
		return 0;
	}
	tipo_arvore *arvore=inicializa();//inicializando a arvore vazia
	tipo_conta *rotacao=(tipo_conta*)malloc(sizeof(tipo_conta));
	FILE *file;
	
	if(argc == 2){
		do{
			
			printf("1-Ler arquivo e inserir valores\n2-Mostrar arvore\n3-Mostrar altura e quantidade de rotacoes\n4-Sair\n");
			scanf("%d",&valor);
			switch(valor){
			
				case 1:
					system("clear");
					printf("[x]Iniciando insercao e balanceamento\n");
					pega_numero(&arvore,rotacao,argv[1]);
					alt=altura(arvore);
					break;
				case 2:
					system("clear");
					mostra_arvore(arvore);
					
					break;
				case 3:
					system("clear");
					printf("\n[x]Altura=%d\n[x]Rotacoes=%d\n",alt,rotacao->cont);	
			}	

		} while (valor!=4);
	}
	else{
		printf("[x]Iniciando insercao e balanceamento\n");
		pega_numero(&arvore,rotacao,argv[1]);
		alt=altura(arvore);
		cmp=strcmp(argv[2],"-G");
		if(cmp==0){
			gravar(alt,rotacao);
		}
		imprime(arvore,0);
	}

	return 0;
}
