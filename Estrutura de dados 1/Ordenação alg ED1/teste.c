#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//prototipo

void gera_arquivo(int n,int valor,char *texto);
void insert_sort(int n,int valor,char *texto);
void bubble_sort(int n,int valor,char *texto);
void selection_sort(int n,int valor,char *texto);
void shell_sort(int n,int valor,char *texto);
int separa_quick(int *v , int p, int r);
void quick_sort (int n,int valor,char *texto, int p);




//funcoes

void gera_arquivo(int n, int valor, char *texto){
	int vet[valor];
	
	
	int i=0,j=0,numero=0,controle1=0,flag=0,b=0;
	srand(time(NULL));
    
	int k=0;
	

    
    for (k = 1; k < n; k++) {
    	char nomearq[1000];
        FILE *file;
        sprintf(nomearq, "Arq-numeros-aleat/%s-arq%02d.txt",texto,k);//gera nomes em sequencia
        
        file = fopen(nomearq, "w");

        if(file == NULL){
		    printf("Erro na abertura do arquivo!\n");
		}

		for (i=0; i < valor; i++){
		    flag=0;

		    
		   controle1=(1+rand() %999999); //numeros de 1 ate 999999
		    
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

		for (b=0; b < valor; b++){
		       
		    
		    fprintf(file, "%d\n",vet[b]);

		    
		}
		fclose(file);
		printf("Gerado %d de %d\n",k,valor );
	}
	printf("\n");
}

void selection_sort (int n,int valor,char *texto) {
	
	int k=1;
	unsigned long int trocas=0;
	long int comp=0;
	
	for (k = 1; k < n; k++) {
		
		char nomearq[1000];
		FILE *file;
		sprintf(nomearq, "Arq-numeros-aleat/%s-arq%02d.txt",texto,k); 
		long int linha=0;
		long int vet[valor];
		unsigned long int cont=0,aux=0,min=0;;
		int i=0,j=0,flag=0;

		file = fopen(nomearq, "rt");

		if (file == NULL){
	    	printf("Problemas na CRIACAO ou abertura do arquivo\n");
	    	
		}
		for(i=0; !feof(file);i++){//le linha por linha ate o final do arquivo e passa para o vetor
			
			fscanf(file,"%ld\n",&linha);
			vet[i]=linha;
			
		}
		fclose(file);

		
		
		i=0;
		j=0;
		
	  
		for (i = 0; i < (valor - 1); i++) {

	    	min = i;
			for (j = i+1; j < valor; j++) {
	      
				if (vet[j] < vet[min]) {
					min = j;
				}
				comp=comp+1;
	    	}
	   		if (i != min) {
				aux = vet[i];
				vet[i] = vet[min];
				vet[min] = aux;
				trocas=trocas+1;
			}
	    }
	    

		char nomearqord[10000];
		FILE *fileord;
		sprintf(nomearqord, "Ordenados_Selection/Ord-selec-%s-arq%02d.txt",texto,k);
		fileord = fopen(nomearqord, "w");
		int b=0;
		for (b=0; b < valor; b++){
		       
		    fprintf(fileord, "%ld\n",vet[b]);   
		}
		fclose(fileord);
	}


	
	
	FILE *trocasarq;
	trocasarq = fopen("comp and trocas", "a");
	fprintf(trocasarq,"selection_sort de %d trocas -> [%lu]\n selection_sort de %d comparação -> [%lu]\n\n ",valor,trocas/5,valor,comp/5);
	fclose(trocasarq);
}

void bubble_sort(int n,int valor,char *texto){
	
	int k=1;
	unsigned long int trocas=0;
	long int comp=0;
	
	for (k = 1; k < n; k++) {
		
		char nomearq[1000];
		FILE *file;
		sprintf(nomearq, "Arq-numeros-aleat/%s-arq%02d.txt",texto,k); 
		
		long int linha=0;
		long int vet[valor];
		unsigned long int cont=0,aux=0;
		int i=0,j=0,flag=0,y=0;

		file = fopen(nomearq, "rt");
		

		if (file == NULL){
	    	printf("Problemas na CRIACAO ou abertura do arquivo\n");
	    	
		}
		for(i=0; !feof(file);i++ && i!=valor){
			
			fscanf(file,"%ld\n",&linha);
			vet[i]=linha;
			
		}

		fclose(file);

		i=0;

		for (i=0;i<valor;i++){
			
			for(y=i+1;y<valor;y++){
				if (vet[i]>vet[y]){
					aux=vet[i];
					vet[i]=vet[y];
					vet[y]=aux;
					trocas=trocas+1;
				}
				comp=comp+1;
			}
		}

		char nomearqord[1000];
		FILE *fileord;
		
		sprintf(nomearqord, "Ordenados_Bubble/Ord-bubble-%s-arq%02d.txt",texto,k);
		fileord = fopen(nomearqord, "w");
		int b=0;

		for (b=0; b < valor; b++){

		    fprintf(fileord, "%ld\n",vet[b]);   

		}
		fclose(fileord);

	}	
	
	FILE *trocasarq;
	trocasarq = fopen("comp and trocas", "a");
	fprintf(trocasarq,"bubble_sort de %d trocas -> [%lu]\n bubble_sort de %d comparação -> [%lu]\n\n ",valor,trocas/5,valor,comp/5);
	fclose(trocasarq);
}

void insert_sort(int n,int valor,char *texto){


	int k=1;
	unsigned long int trocas=0;
	long int comp=0;
	for (k = 1; k < n; k++) {
		
		char nomearq[1000];
		FILE *file;
		sprintf(nomearq, "Arq-numeros-aleat/%s-arq%02d.txt",texto,k); 
		long int linha=0;
		long int vet[valor];
		unsigned long int aux=0;
		int i=0,j=0,flag=0;

		file = fopen(nomearq, "rt");

		if (file == NULL){
	    	printf("Problemas na CRIACAO ou abertura do arquivo\n");
	    	
		}
		for(i=0; !feof(file);i++){
			
			fscanf(file,"%ld\n",&linha);
			vet[i]=linha;
			
		}
		fclose(file);

		i=1;


		for (i = 1; i < valor; i++) {
            j = i;
            flag=0;
            while (j > 0 && vet[j - 1] > vet[j]) {
                  aux = vet[j];
                  vet[j] = vet[j - 1];
                  vet[j - 1] = aux;
                  j--;
                  trocas=trocas+1;
                  comp=comp+1;
                  flag=1;
			}
			if (flag==0){
				comp=comp+1;
			}
			
		}



		char nomearqord[1000];
		FILE *fileord;
		sprintf(nomearqord, "Ordenados_Insert/Ord-Insert-%s-arq%02d.txt",texto,k);
		fileord = fopen(nomearqord, "w");
		int b=0;

		for (b=0; b < valor; b++){
		       
		    fprintf(fileord, "%ld\n",vet[b]);   
		}
		fclose(fileord);

		
	
	}
	


	FILE *trocasarq;
	trocasarq = fopen("comp and trocas", "a");
	fprintf(trocasarq,"insert_sort de %d Trocas -> [%lu]\ninsert_sort de %d comparação -> [%lu]\n\n ",valor,trocas/5,valor,comp/5);
	fclose(trocasarq);

}

void shell_sort(int n,int valor,char *texto){
	int k=1;
	unsigned long int trocas=0;
	long int comp=0;
	for (k = 1; k < n; k++) {
		
		char nomearq[1000];
		FILE *file;
		sprintf(nomearq, "Arq-numeros-aleat/%s-arq%02d.txt",texto,k); 
		long int linha=0;
		long int vet[valor];
		long int aux=0;
		int i=0,j=0,gap=1,flag=0;

		file = fopen(nomearq, "rt");

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
	        }
	    }
		


		char nomearqord[1000];
		FILE *fileord;
		sprintf(nomearqord, "Ordenados_Shell/Ord-Shell-%s-arq%02d.txt",texto,k);
		fileord = fopen(nomearqord, "w");
		int b=0;

		for (b=0; b < valor; b++){
		       
		    fprintf(fileord, "%ld\n",vet[b]);   
		}
		fclose(fileord);

		
	
	}
	


	FILE *trocasarq;
	trocasarq = fopen("comp and trocas", "a");
	fprintf(trocasarq,"Shell_sort de %d Trocas -> [%lu]\nShell_sort de %d comparação -> [%lu]\n\n ",valor,trocas/5,valor,comp/5);
	fclose(trocasarq);
	

}

