#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void ARQ1000(int *vet); //unico retornando o vetor, falta adiconar nos outros
void ARQ10000();
void ARQ100000();
void ARQ5000();
void ARQ500();

//Arquivo com 1000 numeros
void ARQ1000(int *vet){ //unico retornando o vetor, falta adiconar nos outros

	int i=0,j=0,numero=0,Linha=0,result=0,controle1=0,flag=0;
 	FILE *pont_arq;

	pont_arq = fopen("1000-arq1.txt", "w");

	if(pont_arq == NULL){
		printf("Erro na abertura do arquivo!\n");
	}
 
     /* srand(time(NULL)) objetiva inicializar o gerador de números aleatórios
        com o valor da função time(NULL). Este por sua vez, é calculado
        como sendo o total  de segundos passados desde 1 de janeiro de 1970
        até a data atual.
        Desta forma, a cada execução o valor da "semente" será diferente.
     */
	srand(time(NULL));
 
	for (i=0; i < 1000; i++){
		flag=0;

		
		controle1=(1+rand() %999999);
		
		do{
			flag=1;
			for (j=0; j < i; j++){
				
				if (controle1==vet[j]){
					controle1=(1+rand() %999999);
					flag=0;
					
				}	
			}
		
			
		} while (flag==0);	
		
			
		vet[i]=controle1;
		
	}
	i=0;
	for (i=0; i < 1000; i++){
           
		
		fprintf(pont_arq, "%d\n",vet[i]);
		
	}

 
	fclose(pont_arq);
	
	
}
//Arquivo com 10000 numeros
void ARQ10000(){
	int i=0,j=0,numero=0,Linha=0,result=0,controle1=0,flag=0;
 	FILE *pont_arq;
 	int vet[10000];

	pont_arq = fopen("10000-arq1.txt", "w");

	if(pont_arq == NULL){
		printf("Erro na abertura do arquivo!\n");
	}
 
     /* srand(time(NULL)) objetiva inicializar o gerador de números aleatórios
        com o valor da função time(NULL). Este por sua vez, é calculado
        como sendo o total  de segundos passados desde 1 de janeiro de 1970
        até a data atual.
        Desta forma, a cada execução o valor da "semente" será diferente.
     */
	srand(time(NULL));
 
	for (i=0; i < 10000; i++){
		flag=0;
         

		
		controle1=(1+rand() %999999);
		
		do{
			flag=1;
			for (j=0; j < i; j++){
				
				if (controle1==vet[j]){
					controle1=(1+rand() %999999);
					flag=0;
					
				}	
			}
		
			
		} while (flag==0);	
		
			
		vet[i]=controle1;
		
	}
	i=0;
	for (i=0; i < 10000; i++){
           
		
		fprintf(pont_arq, "%d\n",vet[i]);
		
	}

 
	fclose(pont_arq);
}
//Arquivo com 100000 numeros
void ARQ100000(){
	int i=0,j=0,numero=0,Linha=0,result=0,controle1=0,flag=0;
 	FILE *pont_arq;
 	int vet[100000];

	pont_arq = fopen("100000-arq1.txt", "w");

	if(pont_arq == NULL){
		printf("Erro na abertura do arquivo!\n");
	}
 
     /* srand(time(NULL)) objetiva inicializar o gerador de números aleatórios
        com o valor da função time(NULL). Este por sua vez, é calculado
        como sendo o total  de segundos passados desde 1 de janeiro de 1970
        até a data atual.
        Desta forma, a cada execução o valor da "semente" será diferente.
     */
	srand(time(NULL));
 
	for (i=0; i < 100000; i++){
		flag=0;
           

		
		controle1=(1+rand() %999999);
		
		do{
			flag=1;
			for (j=0; j < i; j++){
				
				if (controle1==vet[j]){
					controle1=(1+rand() %999999);
					flag=0;
					
				}	
			}
		
			
		} while (flag==0);	
		
			
		vet[i]=controle1;
		
	}
	i=0;
	for (i=0; i < 100000; i++){
           
		
		fprintf(pont_arq, "%d\n",vet[i]);
		
	}

 
	fclose(pont_arq);
}
//Arquivo com 5000 numeros
void ARQ5000(){
	int i=0,j=0,numero=0,Linha=0,result=0,controle1=0,flag=0;
 	FILE *pont_arq;
 	int vet[5000];

	pont_arq = fopen("5000-arq1.txt", "w");

	if(pont_arq == NULL){
		printf("Erro na abertura do arquivo!\n");
	}
 
     /* srand(time(NULL)) objetiva inicializar o gerador de números aleatórios
        com o valor da função time(NULL). Este por sua vez, é calculado
        como sendo o total  de segundos passados desde 1 de janeiro de 1970
        até a data atual.
        Desta forma, a cada execução o valor da "semente" será diferente.
     */
	srand(time(NULL));
 
	for (i=0; i < 5000; i++){
		flag=0;
           

		
		controle1=(1+rand() %999999);
		
		do{
			flag=1;
			for (j=0; j < i; j++){
				
				if (controle1==vet[j]){
					controle1=(1+rand() %999999);
					flag=0;
					
				}	
			}
		
			
		} while (flag==0);	
		
			
		vet[i]=controle1;
		
	}
	i=0;
	for (i=0; i < 5000; i++){
           
		
		fprintf(pont_arq, "%d\n",vet[i]);
		
	}

 
	fclose(pont_arq);
}
//Arquivo com 500 numeros
void ARQ500(){
	int i=0,j=0,numero=0,Linha=0,result=0,controle1=0,flag=0;
 	FILE *pont_arq;
 	int vet[500];

	pont_arq = fopen("500-arq1.txt", "w");

	if(pont_arq == NULL){
		printf("Erro na abertura do arquivo!\n");
	}
 
     /* srand(time(NULL)) objetiva inicializar o gerador de números aleatórios
        com o valor da função time(NULL). Este por sua vez, é calculado
        como sendo o total  de segundos passados desde 1 de janeiro de 1970
        até a data atual.
        Desta forma, a cada execução o valor da "semente" será diferente.
     */
	srand(time(NULL));
 
	for (i=0; i < 500; i++){
		flag=0;
           

		
		controle1=(1+rand() %999999);
		
		do{
			flag=1;
			for (j=0; j < i; j++){
				
				if (controle1==vet[j]){
					controle1=(1+rand() %999999);
					flag=0;
					
				}	
			}
		
			
		} while (flag==0);	
		
			
		vet[i]=controle1;
		
	}
	i=0;
	for (i=0; i < 500; i++){
           
		
		fprintf(pont_arq, "%d\n",vet[i]);
		
	}

 
	fclose(pont_arq);
}
	





int main(){
	int i=0;
	int vet1[1000];
	
	ARQ1000(vet1);
	ARQ10000();
	ARQ100000();
	ARQ500();
	ARQ5000();
	
	
	for (i=0;i<1000;i++){
		printf("[%d]\n",vet1[i]);
	}
	printf("teste\n");
	
	
	
		
	
	
	
	return 0;
}
