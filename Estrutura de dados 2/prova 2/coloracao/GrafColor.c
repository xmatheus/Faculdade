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
	int contVz;
	struct vertice *proxVertice;
	aresta *proxAresta;
}vertice;

vertice *novoVertice(int indice){
	vertice *novo;
	novo = (vertice*) malloc( sizeof(vertice) );
	novo->proxVertice = NULL;
	novo->proxAresta = NULL;
	novo->contVz = 0;
	novo->indice  = indice;
	return novo;
}	
vertice *insereVertice(vertice *grafo,int indice){
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
				auxVt->contVz++;
			}else {
				// aresta já existente
			}
		} else {
			auxVt->proxAresta = novaAresta(v2,peso);
			auxVt->contVz++;
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
				grafo = posicionaVizinhos(grafo,v2,v1,peso);
			}
			
		} else {
			// vertice v1 ou v2 nao inseridos	
		}
	}

	return grafo;
}
vertice *CarregaGrafo(char *arquivo){
	FILE *arq;
	vertice *grafo;
	grafo = NULL;
	char entrada[50],c,lixo[10];
	int qtdnos,arcs,n1,n2,peso,i,j;
	arq = fopen(arquivo,"r");
	if( arq == NULL){
		printf("falha na abertura do arquivo\n");
		return 0;
	}
	j = 0;
	while(fscanf(arq,"%c",&c) != EOF){
		if( c == 'c'){
			fscanf(arq, "%[^\n]",entrada);
		} else if( c == 'p'){
			fscanf(arq, " %s %d %d",lixo,&qtdnos,&arcs);
			printf("inserindo vertices\n");
			printf("Quantidade de vertices->%d\n",qtdnos);
			for(i = 1; i <= qtdnos; i++){
				//printf("v-%d\n",i);
				grafo = insereVertice(grafo,i);
			}
			printf("vertices inseridos\n");
			printf("inserindo arestas\n");
		} else if( c == 'e'){
			fscanf(arq, " %d %d",&n1,&n2);
			grafo = insereAresta(grafo,n1,n2,1);
		}
	}
	return grafo;
	
}
void veGrafo(vertice *grafo){
	vertice *auxV;
	aresta *auxA;
	auxV = grafo;
	if( grafo != NULL){
		while( auxV != NULL){
			printf("[%d Grau:%d]->",auxV->indice,auxV->contVz);
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
			printf("[%d Grau:%d]->",auxVertice->indice,auxVertice->contVz);
			auxAresta = auxVertice->proxAresta;
			while( auxAresta != NULL ){
				printf("(%d)->",auxAresta->indice);
				auxAresta = auxAresta->proxAresta;
			}
			printf("NULL\n");
		}
	} else {
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
			return auxVertice->contVz;
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
			auxV->contVz--;
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
 						grafo = auxV->proxVertice;
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
int posV(vertice *grafo,int v){
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
		} else {
			return -1;
		}
	}
	return -1;
}

