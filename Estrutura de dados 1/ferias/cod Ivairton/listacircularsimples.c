/*
 * UFMT - Ciẽncia da Computação
 * Disciplina de ED1 - Prof Ivairton
 *
 * Pseudo código de lista encadeada circular.
 *
 */

/* Definição de tipo, para representação do Nó */
tipoNo {
    inteiro valor    //valor a ser armazenado
    tipoNO *prox    //Ponteiro para um próximo nó deste mesmo tipo
}


/* Função que insere um novo valor no fim da lista encadeada circular */
void insereFim(tipoNo **lst, int valor) {
    tipoNo *novoNo, *aux

    //Verifica se a lista está vazia
    se ( *lst == NULO ) {
        //Aloca um novo no na memória e atualiza lista
        aloca memória para (novoNo)
        *lst = novoNo
        novoNo.prox = *lst //Circularidade
    } senao {    //Caso a lista já tenha valores, percorre a lista e posiciona-se no último nó, para inclusão do novo registro.
        aux = *lst
        //Enquanto aux não atingir o último nó, vai para o próximo
        enquanto (aux.prox != *lst) {
            aux = aux.prox
        }

        //Aloca o novo no na memória
        aloca memória para (novoNo)
        novoNo.prox = *lst
        aux.prox = novoNo
    }
}

/* Função que insere um novo valor no início da lista encadeada circular */
void insereInicio(tipoNo **lst, int valor) {
    tipoNo *novoNo, *aux

    //Verifica se a lista está vazia
    se ( *lst == NULO ) {
        //Aloca um novo no na memória e atualiza lista
        aloca memória para (novoNo)
        *lst = novoNo
        novoNo.prox = *lst //Circularidade
    } senao {    //Caso a lista já tenha valores, insere o novo nó no início
        //Aloca o novo no na memória
        aloca memória para (novoNo)
        novoNo.prox = *lst

        //Caminha com aux para o fim da lista, para atualizar o último nó da estrutura
        aux = *lst
        enquanto (aux.prox != *lst) {
            aux = aux.prox
        }
        aux.prox = novoNo

        //Atualiza o ponteiro lista
        *lst = novoNo
    }
}