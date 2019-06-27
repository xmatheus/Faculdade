#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void shell_sort(int n,int valor,char *texto);

void shell_sort(int n,int valor,char *texto){
	int k=0;
	unsigned long int trocas=0;
	long int comp=0;
	for (k = 0; k < n; k++) {
		
		char nomearq[1000];
		FILE *file;
		
		long int linha=0;
		long int vet[valor];
		long int aux=0;
		int i=0,j=0,gap=1,flag=0;

		file = fopen("numeros.txt", "rt");
		

		if (file == NULL){
	    	printf("Problemas na CRIACAO ou abertura do arquivo\n");
	    	
		}
		for(i=0; !feof(file);i++){
			
			fscanf(file,"%ld\n",&linha);
			vet[i]=linha;
		
			
		}
		fclose(file);

		i=1;


		while(gap < valor) {
			gap = 3*gap+1;
			
		}
		while ( gap > 1) {
			gap = gap/3;

				
			for(i = gap; i < valor; i++) {
				flag=0;
				aux = vet[i];
				j = i - gap;
				
				
				while (j >= 0 && aux < vet[j]) {
					vet [j + gap] = vet[j];
					
					j -= gap;
					comp=comp+1;
					flag=1;
					

				}
				if (flag==0){
					comp=comp+1;
				}
				vet [j + gap] = aux;
				trocas=trocas+1;
				printf("[%ld] ",vet[i] );
				
	        }
	        
	        

	    }
		

	    printf("\n");
		char nomearqord[1000];
		FILE *fileord;
		fileord = fopen("shellord", "w");
		int b=0;

		for (b=0; b < valor; b++){
		       
		    fprintf(fileord, "%ld\n",vet[b]);   
		    printf("vet[%ld]\n",vet[b] );
		}
		fclose(fileord);
	}

	FILE *trocasarq;
	trocasarq = fopen("comp and trocas", "a");
	fprintf(trocasarq,"Shell_sort de %d Trocas -> [%lu]\nShell_sort de %d comparação -> [%lu]\n\n ",valor,trocas/5,valor,comp/5);
	fclose(trocasarq);
	

	
	
}


int main(){

	int qtd=1,milao=10,dezmilao=10000,cemmilao=100000;
	char texto1[]="10";
	shell_sort(qtd,milao,texto1);





	return 0;
}








