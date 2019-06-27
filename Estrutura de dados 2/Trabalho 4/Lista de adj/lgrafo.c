/* Aluno: Matheus Felipe Teodoro Correia
 * Trabalho 1 - grafos
 * Lista de adjacencia - grafos
 * Professor: Ivairton
 * Universidade Federal do Mato Grosso
 * Ciencia Da Computacao
 *
 * [x]Nao possui funcao de remocao.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


struct vizinho{
	int vertice;//quantos vertices inseridos
	int peso;//vetor com vertices
	struct vizinho *proxvizinho;
};
typedef struct vizinho tipo_vizinho;
struct grafo{
	int grau;//quantos vertices inseridos
	int vertice;
	struct grafo *proxvertice;
	struct vizinho *proxvizinho;
};
typedef struct grafo tipo_grafo;
struct MaxeMin{
	int valor;
	int vertice;
};
typedef struct MaxeMin tipo_valor;
//prototipos
void inserevertice(tipo_grafo **grafo,int vertice);//insere os vertices 
void Mostravizinhos(tipo_vizinho *vizinho);//mostra os vizinhos do vertice
void MostraLista(tipo_grafo *grafo);//mostra a lista de adjacencia
int InsereLista(tipo_vizinho **vizinho,int vertice,int peso);//insere na lista de adjacencia
int Einserevizinho(tipo_vizinho **vizinho,int aresta,int peso);//acha o vertice
void Einsreverticevizinho(tipo_grafo **grafo, int vertice, int aresta,int peso);//recebe o vertice como parametro e desce adc os vizinhos
void MaiorGrau(tipo_grafo *grafo, tipo_valor **valores);//acha o maior grau
void MenorGrau(tipo_grafo *grafo, tipo_valor **valores);//acha o menor grau
int PegaGrafo(tipo_grafo **grafo);//abre o arquivo e pega os vertice,arestas e pesos
void IniciaValores(tipo_valor **valoresMax,tipo_valor **valoresMin);//inicializa valores de uma struct para nao baguncar o main
int PosVertice(tipo_grafo *grafo,int vertice);//posicao do vertice
int VerificaVisitados(tipo_grafo *grafo,int *visita,int vertice,int tam);//verifica os visitados
void Profundidade(tipo_grafo *grafo,int vertice,int *visitado,int cont,int tam);//varredura em profundidade
void PercursoProfundidade(tipo_grafo *grafo,int vertice);//chama a funcao de varredura em profundidade
void PercursoLargura(tipo_grafo *grafo,int vertice,int *vizinhos,int partida,int tam);//varredura em largura
int buscaVertice(tipo_grafo *grafo, int vertice);//busca o vertice
void PercursoL(tipo_grafo *grafo,int vertice);//chama a varredura em largura

//funcoes
void inserevertice(tipo_grafo **grafo,int vertice){
	if(*grafo == NULL){
		*grafo = malloc(sizeof(tipo_grafo));
		(*grafo)->vertice = vertice;
		(*grafo)->grau = 0;
		(*grafo)->proxvertice = NULL;
		(*grafo)->proxvizinho = NULL;
		//printf("[%d]",(*grafo)->vertice);
	}
	if((*grafo != NULL) && ((*grafo)->vertice != vertice)){
		inserevertice(&(*grafo)->proxvertice,vertice);
	}

}
void Mostravizinhos(tipo_vizinho *vizinho){
	if(vizinho!=NULL){
		printf("(v=%d p=%d)->",vizinho->vertice,vizinho->peso);
		Mostravizinhos(vizinho->proxvizinho);
	}
	else{
		printf("NULL\n");
	}
}
void MostraLista(tipo_grafo *grafo){
	if(grafo != NULL){
		printf("[Vertice]->[%d]->[Grau[%d]]->[Vizinhos]->",grafo->vertice,grafo->grau);
		Mostravizinhos(grafo->proxvizinho);
		MostraLista(grafo->proxvertice);
	}
	else{
		printf("FIm dos vertices/arestas\n");
	}
}
int InsereLista(tipo_vizinho **vizinho,int vertice,int peso){
	int cont=0;
	//printf("[%d][%d]\n",vertice,peso);
	if(*vizinho == NULL){
		*vizinho = malloc(sizeof(tipo_vizinho));
		(*vizinho)->vertice = vertice;
		(*vizinho)->peso = peso;
		(*vizinho)->proxvizinho = NULL;
	}
	else{
		cont = InsereLista(&(*vizinho)->proxvizinho,vertice,peso);
	}
	return cont+1;
}
int Einserevizinho(tipo_vizinho **vizinho,int aresta,int peso){
	int cont=0;
	if(*vizinho == NULL){
		*vizinho = malloc(sizeof(tipo_vizinho));
		(*vizinho)->vertice = aresta;
		(*vizinho)->peso = peso;
		(*vizinho)->proxvizinho = NULL;
	}
	else{
		cont = Einserevizinho(&(*vizinho)->proxvizinho,aresta,peso);
	}
	return cont+1;
}
void Einsreverticevizinho(tipo_grafo **grafo, int vertice, int aresta,int peso){
	if(*grafo == NULL){
		printf("Vertice nao encontrado\n");
		return;
	}
	if((*grafo)->vertice == vertice){		
		(*grafo)->grau=Einserevizinho(&(*grafo)->proxvizinho,aresta,peso);
	}
	else{
		Einsreverticevizinho(&(*grafo)->proxvertice,vertice,aresta,peso);
	}
}
void MaiorGrau(tipo_grafo *grafo, tipo_valor **valores){
	if(grafo != NULL){
		if(grafo->grau > (*valores)->valor){
			(*valores)->valor = grafo->grau;
			(*valores)->vertice = grafo->vertice;
		}
		MaiorGrau(grafo->proxvertice,valores);
	}
}
void MenorGrau(tipo_grafo *grafo, tipo_valor **valores){
	if(grafo != NULL){
		//printf("[%d(%d)] ",grafo->vertice,grafo->grau );
		if(grafo->grau < (*valores)->valor){
			(*valores)->valor = grafo->grau;
			(*valores)->vertice = grafo->vertice;
		}
		MenorGrau(grafo->proxvertice,valores);
	}
}
int PegaGrafo(tipo_grafo **grafo){//, char *argv
	FILE *file;
	int i=0,flagV=0, pos1=0, pos2=0, j=0, num=0, nums[3], grau=0, verfixo=0, pos=0, flag=0;
	char nomearq[100],V0[3],V1[1],V2[1],vertices[100];
	tipo_vizinho *lista=NULL;
	file=fopen("Arq[0][10000].txt","r");
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
				printf("[X]inserindoo vertices\n");
				while(V0[0] != '#'){
					num = atoi(V0);
					inserevertice(grafo,num);
					fscanf(file,"%s",&V0[0]);
					i++;	
				}
				printf("[X]Vertices inseridos, quantidade -> %d\n",i);
				if(V0[1] == 'a'){
					printf("[X]inserindoo arestas na Lista\n");
					flag=0;
					
					while(fscanf(file,"%d %d %d\n",&nums[0],&nums[1],&nums[2])!=EOF){
						//printf("%d %d %d\n",nums[0],nums[1],nums[2]);
						Einsreverticevizinho(grafo,nums[0],nums[1],nums[2]);
						Einsreverticevizinho(grafo,nums[1],nums[0],nums[2]);
					}
				}
			}		
		}
		free(lista);
		lista=NULL;
		fclose(file);
	}
	return i;
}
void IniciaValores(tipo_valor **valoresMax,tipo_valor **valoresMin){
	*valoresMax = malloc(sizeof(tipo_valor));
	(*valoresMax)->valor = 0;
	(*valoresMax)->vertice = 0;
	(*valoresMin) = malloc(sizeof(tipo_valor));
	(*valoresMin)->valor = 0;
	(*valoresMin)->vertice = 0;
}

int PosVertice(tipo_grafo *grafo,int vertice){
	tipo_grafo *auxV;
	int pos;
	if(grafo != NULL){
		pos = 0;
		auxV = grafo;
		while((auxV != NULL) && (auxV->vertice != vertice)){
			pos++;
			auxV = auxV->proxvertice;
		}
		if((auxV != NULL) && (auxV->vertice == vertice)){
			return pos;
		} 
		else{
			return -1;
		}
	}
	return -1;
}
int VerificaVisitados(tipo_grafo *grafo,int *visita,int vertice,int tam){
	int pos=0;
	if( grafo != NULL){
		pos = PosVertice(grafo,vertice);
		if(visita[pos] == 0){
			return 1;
		} else {
			return 0;
		}
	}
	return 0;
} 
void Profundidade(tipo_grafo *grafo,int vertice,int *visitado,int cont,int tam){
	int pos;
	tipo_grafo *auxV;
	tipo_vizinho *auxA;

	pos = PosVertice(grafo,vertice);
	visitado[pos] = cont;

	auxV = grafo;
	while( (auxV != NULL) && (auxV->vertice != vertice) ){
		auxV = auxV->proxvertice;
	}
	if(auxV->vertice == vertice){
		auxA = auxV->proxvizinho;
		while(auxA != NULL){
			if(VerificaVisitados(grafo,visitado,auxA->vertice,tam) == 1){
				Profundidade(grafo,auxA->vertice,visitado,cont+1,tam);
			}
			auxA = auxA->proxvizinho;
		}
	}
}
void PercursoProfundidade(tipo_grafo *grafo,int vertice){
	int *visitado,cont,i;
	tipo_grafo *auxV;
	int tam;
	tam = 0;
	auxV = grafo;

	if( grafo != NULL){
		while(auxV != NULL){

			auxV = auxV->proxvertice;
			tam++;
		}
	}
	visitado = (int*) malloc( tam * sizeof(int) );
	for(i = 0; i < tam; i++){
		visitado[i] = 0;
	}
	cont = 1;
	Profundidade(grafo,vertice,visitado,cont,tam);
	auxV = grafo;
	for(i = 0; i < tam; i++){
		printf("[Profundidade]->Vertice[%d]->distancia[%d]\n",auxV->vertice,visitado[i]);
		auxV = auxV->proxvertice;
	}
	printf("\n");;

}
void PercursoLargura(tipo_grafo *grafo,int vertice,int *vizinhos,int partida,int tam){
	int *fila;
	int i,contF,pos; 
	tipo_grafo *auxV;
	tipo_vizinho *auxA;

	fila = malloc( tam * sizeof(int) );
	if( vizinhos == NULL){
		vizinhos = malloc( tam * sizeof(int) );

		for(i = 0; i < tam; i++){
			vizinhos[i] = 0;
		}
	}
	auxV = grafo;
	while( (auxV != NULL) && (auxV->vertice != vertice) ){
		auxV = auxV->proxvertice;
	}
	if(auxV->vertice == vertice){
		contF = 0;
		auxA = auxV->proxvizinho;
		pos = PosVertice(grafo,vertice);
		vizinhos[pos] = 1;
		while( (auxA != NULL) ){
			if(VerificaVisitados(grafo,vizinhos,auxA->vertice,tam) == 1 ){
				pos = PosVertice(grafo,auxA->vertice);
				vizinhos[pos] = 1;
				printf("[Largura]->vertice[%d]\n",auxA->vertice );
				fila[contF++] = auxA->vertice;
			}
			auxA = auxA->proxvizinho;
			
		}
		for(i = 0; i < contF; i++){
			PercursoLargura(grafo,fila[i],vizinhos,partida,tam);
		}
	}

}
int buscaVertice(tipo_grafo *grafo, int vertice){
	tipo_grafo *aux;
	aux = grafo;
	while( (aux != NULL) && (aux->vertice != vertice) ){
		aux = aux->proxvertice;
	}

	if( aux != NULL){
		if(aux->vertice == vertice){
			return 1;
		} else{
			return -1;
		}
	} else {
		return -1;
	}
}
void PercursoL(tipo_grafo *grafo,int vertice){
	tipo_grafo *auxV;
	int tam,pos;

	tam = 0;
	pos = buscaVertice(grafo,vertice);
	if( pos != -1){
		auxV = grafo;
		if( grafo != NULL){
			while(auxV != NULL){

				auxV = auxV->proxvertice;
				tam++;
			}
			printf("(%d)",vertice);
			PercursoLargura(grafo,vertice,NULL,vertice,tam);
			printf("\n");

		}
	}
}
int main(int argc, char *argv[]){
	clock_t Ticks[2];
	tipo_grafo *grafo=NULL;
	tipo_valor *valoresMax=NULL;
	tipo_valor *valoresMin=NULL;
	
	IniciaValores(&valoresMax,&valoresMin);
	int maior=0,Qtdvertice=0;
    Ticks[0] = clock();
	Qtdvertice = PegaGrafo(&grafo);
	PercursoProfundidade(grafo,0);
	PercursoL(grafo,0);
	MaiorGrau(grafo,&valoresMax);
	printf("[MaiorGrau]Vertice[%d]Grau[%d]\n",valoresMax->vertice,valoresMax->valor);
	Ticks[1] = clock();
    double Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
    printf("Tempo gasto: %g ms.\n", Tempo);
	free(grafo);
	grafo = NULL;
}