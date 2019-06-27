def main():
	quantidade = int(input())
	j = int(0)
	for i in range (quantidade):
		frase= str()
		palavra = str(input())
		palavra = palavra.split()
		p1 = str(palavra[0])
		p2 = str(palavra[1])
		if (len(p1)<len(p2)):
			menor = len(p1)
			maior = len(p2)
		elif(len(p2)<len(p1)):
			menor = len(p2)
			maior = len(p1)
		else:
			menor = len(p1)
			maior = len(p2)
		for h in range(0,menor,1):
			
			frase = frase+(p1[h]+p2[h])
		if (len(p1)<len(p2)):
			frase = frase+p2[len(p1):]

		if (len(p2)<len(p1)):
			frase = frase+p1[len(p2):]

		print(frase)












main()