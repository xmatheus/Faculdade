/*
 * UFMT - Ciencia da Computacao
 * ED1 - Prof. Ivairton Santos
 */

 //Inclusao de bibliotecas
 #include<stdio.h>
 #include<stdlib.h>

//Definicao de constante
//#define MAX 10

//Definicao de tipos
struct s_lista {
    int max;
    int *lista;
    int qtd;
};
typedef struct s_lista tipoLista;

//Prototipo de funcoes
int inicializaLista(tipoLista *lst, int max);
void imprimeLista(tipoLista lst);
int qtdElementos(tipoLista lst);
int maxLista(tipoLista lst);
int insereInicio(tipoLista *lst, int valor);

// FUncao principal
int main() {
    //Declara estrutura lista
    tipoLista lst;

    //Inicializa
    inicializaLista(&lst, 10);

    //Faz uso (insere, remove, imprime, etc);
    imprimeLista(lst);
    insereInicio(&lst, 7);
    insereInicio(&lst, 2);
    insereInicio(&lst, 1);
    insereInicio(&lst, 8);
    imprimeLista(lst);

    return 1;
}

//Funcao que inicializa a estrutura
int inicializaLista(tipoLista *lst, int max) {
    int i;
    (lst)->lista = (int*) malloc(sizeof(int) * max);

    if ( (lst)->lista ) {
        for (i=0; i<max; i++) {
            (lst)->lista[i] = 0;
        }
        (lst)->qtd = 0;
        (lst)->max = max;
        return 1;
    } else {
        return 0;
    }
}

//Funcao que imprime a estrutura lista
void imprimeLista(tipoLista lst) {
    int i;
    printf("Qtd=%d;", lst.qtd);
    for (i=0; i<lst.qtd; i++)
        printf("[%d]", lst.lista[i]);
    printf("\n");
}

//Funcao que retorna quantos elementos estao presentes na estrutura
int qtdElementos(tipoLista lst) {
    return lst.qtd;
}


//Funcao que retorna a capacidade da lista
int maxLista(tipoLista lst) {
    return lst.max;
}


//Funcao que insere um elemento no inicio da lista
int insereInicio(tipoLista *lst, int valor) {
    //Verifica se ha espaco disponivel
    if ( qtdElementos(*lst) < maxLista(*lst) ) {
        int i;
        for (i=lst->qtd; i>0; i--) {
            lst->lista[i] = lst->lista[i-1];
        }
        lst->lista[0] = valor;
        lst->qtd++;
        return 1;
    } else {
        return 0;
    }
}
