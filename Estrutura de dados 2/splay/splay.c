#include <stdlib.h>
#include <stdio.h>

/* Implementacao da Splay tree
 * Matheus Felipe
 * https://www.youtube.com/channel/UCjVHBIAz4TdmVK2rjI8qIbw
 * visualização animada no site: https://www.cs.usfca.edu/~galles/visualization/SplayTree.html
 */	

struct arvore{
	int valor;//guarda o valor
	struct arvore *esq;//ponteiro para a esquerda 
	struct arvore *dir;//ponteiro para a direita
};
typedef struct arvore tipo_arvore;

//prototipos das funcoes
void insere(tipo_arvore **arvore,int valor);//insere valores na arvore recebendo como paramentro um ponteiro de ponteiro e o valor a ser alocado
void imprime(tipo_arvore *p, int nivel);//funcao que mostra a arvore de lado em pre-ordem
void pega_numero(tipo_arvore **arvore,char *argv);//abre o arquivo com os valores a serem inseridos na arvore
int altura(tipo_arvore *arvore);//percorre a arvore e retorna a altura
int insere_splay(tipo_arvore **arvore, tipo_arvore **pai, tipo_arvore **avo, tipo_arvore **raiz,int valor);//insere recursivamente
void verifica_splay(tipo_arvore **arvore,tipo_arvore **pai, tipo_arvore **avo, tipo_arvore **raiz,int valor);//verifica se precisa de rotacao
//rotacoes
void zigDir(tipo_arvore **arvore);
void zigEsq(tipo_arvore **arvore);
void zag_zig(tipo_arvore **pai, tipo_arvore **avo);
void zig_zag(tipo_arvore **pai, tipo_arvore **avo);
void zig_zig(tipo_arvore **arvore);
void zag_zag(tipo_arvore **arvore);

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
void insere(tipo_arvore **arvore, int valor){//funcao anterior a chamada recursiva da funcao que insere, apenas para selecionar a raiz
	int trash;
	tipo_arvore **raiz;
	raiz = arvore;
	trash = insere_splay(arvore,NULL,NULL,raiz,valor);
}
int insere_splay(tipo_arvore **arvore, tipo_arvore **pai, tipo_arvore **avo, tipo_arvore **raiz,int valor){//insere novos valores na arvore de maneira recursiva
	int flag;
	tipo_arvore **aux, **aux2;
	if((*arvore) == NULL){//se a arvore/noh for vazio ele aloca o novo valor e aponta a esq e dir para NULL
		(*arvore)=(tipo_arvore *)malloc(sizeof(tipo_arvore));
		(*arvore)->valor=valor;
		(*arvore)->esq=NULL;
		(*arvore)->dir=NULL;
		return 1;
	}
	else{
		if(valor > (*arvore)->valor){
			aux = &(*arvore)->dir;
		}
		else{
			aux = &(*arvore)->esq;
		}
		flag = insere_splay(aux,arvore,pai,raiz,valor);
		
		switch(flag){
			case 0:
				return 0;//propaga o 0
				break;
			case 1:
				if(*arvore == *raiz){
					//aconteceu a rotacao anteriormente
					//faz o zig soh na raiz

					if(valor < (*arvore)->valor){
						zigDir(arvore);	
					}
					else{
						zigEsq(arvore);	
					}
					return 0;
				}
				else{

					return 2;
					//faz a rotacao
				}
				break;
			case 2:
				//zig esq e zig dir precisa 3 noh
				//esta no avo, aux2 eh o noh inserido, aux eh o pai, arvore avo
				if(((*aux)->esq != NULL) && ((*aux)->esq->valor == valor)){//apenas para achar o novo noh
					aux2 = &(*aux)->esq;
				}
				else if(((*aux)->dir != NULL) && ((*aux)->dir->valor == valor)){//apenas para achar o novo noh
					aux2 = &(*aux)->dir;
				}
				if(valor < (*arvore)->valor){
					verifica_splay(aux2,aux,arvore,raiz,valor);	
				}
				else{
					verifica_splay(aux2,aux,arvore,raiz,valor);	
				}
				return 1;
				break;
		}
	}
}
void verifica_splay(tipo_arvore **arvore,tipo_arvore **pai, tipo_arvore **avo, tipo_arvore **raiz, int valor){//verifica se precisar rotacionar
	if(*arvore != *raiz){
		if(*pai == (*avo)->esq){
			if((*arvore) == (*pai)->esq){
				zig_zig(avo);//duas zidDir
			}
			else{//zag_zig(Esq-pai)(dir-avo)
				zag_zig(pai,avo);
			}
		}
		else{
			if( *arvore == (*pai)->dir){
				zag_zag(avo);//duas zidEsq
			}
			else{//zig_zag(dir-pai)(esq-avo)
				zig_zag(pai,avo);
			}
		}
	}
	else{
		printf("Arvore igual a raiz\n");
	}

}
void zigDir(tipo_arvore **arvore){
	tipo_arvore *aux;
	aux=(*arvore)->esq;
	(*arvore)->esq=aux->dir;
	aux->dir=*arvore;
	*arvore = aux;

}
void zigEsq(tipo_arvore **arvore){
	tipo_arvore *aux;
	aux=(*arvore)->dir;
	(*arvore)->dir=aux->esq;
	aux->esq= *arvore;
	*arvore = aux;
}
void zag_zig(tipo_arvore **pai, tipo_arvore **avo){
	zigEsq(pai);
	zigDir(avo);
}
void zig_zag(tipo_arvore **pai, tipo_arvore **avo){
	zigDir(pai);
	zigEsq(avo);
}
void zig_zig(tipo_arvore **arvore){
	zigDir(arvore);
	zigDir(arvore);
}
void zag_zag(tipo_arvore **arvore){
	zigEsq(arvore);
	zigEsq(arvore);
}
void imprime(tipo_arvore *p, int nivel){//parametro arvore e nivel
	int i;
	
	if(p == NULL){
		return;
	}
	
	imprime(p->dir, nivel+1);
	
	for(i=0;i<nivel;i++){
        printf("\t");
    }
	printf("%d\n",p->valor);
	imprime(p->esq,nivel+1);
     
}
void pega_numero(tipo_arvore **arvore,char *argv){//funcao que pega os valores do arquivo para inserir na matriz
	FILE *file;
	int i=0,j=0;
	int numero=0;
	file=fopen(argv,"r");
	if(file == NULL){//teste de falha na abertura do arquivo
		printf("Erro na abertura do arquivo %s!\n",argv);
	}
	while(fscanf(file,"%d",&numero)!=EOF){//pegando valores do arquivo
		insere(arvore,numero);
		printf("[INSERCAO %d]-----------------------------------\n",i);
		imprime(*arvore,0);//imprime o passo a passo a insercao, se tiver muitos valores vai bugar o printf...
		i++;
	}
	
	fclose(file);
	//printf("[x]Valores inseridos\n");
}

int main(int argc, char *argv[ ]){
	tipo_arvore *arvore = NULL;
	if(argc==1){
		system("clear");
		printf("\t[x]Utilize %s 'nome do arquivo'\n\t[x]O arquivo deve estar na mesma pasta do algoritmo, o conteudo do arquivo deve ser de numeros inteiros.\n\n",argv[0],argv[0]);
		return 0;
	}
	else{
		pega_numero(&arvore,argv[1]);
		//imprime(arvore,0);
	}



	return 0;
}