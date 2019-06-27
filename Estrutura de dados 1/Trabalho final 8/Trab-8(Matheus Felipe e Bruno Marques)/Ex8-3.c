/*
	Aluno: Matheus Felipe Teodoro Correia
	Algorimo do exercicio 3, faltando um teste, caso os alunos
	 da UFMT ou da escola fudamental sejam maiores em quantidades o algoritmo apresentara erro.

	 Necessario: 2 arquivos, um chamado alunos.txt com parametro nome:idade para o algoritmo organizar,o segundo é 
	 chamado alunos-organizados.txt, esse vai conter os pares de alunos ja organizados.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct teste{
	char nome[50];
	int numero;
	int tamanho_frase;
};
typedef struct teste tipo_teste;

void shell_sort(tipo_teste *estrutura,int valor){
	int k=1;
	int linha=0;
	
	int i=0,j=0,gap=1,flag=0;
	tipo_teste aux;

	while(gap < valor) {
		gap = 3*gap+1;
		
	}
	while ( gap > 1) {
		gap = gap/3;
		
		for(i = gap; i < valor; i++) {
			flag=0;
			aux = estrutura[i];
			
			j = i - gap;
			
			while (j >= 0 && aux.numero < estrutura[j].numero) {
				estrutura[j + gap] = estrutura[j];
				j -= gap;
				flag=1;
			}
			estrutura[j+gap]= aux;
		
        }
    }
			
}

void guarda_nome(tipo_teste *estrutura,int cont){
	FILE *file;
	int i=0,j=0,cont1=0,cont2=0,k=cont-1;
	file=fopen("alunos-organizados.txt","w");
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
			//printf("%c",estrutura[i].nome[j]);
			fprintf(file, "%c",estrutura[i].nome[j]);
		}
		fprintf(file, " : %d",estrutura[i].numero);
		//printf(" %d",estrutura[i].numero);
		//printf("\n");
		if(estrutura[i].numero<=16){
			fprintf(file, " com ");
		}
		
		
		if(k>cont1){
			
			for(j=0;j<estrutura[k].tamanho_frase;j++){
				//printf("%c",estrutura[k].nome[j]);
				//printf("k=%d j=%d \n",k,j );
				fprintf(file, "%c",estrutura[k].nome[j]);
			}
			//printf(" %d",estrutura[	k].numero);
			fprintf(file, " : %d\n",estrutura[k].numero);
			//printf("\n");
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
		printf("Erro na abertura do arquivo alunox.txt, ele deve ter o parametro nome:idade\n");
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
		printf("Erro na abertura do arquivo alunox.txt, ele deve ter o parametro nome:idade!\n");
		return 0;
	}
	tipo_teste estrutura[cont];
	//printf("cont %d\n",cont);
	
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
			//printf("tamanho da frase %d\n",estrutura[j].tamanho_frase );
			j++;
			i=0;
			flag=0;
			
			
		}

		
		
	}
	



	shell_sort(estrutura,cont);
	fclose(file);
	guarda_nome(estrutura,cont);
	printf("Finalizado com sucesso, arquivo alunos-organizados.txt criado\n");

	return 0;
		
}