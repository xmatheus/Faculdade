def main():
	vetor = []
	tamanhovet = int(input())

	while tamanhovet<=1 or tamanhovet>=1000:
		tamanhovet = int(input())
	

	vetor = str(input()).split()
	
	i = int(0)
	for i in range(tamanhovet):
		vetor[i] = int(vetor[i])

	i = int(1)

	indice = int(0)

	menor = int(0)

	menor = vetor[0]

	while i <= tamanhovet-1:
		if menor>vetor[i]:
			menor = vetor[i]
			indice = i
		i = i+1

	if menor == vetor[0]:
		indice = 0

	print("Menor valor: " +str(menor))
	print("Posicao: " +str(indice))
	
main()