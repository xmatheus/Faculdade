#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
/*
 * UFMT - CUA - Ciência da Computação
 * Disciplina: ED2
 * Professor: Ivairton M. Santos
 * Autor: Matheus Felipe Teodoro Correia
 *
 * Algoritmo de uma arvore AVL
 * 
 */

/*struct arvore
 *guarda o valor
 *fator de balanceamento
 *ponteiro para a esquerda 
 *ponteiro para a direita
 */	
struct arvore{
	int valor;
	int fb;
	struct arvore *esq;
	struct arvore *dir;
};
typedef struct arvore tipo_arvore;

//struct para facilitar a contagem das rotacoes
struct conta{
	int cont;
};
typedef struct conta tipo_conta;


//prototipos das funcoes
int insere(tipo_arvore **arvore,int valor,tipo_conta *rotacao);//insere valores na arvore recebendo como paramentro um ponteiro de ponteiro e o valor a ser alocado
void pega_numero(tipo_arvore **arvore,tipo_conta *rotacao,char *argv);//abre o arquivo com os valores a serem inseridos na arvore
void rotacaoEsquerda(tipo_arvore **arvore);//rotaciona determinado ponto da arvore a esquerda
void rotacaoDireita(tipo_arvore **arvore);//rotaciona determinado ponto da arvore a direita
void duplarotacaoEsq(tipo_arvore **arvore);//rotaciona determinado ponto da arvore a direita e esquerda
void duplarotacaoDir(tipo_arvore **arvore);//rotaciona determinado ponto da arvore a esquerda e direita
void imprime(tipo_arvore *p, int nivel);//mostra a arvore de lado
void verificaEsquerda(tipo_arvore **arvore, tipo_conta *rotacao);//verifica se eh necessario rotacaionar
void verificaDireita(tipo_arvore **arvore, tipo_conta *rotacao);//verifica se eh necessario rotacaionar

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
void pega_numero(tipo_arvore **arvore,tipo_conta *rotacao,char *argv){//funcao que pega os valores do arquivo para inserir na arvore
	FILE *file;
	int i=0,j=0,trash;
	int numero=0;
	char nomearq[100];

	strcpy(nomearq,argv);
	file=fopen(nomearq,"r");
	if(file == NULL){//teste  de erro
		printf("Erro na abertura do arquivo %s!\n",nomearq);
	}
	while(fscanf(file,"%d",&numero)!=EOF){
		trash=insere(arvore,numero,rotacao);
	}
	
	fclose(file);
	printf("[x]Valores inseridos\n");
}
int insere(tipo_arvore **arvore,int valor,tipo_conta *rotacao){//funcao de insercao
	int flag=0,total=0;
	if((*arvore) == NULL){
		(*arvore)=(tipo_arvore *)malloc(sizeof(tipo_arvore));
		if((*arvore) != NULL){
			(*arvore)->valor=valor;
			(*arvore)->esq=NULL;
			(*arvore)->dir=NULL;
			(*arvore)->fb=0;
			return 1;
		}
		else{
			return 0;
		}
	}
	if( valor < (*arvore)->valor){//recursiavmente pela esq, valor menor
		flag = insere(&(*arvore)->esq, valor,rotacao);//retorna uma flag de sucesso
		if(flag){//Se ocorrer sucesso na inserção, verifica o balanceamento da árvore, executando uma rotação (a ser verificada) se necessário.
			switch((*arvore)->fb){//teste com o coeficiente de balaceamento
				case 1://arvore mais pesada a direita, mas adc a esq, balanceamento igual
					(*arvore)->fb = 0;
					flag = 0;
					break;
				case 0://arvore balanceada, mas adc a esq, -1 por conta que foi a esq
					(*arvore)->fb = -1;
					break;
				case -1://adc a esq,vai ficar desbalanceado, verifica o tipo de rotacao
					verificaEsquerda(arvore,rotacao);
					flag = 0;
					break;
			}
		}
	}
	else if(valor > (*arvore)->valor){//recursiavmente pela dir, valor maior
		flag = insere(&(*arvore)->dir,valor,rotacao);
		if(flag){
			switch((*arvore)->fb){
				case -1://arvore mais pesada a esquerda, mas adc a direita, balanceamento igual
					(*arvore)->fb = 0;
					flag = 0;
					break;
				case 0://arvore balanceada, mas adc a direita, +1 por conta que foi a direita
					(*arvore)->fb = 1;
					break;
				case 1://adc a direita,vai ficar desbalanceado, verifica o tipo de rotacao
					verificaDireita(arvore,rotacao);
					flag = 0;
					break;
			}
		}
	}
	else{
		flag = 0;
	}
	return flag;	
}
void verificaEsquerda(tipo_arvore **arvore, tipo_conta *rotacao){
	tipo_arvore *aux;
	aux = (*arvore)->esq;
	if(aux->fb == -1){
		rotacaoDireita(arvore);
		rotacao->cont++;
	}
	else{
		duplarotacaoDir(arvore);
		rotacao->cont=rotacao->cont+2;
	}
	(*arvore)->fb = 0;
}
void verificaDireita(tipo_arvore **arvore, tipo_conta *rotacao){
	tipo_arvore *aux;
	aux = (*arvore)->dir;
	if(aux->fb == 1){
		rotacaoEsquerda(arvore);
		rotacao->cont++;
	}
	else{
		duplarotacaoEsq(arvore);
		rotacao->cont=rotacao->cont+2;
	}
	(*arvore)->fb = 0;
}



