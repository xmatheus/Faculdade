--- Pseudo código do INSERT SORT ---
Funcao insert_sot(vetor[], inteiro tamanho)
inicio
	// Há duas estratégias possíveis:
	// (1) Processar cada elemento da lista, inserindo na posição correta;
	// (2) Selecionar o elemento de menor valor da lst, inserindo na nova lista ordenada.
	// Será implementada a estratégia (1)

	Aloca nova lista: lstOrdenada[]
	inteiro: qtdElementosLstOrdenada <- 0
	inteiro: i

	//percorre a lista desordenada, processando elemento por elemento
	para (i <- 0 enquanto i < tamanho; i <- i + 1) faça
		//Verifica se a lista ordenada está vazia
		se ( qtdElementoslstOrdenada == 0 ) então
			   insereInicio(lstOrdenada[], vetor[i]);
		senão
         //A funcao inserePosiçao recebe o vetor, o valor e a posição a ser inserido (que aqui será descoberta pela função "encontraPosicao")
			   inserePosicao(lstOrdenada[], vetor[i], encontraPosicao(lstOrdenada[], qtdElementoslstOrdenada, vetor[i]) )
		fim se
	fim para

	retorna lstOrdenada[]
fim

Funçao inteiro: encontraPosicao(vetor[], inteiro: tamanho, inteiro: valor)
inicio
	inteiro: i
	i <- 0

	enquanto (i < tamanho) faça
		se ( valor > vetor[i] )
			i <- i+1
		senão
			retorna i; //Devolve a posição
	}
}
