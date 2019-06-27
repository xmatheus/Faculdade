def main():
	

	valores = str(input())
	n1,n2 = valores.split()
	vet = []
	soma = int()
	texto = str()

	menor = int(n1)
	maior = int(n2)



	while (menor>0 and maior>0):
		
		if (maior<menor):
			maior = int(n1)
			menor = int(n2)
		while (menor<=maior):
			vet.append(menor)
			menor+=1
		for i in range(len(vet)):
			soma = vet[i]+soma
			texto = (texto+str(vet[i])+str(' '))
			
		
		print(texto+ 'Sum=%s ' % soma)

		valores = str(input())
		n1,n2 = valores.split()
		vet = []
		soma = int()
		texto = str()

		menor = int(n1)
		maior = int(n2)

		


main()

