#include <stdio.h>
#include <stdlib.h>




struct lista{
	int valor;
	struct lista* prox;
	
};

typedef struct lista lista;

/*lista* inicializa (void){
	lista* l;
	l->valor=0;
	l->prox=l;
}
*/

lista* insere (lista* l, int i){
	lista* novo = (lista*) malloc(sizeof(lista));
	novo->valor = i;
	novo->prox = novo;
	return novo;
}

void imprime (lista* l){
	/*lista* p;
	for (p = l; p != NULL; p = p->prox){
		printf("Valor = %d \n", p->valor);
	}
	*/
	if(l == NULL){

		printf("Lista vazia!");

		return;
	}

	lista* loop = l;

	do{

		printf("%d\n", loop->valor);

		loop = loop->prox;

	}while(loop != l);

}




lista* doc_insere (lista* l,char *texto){
	int i=0,j=0;
	FILE *file;
	file = fopen(texto,"rt");
	printf("Valores dentro do arquivo: \n");
	for(i=0; !feof(file);i++){
		fscanf(file,"%d\n",&j);
		l = insere(l, j);
		printf("[%d] ",j);
	}
	printf("\n");
	fclose(file);
	
	printf("quantidade de valores no arq: %d\n",i);	
	return l;
}






int main(){
	char doc_nome[]="numero1.txt";
	lista* l;          /* declara uma lista não iniciada */
	//l = inicializa();  // inicia lista vazia
	l=doc_insere(l,doc_nome);

	imprime(l);        /* imprimirá: 78 56 45 23 */


	return 0;
}