#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
/**
 * UFMT - Disciplina de ED2
 * Prof: Ivairton
 * Matheus Felipe Teodoro Correia
 * Trabalho 3 
 * estrutura da Arvore B
 *
 */

/*
#define T 	//Constante T que determina o tamanho da Arv.B
#define constante->MAX_CHAVES ( 2 * T - 1 )	//Máximo de registros
#define constante->MAX_FILHOS ( 2 * T )		//Máximo de filhos
#define constante->MIN_CHAVES ( T - 1 )		//Mínimo de registros
*/

//estruturas
struct constante{
	int T;
	int MAX_CHAVES;
	int MAX_FILHOS;
	int MIN_CHAVES;
};
typedef struct constante tipo_constante;

struct tipo_livro{

	int valor;
	char nome[100];

};
typedef struct tipo_livro tipo_livro;

struct arvore{
	int contChaves;
	tipo_livro **chaves;//chaves[constante->MAX_CHAVES];
	struct arvore **filhos;//*filhos[constante->MAX_FILHOS]
	int folha;
};
typedef struct arvore tipo_arvore;

//Prototipos
tipo_arvore* insereArvB(tipo_arvore *raiz, tipo_livro *valor,tipo_constante *constante);
tipo_arvore *insere (tipo_arvore *no, tipo_livro *novoLivro, int *flag, tipo_livro **valorRetorno,tipo_constante *constante);
void insereChave(tipo_arvore **arvore,tipo_livro *valorRetorno, tipo_arvore *filhoDir,tipo_constante *constante);
void CriarConstante(int T, tipo_constante **constante);
int BuscaBinaria(tipo_arvore *arvore, int valor,tipo_constante *constante);
tipo_arvore* AlocaArv(tipo_arvore *arvore, tipo_constante *constante);
tipo_livro *IniLivro(tipo_livro *livro, int valor, char *nome);
tipo_arvore* pega_numero(tipo_arvore *arvore,tipo_constante *constante,char *argv);
void Ordem(tipo_arvore *arvore);


//funcoes
tipo_livro *IniLivro(tipo_livro *livro, int valor, char *nome){//incializa o tipo_livro, alocando o ISBN e nome
	livro = (tipo_livro*) malloc(sizeof(tipo_livro));
	livro->valor = valor;
	strcpy(livro->nome,nome);
	return livro;
}	

tipo_arvore* AlocaArv(tipo_arvore *arvore, tipo_constante *constante){//aloca a arvore dinamicamente, os registros sao do tipo_livro que guarda: ISBN; Nome.
	int i =0;
	arvore = (tipo_arvore*) malloc(sizeof(tipo_arvore));
	tipo_livro *livro;
	arvore->contChaves = 0;
	arvore->chaves = (tipo_livro**)malloc(sizeof(tipo_livro*) * constante->MAX_CHAVES);//chaves[constante->MAX_CHAVES];
	arvore->filhos = (tipo_arvore**)malloc(sizeof(tipo_arvore*) * constante->MAX_FILHOS);;//*filhos[constante->MAX_FILHOS]
	arvore->folha = 0;
	while(i<constante->MAX_FILHOS){
		arvore->filhos[i]=NULL;
		if(i < constante->MAX_CHAVES){
			arvore->chaves[i]=IniLivro(livro,0,"");
		}
		i++;
	}

	return arvore;
}