int separa_quick (int *v, int p, int r){	

	int c = v[p], i = p+1, j = r, t;
	while ( i <= j) {
		if (v[i] <= c){ 
			++i;
		}

		else if (c < v[j]){ 
			--j; 
		}
		else {
			t = v[i], v[i] = v[j], v[j] = t;
			++i; --j;
		}
	}
               
	v[p] = v[j];
	v[j] = c;
	return j; 

}
void quick_sort (int n,int valor,char *texto, int p){

	int k=1;
	unsigned long int trocas=0;
	long int comp=0;
	for (k = 1; k < n; k++) {
		
		char nomearq[1000];
		FILE *file;
		sprintf(nomearq, "Arq-numeros-aleat/%s-arq%02d.txt",texto,k); 
		long int linha=0;
		long int vet[valor];
		long int aux=0;
		int i=0,j=0,gap=1,flag=0;

		file = fopen(nomearq, "rt");

		if (file == NULL){
	    	printf("Problemas na CRIACAO ou abertura do arquivo\n");
	    	
		}
		for(i=0; !feof(file);i++){
			
			fscanf(file,"%ld\n",&linha);
			vet[i]=linha;
			
		}
		fclose(file);
	

		j=0;
		
		if (p < valor){                   
			j = separa_quick(vet, p, valor);     
			quick_sort (vet, p, j-1);     
			quick_sort (vet, j+1, valor);   
		}

		char nomearqord[1000];
		FILE *fileord;
		sprintf(nomearqord, "Ordenados_Quick/Ord-Quick-%s-arq%02d.txt",texto,k);
		fileord = fopen(nomearqord, "w");
		int b=0;

		for (b=0; b < valor; b++){
		       
		    fprintf(fileord, "%ld\n",vet[b]);   
		}
		fclose(fileord);

		
	
	}
}

