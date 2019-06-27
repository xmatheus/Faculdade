#include <stdio.h>
#include <stdlib.h>

struct arv{
	char info;
	struct arv *f1,*f2,*f3;
	
	
};
typedef struct arv str_arv;

void inicializa(char nome);

void inicializa(char nome){
	str_arv *a=(str_arv*)malloc(sizeof(str_arv));
	a->info=nome;
	a->f1=NULL;
	a->f2=NULL;
	a->f3=NULL;
}

void insere(str_arv *nome,int *vetor, int qtd);
int FUN_MAIOR(int *vet);

int FUN_MAIOR(int *vet){
	int i=0,indice=0;
	maior=vet[0];
	for(i=0;i<3;i++){
		if (maior>vet[i]){
			maior=vet[i];
			indice = i;
		}
	}
	return maior, i;
	
}

void insere(str_arv *nome, int *vetor, int qtd){
	int i=0,j=0,mult=0,maior=0,marc=0;
	int vet_aux[3];
	mult=mult+1;
	maior=vet[0];
	
	for (i=marc;i<qtd*mult;i++){
		vet_aux[j]=vetor[i];
		j=j+1;
	

	}
	maiordf,indicdf=FUN_MAIOR(vet_aux);
	
	
	
	
	
	
	marc=marc+3;
	
	
	
	

}


int main(){
	
	inicializa('a');
	
	
	
	
	
	return 0;
}