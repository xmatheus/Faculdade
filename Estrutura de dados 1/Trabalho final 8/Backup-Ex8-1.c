#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pilha{
	char frase[1];
	int posicao;
	struct pilha *prox;
};
typedef struct pilha tipo_pilha;
struct retorno{
	int v1,v2;
	int qtd;
	char frase_arrumada[100];
};
typedef struct retorno tipo_retorno;


tipo_pilha* inicia_pilha(tipo_pilha *pilha);
tipo_pilha* arruma_frase(tipo_retorno *retorno, char *frase);
tipo_pilha* arruma_pilha(tipo_retorno *retorno,tipo_pilha *pilha1,tipo_pilha *pilha2);
tipo_pilha* teste_pali(tipo_retorno *retorno,tipo_pilha *pilha1,tipo_pilha *pilha2);
tipo_pilha* toda_frase(tipo_retorno *retorno,tipo_pilha *pilha1,tipo_pilha *pilha2);
tipo_pilha*	teste_final(tipo_retorno *retorno,tipo_pilha *pilha1);
tipo_pilha* teste_substituicao(tipo_retorno *retorno,tipo_pilha *pilha1,tipo_pilha *pilha2);



tipo_pilha* inicia_pilha(tipo_pilha *pilha){//inicializa a pilha com valores vazios menos o vetor de strings
	pilha->prox=NULL;
	pilha->posicao=0;
	pilha->frase[0]="$";
	
	return pilha;
}

tipo_pilha* arruma_frase(tipo_retorno *retorno, char *frase){//funcao que tirar os espacos e retorna os tamanhos que as duas pilhas devem ter para uma boa comparacao
	int tamanho_frase=0,tamanho_frasenew=0,i=0,j=0;
	int cont1=0,cont2=0,vet[2];
	char frase_new[100];
	tamanho_frase = strlen(frase);

	for (i=0;i<tamanho_frase;i++){
		if(frase[i]!=' '){
			frase_new[j]=frase[i];
			j++;
		}

	}
	frase_new[j]='\0';
	tamanho_frasenew = strlen(frase_new);
	
	if((tamanho_frasenew%2)!=0){//se a frase tiver um tamanho impar ele separa deixando cont 1 com o maior valor
		cont1=(tamanho_frasenew/2)+1;
		cont2=(tamanho_frasenew/2);
		//printf("cont1=%d cont2=%d\n",cont1,cont2);
	}
	else{//se nao os valores ficam iguais
		cont1=(tamanho_frasenew/2);
		cont2=(tamanho_frasenew/2);
		//printf("cont1=%d cont2=%d\n",cont1,cont2);
	}
	
	retorno->v1=cont1;
	retorno->v2=cont2;
	strcpy(retorno->frase_arrumada,frase_new);
	return retorno;
}

tipo_pilha* arruma_pilha(tipo_retorno *retorno,tipo_pilha *pilha1,tipo_pilha *pilha2){
	int i=0,j=0;
	pilha1=inicia_pilha(pilha1);//inicializando pilha1 e pilha2
	pilha2=inicia_pilha(pilha2);

	
	for(i=0;i<retorno->v1+retorno->v2;i++){

		retorno->frase_arrumada[i]=tolower(retorno->frase_arrumada[i]);
	}
	for(i=0;i<retorno->v1;i++){

		pilha1->frase[0]=retorno->frase_arrumada[i];
		pilha1->prox=(tipo_pilha *) malloc(sizeof(tipo_pilha));
		pilha1=pilha1->prox;
	}
 	
 	for(j=retorno->v1+retorno->v2-1;j>=retorno->v1;j--){
 		pilha2->frase[0]=retorno->frase_arrumada[j];
 		pilha2->prox=(tipo_pilha *) malloc(sizeof(tipo_pilha));
 		pilha2=pilha2->prox;
 	}

}



