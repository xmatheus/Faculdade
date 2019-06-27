def main():
	i = int(0)
	cont = int(0)
	vetor = list(range(6))
	while i<6:
		vetor[i] = float(input())
		i=i+1
	i=int(0)
	while i<6:
		if int(vetor[i])>0:
			cont=cont+1
			
		i=i+1
	print(str(cont)+ " valores positivos")		
main()