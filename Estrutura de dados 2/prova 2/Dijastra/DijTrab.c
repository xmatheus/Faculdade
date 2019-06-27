#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct aresta{
	int peso;
	int indice;
	struct aresta *proxAresta;
}aresta;
typedef struct vertice{
	int indice;
	int contVizin;
	struct vertice *proxVertice;
	aresta *proxAresta;
}vertice;

//prototipos
vertice *novoVertice(int indice){//cria novo vertice
	vertice *novo;
	novo = (vertice*) malloc( sizeof(vertice) );
	novo->proxVertice = NULL;
	novo->proxAresta = NULL;
	novo->contVizin = 0;
	novo->indice  = indice;
	return novo;
}	
vertice *insereVertice(vertice *grafo,int indice){//insere o vertice
	vertice *aux;
	aux = grafo;
	if( grafo != NULL){
		while( ( aux->proxVertice != NULL ) &&  ( aux->indice != indice ) ){
			aux = aux->proxVertice;
		}
		if(aux->indice != indice){
			aux->proxVertice = novoVertice(indice);	
		} else {
			//vertice ja existente
			return grafo;
		}
	} else {
		grafo = novoVertice(indice);
	}
	return grafo;
}
// funcoes de insercao das arestas
int buscaVertice(vertice *grafo, int indice){
	vertice *aux;
	aux = grafo;
	while( (aux != NULL) && (aux->indice != indice) ){
		aux = aux->proxVertice;
	}

	if( aux != NULL){
		if(aux->indice == indice){
			return 1;
		} else{
			return -1;
		}
	} else {
		return -1;
	}
}
aresta *novaAresta(int indice,int peso){
	aresta *nova;
	nova = (aresta*) malloc( sizeof(aresta) );
	nova->peso = peso;
	nova->indice = indice;
	nova->proxAresta = NULL;
	return nova;
}
vertice *posicionaVizinhos(vertice *grafo,int v1,int v2,int peso){
	vertice *auxVt;
	aresta  *auxAr;
	auxVt = grafo;
	while ( (auxVt->proxVertice != NULL) && (auxVt->indice != v1 ) ){
		auxVt = auxVt->proxVertice;
	}
	if(auxVt->indice == v1){
		auxAr = auxVt->proxAresta;
		if(auxAr != NULL){
			while( (auxAr->proxAresta != NULL) && (auxAr->indice != v2) ){
				auxAr = auxAr->proxAresta;
			}
			if( auxAr->indice != v2){
				auxAr->proxAresta = novaAresta(v2,peso);
				auxVt->contVizin++;
			}else {
				// aresta já existente
			}
		} else {
			
			auxVt->proxAresta = novaAresta(v2,peso);
			auxVt->contVizin++;
		}
	}
	return grafo;
}
vertice *insereAresta(vertice *grafo,int v1,int v2,int peso){
	int flag1,flag2;
	if( grafo != NULL){		
		flag1 = buscaVertice(grafo,v1);		
		flag2 = buscaVertice(grafo,v2);
		if( (flag1 == 1) && (flag2 == 1) ){
			if( v1 != v2){
				grafo = posicionaVizinhos(grafo,v1,v2,peso);
			}			
		} else {
			// vertice v1 ou v2 nao inseridos	
		}
	}
	return grafo;
}
vertice *InicializaGrafo(){
	FILE *arq;
	vertice *grafo;
	grafo = NULL;
	char entrada[50],c;
	int qtdnos,arcs,n1,n2,peso,i,j;
	arq = fopen("teste.txt","r");
	if( arq == NULL){
		puts("Erro na abertura do arquivo");
		return 0;
	}
	j = 0;
	while(fscanf(arq,"%c",&c) != EOF){
		if( c == 'c'){
			fscanf(arq, "%[^\n]",entrada);
		} else if( c == 'p'){
			fscanf(arq, " sp %d %d",&qtdnos,&arcs);
			printf("[x]Inserindo vertice\n");
			//printf("%c\n",c );
			printf("[x]Quantidade de vertices-> %d\n",qtdnos);
			for(i = 1; i <= qtdnos; i++){
				//printf("v-%d\n",i);
				grafo = insereVertice(grafo,i);
			}
			printf("[x]Vertices inseridos\n");
			printf("[x]Inserindo Arestas\n\n");
		} else if( c == 'a'){
			fscanf(arq, " %d %d %d",&n1,&n2,&peso);
			grafo = insereAresta(grafo,n1,n2,peso);
		}
	}
	return grafo;
}
void mostraGrafo(vertice *grafo){
	vertice *auxV;
	aresta *auxA;
	auxV = grafo;
	if( grafo != NULL){
		while( auxV != NULL){
			printf("[%d Grau:%d]->",auxV->indice,auxV->contVizin);
			if(auxV->proxAresta != NULL){
				auxA = auxV->proxAresta;
				while( auxA != NULL){
					printf("(%d)->",auxA->indice);
					auxA = auxA->proxAresta;
				}
			}
			auxV = auxV->proxVertice;
			puts("NULL");
		}

	}
}
void VizinhoVertice(vertice *grafo,int indice){
	vertice *auxVertice;
	aresta *auxAresta;
	auxVertice = grafo;
	if( auxVertice != NULL){
		while( (auxVertice->proxVertice != NULL) && (auxVertice->indice != indice) ){
			auxVertice = auxVertice->proxVertice;
		}
		if( auxVertice->indice == indice){
			printf("[%d Grau:%d]->",auxVertice->indice,auxVertice->contVizin);
			auxAresta = auxVertice->proxAresta;
			while( auxAresta != NULL ){
				printf("(%d)->",auxAresta->indice);
				auxAresta = auxAresta->proxAresta;
			}
			puts("NULL");
		}
	} 
	else {
		//grafo nullo
	}
}
int GrauVertice(vertice *grafo,int indice){
	vertice *auxVertice;
	auxVertice = grafo;
	if( auxVertice != NULL){
		while( (auxVertice->proxVertice != NULL) && (auxVertice->indice != indice) ){
			auxVertice = auxVertice->proxVertice;
		}
		if( auxVertice->indice == indice){
			return auxVertice->contVizin;
		} else {
			return -1;
			//vertice nao existe
		}
	} 
	return -1;

}
vertice *RemoveAresta(vertice *grafo,int v1,int v2){
	vertice *auxV;
	aresta *auxA,*sent;
	if( grafo != NULL){
		auxV = grafo;
		while( (auxV != NULL) && (auxV->indice != v1) ){
			auxV = auxV->proxVertice;
		}
		if(auxV->indice == v1){
			auxV->contVizin--;
			auxA = auxV->proxAresta;
			if(auxA != NULL){
				sent = NULL;
				while( (auxA != NULL) && (auxA->indice != v2) ){
					sent = auxA;
					auxA = auxA->proxAresta;
				}
				if(  (auxA->indice == v2) && (sent != NULL) ){
					sent->proxAresta = auxA->proxAresta;
					free(auxA);
					return grafo;
				} else if( auxA->indice == v2) {
					auxV->proxAresta = auxA->proxAresta;
					free(auxA);
					return grafo;
				}
			}
		}
	}
}
vertice *RemoveA(vertice *grafo,int v1,int v2){
	int flag1,flag2;

	flag1 = buscaVertice(grafo,v1);
	flag2 = buscaVertice(grafo,v2);

	if( (flag1 == 1) && (flag2 == 1) ){
		grafo = RemoveAresta(grafo,v1,v2);
		grafo = RemoveAresta(grafo,v2,v1);
		return grafo;
	}
	// nao é possivel remover, aresta nao existente
}
void RemoveVertice(vertice *grafo,vertice *vertice,aresta *vizinho){
	if(vizinho->proxAresta != NULL){
		RemoveVertice(grafo,vertice,vizinho->proxAresta);
		RemoveAresta(grafo,vizinho->indice,vertice->indice);
		free(vizinho);
	} else {
		RemoveAresta(grafo,vizinho->indice,vertice->indice);
		free(vizinho);
	}
}
vertice *RemoveV(vertice *grafo,int v){
	vertice *auxV,*sent;
 	aresta *auxA;
	int indice;
 	int flag;
 	if(grafo != NULL){
 		flag = buscaVertice(grafo,v);
 		if( flag){
 			auxV = grafo;
 			sent = NULL;
 			while( (auxV != NULL) &&  (auxV->indice != v)   ){
 				sent = auxV;
 				auxV = auxV->proxVertice;
 			}
 			if(auxV->indice == v){
 				if(auxV->proxAresta != NULL){
 					RemoveVertice(grafo,auxV,auxV->proxAresta);
 					if(sent != NULL){
 						sent->proxVertice = auxV->proxVertice;
 					} else {
 						grafo  = auxV->proxVertice;
 					}	
 					free(auxV);
 					return grafo;
 				} else {
 					if( sent != NULL){
 						sent->proxVertice = auxV->proxVertice;	
 					} else{
 						grafo->proxVertice = auxV->proxVertice;
 					}
 					free(auxV);
 					return grafo;		
 				}
 			}
 		}
 	}
}
// auxilia nos percursos
int posVertice(vertice *grafo,int v){
	vertice *auxV;
	int pos;
	if(grafo != NULL){
		pos = 0;
		auxV = grafo;
		while( (auxV != NULL) && (auxV->indice != v) ){
			pos++;
			auxV = auxV->proxVertice;
		}
		if( (auxV != NULL) && (auxV->indice == v) ){
			return pos;
		}
		else {
			return -1;
		}
	}
	return -1;
}
int contVertice(vertice *grafo){
	int tam;
	vertice *aux;
	tam = 0;
	aux = grafo;

	while(aux != NULL){
		aux = aux->proxVertice;
		tam++;
	}
	return tam;
}
int VeVisita(vertice *grafo,int *visita,int v,int tam){
	int pos;
	if( grafo != NULL){
		pos = posVertice(grafo,v);
		if(visita[pos] == 0){
			return 1;
		} else {
			return 0;
		}
	}
	return 0;
} 	

