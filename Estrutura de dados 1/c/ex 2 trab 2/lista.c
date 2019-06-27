#include <stdio.h>
#include <stdlib.h>


struct lista{
	
	int RGA;
	struct lista* prox;
	
};
typedef struct lista Lista;

Lista* inicializa (void){
   return NULL;
}


Lista* insere (Lista* l, int i){
   Lista* novo = (Lista*) malloc(sizeof(Lista));
   novo->RGA = i;
   novo->prox = l;
   return novo;
}

void imprime (Lista* l)
{
	Lista* p;   /* variável auxiliar para percorrer a lista */
	for (p = l; p != NULL; p = p->prox){
		printf("info = %d \n", p->RGA);
	}
}





Lista* lista_10 (Lista* l){
	int i=0;
	for (i=0;i<10;i++){
		l = insere(l, i);
	}
	
   
	return l;
}

Lista* retira (Lista* l, int v) {
	Lista* ant = NULL;
	Lista* p = l;

	while (p != NULL && p->RGA != v) {
		ant = p;
		p = p->prox;
	}

	if (p == NULL)
		return l;
	if (ant == NULL) {
 
		l = p->prox;
	}
	else {
 
		ant->prox = p->prox;
	}
	free(p);
	return l;
}

int main(){

	Lista* l;          /* declara uma lista não iniciada */
	l = inicializa();  // inicia lista vazia
	l=lista_10(l);
	printf("Inteira\n");
	imprime(l);        /* imprimirá: 78 56 45 23 */
	l = retira(l, 2);
	printf("Inteira/2\n");
	imprime(l);        /* imprimirá: 56 45 23 */
	l = retira(l, 1);
	printf("Inteira/3\n");
	imprime(l);        /* imprimirá: 56 23 */

	return 0;
}
	
	
	
	
	