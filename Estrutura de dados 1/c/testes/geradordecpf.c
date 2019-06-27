#include <stdio.h>
#include <stdlib.h>
#include <time.h>



void ale_vet(int qtd);

void ale_vet(int qtd){
	FILE *file;
	file = fopen("cpf.txt", "a");
	if(file == NULL){
		printf("Erro na abertura do arquivo!\n");
	}
	int i=0;
	for(i=0;i<qtd;i++){
		
		int vet[11];
		int i=0,multiplicador=0,cont=10;
		for (i=0;i<9;i++){
			vet[i]=(0+rand() %9);//valores de 0 ate 9
			multiplicador=(vet[i]*cont)+multiplicador;
			
			cont=cont-1;

		}

		if (multiplicador%11<2){
			vet[9]=0;
		}
		else if(multiplicador%11>=2){
			vet[9]=11-(multiplicador%11);
		}
		cont=11;
		multiplicador=0;
		i=0;
		for (i=0;i<10;i++){
			multiplicador=(vet[i]*cont)+multiplicador;
			cont=cont-1;

		}
		if (multiplicador%11<2){
			vet[10]=0;
		}
		else if(multiplicador%11>=2){
			vet[10]=11-(multiplicador%11);
		}



		fprintf(file, "%d%d%d.%d%d%d.%d%d%d-%d%d\n",vet[10],vet[9],vet[8],vet[7],vet[6],vet[5],vet[4],vet[3],vet[2],vet[1],vet[0]);	    
	}
	fclose(file);


}



int main(){

	int qtd=0,i=0;
	printf("Quantidade de CPF a serem gerados? \n");
	scanf("%d",&qtd);
	system("clear");
	srand(time(NULL));
	ale_vet(qtd);
	printf("gerado!\n");


















	return 0;
}