#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct teste{
	char nome[50];
	int numero;
	int tamanho_frase;
};
typedef struct teste tipo_teste;
/*
void quickSort(tipo_teste *estrutura, int inicio, int fim){
   int k,i, j, meio, aux;

   printf("\n");
   i = inicio;
   j = fim;
   meio = estrutura[(inicio + fim) / 2].numero;
   
   do{

      while(estrutura[i].numero < meio){

         i++;
         
      }
      if(i==21){
      	printf("merdai\n");
      }
      while(estrutura[j].numero > meio){
 
         j--;
         
      }
       if(j==21){
      	printf("merdaj\n");
      }

      if(i <= j){
         aux = estrutura[i].numero;
         estrutura[i].numero = estrutura[j].numero;
         estrutura[j].numero = aux;
         i++;
         j--;
        
      }
      
   }while(i <= j);
 
   if(inicio < j){
      quickSort(estrutura->numero, inicio, j);
   }
 
   if(i < fim){
      quickSort(estrutura->numero, i, fim);
   }
}*/
void shell_sort(tipo_teste *estrutura,int valor){
	int k=1;
	int linha=0;
	int aux=0;
	int i=0,j=0,gap=1,flag=0;
	

	while(gap < valor) {
		gap = 3*gap+1;
		
	}
	while ( gap > 1) {
		gap = gap/3;
		
		for(i = gap; i < valor; i++) {
			flag=0;
			aux = estrutura[i].numero;
			j = i - gap;
			
			while (j >= 0 && aux < estrutura[j].numero) {
				estrutura[j + gap].numero = estrutura[j].numero;
				j -= gap;
				flag=1;
			}
			estrutura[j+gap].numero= aux;
		
        }
    }
			
}
void guarda_nome(tipo_teste *estrutura,int cont){
	FILE *file;
	int i=0,j=0,cont1=0,cont2=0,k=cont;
	file=fopen("alunos-organizados.txt","r");
	if(file == NULL){//teste  de erro
		printf("Erro na abertura do arquivo!\n");
		return 0;
	}
	if(cont%2!=0){
		cont1=(cont/2)+1;
		cont2=(cont/2);
	}
	if(cont%2==0){
		cont1=cont/2;
		cont2=cont/2;
	}
	for(i=0;i<=cont1;i++){
		for(j=0;j<estrutura[i].tamanho_frase;j++){
			printf("%c",estrutura[i].nome[j]);
		}
		printf(" %d",estrutura[i].numero);
		printf("\n");
	
		if(k>cont1){
			for(j=0;j<estrutura[k].tamanho_frase;j++){
				printf("%c",estrutura[k].nome[j]);
			}
			printf(" %d",estrutura[k].numero);
			printf("\n");
			k--;
		}
	}
	fclose(file);
}

int main(){
	FILE *file;
	char letra,frase[100];
	int i=0,cont=0,flag=0,j=0,numero=0;
	file=fopen("alunos.txt","r");
	if(file == NULL){//teste  de erro
		printf("Erro na abertura do arquivo!\n");
		return 0;
	}
    while(fscanf(file,"%c",&letra)!=EOF){
    	if(letra=='\n'){
    		cont++;
    	}
	}
	fclose(file);
	file=fopen("alunos.txt","r");
	if(file == NULL){//teste  de erro
		printf("Erro na abertura do arquivo!\n");
		return 0;
	}
	tipo_teste estrutura[cont];
	printf("cont %d\n",cont);
	
	while(fscanf(file,"%c",&letra)!=EOF){
		//printf("%c\n",letra );
		//printf("i=%d e j=%d\n",i,j);
		if(letra != ':' && letra != '\n' && flag==0){
			estrutura[j].nome[i] = letra;
			

			//printf("%c ",estrutura[j].nome[i]);
			i++;
			
		}
		if(letra==':'&& letra != '\n'){
			flag=1;
			fscanf(file,"%d",&numero);
			
		}
		if(numero!=0){
			estrutura[j].numero=numero;
			numero=0;
			

		}
		if(letra=='\n'){
			estrutura[j].tamanho_frase=i;
			printf("tamanho da frase %d\n",estrutura[j].tamanho_frase );
			j++;
			i=0;
			flag=0;
			
			
		}

		
		
	}
	
	for(i=0;i<cont;i++){
		printf("%d ",estrutura[i].numero);
	}
	printf("\n");

	shell_sort(estrutura,cont);
	for(i=0;i<cont;i++){
		printf("%d ",estrutura[i].numero);
	}
	printf("\n");
	fclose(file);
	guarda_nome(estrutura,cont);


	return 0;
		
}