void PercursoLargura(vertice *grafo,int v,int *vizinhos,int partida,int tam){
	int *fila;
	int i,contF,pos; 
	vertice *auxV;
	aresta *auxA;
	fila = (int*) malloc( tam * sizeof(int) );
	if( vizinhos == NULL){
		vizinhos = (int*) malloc( tam * sizeof(int) );
		for(i = 0; i < tam; i++){
			vizinhos[i] = 0;
		}
	}
	auxV = grafo;
	while( (auxV != NULL) && (auxV->indice != v) ){
		auxV = auxV->proxVertice;
	}
	if(auxV->indice == v){
		contF = 0;
		auxA = auxV->proxAresta;
		pos = posVertice(grafo,v);
		vizinhos[pos] = 1;
		while( (auxA != NULL) ){
			if(VeVisita(grafo,vizinhos,auxA->indice,tam) == 1 ){
				pos = posVertice(grafo,auxA->indice);
				vizinhos[pos] = 1;
				printf("[%d]",auxA->indice );
				fila[contF++] = auxA->indice;
			}
			auxA = auxA->proxAresta;
		}
		for(i = 0; i < contF; i++){
			PercursoLargura(grafo,fila[i],vizinhos,partida,tam);
		}
	}

}
void PercursoL(vertice *grafo,int v){
	vertice *auxV;
	int tam,pos;
	tam = 0;
	pos = buscaVertice(grafo,v);
	if( pos != -1){
		auxV = grafo;
		if( grafo != NULL){
			while(auxV != NULL){
				auxV = auxV->proxVertice;
				tam++;
			}
			printf("[%d]:",v);
			PercursoLargura(grafo,v,NULL,v,tam);
			printf("\n");
		}
	}
}

