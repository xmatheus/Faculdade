


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
tipo_pilha *quebra(tipo_pilha *pilha1,tipo_pilha *pilha2,char *frase);
tipo_pilha *testa(tipo_pilha *pilha1,tipo_guarda *quantidade,char frase1,char frase2);
tipo_pilha *empilha(tipo_pilha *pilha,char valor);
tipo_pilha *desempilha(tipo_pilha *pilha,char *vet);



tipo_pilha *inicializa(tipo_pilha *pilha){//inicializa pilha
	pilha=(tipo_pilha *)malloc(sizeof(tipo_pilha));
	pilha->frase[0]='$';
	pilha->posicao=0;
	pilha->prox=NULL;
	return pilha;
}
tipo_pilha *conta(tipo_guarda *quantidade, char *frase){//conta os (){}[]
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
	if(quantidade->parenteses%2!=0 && quantidade->parenteses!=0){//caso seja impar parecenteses esta errado
		quantidade->parenteses=-1;
	}
	if(quantidade->colchetes%2!=0 && quantidade->colchetes!=0){//caso seja impar parenteses esta errado
		quantidade->colchetes=-1;
	}
	if(quantidade->chave%2!=0 && quantidade->chave!=0){//caso seja impar parenteses esta errado
		quantidade->chave=-1;
	}
	quantidade->total=total;//quantidade de chaves colchetes e parentes
	

}
tipo_pilha *quebra(tipo_pilha *pilha1,tipo_pilha *pilha2,char *frase){//cria os dois vetores com os ()[]{}

	
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
			pilha1=empilha(pilha1,frase[i]); 
			
		}
	}
	printf("saiu\n");

}

tipo_pilha *testa(tipo_pilha *pilha1,tipo_guarda *quantidade,char frase1,char frase2){//conta (){}[] direto na pilha substituindo por $
	int controle=1,i=0;
	char vet[1000];
	desempilha(pilha1,vet);
	if(frase1=='('){
		controle=1;
		for(i=0;i<quantidade->total;i++){
			if(vet[i]==frase1 && controle==1){
				quantidade->parenteses=quantidade->parenteses-1;
				vet[i]='$';
				controle=0;
			}
			if(pilha1->frase[0]==frase2 && controle==0){
				quantidade->parenteses=quantidade->parenteses-1;
				vet[i]='$';
			}
			
		}
	}
	if(frase1=='['){
		controle=1;
		for(i=0;i<quantidade->total;i++){
			if(vet[i]==frase1 && controle==1){
				quantidade->colchetes=quantidade->colchetes-1;
				vet[i]='$';
				controle=0;
			}
			if(pilha1->frase[0]==frase2 && controle==0){
				quantidade->colchetes=quantidade->colchetes-1;
				vet[i]='$';
			}
			
		}
	}
	if(frase1=='{'){
		controle=1;
		for(i=0;i<quantidade->total;i++){
			if(vet[i]==frase1 && controle==1){
				quantidade->chave=quantidade->chave-1;
				vet[i]='$';
				controle=0;
			}
			if(pilha1->frase[0]==frase2 && controle==0){
				quantidade->chave=quantidade->chave-1;
				vet[i]='$';
			}
			
		}
	}
}
tipo_pilha *empilha(tipo_pilha *pilha,char valor){
	tipo_pilha *novo_no=inicializa(novo_no);
	int qtd;
	//printf("valor %d\n",valor);
	if(pilha->prox==NULL){
		qtd++;
		pilha->frase[0]=valor;
		pilha->prox=NULL;
		pilha->posicao=qtd;
		novo_no->prox=pilha;

		printf("pilha->numero %c\n",pilha->frase[0] );
		return novo_no;
	}

	
	novo_no->frase[0]=valor;
	printf("novo_no->numero %c\n",novo_no->frase[0] );
	novo_no->prox=pilha;
	qtd++;
	novo_no->posicao=qtd;
	return novo_no;

}
tipo_pilha *desempilha(tipo_pilha *pilha,char *vet){
	printf("começou desempilha\n");
	tipo_pilha *proximo=inicializa(proximo);
	int i=0;
	
	proximo=pilha->prox;

	while(proximo!=NULL){
		vet[i]=pilha->frase[0];
		free(pilha);
		pilha=proximo;
		proximo=pilha->prox;
		i++;
		
	}
	printf("saiu\n");	

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
	pilha1 = inicializa(pilha1);//inicializa pilha
	pilha2 = inicializa(pilha2);//inicializa pilha
	printf("Frase:"); 
	fgets(frase,100,stdin);
	printf("\n");
	conta(quantidade,frase);//conta todos()[]{}
	quebra(pilha1,pilha2,frase);//coloca na pilha
	//printf("quantidade->parenteses %d\nquantidade->chaves %d\nquantidade->colchetes %d\n",quantidade->parenteses,quantidade->chave,quantidade->colchetes);
	printf("Balanceamento de ");
	if(quantidade->parenteses==0){
		printf("Parênteses= (ND), ");
			
	}
	if(quantidade->parenteses != -1 && quantidade->parenteses != 0){
		while(quantidade->parenteses!=0){
			testa(pilha1,quantidade,'(',')');//localiza na pilha

		}
		printf("Parênteses= OK, ");
		
	}

	if(quantidade->parenteses==-1){
		printf("Parênteses=ERRADO, ");
	}
	
	if(quantidade->chave==0){
		printf(" Chaves = (ND), ");
	}
	if(quantidade->chave != -1 && quantidade->chave != 0){
		while(quantidade->chave!=0){
			testa(pilha1,quantidade,'{','}');//localiza na pilha

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
			testa(pilha1,quantidade,'[',']');//localiza na pilha

		}
		printf(" Colchetes = OK.\n");
	}

	if(quantidade->colchetes==-1){
		printf(" Colchetes = ERRADO.\n");
	}



	return 0;
}