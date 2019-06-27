#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void gera_arquivo(int quantidade,int valor);

void gera_arquivo(int quantidade,int valor){
	long int vet[valor];
	int i=0,j=0,numero=0,flag=0,b=0;
	long int controle=0;
	srand(time(NULL));
	int k=0;
	
	system("mkdir arquivos-INT");
	for (k = 0; k < quantidade; k++){

		FILE *file;
		char nomearq[1000];

		sprintf(nomearq, "arquivos-INT/Arq[%d][%d].txt",k,valor);
		file = fopen(nomearq, "w");
		if(file == NULL){
			printf("Erro na abertura do arquivo!\n");
		}
		for(i=0; i < valor; i++){
			flag=0;
			controle=(1+rand() %99999999); //numeros de 1 ate 100000
			do{
				flag=1;				
				for (j=0; j < i; j++){
					if (controle==vet[j]){
						controle=(1+rand() %99999999);
						flag=0;			
					}   
				}
			}while (flag==0);	
			vet[i]=controle;  
		}
		for (b=0; b < valor; b++){			   
				fprintf(file,"%ld\n",vet[b]);		 
		}
		fclose(file);
		printf("[%d]Arquivo gerado\n",k+1);
	}

}
int main(int argc, char *argv[ ]){

	if(argc==3){
		int quantidade=atoi(argv[1]);
		int valor=atoi(argv[2]);
		system("clear");
		gera_arquivo(quantidade,valor);
	}
	else{
		system("clear");
		printf("\n\t[x]Utilize %s 'quantidade de arquivos' 'quantidade de valores'\n\t[EX]%s 3 20000\n",argv[0],argv[0]);
		return 0;
	}
}