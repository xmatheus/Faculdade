def main():
	vetor = []

	i =int(0)

	
	for i in range(10):
   		vetor.append(eval(input()))
	
	i = int(0)
	
	
	while i<10:
		
		if vetor[i]<=0:
			
			vetor[i] = int(1)
		
		
		print("X["+str(i)+"] =",vetor[i]) 
		i = i+1


main()