//funcao principal
int main(){
	
    int qtd=6,milao=1000,dezmilao=10000,cemmilao=100000;
    
    //Nome dos arquivos
    //mudar conforme desejar 
    char texto1[]="1000";
    char texto2[]="10000";
    char texto3[]="100000";

    //chamando a funcao para gerar os arquivos e gravar os numeros aleatoriamente
	system("mkdir Arq-numeros-aleat");
	gera_arquivo(qtd,milao,texto1);
	gera_arquivo(qtd,dezmilao,texto2);
	//gera_arquivo(qtd,cemmilao,texto3);

    //metodos de ordenacao
	

	/*
	
	printf("Gerando arquivos organizados com o método selection_sorts\n");
	system("mkdir Ordenados_Selection");//cria pasta ordenados selection
	selection_sort(qtd,milao,texto1);
	selection_sort(qtd,dezmilao,texto2);
	selection_sort(qtd,cemmilao,texto3);
	printf("selection_sort terminado!\n");
	

    
	printf("Gerando arquivos organizados com o método bubble_sort\n");
    system("mkdir Ordenados_Bubble");//cria pasta ordenados bubble
    bubble_sort(qtd,milao,texto1);
    bubble_sort(qtd,dezmilao,texto2);
    bubble_sort(qtd,cemmilao,texto3);
    printf("bubble_sort terminado!\n");
    

	
    printf("Gerando arquivos organizados com o método insert_sort\n");
	system("mkdir Ordenados_Insert");//cria pasta ordenados insert
	insert_sort(qtd,milao,texto1);
	insert_sort(qtd,dezmilao,texto2);
	insert_sort(qtd,cemmilao,texto3);
	printf("insert_sort terminado!\n");
	*/
	


	printf("Gerando arquivos organizados com o método shell_sort\n");
	system("mkdir Ordenados_Shell");
	shell_sort(qtd,milao,texto1);
	shell_sort(qtd,dezmilao,texto2);
	shell_sort(qtd,cemmilao,texto3);
	printf("shell_sort terminado!\n");

	printf("Gerando arquivos organizados com o método Quick_sort\n");
	system("mkdir Ordenados_Quick");
	quick_sort(qtd,milao,texto1,0);
	quick_sort(qtd,dezmilao,texto2,0);
	quick_sort(qtd,cemmilao,texto3,0);
	printf("Quick_sort terminado!\n");


	
    



    




    return 0;
}