int contV(vertice *grafo){
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
int posCor(vertice *grafo,vertice *vetCor,int n){
	int i,tam;
	tam = contV(grafo);
	for( i = 0; i < tam; i++){
		if(vetCor[i].indice == n){
			return i;
		}
	}
	return -1;
}
int coloreGrafo(vertice *grafo,int *cors,int qtdCor,int indice,vertice *vtVertice){
	vertice *naveVertice;
	aresta *naveAresta;
	int *rangeCor,cor,i,pos,corRef;
	naveVertice = grafo;
	// vetor para controle das flags das corres ja aplicadas nos vizinhos
	rangeCor = (int*) malloc( qtdCor *sizeof(int) );
	for( i = 0; i < qtdCor; i++){
		rangeCor[i] = 0;
	}
	//Acessa o vertice de partida
	while( (naveVertice->proxVertice != NULL) && (naveVertice->indice != indice) ){
		naveVertice = naveVertice->proxVertice;
	}
	if( naveVertice->indice == indice){
		//acessa ao inicio dos vertices adjacentes ao de referencia
		naveAresta = naveVertice->proxAresta;
		while( naveAresta != NULL){
			//olha pra cada vertice adjacente ao de referencia e vê se ele ja tem cor e qual
			pos = posCor(grafo,vtVertice,naveAresta->indice);
			if( cors[pos] != -1  ){
				corRef = cors[pos] - 1;
				rangeCor[corRef] = 1;
			}
			naveAresta = naveAresta->proxAresta;
		}
		cor = -1; 
		for( i = 0; i < qtdCor; i++){
			if( cor == -1){
				if(rangeCor[i] == 0){
					cor = i+1;
				}
			}
		}
		pos = posCor(grafo,vtVertice,naveVertice->indice);
		//pinta o vertice com a nova cor ou com uma cor ja existente no range se possivel
		//etapa 4
		if( cor == -1){
			qtdCor++;
			cors[pos] = qtdCor;
		} 
		else {
			
			cors[pos] = cor;
		}
		return qtdCor;	
	}
}
void Merge(vertice vet[],int inicio, int meio, int fim){
        int i,j,k,tam;
        vertice *vetAux;
        tam = (fim - inicio) + 1;
        vetAux = (vertice*) malloc(sizeof(vertice)*tam);
        // i com o inicio do subvetor a esquerda
        i=inicio;
        // j com o inicio do subvetor a direita
        j=meio+1;
        // tamanho do vetor inicial
        for(k=0; k < tam; k++){
            // verifica se os lados dos meus subvetores aindicea tem valores a direita
            if(i < (meio+1) && j <= fim){
                // faz a ordenacao crescente
                if(vet[i].contVz > vet[j].contVz){
                    vetAux[k] = vet[i++];    
                }
                else{
                    vetAux[k] = vet[j++];   
                }    
            // se um dos subvetores chegou ao fim completa com o outro
            }
            else if(i < (meio+1) && j > fim){
                vetAux[k] = vet[i++];    
            }
            else{
                vetAux[k] = vet[j++];          
            }           
        }
        i = 0;
        for(k=inicio; k <= fim; k++){
            vet[k] = vetAux[i++];
        }
        free(vetAux);       
}
void Sort(vertice vet[],int inicio, int fim){
    int meio;
    if( inicio < fim){
        meio = ( (inicio + fim)/ 2);
        // quebra pro lado esquerdo
        Sort(vet, inicio, meio);
        // quebra pro lado direito
        Sort(vet, meio+1, fim);
        // faz o merge
        Merge(vet,inicio, meio, fim);
    }
}
void Coloracao(vertice *grafo){
	int qtdCor,*cors;
	vertice *vtVertice;
	vertice aux;
	vertice *auxV;
	int tam,i,j,pos;
	if( grafo != NULL){
		tam = contV(grafo);
		vtVertice = (vertice*) malloc( tam * sizeof(vertice) );
		cors = (int*) malloc( tam* sizeof(int) );
		auxV = grafo;

		for(i = 0; i < tam; i++){
			//copia grafo para vetor
			cors[i] = -1;
			vtVertice[i] = *auxV;
			auxV = auxV->proxVertice;
		}
		// chama a funcao de ordenacao
		// etapa 1
		Sort(vtVertice,0,tam-1);
		//etapa 2
		qtdCor = 1;
		cors[0] = qtdCor;
		for(i = 1; i < tam; i++){
			//etapa 3
			qtdCor = coloreGrafo(grafo,cors,qtdCor,vtVertice[i].indice,vtVertice);
			//etapa 5
			
		}
		int maiorC = 1;
		for(i = 0; i < tam; i++){
			printf("vet[%d,%d)->",vtVertice[i].indice,cors[i]);
			if( maiorC < cors[i]){
				maiorC = cors[i];
			}
		}
		printf("\n");
		printf("Numero Cromatico: %d\n",maiorC);
	}

}
int main(int argc,char *argv[]){
	if(argc <= 1){
		puts("Entre com o nome do arquivo: \nEx.: ./exec test.txt ");
		return 0;
	}
	int tam, pos;
	vertice *grafo,*aux;
	grafo = NULL;
	int maior,indiceV;
	grafo = CarregaGrafo(argv[1]);
	Coloracao(grafo);
	return 0;
}