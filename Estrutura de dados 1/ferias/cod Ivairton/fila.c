/*
 * UFMT - Ciencia da Computacao
 * ED1 - Ivairton
 * Implementacao de FILA
 */

 //Inclusao de bibliotecas
 #include<stdio.h>
 #include<stdlib.h>

//Definicao de tipos
struct s_fila {
    int max;
    int *fila;
    int qtd;
};
typedef struct s_fila tipoFila;

//Prototipos
void inicializaFila(tipoFila *fl, int max);
int insereFila(tipoFila *fl, int valor);
int primeiroFila(tipoFila fl);
int removeFila(tipoFila *fl);
void imprimeFila(tipoFila fl);

//FUNCAO principal
int main() {
    int valor;
    tipoFila fila;
    inicializaFila(&fila, 10);
    insereFila(&fila, 10);
    insereFila(&fila, 29);
    printf("primeiro=%d", valor = primeiroFila(fila) );
    valor = removeFila(&fila);
    imprimeFila(fila);
}

//Funcao que inicizaliza fila
void inicializaFila(tipoFila *fl, int max) {
    fl->fila = (int*) malloc( sizeof(int) * max );
    fl->max = max;
    fl->qtd = 0;
}

//Funcao que insere um novo elemento na fila, considerando a insercao pela direita
int insereFila(tipoFila *fl, int valor) {
    if (fl->qtd < fl->max)
        fl->fila[fl->qtd++] = valor;
    else
        return 0;
    return 1;
}

//Funcao que retorna o primeiro elemento a ser atendido da fila
int primeiroFila(tipoFila fl) {
    if (fl.qtd > 0)
        return fl.fila[0];
    else
        return -1; //Representa que a fila está vazia
}

//Funcao que remove um primeiro elemento da fila, considerando a retirada pela esq
int removeFila(tipoFila *fl) {
        int valor, i;
        if (fl->qtd >0) {
            valor = fl->fila[0];
            for (i=0; i < (fl->qtd-1); i++) {
                fl->fila[i] = fl->fila[i+1];
            }
            fl->qtd--;
            return valor;
        } else
            return -1;
}

//Funcao que imprime fila
void imprimeFila(tipoFila fl) {
    int i;
    printf("FILA: Max=%d; Qtd=%d; ", fl.max, fl.qtd);
    for (i=0; i<fl.qtd; i++) {
        printf("[%d]", fl.fila[i]);
    }
    printf("\n");
}
