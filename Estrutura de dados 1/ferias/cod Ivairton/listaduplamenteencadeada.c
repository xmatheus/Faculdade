/**
 * UFMT - Ciencia da Computacao
 * ED1 - Prof. Ivairton
 *
 * Pseudo código de lista duplamente ligada/encadeada
 *
 */

/* Definicao do tipo do noh da lista */
tipoNo {
    inteiro valor
    tipoNo *prox
    tipoNo *ant
}

/* Funcao que insere no fim da lista */
void insereFim(tipoNo **lst, int vlr) {
    tipoNo *novoNo, *aux
    aloca memoria para (novoNo)

    //Inicializa valores do novo no
    novoNo.valor = vlr
    novoNo.prox = NULO
    novoNo.ant = NULO

    //Acopla novo no na lista
    se ( *lst == NULO ) { //Trata o caso especial que é a lista vazia
        *lst = novoNo
    } senao {
        //percorre a lista até o último no
        aux = *lst
        enquanto (aux.prox != NULO) {
            aux = aux.prox
        }

        //anexa o novo no ao último no
        aux.prox = novoNo
        novoNo.ant = aux
    }
}


/* Funcao que insere no inicio da lista encadeada */
void insereInicio(tipoNo **lst, int vlr) {
    tipoNo *novono;
    aloca memória para (novono)
    se (novono != NULO) {
        novono.valor = vlr
        novono.prox = *lst
        *lst.ant = novono
        *lst = novono
    }
}
