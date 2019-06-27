#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void gera_arquivo(int quantidade,int valor);

void gera_arquivo(int quantidade,int valor){
	long int vet[valor];
	int i=0,j=0,k=0,T=0;
	int controle1,controle2;
	char vetor[10];

	srand(time(NULL));
	
	
	system("mkdir arquivos-INT");
	for (k = 0; k < quantidade; k++){
		
		FILE *file;
		
		char nomearq[1000];

		sprintf(nomearq, "arquivos-INT/Arq[%d][%d].txt",k,valor);
		file = fopen(nomearq, "w");
		if(file == NULL){
			printf("Erro na abertura do arquivo!\n");
		}
		T = 1+(rand() %10);
		fprintf(file,"%d\n",T);	
		for(i=0; i < valor; i++){
			
			controle1=0001+(rand() %9999); //numeros de 1 ate 9999
			controle2=0001+(rand() %9999);
			for(j=0; j<10; j++){
				vetor[j]= 'a' + (char)(rand()%26);
			}
			vetor[j] = '\0';
			fprintf(file,"%d-%d %s\n",controle1,controle2,vetor);	
    	}
		printf("[%d]Arquivo gerado\n",k+1);
		fclose(file);
	}
}
int main(int argc, char *argv[ ]){

	if(argc==3){
		int quantidade=atoi(argv[1]);
		int valor=atoi(argv[2]);
		printf(" quantidade %d valor %d\n",quantidade,valor);
		system("clear");
		gera_arquivo(quantidade,valor);
	}
	else{
		system("clear");
		printf("\n\t[x]Utilize %s 'quantidade de arquivos' 'quantidade de valores'\n\t[EX]%s 3 20000\n",argv[0],argv[0]);
		return 0;
	}
}