void rotacaoEsquerda(tipo_arvore **arvore){
	tipo_arvore *aux;
	aux=(*arvore)->dir;
	(*arvore)->dir=aux->esq;
	aux->esq=*arvore;
	(*arvore)->fb = 0;
	aux->fb = 0;//talves precise retirar isso aqui
	*arvore=aux;
}
void rotacaoDireita(tipo_arvore **arvore){
	tipo_arvore *aux;
	aux=(*arvore)->esq;
	(*arvore)->esq=aux->dir;
	aux->dir=*arvore;
	(*arvore)->fb = 0;
	aux->fb = 0;
	*arvore=aux;
}
void duplarotacaoEsq(tipo_arvore **arvore){
	tipo_arvore *aux, *tmp;
	aux = (*arvore)->dir;
	tmp = aux->esq;
	aux->esq = tmp->dir;
	tmp->dir = aux;
	(*arvore)->dir = tmp->esq;
	tmp->esq = *arvore;
	if(tmp->fb == -1){
		(*arvore)->fb = 0;
		aux->fb = 1;
	}
	else if(tmp->fb == 0){
		(*arvore)->fb = 0;
		aux->fb = 0;
	}
	else if(tmp->fb == 1){
		(*arvore)->fb = -1;
		aux->fb = 0;
	}
	*arvore = tmp;
}
void duplarotacaoDir(tipo_arvore **arvore){
	tipo_arvore *aux, *tmp;
	aux = (*arvore)->esq;
	tmp = aux->dir;
	aux->dir = tmp->esq;
	tmp->esq = aux;
	(*arvore)->esq = tmp->dir;
	tmp->dir = *arvore;
	if(tmp->fb == -1){
		(*arvore)->fb = 1;
		aux->fb = 0;
	}
	else if(tmp->fb == 0){
		(*arvore)->fb = 0;
		aux->fb = 0;
	}
	else if(tmp->fb == 1){
		(*arvore)->fb = 0;
		aux->fb = -1;
	}
	*arvore = tmp;
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
void gravar(int altura,tipo_conta *rotacao){//funcao que guarda as rotacoes e altura em um arquivo
	FILE *file;
	//data e hora, cria variaveis
	struct tm *local;
	time_t t;
	t= time(NULL);
	local=localtime(&t);
	int dia,mes,ano,hora,minuto;
	dia = local->tm_mday;
	mes = local->tm_mon+1;
	ano = local->tm_year+1900;
	hora = local->tm_hour;
	minuto = local->tm_min;

	if(!(file=fopen("info-AVL.txt","a"))){
		printf("Falha na abertura do arquivo 'info-ARVORES.txt'\n");
	}
	fprintf(file, "\nArvore AVL [%d/%d/%d %d:%d]{\n\tAltura=%d\n\tRotacoes=%d\n}",dia,mes,ano,hora,minuto,altura,rotacao->cont);
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
	tipo_arvore *arvore=NULL;
	tipo_conta *rotacao=(tipo_conta*)malloc(sizeof(tipo_conta));
	FILE *file;
	
	if(argc == 2){
		do{
			
			printf("1-Ler arquivo e inserir valores\n2-Mostrar arvore(se for grande, vai bugar)\n3-Mostrar altura e quantidade de rotacoes\n4-Sair\n");
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
					imprime(arvore,0);
					
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
		//imprime(arvore,0);
	}
	return 0;
}
