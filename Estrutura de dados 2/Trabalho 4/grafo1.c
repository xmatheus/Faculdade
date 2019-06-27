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
	printf("[X]Vertices: ");
	for(i=0;i<grafo->contV;i++){
		printf("{%c} ",grafo->vertice[i]);
	}
	printf("\n\n");
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
int buscaIndice(tipo_grafo *grafo,char letra,int QtdVertice){
	int i=0;
	while(i<QtdVertice){
		if(grafo->vertice[i] == letra){
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
void removeVerticeVetor(tipo_grafo **grafo, char Ver1){
	int pos=0,i=0,j;
	pos = buscaIndice(*grafo,Ver1,(*grafo)->contV);
	for(i=pos;i<(*grafo)->contV-1;i++){
		(*grafo)->vertice[i] = (*grafo)->vertice[i+1];
		//printf("vertice[%d] %c \n",i,(*grafo)->vertice[i]); 
	}
	(*grafo)->vertice[i] = '\0';
	for(j=0;j<(*grafo)->contV;j++){;
		(*grafo)->matriz[j][i] = 0;
	}
	(*grafo)->contV--;
}
void removeMatrizVertice(tipo_grafo **grafo, char Ver1){
	int pos1=0, pos2=0,i=0,j=0;
	printf("[X]REMOVENDO-> %c\n",Ver1);
	pos1 = buscaIndice(*grafo,Ver1,(*grafo)->contV);	
	if(pos1 == -1){
		printf("[X]Erro na remocao, vertice nao encontrado!\n");
	}
	else{
		for(i=0;i<(*grafo)->contV;i++){
			(*grafo)->matriz[pos1][i] = 0;
			(*grafo)->matriz[i][pos1] = 0;
			
		}
		for(i=0;i<(*grafo)->contV;i++){//
			for(j=pos1;j<(*grafo)->contV-1;j++){
				(*grafo)->matriz[i][j] = (*grafo)->matriz[i][j+1];
			}
		}
		for(i=0;i<(*grafo)->contV;i++){
			for(j=pos1;j<(*grafo)->contV-1;j++){
				(*grafo)->matriz[j][i] = (*grafo)->matriz[j+1][i];
			}
		}
		for(i=0;i<(*grafo)->contV;i++){
			(*grafo)->matriz[i][(*grafo)->contV-1] = 0;
			(*grafo)->matriz[(*grafo)->contV-1][i] = 0;
		}
		removeVerticeVetor(grafo,Ver1);
	}
}
void PegaGrafo(tipo_grafo **grafo){//, char *argv
	FILE *file;
	int i=0,flagV = 0 , pos1=0, pos2=0,j=0;
	char nomearq[100],V0[2],V1[1],V2[1],vertices[100];

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
			printf("[X]Qtd Vertices = %d\n",i);
			iniMatriz(grafo,i);
			strcpy((*grafo)->vertice,vertices);
			(*grafo)->contV = i;
			if(V0[1] == 'a'){
				printf("[X]Arestas: \n");
				while(fscanf(file,"%s",&V0)!=EOF){
					printf("[X](%c,%c)\n",V0[0],V0[2]);
					insereMatriz(grafo,V0[0],V0[2]);
				}
			}
		}		
	}
	fclose(file);
}
void MostraVizinhos(tipo_grafo **grafo, char vertice){
	int i,j,pos;
	pos = buscaIndice(*grafo,vertice,(*grafo)->contV);
	printf("\nvizinhos do vertice '%c': ",vertice);
	for(i=0;i<(*grafo)->contV;i++){
		if((*grafo)->matriz[pos][i] > 0 || (*grafo)->matriz[i][pos] > 0){
			printf("[%c]",(*grafo)->vertice[i]);	
		}
	}
	printf("\n");
}
void BuscaVertice(tipo_grafo **grafo, char vertice){
	int pos;
	pos = buscaIndice(*grafo,vertice,(*grafo)->contV);
	if(pos == -1){
		printf("\n[X] VERTICE nao encontrado\n");
	}
	else{
		MostraVizinhos(grafo,vertice);
	}
}
int GrauVertice(tipo_grafo *grafo, char vertice){
	int i,pos,grau=0;
	pos = buscaIndice(grafo,vertice,grafo->contV);
	if(pos == -1){
		printf("\n[X] VERTICE nao encontrado\n");	
	}
	else{
		for(i=0; i < grafo->contV;i++){
			if( (grafo->matriz[pos][i] > 0) || (grafo->matriz[i][pos] > 0) ){
				grau++;	
			}
		}
	}
	return grau;
}
void incializaFila(tipo_grafo *grafo,char *fila){
	int i =0;
	for(i=0;i<grafo->contV;i++){
		fila[i] = '-';
	}
}
int contaVisitados(tipo_grafo *grafo, char *visitados){
	int i=0;
	while(visitados[i] != '-' && i !=grafo->contV){
		i++;
	}
	return i;
}
int AddFila(tipo_grafo *grafo, char *fila, char vertice, char *visitados){
	int i=0,flag = 0;
	while( (i<grafo->contV) || (flag != 1)){
		if(visitados[i] == vertice){
			flag = 1;
			return 0;
		}
		if(fila[i] == vertice){
			flag = 1;
			return 0;
		}
		if(fila[i] == '-' && flag != 1){
			fila[i] = vertice;
			flag = 1;
			return 1;
		}
		//printf("fila: %c\n",fila[i]);
		i++;
	}
}
void AddVisitados(tipo_grafo *grafo, char *visitados, char vertice){
	int i=0,flag = 0;
	while( (i<grafo->contV) || (flag != 1)){
		if(visitados[i] == vertice){
			flag = 1;
		}
		if(visitados[i] == '-' && flag != 1){
			visitados[i] = vertice;
			flag = 1;
		}
		//printf("Visitado: %c\n",visitados[i]);
		i++;
	}
}
void removeFila(tipo_grafo *grafo,char *fila, char vertice){
	int k=0,i=0,flag =0;
	while(i<grafo->contV && flag != 1){
		if(fila[i] == vertice){
			flag = 1;
		}
		i++;
	}
	for(k=i-1;k<grafo->contV-1;k++){
		fila[k] = fila[k+1];
	}
}
void PercorreLargura(tipo_grafo *grafo, char vertice, char *fila, char *visitados){
	int i=0,pos=0,j=0,teste=0,QtdVisitados=0;
	
	printf("(%c)\n",vertice);
	AddVisitados(grafo,visitados,vertice);
	removeFila(grafo,fila,vertice);
	pos = buscaIndice(grafo,vertice,grafo->contV);
	QtdVisitados = contaVisitados(grafo,visitados);

	if(pos > -1 && QtdVisitados != grafo->contV){
		for(i=0;i<grafo->contV;i++){
			if(i < pos ){
				if(grafo->matriz[i][pos] > 0){
					teste = AddFila(grafo,fila,grafo->vertice[i],visitados);
					if(teste){
						j++;
					}
				}
			}
			else{
				if(grafo->matriz[pos][i] > 0){
					teste = AddFila(grafo,fila,grafo->vertice[i],visitados);
					if(teste){		
						j++;
					}
				}	
			}
		}
		QtdVisitados = contaVisitados(grafo,visitados);
		if(QtdVisitados != grafo->contV){
			j = grafo->contV - QtdVisitados;
			for(i=0;i<j;i++){
				if(fila[i]!= '-'){
					PercorreLargura(grafo,fila[i],fila,visitados);	
				}
			}
		}
		
	}
}
void ChamaLargura(tipo_grafo *grafo,char vertice){
	char *fila = malloc(grafo->contV * sizeof(char));
	char *visitados = malloc(grafo->contV * sizeof(char));
	incializaFila(grafo,fila);
	incializaFila(grafo,visitados);
	fila[0] = vertice;
	PercorreLargura(grafo,vertice,fila,visitados);
}
int VerificaFila(char vertice, char *fila){
	int i=0,flag=0;
	while(fila[i] != '\0' || flag != 1){	
		if(fila[i] == vertice){
			flag=1;
			return 1;
		}
		i++;
	}
	return 0;
}
void Profundidade(tipo_grafo *grafo, char vertice, int cont, char *fila){
	int pos;
	if(cont < grafo->contV){
		
		
		printf("vertice[%c]\n",vertice);
		pos = buscaIndice(grafo,vertice,grafo->contV);
		Profundidade(grafo,grafo->vertice[cont+1],cont+1,fila);
		
		for(int j=0;j < grafo->contV;j++){	
			if(pos<j){	
				if(grafo->matriz[pos][j] > 0){
					if(!VerificaFila(grafo->vertice[j],fila)){//grafo->vertice[j]!=fila[cont]
						//printf("vertice[%c]\n",grafo->vertice[j]);
						fila[cont]=grafo->vertice[j];
						Profundidade(grafo,grafo->vertice[j],cont+1,fila);
					}
				}
			}
			else{
				if(grafo->matriz[j][pos] > 0){
					if(!VerificaFila(grafo->vertice[j],fila)){//grafo->vertice[j]!=fila[cont]
						//printf("vertice[%c]\n",grafo->vertice[j]);
						fila[cont]=grafo->vertice[j];
						Profundidade(grafo,grafo->vertice[j],cont+1,fila);
					}
				}	
			}
		}
	}
}
void chamaProfundidade(tipo_grafo *grafo, char vertice){
	int j=0;
	char *fila = malloc(sizeof(char)*grafo->contV);
	Profundidade(grafo,vertice,0,fila);
}


int main(int argc, char *argv[]){
	tipo_grafo *grafo;
	int grau;
	PegaGrafo(&grafo);//,argv[1]
	//imprimeMatriz(grafo,grafo->contV);
	//BuscaVertice(&grafo,'d');
	//removeMatrizVertice(&grafo,'d');
	//grau = GrauVertice(grafo,'e');
	//printf("Grau = %d\n",grau );
	imprimeMatriz(grafo,grafo->contV);
	chamaProfundidade(grafo,'e');
	//ChamaLargura(grafo,'a');
	return 0;
}