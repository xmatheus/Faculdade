/*
	Aluno: Matheus Felipe Teodoro Correia
	verifica parenteses, colchetes e etc.


*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct pilha{
	char frase[1];
	int posicao;
	struct pilha *prox;
};
typedef struct pilha tipo_pilha;
struct struct2{
	int parenteses;
	int colchetes;
	int chave;
	int total;
};
typedef struct struct2 tipo_guarda;

tipo_pilha *inicializa(tipo_pilha *pilha);
tipo_pilha *conta(tipo_guarda *quantidade, char *frase);
tipo_pilha *empilha(tipo_pilha *pilha1,tipo_pilha *pilha2,char *frase);
tipo_pilha *testa(tipo_pilha *pilha1,tipo_guarda *quantidade,char frase1,char frase2);



tipo_pilha *inicializa(tipo_pilha *pilha){
	pilha=(tipo_pilha *)malloc(sizeof(tipo_pilha));
	pilha->frase[0]='$';
	pilha->posicao=0;
	pilha->prox=NULL;
	return pilha;
}
tipo_pilha *conta(tipo_guarda *quantidade, char *frase){
	int tamanho_frase=0,i=0,total=0;
	tamanho_frase=strlen(frase);
	for(i=0;i<tamanho_frase;i++){
		if(frase[i]=='('){
			quantidade->parenteses++;
			total++;
		}
		if(frase[i]==')' && quantidade->parenteses%2!=0){
			quantidade->parenteses++;
			total++;
		}
		if(frase[i]=='['){
			quantidade->colchetes++;
			total++;
		}
		if(frase[i]==']' && quantidade->colchetes%2!=0){
			quantidade->colchetes++;
			total++;
		}
		if(frase[i]=='{'){
			quantidade->chave++;
			total++;
		}
		if(frase[i]=='}' && quantidade->chave%2!=0){
			quantidade->chave++;
			total++;
		}
	}
	if(quantidade->parenteses%2!=0 && quantidade->parenteses!=0){
		quantidade->parenteses=-1;
	}
	if(quantidade->colchetes%2!=0 && quantidade->colchetes!=0){
		quantidade->colchetes=-1;
	}
	if(quantidade->chave%2!=0 && quantidade->chave!=0){
		quantidade->chave=-1;
	}
	quantidade->total=total;
	

}
tipo_pilha *empilha(tipo_pilha *pilha1,tipo_pilha *pilha2,char *frase){

	
	int tamanho_frase=0,i=0,cont1=0,cont2=0,cont_pilha1=0,cont_pilha2=0;
	tamanho_frase=strlen(frase)-1;

	if((tamanho_frase%2)!=0){//se a frase tiver um tamanho impar ele separa deixando cont 1 com o maior valor
		cont1=(tamanho_frase/2)+1;
		cont2=(tamanho_frase/2);
		//printf("cont1=%d cont2=%d\n",cont1,cont2);
	}
	else{//se nao os valores ficam iguais
		cont1=(tamanho_frase/2);
		cont2=(tamanho_frase/2);
		//printf("cont1=%d cont2=%d\n",cont1,cont2);
	}


	for(i=0;i<tamanho_frase;i++){
		if(frase[i]=='(' || frase[i]==')' || frase[i]=='[' || frase[i]==']' || frase[i]=='{' || frase[i]=='}'){
			pilha1->frase[0]=frase[i];
			pilha1->posicao=cont_pilha1;
			
			pilha1->prox=(tipo_pilha *) malloc(sizeof(tipo_pilha));
			pilha1=pilha1->prox;
			cont_pilha1++;
		}
	}

}

tipo_pilha *testa(tipo_pilha *pilha1,tipo_guarda *quantidade,char frase1,char frase2){
	int controle=1,i=0;
	if(frase1=='('){
		controle=1;
		for(i=0;i<quantidade->total;i++){
			if(pilha1->frase[0]==frase1 && controle==1){
				quantidade->parenteses=quantidade->parenteses-1;
				pilha1->frase[0]='$';
				controle=0;
			}
			if(pilha1->frase[0]==frase2 && controle==0){
				quantidade->parenteses=quantidade->parenteses-1;
				pilha1->frase[0]='$';
			}
			pilha1=pilha1->prox;
		}
	}
	if(frase1=='['){
		controle=1;
		for(i=0;i<quantidade->total;i++){
			if(pilha1->frase[0]==frase1 && controle==1){
				quantidade->colchetes=quantidade->colchetes-1;
				pilha1->frase[0]='$';
				controle=0;
			}
			if(pilha1->frase[0]==frase2 && controle==0){
				quantidade->colchetes=quantidade->colchetes-1;
				pilha1->frase[0]='$';
			}
			pilha1=pilha1->prox;
		}
	}
	if(frase1=='{'){
		controle=1;
		for(i=0;i<quantidade->total;i++){
			if(pilha1->frase[0]==frase1 && controle==1){
				quantidade->chave=quantidade->chave-1;
				pilha1->frase[0]='$';
				controle=0;
			}
			if(pilha1->frase[0]==frase2 && controle==0){
				quantidade->chave=quantidade->chave-1;
				pilha1->frase[0]='$';
			}
			pilha1=pilha1->prox;
		}
	}




}
int main(){
	char frase[100];
	int retorno=0,teste=0;
	tipo_pilha *pilha1;
	tipo_pilha *pilha2;
	tipo_guarda *quantidade;
	quantidade->parenteses=0;
	quantidade->chave=0;
	quantidade->colchetes=0;
	quantidade->total=0;
	pilha1 = inicializa(pilha1);
	pilha2 = inicializa(pilha2);
	printf("Frase:"); 
	fgets(frase,100,stdin);
	printf("\n");
	conta(quantidade,frase);
	empilha(pilha1,pilha2,frase);
	//printf("quantidade->parenteses %d\nquantidade->chaves %d\nquantidade->colchetes %d\n",quantidade->parenteses,quantidade->chave,quantidade->colchetes);
	printf("Balanceamento de ");
	if(quantidade->parenteses==0){
		printf("Parênteses = (ND), ");
			
	}
	if(quantidade->parenteses != -1 && quantidade->parenteses != 0){
		while(quantidade->parenteses!=0){
			testa(pilha1,quantidade,'(',')');

		}
		printf("Parênteses = OK, ");
		
	}

	if(quantidade->parenteses==-1){
		printf("Parênteses = ERRADO, ");
	}
	
	if(quantidade->chave==0){
		printf(" Chaves = (ND), ");
	}
	if(quantidade->chave != -1 && quantidade->chave != 0){
		while(quantidade->chave!=0){
			testa(pilha1,quantidade,'{','}');

		}
		printf(" Chaves = OK, ");
	}
	if(quantidade->chave==-1){
		printf(" Chaves = ERRADO, ");
	}
	

	if(quantidade->colchetes==0){
		printf(" Colchetes = (ND).\n");
	}	
	if(quantidade->colchetes != -1 && quantidade->colchetes != 0){
		while(quantidade->colchetes!=0){
			testa(pilha1,quantidade,'[',']');

		}
		printf(" Colchetes = OK.\n");
	}

	if(quantidade->colchetes==-1){
		printf(" Colchetes = ERRADO.\n");
	}



	return 0;
}