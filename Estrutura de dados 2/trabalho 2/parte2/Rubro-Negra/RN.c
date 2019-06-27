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
 * Algoritmo de uma arvore rubro-negra
 * 
 */

/*struct arvore
 *guarda o valor
 *ponteiro para a esquerda 
 *ponteiro para a direita
 *Cor do noh
 */	
struct arvore{
 	int valor;
	struct arvore *esq;
	struct arvore *dir;
	int cor;
};
typedef struct arvore tipo_arvore;
#define RED 1 //define RED como 1 e BLACK como 0 para facilitar na leitura
#define BLACK 0

//struct para facilitar a contagem das rotacoes
struct conta{
	int cont;
};
typedef struct conta tipo_conta;



//prototipos das funcoes
tipo_arvore *inicializa();//inicializa a arvore como NULL
void mostra_arvore(tipo_arvore *arvore);//printa a arvore em ordem so que do maior para o menos
tipo_arvore* pega_numero(tipo_arvore *arvore,tipo_conta *contador,char *argv);//abre o arquivo com os valores a serem inseridos na arvore
tipo_arvore* rotacaoEsquerda(tipo_arvore *arvore);//rotaciona determinado ponto da arvore a esquerda eretorna um ponteiro do tipo_arvore
tipo_arvore* rotacaoDireita(tipo_arvore *arvore);//rotaciona determinado ponto da arvore a direita eretorna um ponteiro do tipo_arvore
void gravar(int altura,tipo_conta *contador);//funcao que guarda as rotacoes e altura em um arquivo
int insere_em_RN(tipo_arvore *arvore,int valor,tipo_arvore *pai,tipo_arvore *avo,tipo_arvore **raiz, tipo_conta *contador);//funcao recursiva para insercao e chamada da funcao de balanceamento
tipo_arvore* insere_RN(tipo_arvore *arvore, int valor, tipo_conta *contador);//funaco que organiza as informacoes e mantem o controle do noh raiz para chamada da funcao de insercao
int balanceamento(tipo_arvore **arvore,tipo_arvore *pai,tipo_arvore *avo,tipo_arvore *bisavo,tipo_arvore **raiz, tipo_conta *contador);//funcao que faz o balanceamento da arvore
void imprime(tipo_arvore *p, int nivel);//funcao que printa a arvore de lado
int altura(tipo_arvore *arvore);//funcao que percorre a arvore e retorna a altura

