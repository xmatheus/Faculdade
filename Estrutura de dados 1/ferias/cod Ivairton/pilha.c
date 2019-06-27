/*
 * UFMT - Ciencia da Computacao
 * ED1 - Ivairton
 * Implementacao de PILHA
 */

 //Inclusao de bibliotecas
 #include<stdio.h>
 #include<stdlib.h>

//Definicao de tipos
struct s_pilha {
    int max;
    int *pilha;
    int qtd;
};
typedef struct s_pilha tipoPilha;

//Prototipos
void inicializaPilha(tipoPilha *q, int max);
int empilha(tipoPilha *q, int valor);
int topo(tipoPilha q);
int desempilha(tipoPilha *q);
void imprimePilha(tipoPilha q);

//FUNCAO principal
int main() {
    int valor;
    tipoPilha pilha;
    inicializaPilha(&pilha, 10);
    empilha(&pilha, 10);
    empilha(&pilha, 29);
    printf("Topo=%d", valor = topo(pilha) );
    valor = desempilha(&pilha);
    imprimePilha(pilha);
}

//Funcao que inicizaliza PILHA
void inicializaPilha(tipoPilha *q, int max) {
    q->pilha = (int*) malloc( sizeof(int) * max );
    q->max = max;
    q->qtd = 0;
}

//Funcao que insere um novo elemento na pilha (EMPILHA), considerando a insercao pela direita
int empilha(tipoPilha *q, int valor) {
    if (q->qtd < q->max) {
        q->pilha[q->qtd++] = valor;
        return 1;
    } else {
        return 0;
    }
}

//Funcao que retorna o primeiro elemento do topo da PILHA
int topo(tipoPilha q) {
    if (q.qtd > 0)
        return q.pilha[q.qtd-1];
    else
        return -1; //Representa que a pilha está vazia
}

//Funcao que remove (DESEMPILHA) o elemento do topo da pilha, considerando a retirada pela direita
int desempilha(tipoPilha *q) {
        int valor;
        if (q->qtd > 0) {
            valor = topo(*q);
            q->qtd--;
            return valor;
        } else
            return -1;
}

//Funcao que imprime fila
void imprimePilha(tipoPilha q) {
    int i;
    printf("PILHA: Max=%d; Qtd=%d; ", q.max, q.qtd);
    for (i=0; i<q.qtd; i++) {
        printf("[%d]", q.pilha[i]);
    }
    printf("<-TOPO\n");
}
