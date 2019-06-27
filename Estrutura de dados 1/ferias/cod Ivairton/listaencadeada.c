/**
 * UFMT - Ciencia da Computacao
 * ED1 - Prof. Ivairton
 *
 * Pseudo código da implementacao de lista ligada/encadeada
 *
 */


/* Estrutura */
estrutura tipoNo {
    inteiro valor;
    tipoNo *prox;
}


/* Funcao que insere no fim da lista */
void insereFim(tipoNo **lst, int vlr) {
    tipoNo *novoNo, *aux
    aloca memória para (novoNo)

    //Inicializa valores do novo no
    novoNo.valor = vlr
    novoNo.prox = NULO

    //Acopla novo no na lista
    se ( (*lst) == NULO ) { //Trata o caso especial que é a lista vazia
        *lst = novoNo;
    } senao {
        //percorre a lista até o último no
        aux = *lst;
        enquanto (aux->prox != NULO) {
            aux = aux->prox
        }
        //anexa o novo no ao último no
        aux->prox = novoNo
    }
}


/* Funcao que insere no inicio da lista encadeada */
void insereInicio(tipoNo **lst, int vlr) {
        tipoNo *novono;
        aloca memória para (novono)
        novono.valor = vlr
        novono.prox = *lst
        *lst = novono

}


/* Funcao que insere um valor em uma posicao especifica da lst */
void inserePos(tipoNo **lst, int pos, int vlr) {
    int cont;
    tipoNo *novono, *aux, *aux_ant;
    aloca memória para (novono)
    novono.valor = vlr
    cont = 0
    aux = (*lst)

    enquanto ( (cont < pos) E (aux != NULO) ) {
        cont = cont + 1
        aux_ant = aux
        aux = aux.prox
    }

    //Verifica o contexto da parada do enquanto
    se ( (cont == pos) E (pos > 0) ) {
        novono.prox = aux
        aux_ant.prox = novono
    } senao {
        novono.prox = *lst;
        *lst = novono
    }
}


/* Funcao que remove o noh do fim da lista */
tipoNo removeFim(tipoNo **lst) {
    tipoNo *aux, *noRemover, noCopia;

    //trata o caso especial de haver apenas 1 no
    se ((*lst).prox == NULO) {
        noCopia = **lst
        Libera memória(*lst)
        (*lst) = NULO
        retorna noCopia
    } senao {
        noRemover = (*lst);
        enquanto( noRemover.prox != NULO) {
            aux = noRemover
            noRemover = noRemover.prox
        }
        noCopia = *noRemover
        libera memória(noRemover)
        aux.prox = NULO
        retorna noCopia
    }
}