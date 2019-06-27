#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>// necessário p/ as funções rand() e srand()
#include <time.h>//necessário p/ função time()
 
int main(void)
{
	int i=0,j=0,numero=0,Linha=0,result=0,controle1=0,flag=0;
 	FILE *pont_arq;
 	int vet[10000];

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
 
	for (i=0; i < 10000; i++){
		flag=0;
           // gerando valores aleatórios na faixa de 0 a 10000

		
		controle1=(1+rand() %10000);
		
		do{
			flag=1;
			for (j=0; j < i; j++){
				
				if (controle1==vet[j]){
					controle1=(1+rand() %10000);
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
	return 0;
}