tipo_arvore* insereArvB(tipo_arvore *raiz, tipo_livro *valor,tipo_constante *constante){
	int flag;
	tipo_livro *valorRetorno;
	tipo_arvore *filhoDir, *novaRaiz;

	filhoDir = insere(raiz, valor, &flag, &valorRetorno,constante);

	//Verifica se ocorreu a descida na árvore adequadamente, se há a necessidade de um novo nó como raiz
	if (flag){
		novaRaiz = AlocaArv(novaRaiz,constante);
		novaRaiz->contChaves = 1;
		novaRaiz->chaves[0] = valorRetorno;
		novaRaiz->filhos[0] = raiz;
		novaRaiz->filhos[1] = filhoDir;
		novaRaiz->folha = 0;
		return novaRaiz;
	}
	else {
		return raiz;
	}
}
//Função que busca pelo nó onde deve ser inserido o valor/chave e faz a quebra do nó, quando necessário
tipo_arvore *insere (tipo_arvore *no, tipo_livro *novoLivro, int *flag, tipo_livro **valorRetorno,tipo_constante *constante){
	int i, pos;
	tipo_livro *meio;
	tipo_arvore *noAux, *filhoDir;

	if (no == NULL) {
		//Então o nó pai (anterior) é o nó onde deve ser feita a inserção, pois alcançou um nó folha
		*flag = 1;
		*valorRetorno = novoLivro;
		return NULL;
	} 
	else {
		//Executa a busca pelo nó onde o valor deve ser inserido
		pos = BuscaBinaria (no, novoLivro->valor,constante); //verifica/busca a posição
		//pos--;
		//Identifica se a chave já está presente na árvore
		if ( (pos < no->contChaves) && (no->chaves[pos]->valor == novoLivro->valor) ){
			printf("O valor da chave já está presente na Árvore B!\n");
			*flag = 0;
		} 
		else {
			if ((no->chaves[pos] != NULL) && (no->contChaves < constante->MAX_CHAVES) && (no->chaves[pos]->valor < novoLivro->valor) && (no->chaves[pos]->valor != 0)){
				pos++;
			}

			filhoDir = insere(no->filhos[pos], novoLivro, flag, valorRetorno,constante); 	//Executa chamada recursiva

			if ( *flag ) { //Se ocorreu a descida como esperado, então insere o valor no nó 
				if ( no->contChaves < constante->MAX_CHAVES) { //Verifica se há espaço no nó
					insereChave(&no, *valorRetorno, filhoDir,constante);
					*flag = 0;
				}
				else { //Então é preciso dividir o nó p/ poder inserir o valor
					noAux = AlocaArv(noAux,constante);
					meio = malloc(sizeof(tipo_livro));	
					meio = no->chaves[constante->MIN_CHAVES];
					//Insere metade das chaves no novo nó
					noAux->filhos[0] = no->filhos[constante->MIN_CHAVES+1];
					for (i = constante->MIN_CHAVES+1; i < constante->MAX_CHAVES; i++){
						insereChave(&noAux,no->chaves[i],no->filhos[i+1],constante);
					}
					//Atualiza o nó ("aarvorea" as chaves transferidas
					for (i = constante->MIN_CHAVES; i < constante->MAX_CHAVES; i++){
						no->chaves[i] = 0;
						no->filhos[i+1] = NULL;
						no->contChaves--;
					}
					//Verifica em qual dos novos nós o valor deve ser inserido e executa
					if ( pos <= constante->MIN_CHAVES) {
						insereChave(&no, *valorRetorno, filhoDir,constante);
					}
					else {
						insereChave(&noAux, *valorRetorno, filhoDir,constante);
					}
					//Retorna o elemento do meio para ser inserido no nó pai e o filho direito da chave central
					*flag = 1;
					*valorRetorno = meio;
					return (noAux);
				}
			}
		}
	}
}
int BuscaBinaria(tipo_arvore *arvore, int valor,tipo_constante *constante){//busca a posicao para inserir o novo livro
	int i=0;
	while( (i != arvore->contChaves) && (i != constante->MAX_CHAVES) && (arvore->chaves[i]->valor != 0) &&  (i != constante->MAX_CHAVES) && (arvore->chaves[i]->valor < valor)){
		i++;
	}
	return i;
}
void insereChave(tipo_arvore **arvore,tipo_livro *valorRetorno, tipo_arvore *filhoDir,tipo_constante *constante){//insere jogando o maior ISBN para a dir no vetor chaves
	int i;
	i = (*arvore)->contChaves;
	while( (i > 0) && ( (valorRetorno->valor) < ((*arvore)->chaves[i-1]->valor))){
		(*arvore)->chaves[i] = (*arvore)->chaves[i-1];
		(*arvore)->filhos[i+1] = (*arvore)->filhos[i];
		i--;
	}
	(*arvore)->chaves[i] = valorRetorno;
	(*arvore)->filhos[i+1] = filhoDir;
	(*arvore)->contChaves++;
}
void CriarConstante(int T, tipo_constante **constante){//cria as 'constantes' para a criacao dinamica da arvore
	*constante = (tipo_constante*)malloc(sizeof(tipo_constante));
	(*constante)->T = T;
	(*constante)->MAX_FILHOS = 2*T;
	(*constante)->MAX_CHAVES = 2 * T - 1;
	(*constante)->MIN_CHAVES = T - 1 ;
}
void Ordem(tipo_arvore *arvore){//imprime em ordem
    int i;
    i = 0;
    if( arvore != NULL ){
        while ( ( i < arvore->contChaves )){
            printf("[%.4d %s]\n",arvore->chaves[i]->valor,arvore->chaves[i]->nome);
            Ordem(arvore->filhos[i]);
            i++;
        }
		Ordem(arvore->filhos[i]);
    }
}
tipo_arvore* pega_numero(tipo_arvore *arvore,tipo_constante *constante,char *argv){//funcao que pega os valores do arquivo para inserir na arvore
	FILE *file;
	int i=0,j=0,T=0;
	int numero1=0,numero2=0,total=0;
	char nomearq[100],nome[100];
	tipo_livro *livro;

	strcpy(nomearq,argv);
	file=fopen(nomearq,"r");
	if(file == NULL){//teste  de erro
		printf("Erro na abertura do arquivo %s!\n",nomearq);
	}
	fscanf(file,"%d",&T);
	CriarConstante(T,&constante);
	while(fscanf(file,"%d-%d %[^\n]",&numero1,&numero2,&nome)!=EOF){
		total = numero1*10*10*10*10+numero2;
		livro = IniLivro(livro,total,nome);
		arvore = insereArvB(arvore,livro,constante);
	}
	
	Ordem(arvore);
	fclose(file);
	return arvore;
}
int main(int argc, char *argv[ ]){
	tipo_arvore *arvore=NULL;
	tipo_constante *constante;
	clock_t Ticks[2];
	if(argc==2){
		Ticks[0] = clock();//inicia contagem
		arvore = pega_numero(arvore,constante,argv[1]);
		Ticks[1] = clock();//para contagem
		double tempo =( (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC );
		printf("Tempo de exec: [%g] ms\n",tempo);
	}
	else{
		system("clear");
		printf("\n\t[x]Utilize %s 'nomedoarquivo.txt' \n",argv[0]);
	}
	return 0;
}

