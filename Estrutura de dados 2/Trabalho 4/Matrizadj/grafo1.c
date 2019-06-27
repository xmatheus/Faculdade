/* Aluno: Matheus Felipe Teodoro Correia
 * Trabalho 1 - grafos
 * Matriz de adjacencia - grafos
 * Professor: Ivairton
 * Universidade Federal do Mato Grosso
 * Ciencia Da Computacao
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct grafo{
	int max;//MAX de vertices
	int contV;//quantos vertices inseridos
	int *vertice;//vetor com vertices
	int **matriz;//matriz
};
typedef struct grafo tipo_grafo;
struct lista{
	int vertice[1];
	struct lista *prox;
};
typedef struct lista tipo_lista;

//Prototipos
void iniMatriz(tipo_grafo **grafo, int n);
void imprimeMatriz(tipo_grafo *grafo, int n);
int buscaIndice(tipo_grafo *grafo,int vertice,int QtdVertice);
void insereMatriz(tipo_grafo **grafo, int Ver1,int Ver2,int peso);
void removeVerticeVetor(tipo_grafo **grafo, int Ver1);
void removeMatrizVertice(tipo_grafo **grafo, int Ver1);
void ListaEncadeada(tipo_lista **lista,int vertice);
void mostralista(tipo_lista *lista);
int ListaParaVetor(tipo_grafo **grafo, tipo_lista *lista,int pos);
int Maiorvetor(int *vetor,tipo_grafo *grafo);
int Menorvetor(int *vetor,tipo_grafo *grafo);
void GrauMatriz(tipo_grafo *grafo);
void MostraVizinhos(tipo_grafo **grafo, char vertice);
void BuscaVertice(tipo_grafo **grafo, char vertice);
int GrauVertice(tipo_grafo *grafo, char vertice);
void incializaFila(tipo_grafo *grafo,int *fila);
int contaVisitados(tipo_grafo *grafo, int *visitados);
int AddFila(tipo_grafo *grafo, int *fila, int vertice, int *visitados);
void AddVisitados(tipo_grafo *grafo, int *visitados, int vertice);
void removeFila(tipo_grafo *grafo,int *fila, int vertice);
void PercorreLargura(tipo_grafo *grafo, int vertice, int *fila, int *visitados,int cont);
void ChamaLargura(tipo_grafo *grafo,int vertice);
int VerificaFila(tipo_grafo *grafo,int vertice, int *visitados);
void Profundidade(tipo_grafo *grafo, int vertice, int cont, int *visitados);
void chamaProfundidade(tipo_grafo *grafo, int vertice);
void PegaGrafo(tipo_grafo **grafo);

//funcoes
void iniMatriz(tipo_grafo **grafo, int n){
	int i=0,j=0;
	*grafo = (tipo_grafo*)malloc(sizeof(tipo_grafo));
	(*grafo)->max = n;
	(*grafo)->contV = n;
	(*grafo)->vertice =(int*)malloc(n*(sizeof(int)));
	(*grafo)->matriz =(int**)malloc(n*(sizeof(int*)));

	for (i = 0; i < n; i++){ //Percorre as linhas do Vetor de Ponteiros
		(*grafo)->matriz[i] = (int*)malloc(n*(sizeof(int))); //Aloca um Vetor de Inteiros para cada posição do Vetor de Ponteiros.
	}
	for (i = 0; i < n; i++){ //Percorre as linhas do Vetor de Ponteiros
		for (j = 0; j < n; j++){ //Percorre o Vetor de Inteiros atual.
			(*grafo)->matriz[i][j] = 0; //Inicializa com 0.
		}
	}
}
void imprimeMatriz(tipo_grafo *grafo, int n){//funcao que mostra a matriz
	int i=0,j=0;
	printf("[X]Imprimindo matriz\n[x]Vertices: ");
	for(i=0;i<grafo->contV;i++){
		printf("{%d} ",grafo->vertice[i]);
	}
	printf("\n\n");
	printf("[ ]");
	for(i=0;i<n;i++){
		printf("[%d] ",grafo->vertice[i]);
	}
	printf("\n");
	for(i=0;i<n;i++){
		printf("[%d]",grafo->vertice[i]);
		for(j=0;j<n;j++){
			printf("[%d] ",grafo->matriz[i][j]);
		}
		printf("\n");
	}
}
int buscaIndice(tipo_grafo *grafo,int vertice,int QtdVertice){//busca o indice do vertice no vetor presente dentro da struct tipo_grafo
	int i=0;
	while(i<QtdVertice){
		if(grafo->vertice[i] == vertice){
			return i;	
		}
		i++;
	}
	return -1;
}
void insereMatriz(tipo_grafo **grafo, int Ver1,int Ver2,int peso){//insere as arestas na matriz
	int pos1=0, pos2=0;
	pos1 = buscaIndice(*grafo,Ver1,(*grafo)->max);
	pos2 = buscaIndice(*grafo,Ver2,(*grafo)->max);
	if(pos1 >= 0 && pos2 >= 0){
		if(pos1 < pos2){
			(*grafo)->matriz[pos1][pos2] = peso;
		}
		else{
			(*grafo)->matriz[pos2][pos1] = peso;
		}
	}
}
void removeVerticeVetor(tipo_grafo **grafo, int Ver1){//remove o vertice do vetor e organiza o vetor novamente
	int pos=0,i=0,j;
	pos = buscaIndice(*grafo,Ver1,(*grafo)->contV);
	for(i=pos;i<(*grafo)->contV-1;i++){
		(*grafo)->vertice[i] = (*grafo)->vertice[i+1];
	}
	(*grafo)->vertice[i] = '\0';
	for(j=0;j<(*grafo)->contV;j++){;
		(*grafo)->matriz[j][i] = 0;
	}
	(*grafo)->contV--;
}
void removeMatrizVertice(tipo_grafo **grafo, int Ver1){//remove o vertice da matriz junto com suas arestas
	int pos1=0, pos2=0,i=0,j=0;
	printf("[X]Removendo da matriz-> %d\n",Ver1);
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
void ListaEncadeada(tipo_lista **lista,int vertice){//lista encadeada para onde vao os vertices
	tipo_lista *novo = malloc(sizeof(tipo_lista));
	if(*lista == NULL){
		*lista = malloc(sizeof(tipo_lista));
		(*lista)->vertice[0] = vertice;
		(*lista)->prox = NULL; 
	}
	else{
		novo->vertice[0] = vertice;
		novo->prox = *lista;
		*lista = novo;
	}
}
void mostralista(tipo_lista *lista){//mostra a lista encadeada
	if(lista != NULL){
		printf("[%d]->",lista->vertice[0]);
		mostralista(lista->prox);
	}
	else{
		printf("[NULL]\n");
	}
}
int ListaParaVetor(tipo_grafo **grafo, tipo_lista *lista,int pos){//transfere o que esta na lista para a o vetor da struct tipo_grafo
	int i=0;
	if(lista != NULL){
		
		i=ListaParaVetor(grafo,lista->prox,pos+1);
		(*grafo)->vertice[i] = lista->vertice[0];
		return i+1;
	}
	else{
		//printf("Fim ->");
	}
	return i;
}
int Maiorvetor(int *vetor,tipo_grafo *grafo){//verifica o vertice com maior grau
	int i=0,maior=0,vertice;
	for(i=0;i<grafo->contV;i++){
		if(vetor[i] > maior){
			maior=vetor[i];
			vertice = grafo->vertice[i];
		}
	}
	printf("[MaiorGrau]Vertice[%d]",vertice);
	return maior;
}
int Menorvetor(int *vetor,tipo_grafo *grafo){//verifica o vertice com menor grau
	int i=0,menor=0,vertice;
	menor=vetor[i];
	for(i=0;i<grafo->contV;i++){
		if(vetor[i] < menor){
			menor=vetor[i];
			vertice = grafo->vertice[i];
		}
	}
	printf("[MenorGrau]Vertice[%d]",vertice);
	return menor;
}
void GrauMatriz(tipo_grafo *grafo){//chama as funbcoes para verificar o maior e menor grau
	int i,j,grau=0,graumenor=0;
	int vetor[grafo->contV];
	printf("[x]Verificando o maior grau \n");//e o menor grau
	for(i=0; i < grafo->contV;i++){
		grau=0;
		for(j=0;j<grafo->contV;j++){
			if((grafo->matriz[i][j] > 0 || grafo->matriz[j][i] > 0)){
				grau++;	

			}
		}
		vetor[i]=grau;

	}
	grau = Maiorvetor(vetor,grafo);
	printf("Grau[%d]",grau);
	//graumenor = Menorvetor(vetor,grafo);
	//printf("[%d]\n",graumenor);
}

void MostraVizinhos(tipo_grafo **grafo, char vertice){//mostra os vizinhos dos vertices
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
void BuscaVertice(tipo_grafo **grafo, char vertice){//busca a posicao do vertice no vetor e mostra seus vizinhos
	int pos;
	pos = buscaIndice(*grafo,vertice,(*grafo)->contV);
	if(pos == -1){
		printf("\n[X] VERTICE nao encontrado\n");
	}
	else{
		MostraVizinhos(grafo,vertice);
	}
}
int GrauVertice(tipo_grafo *grafo, char vertice){//verifica o grau de um vertice
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

void incializaFila(tipo_grafo *grafo,int *fila){//inicializa a fila
	int i =0;
	for(i=0;i<grafo->contV;i++){
		fila[i] = -1;
	}
}
int contaVisitados(tipo_grafo *grafo, int *visitados){//conta quantas vezes um vertice ja foi vizitado
	int i=0;
	while(visitados[i] != -1 && i !=grafo->contV){
		i++;
	}
	return i;
}
int AddFila(tipo_grafo *grafo, int *fila, int vertice, int *visitados){//adiciona o vertice a fila
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
		if(fila[i] == -1 && flag != 1){
			fila[i] = vertice;
			flag = 1;
			return 1;
		}
		i++;
	}
}
void AddVisitados(tipo_grafo *grafo, int *visitados, int vertice){//adiciona o vertice ao vetor de vertices visitados
	int i=0,flag = 0;
	while( (i<grafo->contV) || (flag != 1)){
		if(visitados[i] == vertice){
			flag = 1;
		}
		if(visitados[i] == -1 && flag != 1){
			visitados[i] = vertice;
			flag = 1;
		}
		//printf("Visitado: %c\n",visitados[i]);
		i++;
	}
}
void removeFila(tipo_grafo *grafo,int *fila, int vertice){//remove o vertice da fila
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
void PercorreLargura(tipo_grafo *grafo, int vertice, int *fila, int *visitados,int cont){//varredura em largura
	int i=0,pos=0,j=0,teste=0,QtdVisitados=0;
	
	printf("[largura]->vertice[%d]distancia[%d]\n",vertice,cont);
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
				if(fila[i]!= -1){
					PercorreLargura(grafo,fila[i],fila,visitados,cont+1);	
				}
			}
		}
		
	}
}
void ChamaLargura(tipo_grafo *grafo,int vertice){//chama a varredura em largura
	int *fila = malloc(grafo->contV * sizeof(int));
	int *visitados = malloc(grafo->contV * sizeof(int));
	printf("[x]Iniciando percurso em largura\n");
	incializaFila(grafo,fila);
	incializaFila(grafo,visitados);
	fila[0] = vertice;
	PercorreLargura(grafo,vertice,fila,visitados,1);
	printf("\n");
}

int VerificaFila(tipo_grafo *grafo,int vertice, int *visitados){//verifica se vertice ja foi visitado
	int pos=0,i=0;
	pos = buscaIndice(grafo,vertice,grafo->contV);
	if(visitados[pos] == 0){
		return 0;
	}
	else{
		return 1;	
	}
	
}
void Profundidade(tipo_grafo *grafo, int vertice, int cont, int *visitados){//varredura em profundidade
	int pos;	
	pos = buscaIndice(grafo,vertice,grafo->contV);
	visitados[pos] = cont;
	printf("[Profundidade]->vertice[%d]distancia[%d]\n",vertice,cont);	
	for(int j=0;j < grafo->contV;j++){
		if(pos > j){		
			if(grafo->matriz[j][pos] > 0){
				if(!VerificaFila(grafo,grafo->vertice[j],visitados)){//grafo->vertice[j]!=fila[cont]
					Profundidade(grafo,grafo->vertice[j],cont+1,visitados);
				}
			}
		}
		else{
			if(grafo->matriz[pos][j] > 0){
				if(!VerificaFila(grafo,grafo->vertice[j],visitados)){//grafo->vertice[j]!=fila[cont]
					Profundidade(grafo,grafo->vertice[j],cont+1,visitados);
				}
			}
		}	
	}	
}
void chamaProfundidade(tipo_grafo *grafo, int vertice){//funcao que chama a funcao de varredura profundidade
	int *visitados = malloc(sizeof(int)*grafo->contV);
	printf("[x]Iniciando percurso em profundidade\n");
	for(int i =0;i<grafo->contV;i++){
		visitados[i] = 0;
	}
	Profundidade(grafo,vertice,1,visitados);
}
void PegaGrafo(tipo_grafo **grafo){//funcao que abre o arquivo e pegas os vertices, arestas e pesos
	FILE *file;
	tipo_lista *lista=NULL;
	int i=0,flagV=0,j=0,num=0,nums[3],grau=0,teste=0;
	char nomearq[100],V0[3],V1[1],V2[1],vertices[100];

	file=fopen("Arq[0][5000].txt","r");//abre o arquivo especificado
	if(file == NULL){//teste  de erro
		printf("Erro na abertura do arquivo Arq[0][10000].txt!\n");
	}
	else{
		while(fscanf(file,"%s",&V0)!=EOF){
			
			if(V0[0] == '#'){
				if(V0[1] == 'v'){
					flagV = 1;
				}
			}
			if(flagV == 1){
				fscanf(file,"%s",&V0[0]);
				while(V0[0] != '#'){
					num = atoi(V0);
					ListaEncadeada(&lista,num);
					fscanf(file,"%s",&V0[0]);
					i++;
				}
				printf("[X]Vertices inseridos, quantidade -> %d\n",i);
				//mostralista(lista);
				iniMatriz(grafo,i);
				teste = ListaParaVetor(grafo,lista,0);
				if(V0[1] == 'a'){
					printf("[X]Inserindo arestas na matriz\n");
					while(fscanf(file,"%d %d %d\n",&nums[0],&nums[1],&nums[2])!=EOF){
						insereMatriz(grafo,nums[0],nums[1],nums[2]);
					}
				}
			}		
		}
		fclose(file);
	}
}

int main(int argc, char *argv[]){
	tipo_grafo *grafo;
	int grau;
	clock_t Ticks[2];//para verificar o tempo de execucao
    Ticks[0] = clock();//inicializa o contador
	PegaGrafo(&grafo);
	//removeMatrizVertice(&grafo,2660);
	chamaProfundidade(grafo,0);
	ChamaLargura(grafo,0);
	GrauMatriz(grafo);
	Ticks[1] = clock();//finaliza o contador
	double Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
    printf("Tempo gasto: [%g ms].\n", Tempo);
	return 0;
}