//F U C O E S
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
tipo_arvore *insere_RN(tipo_arvore *arvore, int valor, tipo_conta *contador){//funaco que organiza as informacoes e mantem o controle do noh raiz para chamada da funcao de insercao
	int trash;
	tipo_arvore *raiz;
	raiz = arvore;
	trash = insere_em_RN(arvore,valor,NULL,NULL, &raiz,contador);
	raiz->cor=BLACK;
	return raiz;
}
int insere_em_RN(tipo_arvore *arvore,int valor,tipo_arvore *pai,tipo_arvore *avo,tipo_arvore **raiz, tipo_conta *contador){//funcao recursiva para insercao e chamada da funcao de balanceamento
	tipo_arvore **aux;
	int flag;
	if(arvore == NULL){
		arvore = (tipo_arvore*)malloc(sizeof(tipo_arvore));
		arvore->valor = valor;
		arvore->cor=RED;
		arvore->dir=NULL;
		arvore->esq=NULL;
		if(*raiz == NULL){
			*raiz = arvore;
			return 1;//verifica o balanceamento
		}
		else{
			if(valor < pai->valor){
				pai->esq = arvore;
			}
			else{
				pai->dir = arvore;
			}
			return 1;
		}
	}
	else{
		if(valor != arvore->valor){
			if(valor < arvore->valor){
				aux = &(arvore)->esq;
			}
			else{
				aux = &(arvore)->dir;	
			}
			flag = insere_em_RN(*aux,valor,arvore,pai,raiz,contador);
			switch(flag){
				case 0://se nao ocorreu a insercao, propaga o 1
					return 1;
					break;
				case 1://se a insercao foi um sucesso, verifica o balanceamento
					flag = balanceamento(aux,arvore,pai,avo,raiz,contador);
					return flag;
				case 2://O retorno "2" significa que ocorreu uma rotacao e os ponteiros precisam ser estruturados
					return 2;
			}
		}
		else{
			return 0;
		}
	}

}
int balanceamento(tipo_arvore **arvore,tipo_arvore *pai,tipo_arvore *avo,tipo_arvore *bisavo,tipo_arvore **raiz, tipo_conta *contador){
	tipo_arvore *tio,*raizsubarv;
	
	int flagBalanco = 2;
	
	if(pai != NULL){
		if(pai->cor == RED){
			if(pai == avo->esq){
				tio = avo->dir;
			}
			else{
				tio = avo->esq;
			}
			if((tio == NULL) || (tio->cor == BLACK)){
				if(pai == avo->esq){//pai lado esquerdo
					if(*arvore == pai->esq){//tio direito
						//se o pai é filho esq e o no tb é filho esq, entao rotacao simples à direita
						pai->cor=!(pai->cor);
						avo->cor = !(avo->cor);
						raizsubarv = rotacaoDireita(avo);
						contador->cont++;
						
					}
					else{
						//se o pai é filho esq, mas o no é filho direito, entao rotacao dupla esq-dir
						//rotacao dup1la esq dir
						(*arvore)->cor = !(*arvore)->cor;
						avo->cor = !(avo->cor); 
						avo->esq = rotacaoEsquerda(pai);
						raizsubarv = rotacaoDireita(avo);
						contador->cont=contador->cont+2;

					}
				}
				else{//pai lado direito
					if(*arvore == pai->dir){//tio esquerdo 
						//se o pai é filho dir e o no tb, entao rotacao simples à esq
						pai->cor=!(pai->cor);
						avo->cor = !(avo->cor);
						raizsubarv = rotacaoEsquerda(avo);
						contador->cont++;
						
					}
					else{
						//se o pai é filho dir e o no é filho esq, entao rotacao dupla dir-esq
						(*arvore)->cor = !(*arvore)->cor;
						avo->cor = !(avo->cor);
						avo->dir = rotacaoDireita(pai);
						raizsubarv = rotacaoEsquerda(avo);
						contador->cont=contador->cont+2;
					}
				}
				if(bisavo != NULL){
					//bisavo aponta para a nova arvore alterada
					if((raizsubarv->valor) < (bisavo->valor)){
						bisavo->esq = raizsubarv;
					}
					else{
						bisavo->dir = raizsubarv;	
					}
				}
				else{
					*raiz = raizsubarv;
				}
			}
			else{
				pai->cor = !pai->cor;
				tio->cor = !tio->cor;
				avo->cor = !avo->cor;
				flagBalanco = 0;
			}
		}
		return flagBalanco;
	}
	else{
		return 2;
	}
}
tipo_arvore* pega_numero(tipo_arvore *arvore,tipo_conta *contador,char *argv){//funcao que pega os valores do arquivo para inserir na arvore
	FILE *file;
	int i=0,j=0;
	long int numero=0;
	char nomearq[100];

	strcpy(nomearq,argv);
	file=fopen(nomearq,"r");
	if(file == NULL){//teste  de erro
		printf("Erro na abertura do arquivo %s!\n",nomearq);
	}

	
	while(fscanf(file,"%d",&numero)!=EOF){
		arvore = insere_RN(arvore,numero,contador);
	}
	
	
	fclose(file);
	printf("[x]Valores inseridos\n");
	return arvore;
}
tipo_arvore* rotacaoEsquerda(tipo_arvore *arvore){//pai att e cor att
	//passando avo como parametro
	tipo_arvore *aux;
	aux=arvore->dir;
	arvore->dir=aux->esq;
	aux->esq=arvore;
	return aux;

}
tipo_arvore* rotacaoDireita(tipo_arvore *arvore){//pai att e cor att
	//passando avo como parametro
	tipo_arvore *aux;
	aux=arvore->esq;
	arvore->esq=aux->dir;
	aux->dir=arvore;
	return aux;
}
void gravar(int altura,tipo_conta *contador){//funcao que guarda as rotacoes e altura em um arquivo
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
	if(!(file=fopen("info-RN.txt","a"))){
		printf("Falha na abertura do arquivo 'info-ARVORES.txt'\n");
	}
	fprintf(file, "\nArvore RED-BLACK [%d/%d/%d %d:%d]{\n\tAltura=%d\n\tRotacoes=%d\n}",dia,mes,ano,hora,minuto,altura,contador->cont);
	fclose(file);
	printf("[x]Informacoes gravadas\n");
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
	printf("%d(%d)\n\n",p->valor,p->cor);
	imprime(p->esq,nivel+1);
     
}
//int argc, char *argv[ ]
int main(int argc, char *argv[ ]){
	int marcador,numero,valor,alt,i,j,cmp;
	if(argc==1){
		system("clear");
		printf("\t[x]Utilize %s 'nome do arquivo'\n\t[x]O arquivo deve estar na mesma pasta do algoritmo, o conteudo do arquivo deve ser de numeros inteiros.\n\t[x]para gravar a altura e rotacoes no arquivo Utilize %s 'nome do arquivo' -G, o menu de opcoes sera ignorado\n\n",argv[0],argv[0]);
		return 0;
	}
	tipo_arvore *arvore=NULL;//inicializando a arvore vazia
	tipo_conta *contador=(tipo_conta*)malloc(sizeof(tipo_conta));
	FILE *file;
	if(argc == 2){
		do{
			
			printf("1-Ler arquivo e inserir valores\n2-Mostrar arvore(se for grande vai bugar)\n3-Mostrar altura e quantidade de rotacoes\n4-Sair\n");
			scanf("%d",&valor);
			switch(valor){
			
				case 1:
					system("clear");
					printf("[x]Iniciando insercao e balanceamento\n");
					arvore = pega_numero(arvore,contador,argv[1]);
					
					break;
				case 2:
					system("clear");
					imprime(arvore,0);
					
					break;
				case 3:
					system("clear");
					printf("\n[x]Altura=%d\n[x]Rotacoes=%d\n",alt,contador->cont);	
			}	

		} while (valor!=4);
	}
	else{
		system("clear");
		printf("[x]Iniciando insercao e balanceamento\n");
		arvore = pega_numero(arvore,contador,argv[1]);
		alt=altura(arvore);
		cmp=strcmp(argv[2],"-G");
		if(cmp==0){
			gravar(alt,contador);
		}
		//imprime(arvore,0);
	}
	
	return 0;
}