tipo_pilha* teste_pali(tipo_retorno *retorno,tipo_pilha *pilha1,tipo_pilha *pilha2){
	char vet_guarda[30];
	int j=0,i=0,marcador=0,marcador_t,marcador_sub=0,marcador_t2=0,marcador_ind=0;
	marcador=toda_frase(retorno,pilha1,pilha2);//compara as duas pilhas com frase e retorna 0 pra igual e <0 ou >0 para diferente
	marcador_sub=teste_substituicao(retorno,pilha1,pilha2);//substitui os * pelas letras da outra pilha quando possivel e retorna 0 pra certo e 1 pra errado

	if(marcador!=0){
		if(marcador_sub==0){
			marcador_t2=toda_frase(retorno,pilha1,pilha2);

			if(marcador_t2==0){
				printf("É palíndrome – Letra(s): ");
				for(j=0;j<retorno->qtd;j++){

					printf("%c ",retorno->frase_arrumada[j]);
				}
				printf("\n");
			}
			else{
				printf("Não é palindrome\n");
				
			}
		}
		else if(marcador_sub==1){
			printf("Indefinido (Impossível determinar letra(s)\n");
			marcador_ind=1;//para nao printar duas vezes o impossivel determinar
			
		}
	}

	marcador_t=teste_final(retorno,pilha1);
	/*printf("marcador %d\n",marcador);
	printf("marcador_sub %d\n",marcador_sub);
	printf("marcador_t2 %d\n",marcador_t2);
	printf("marcador_t %d\n",marcador_t);//para acompanhar os marcadores caso de algum bug*/
	
	if(marcador_t == 1 && marcador_ind !=1 || marcador_sub ==1){
		printf("Indefinido (Impossível determinar letra(s))\n");
	}
	if(marcador==0 && marcador_t!= 1 && marcador_sub!=1){
		printf("é palindrome\n");
	}
	
	

	
}
tipo_pilha* toda_frase(tipo_retorno *retorno, tipo_pilha *pilha1,tipo_pilha *pilha2){//compara as duas pilhas passando as para dois vetores de strings
	char vet_pilha1[retorno->v2],vet_pilha2[retorno->v2];
	int i=0,marcador=0;
	char aux[1];
	
	for(i=0;i<retorno->v2;i++){
		
		vet_pilha1[i]=pilha1->frase[0];
		vet_pilha2[i]=pilha2->frase[0];
		//printf("%c %c\n",vet_pilha1[i],vet_pilha2[i]);//para acompanhar como está destribuida as pilhas
		
		pilha1=pilha1->prox;//andando na pilha1
		pilha2=pilha2->prox;//andando na pilha2

	}
	//printf("\n");

	aux[0]=vet_pilha1[0];//solucao para um erro que eu ainda nao resolvi
	vet_pilha1[i]='\0';
	vet_pilha2[i]='\0';
	
	vet_pilha1[0]=aux[0];//solucao para um erro que eu ainda nao resolvi
	//marcador=strcmp(vet_pilha1,vet_pilha2);//metodo anterior para comparar strings mas deu algumas falhas
	for(i=0;i<retorno->v2;i++){
		if(vet_pilha1[i]==vet_pilha2[i]){
			marcador=0;//caso igual retorna 0
		}
		else{
			marcador=1;//caso diferente retorn 1 parando o laco
			break;
		}
	}

	return marcador;
}
tipo_pilha*	teste_final(tipo_retorno *retorno,tipo_pilha *pilha1){
	int i=0;
	if(retorno->v2%2 != 0){//caso o * caia no meio da frase
		for(i=0;i<retorno->v2;i++){
			pilha1=pilha1->prox;

		}
		if(pilha1->frase[0]=='*'){
			return 1;
		}
	}
	
	return 0;
}
tipo_pilha* teste_substituicao(tipo_retorno *retorno,tipo_pilha *pilha1,tipo_pilha *pilha2){//compara as duas pilhas e substitui todos os * pelas letras quando possivel
	int i=0,qtd=0,controle=0;
	char vet[100],vet_aux[100];
	for(i=0;i<100;i++){
		retorno->frase_arrumada[i]=' ';
	}
	
	for(i=0;i<retorno->v2;i++){
		
		if(pilha1->frase[0]=='*' && pilha2->frase[0]!='*'){
			
			pilha1->frase[0]=pilha2->frase[0];
			vet[qtd]=pilha2->frase[0];//guarda a letra utilizada
			
			retorno->qtd++;
			qtd++;//qtd so para nao utilizar o da struct que ficaria enorme
		}
		if(pilha2->frase[0]=='*' && pilha1->frase[0]!='*'){
			
			pilha2->frase[0]=pilha1->frase[0];
			vet[qtd]=pilha1->frase[0];//guarda a letra utilizada
			retorno->qtd++;
			qtd++;//qtd so para nao utilizar o da struct que ficaria enorme
		}
		
		if(pilha1->frase[0]=='*' && pilha2->frase[0]=='*'){//caso as duas pilhas tenham * na mesma posicao entao ele retorna 1 que significa "impossivel determinar"
			controle=1;
			return 1;
			break;//sai do laco
		}
		
		pilha1=pilha1->prox;
		pilha2=pilha2->prox;
	}



	strcpy(retorno->frase_arrumada,vet);
	if(controle==0){//se controle for 1 retorna 1
		return 0;
	}
}


int main(){

	tipo_retorno *retorno;
	tipo_pilha *pilha1;
	tipo_pilha *pilha2;
	pilha1 = (tipo_pilha *) malloc(sizeof(tipo_pilha));
	pilha2 = (tipo_pilha *) malloc(sizeof(tipo_pilha));
	retorno = (tipo_pilha *) malloc(sizeof(tipo_pilha));

	int valor=0,i=0,j=0;
	system("clear");
	do{
		printf("\nVerificador de frases palíndromes\n");
		printf("\n1-Verificar frase\n2-sair\n");
		printf("opção: ");scanf("%d",&valor);
		switch(valor){
			case 1:
				system("clear");
				char frase[100],palavra[100];
				printf("Digite a palavra: ");
				__fpurge(stdin);
				gets(palavra);
				printf("\n");
				strcpy(frase,palavra);
				retorno->v1=0;
				retorno->v2=0;
				retorno->qtd=0;
				retorno=arruma_frase(retorno,frase);
				//printf("\nv1=%d v2=%d\n",retorno->v1,retorno->v2);
				arruma_pilha(retorno,pilha1,pilha2);
				teste_pali(retorno,pilha1,pilha2);

						
				break;
		}
		
	}while(valor!=2);
	system("clear");

	return 0;
}