#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct grafo{
	int max;//MAX de vertices
	int contV;//quantos vertices inseridos
	char *vertice;//vetor com vertices
	int **matriz;//matriz
};
typedef struct grafo tipo_grafo;

void iniMatriz(tipo_grafo **grafo, int n){
	int i=0,j=0;
	*grafo = (tipo_grafo*)malloc(sizeof(tipo_grafo));
	(*grafo)->max = n;
	(*grafo)->vertice =(char*)malloc(n*(sizeof(char)));
	(*grafo)->matriz =(int**)malloc(n*(sizeof(int*)));

	for (i = 0; i < n; i++){ //Percorre as linhas do Vetor de Ponteiros
		(*grafo)->matriz[i] = (int*)malloc(n*(sizeof(int))); //Aloca um Vetor de Inteiros para cada posição do Vetor de Ponteiros.
	}
	for (i = 0; i < n; i++){ //Percorre as linhas do Vetor de Ponteiros
		for (j = 0; j < n; j++){ //Percorre o Vetor de Inteiros atual.
			(*grafo)->matriz[i][j] = 0; //Inicializa com 0.
		}
	}	
	//return grafo; //Retorna o Ponteiro para a Matriz Alocada

}

void imprimeMatriz(tipo_grafo *grafo, int n){
	int i=0,j=0;
	printf("[ ]");
	for(i=0;i<n;i++){
		printf("[%c] ",grafo->vertice[i]);
	}
	printf("\n");
	for(i=0;i<n;i++){
		printf("[%c]",grafo->vertice[i]);
		for(j=0;j<n;j++){
			printf("[%d] ",grafo->matriz[i][j]);
		}
		printf("\n");
	}
}
int buscaIndice(tipo_grafo *grafo,char letra,int N){
	int i=0,flag =0,teste =0;
	while(i<N && flag != 1){
		if(grafo->vertice[i] == letra){
			flag =1;
			return i;	
		}
		i++;
	}
	return -1;
}
void insereMatriz(tipo_grafo **grafo, char Ver1,char Ver2){
	int pos1=0, pos2=0;
	pos1 = buscaIndice(*grafo,Ver1,(*grafo)->max);
	pos2 = buscaIndice(*grafo,Ver2,(*grafo)->max);
	if(pos1 >= 0 && pos2 >= 0){
		if(pos1 < pos2){
			(*grafo)->matriz[pos1][pos2] = 1;
		}
		else{
			(*grafo)->matriz[pos2][pos1] = 1;
		}
	}
}
void removeMatriz(tipo_grafo **grafo, char Ver1,char Ver2){
	int pos1=0, pos2=0,i=0;
	pos1 = buscaIndice(*grafo,Ver1,(*grafo)->contV);
	pos2 = buscaIndice(*grafo,Ver2,(*grafo)->contV);
	if(pos1 >= 0 && pos2 >=0){
		
		if(pos1 < pos2){
			(*grafo)->matriz[pos1][pos2] = 0 ;
		}
		else{
			(*grafo)->matriz[pos2][pos1] = 0;
		}
		//(*grafo)->contV--;
	}
}
void PegaGrafo(tipo_grafo **grafo){//, char *argv
	FILE *file;
	int i=0,flagV = 0 , pos1=0, pos2=0,j=0;
	char nomearq[100],V0[2],V1[1],V2[1],vertices[100];

	//strcpy(nomearq,argv);
	//printf("%s\n",nomearq);
	file=fopen("info.txt","r");
	if(file == NULL){//teste  de erro
		printf("Erro na abertura do arquivo %s!\n",nomearq);
	}
	while(fscanf(file,"%s",&V0)!=EOF){
		
		if(V0[0] == '&'){
			if(V0[1] == 'v'){
				flagV = 1;
			}
		}
		if(flagV == 1){
			fscanf(file,"%s",&V0[0]);
			while(V0[0] != '&'){
				vertices[i] = V0[0];
				fscanf(file,"%s",&V0[0]);
				i++;
			}
			printf("i = %d\n",i);
			iniMatriz(grafo,i);
			strcpy((*grafo)->vertice,vertices);
			(*grafo)->contV = i;
			if(V0[1] == 'a'){
				while(fscanf(file,"%s",&V0)!=EOF){
					printf("(%c,%c)\n",V0[0],V0[2]);
					insereMatriz(grafo,V0[0],V0[2]);
				}
			}
		}
		imprimeMatriz(*grafo,(*grafo)->max);
		
	}
	fclose(file);
}

int main(int argc, char *argv[ ]){
	tipo_grafo *grafo;
	PegaGrafo(&grafo);//,argv[1]
	removeMatriz(&grafo,'a','b');
	printf("\n\n");
	imprimeMatriz(grafo,grafo->contV);
	return 0;
}