void Profundidade(vertice *grafo,int v,int *visitado,int cont,int tam){
	int pos;
	vertice *auxV;
	aresta *auxA;
	pos = posVertice(grafo,v);
	visitado[pos] = cont;
	auxV = grafo;
	while( (auxV != NULL) && (auxV->indice != v) ){
		auxV = auxV->proxVertice;
	}
	if(auxV->indice == v){
		auxA = auxV->proxAresta;
		while(auxA != NULL){
			if(VeVisita(grafo,visitado,auxA->indice,tam) == 1){
				Profundidade(grafo,auxA->indice,visitado,cont+1,tam);
			}
			auxA = auxA->proxAresta;
		}
	}
}
void percursoP(vertice *grafo,int v){
	int *visitado,cont,i;
	vertice *auxV;
	int tam;
	tam = 0;
	auxV = grafo;
	if( grafo != NULL){
		while(auxV != NULL){
			auxV = auxV->proxVertice;
			tam++;
		}
	}
	visitado = (int*) malloc( tam * sizeof(int) );
	for(i = 0; i < tam; i++){
		visitado[i] = 0;
	}
	cont = 1;
	Profundidade(grafo,v,visitado,cont,tam);
	auxV = grafo;
	for(i = 0; i < tam; i++){
		auxV = auxV->proxVertice;
	}
	printf("\n");

} 

