def main():
	vetor = []

	i =int(0)
	valor = float(input())
	valor = float('%.4f' % valor)

	
	while i<100:
		
		vetor.append(float(valor))
		valor = valor/2
		
		
		print("N["+str(i)+"] = %.4f"% vetor[i]) 
		i = i+1


main()