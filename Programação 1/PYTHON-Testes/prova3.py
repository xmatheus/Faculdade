def main():
	n = float(input())
	vet = []
	if (n<=0):
		n = float(input())
	
	vet.append(n)

	for i in range(6):
		if (vet[i]<=10):
			vet.append(vet[i]*vet[i])
		else:
			vet.append(vet[i]/3)
		print(vet,)

main()