int retVertice(vertice *grafo, int pos){
	vertice *aux;
	aux = grafo;
	int cont = 0;
	while( aux != NULL && cont < pos){
		aux = aux->proxVertice;
	}
	return aux->indice;
}
void ConstroiCaminho(int *cam,int pos){
	int i;
	if( cam[pos] == pos){
		printf("[%d]<-partida\n",cam[pos]+1);
	}else {
		printf("[%d]",pos+1);
		ConstroiCaminho(cam,cam[pos]);
	}
}
void RelaxDijkstra(vertice *grafo,int *dist,int *abertos,int *cam){
	int pos,tam,i, qtdAB,posMenor;
	qtdAB = 0;
	int indice;
	vertice *naveVertice;
	aresta *naveAresta;
	tam = contVertice(grafo);
	while(qtdAB  < tam ){
		posMenor = -1;
		for(i = 0; i < tam; i++){
			if( abertos[i] == 1 && ( dist[i] < posMenor || posMenor == -1) && (dist[i] != -1) ){
				posMenor = i;
			}
		}
		abertos[posMenor] = 0;
		qtdAB++;
		naveVertice = grafo;
		// acha o vertice
		int controlePos = 0;
		while( naveVertice != NULL &&  controlePos != posMenor ){
			naveVertice = naveVertice->proxVertice;
			controlePos++;
		}
		naveAresta = naveVertice->proxAresta;
		//relaxamento em todos os vertices adjacentes
		while( naveAresta != NULL){
			pos = posVertice(grafo,naveAresta->indice);
			if( (dist[pos] == -1) || dist[pos] > (dist[posMenor] + naveAresta->peso ) ){
				dist[pos] = dist[posMenor] + naveAresta->peso;
				cam[pos] = posMenor;		
			}
			naveAresta = naveAresta->proxAresta;
		}
	}
	puts("Distancia:");
	for( i = 0; i < tam; i++){
		printf("V=[%d] D=[%d]\n",i+1,dist[i]);
	}
	printf("\n");
}


void Dijkstra(vertice *grafo,int indice){
	int pos,tam,i;
	int *dist,*cam,*abertos;
	if( grafo != NULL){
		pos = posVertice(grafo,indice);
		if( pos != -1){
			tam = contVertice(grafo);
			dist = (int*) malloc( tam * sizeof(int) );
			abertos = (int*) malloc( tam * sizeof(int) ); 
			cam =  (int*) malloc( tam * sizeof(int) );

			for( i = 0; i < tam; i++){
				abertos[i] = 1;
				dist[i] = -1;
				cam[i] = -1;
			}
			dist[pos] = 0;
			cam[pos] = pos;
			RelaxDijkstra(grafo,dist,abertos,cam);

		} else {
			// vertice s(inicial) nao existe no grafo
		}

	} else {
		// nao existe grafo
	}
}
int main(){
	int tam, pos;
	vertice *grafo;
	grafo = NULL;
	grafo = InicializaGrafo();
	tam = contVertice(grafo);
	pos = posVertice(grafo,1);
	Dijkstra(grafo,1);
	return 0;
}