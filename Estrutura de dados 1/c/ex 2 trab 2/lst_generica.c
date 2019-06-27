/**
 * UFMT - Ciencia da computacao
 * ED1 - Prof. Ivairton
 *
 * Implementacao de estrutura de dados com manipulacao
 * de dados de tipo generico
 * Sera implementada uma lista encadeada.
 *
 */

#include<stdio.h>
#include<stdlib.h>

//Definicao de biblioteca LST_GENERICA
#ifndef LST_GENERICA
#define LST_GENERICA

// Definicao de tido de dados com ponteiro do tipo void
struct est_no_lista {
    void *dado;
    struct est_no_lista *prox;
};
typedef struct est_no_lista tipoLista;


// Prototipacao
void insere_inicio_lst(tipoLista **lst, void *pt_dado);
void insere_fim_lst(tipoLista **lst, void *pt_dado);
void *pega_primeiro(tipoLista *lst);
void *pega_posicao(tipoLista *lst, int pos);


// Funcao que insere no inicio da lista
void insere_inicio_lst(tipoLista **lst, void *pt_dado) {
    tipoLista *novoNo;
    novoNo = (tipoLista*) malloc(sizeof(tipoLista));

    //Verifica alocacao
    if (novoNo != NULL) {
        novoNo->dado = pt_dado;
        novoNo->prox = (*lst);
        (*lst) = novoNo;
    }
}


//Funcao que insere no fim da lista
void insere_fim_lst(tipoLista **lst, void *pt_dado) {
    tipoLista *novoNo, *aux;
    novoNo = (tipoLista*) malloc(sizeof(tipoLista));
    //Verifica alocacao
    if (novoNo != NULL) {
        novoNo->dado = pt_dado;
        novoNo->prox = NULL;

        //Verifica se lista estah vazia
        if ((*lst) == NULL) {
            (*lst) = novoNo;
        } else {
            aux = (*lst);
            while (aux->prox != NULL) {
                aux = aux->prox;
            }
            aux->prox = novoNo;
        }
    }
}


//Funcao que retorna o primeiro elemento da lista
void *pega_primeiro(tipoLista *lst) {
    if (lst != NULL)
        return lst->dado;
    else
        return NULL;
}


//Funcao que retorna um elemento da posicao especificada
void *pega_posicao(tipoLista *lst, int pos) {
    tipoLista *aux;
    aux = lst;
    if (lst != NULL) {
        while( (aux != NULL) && (pos >= 0) ) {
            if (pos == 0) {
                return aux->dado;
            }
            pos--;
            aux = aux->prox;
        }
    }
    return NULL;
}

#endif
