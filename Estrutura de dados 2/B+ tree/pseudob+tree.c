/**
 * UFMT - Disciplina de ED2
 * Prof. Ivairton
 *
 * Pseudocódigo da estrutura Árvore B+
 *
 */

Considere:
 T 2	//Constante T que determina a capacidade do nó da Arv.B+
 MAX_CHAVES ( 2 * T - 1 )	//Máximo de registros
 MAX_FILHOS ( 2 * T )		//Máximo de filhos
 MIN_CHAVES ( T - 1 )		//Mínimo de registros


// estrutura 'tipoArvB'
estruturaArvB {
	inteiro contChaves;
	inteiro chaves[MAX_CHAVES];
	struct estruturaArvB *filhos[MAX_FILHOS];
	inteiro folha;
    estruturaArvB *prox;
} tipoArvB;


// Função principal de inserção na Árvore B (função a ser chamada pelas funções externas/principal)
tipoArvB* insereArvB (tipoArvB *raiz, inteiro valor) {
	int flag;
	char valorRetorno, i;
	tipoArvB *filhoDir, *novaRaiz;

	filhoDir = insere (raiz, valor, &flag, &valorRetorno);

	//Verifica se ocorreu a descida na árvore adequadamente, se há a necessidade de um novo nó como raiz
	if ( flag ) {
		novaRaiz = alocaNovoNo();
		novaRaiz->contChaves = 1;
		novaRaiz->chaves[0] = valorRetorno;
		novaRaiz->filhos[0] = raiz;
		novaRaiz->filhos[1] = filhoDir;
		novaRaiz->folha = 1;
        novaRaiz->prox = NULL;
		return (novaRaiz);
	} else {
		return (raiz);
	}
}

//Função que busca pelo nó onde deve ser inserido o valor/chave e faz a quebra do nó, quando necessário
tipoArvB *insere (tipoArvB *no, inteiro valor, inteiro *flag, inteiro *valorRetorno) {
	inteiro i, pos, meio;
	tipoArvB *noAux, *filhoDir;

	if (no == NULL) {
		//Então o nó pai (anterior) é o nó onde deve ser feita a inserção, pois alcançou um nó folha
		*flag = 1;
		*valorRetorno = valor;
		return (NULL);
	} else {
		//Executa a busca pelo nó onde o valor deve ser inserido
		pos = buscaBinaria (no, valor); //verifica/busca a posição

		//Identifica se a chave já está presente na árvore
		if ( 	(pos < no->contChaves) && (no->chaves[pos] == valor) ){
			printf("O valor da chave já está presente na Árvore B!\n");
			*flag = 0;
		} else {
			//Desce na árvore, buscando pelo nó folha onde deve ocorrer a inserção
			if ( no->chaves[pos] < valor)
				pos++;
			filhoDir = insere(no->filhos[pos], valor, flag, valorRetorno); 	//Executa chamada recursiva

			if ( *flag ) { //Se ocorreu a descida como esperado, então insere o valor no nó
				if ( no->contChaves < MAX_CHAVES) { //Verifica se há espaço no nó
					insereChaveOrdenado(no, *valorRetorno, filhoDir);
					*flag = 0;
				} else { //Então é preciso dividir o nó p/ poder inserir o valor
					noAux = alocaNovoNo();
					meio = no->chaves[MIN_CHAVES];

                    //Neste ponto é preciso garantir que o valor "meio" será mantido
                    //em um nó folha. Para isso, basta copiar os valores após o
                    //"meio" e mantêno no nó original

					//Insere metade das chaves no novo nó
					noAux->filhos[0] = no->filhos[MIN_CHAVES+1];
					for ( 	i = MIN_CHAVES + 1; i < MAX_CHAVES; i++) {
						insereChaveOrdenado( noAux, no->chaves[i], no->filhos[i+1] );
					}

					//Atualiza o nó "apaga" as chaves transferidas
                    //mantém o nó do "meio"
					for (i = MIN_CHAVES+1; i < MAX_CHAVES; i++) {
						no->chaves[i] = 0;
						no->filhos[i+1] = NULL;
						no->contChaves--;
					}

					//Verifica em qual dos novos nós o valor deve ser inserido e executa
					if ( pos <= MIN_CHAVES) { //o mesmo que: (meio > valorRetorno)
						insereChaveOrdenado(no, *valorRetorno, filhoDir);
					} else {
						insereChaveOrdenado(noAux, *valorRetorno, filhoDir);
					}

                    //Atualiza o encadeamento entre os possíveis nós folha, o antigo
                    //e o novo criado pela cisão

                    //Verifica se são nós folha:
                    if ( (no.folha == 1) && (noAux.folha == 1) ) {
                        noAux.prox = no.prox
                        no.prox = noAux
                    }


					//Retorna o elemento do meio para ser inserido no nó pai e o filho direito da chave central
					*flag = 1;
					*valorRetorno = meio;
					return (noAux);
				}
			}
		}
	}
}