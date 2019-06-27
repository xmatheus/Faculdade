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
 * Algoritmo de uma arvore Binaria(classica)
 * 
 */

/*struct arvore
 *guarda o valor
 *ponteiro para a esquerda 
 *ponteiro para a direita
 */	
struct arvore{
	int valor;
	struct arvore *esq;
	struct arvore *dir;
};
typedef struct arvore tipo_arvore;

//prototipos das funcoes
void insere(tipo_arvore **arvore,int valor);//insere valores na arvore recebendo como paramentro um ponteiro de ponteiro e o valor a ser alocado
void imprime(tipo_arvore *p, int nivel);//funcao que mostra a arvore de lado em pre-ordem
int busca_arvore(tipo_arvore *arvore, int valor, int marcador);//funcao para buscar um valor na arvore
void pega_numero(tipo_arvore **arvore,char *argv);//abre o arquivo com os valores a serem inseridos na arvore
int altura(tipo_arvore *arvore);//percorre a arvore e retorna a altura
void gravar(int altura);//funcao que guarda as rotacoes e altura em um arquivo

int altura(tipo_arvore *arvore){//retorn a altura
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
void insere(tipo_arvore **arvore,int valor){//insere novos valores na arvore de maneira recursiva
	if((*arvore) == NULL){//se a arvore/noh for vazio ele aloca o novo valor e aponta a esq e dir para NULL
		(*arvore)=(tipo_arvore *)malloc(sizeof(tipo_arvore));//alocando o novo noh
		(*arvore)->valor=valor;
		(*arvore)->esq=NULL;
		(*arvore)->dir=NULL;
	}
	else{
		if(valor>=(*arvore)->valor){//se valor for maior que o ponteiro da arvore->valor ele chama a funcao recursivamente pela direita
			insere(&(*arvore)->dir,valor);
		}
		else if(valor<=(*arvore)->valor){//se nao se, valor for menor que o ponteiro da arvore->valor ele chama a funcao recursivamente pela esquerda
			insere(&(*arvore)->esq,valor);
		}
	}
	
}
void imprime(tipo_arvore *p, int nivel){//parametro arvore e nivel
	int i;
	if(p == NULL){//case arvore/noh null retorna/para a funcao
		return;
	}
	imprime(p->dir, nivel+1);//chamada recursiva para a dir
	for(i=0;i<nivel;i++){//quando maior o niveel mais espacamentos
        printf("\t");
    }
	printf("%d(%d)\n\n",p->valor);
	imprime(p->esq,nivel+1);//chamada recursiva para a esq
     
}
int busca_arvore(tipo_arvore *arvore, int valor,int marcador){//busca na arvore
	
	if(arvore!=NULL){
		if(arvore->valor==valor){//conta quantas vezes o valor foi encontrado
			marcador++;
		}
		marcador=busca_arvore(arvore->dir,valor,marcador);//chamadas recursivas
		marcador=busca_arvore(arvore->esq,valor,marcador);
	}
	return marcador;
	
}
void pega_numero(tipo_arvore **arvore,char *argv){//funcao que pega os valores do arquivo para inserir na matriz
	FILE *file;
	int i=0,j=0;
	long int numero=0;
	file=fopen(argv,"r");
	if(file == NULL){//teste de falha na abertura do arquivo
		printf("Erro na abertura do arquivo %s!\n",argv);
	}
	while(fscanf(file,"%ld",&numero)!=EOF){//pegando valores do arquivo
		insere(arvore,numero);
	}
	
	fclose(file);
	printf("[x]Valores inseridos\n");
}
void gravar(int altura){//funcao que guarda as rotacoes e altura em um arquivo
	FILE *file;
	//data e hora cria variaveis
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

	if(!(file=fopen("info-ARVORES.txt","a"))){
		printf("Falha na abertura do arquivo 'info-ARVORES.txt'\n");
	}
	fprintf(file, "\nArvore Binaria [%d/%d/%d %d:%d]{\n\tAltura=%d\n\tRotacoes=0\n}",dia,mes,ano,hora,minuto,altura);
	fclose(file);
	printf("[x]Informacoes gravadas\n");
}

int main(int argc, char *argv[ ]){
	int marcador,numero,valor,alt,cmp;
	if(argc==1){
		system("clear");
		printf("\t[x]Utilize %s 'nome do arquivo'\n\t[x]O arquivo deve estar na mesma pasta do algoritmo, o conteudo do arquivo deve ser de numeros inteiros.\n\t[x]para gravar a altura e rotacoes no arquivo Utilize %s 'nome do arquivo' -G, o menu de opcoes sera ignorado.\n\n",argv[0],argv[0]);
		return 0;
	}
	tipo_arvore* arvore=NULL;//inicializando o ponteiro como NULL
	system("clear");
	if(argc == 2){
		do{
			
			printf("\n1-Inserir valores do arquivo na arvore\n2-printar em pre pre-ordem\n3-Buscar valor\n4-Mostrar altura da arvore\n5-Sair\n\n");
			scanf("%d",&valor);
			switch(valor){
				case 1:
					system("clear");
					pega_numero(&arvore,argv[1]);
					break;
				case 2:
					system("clear");
					imprime(arvore,0);
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
					system("clear");
					numero=altura(arvore);
					printf("Altura=%d\n",numero);
			}
		} while (valor!=5);
	}
	else{
		printf("[x]Iniciando insercao\n");
		pega_numero(&arvore,argv[1]);
		alt=altura(arvore);
		cmp=strcmp(argv[2],"-G");
		if(cmp==0){
			gravar(alt);
		}
	}
	return 0;
}
