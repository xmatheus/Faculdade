--- Pseudo código do SHELL SORT ---
Funcao shellSort(vetor[], inteiro: tamanho)
início
	inteiro: flagTroca;	//Flag utilizada para saber se ocorreram trocas
	inteiro: i, j, auxValor, salto, flagTroca, k

	salto <- tamanho/2;
	se (salto é par) então
		salto <- salto + 1
	fim se

	enquanto (salto >= 1) faça
		para (i<-1, j<-salto, enquanto j < tamanho, passo i<-i+1, j<-j+1) faça
			se (vetor[i] > vetor[j]) então
				auxValor <- vetor[i]
				vetor[i] <- vetor[j]
				vetor[j] <- auxValor
				//verifica valores anteriores a atual posição do salto (i)
				flagTroca <- 1
				k <- i
				enquanto (flagTroca = 1) faça
					flagTroca <- 0
					se (vetor[k] < vetor[k-salto]) então
						auxValor <- vetor[k]
						vetor[k] <- vetor[k-salto]
						vetor[k-salto] <- auxValor
						flagTroca <- 1
						k <- k-salto
					fim se
				fim enquanto
			fim se
		fim para
		//atualiza o valor do salto
		salto <- salto/2 //arredondando para baixo
		se (salto é par) então
			salto <- salto + 1
		fim se
	fim enquanto
fim
