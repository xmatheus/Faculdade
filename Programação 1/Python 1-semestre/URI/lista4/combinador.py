def main():
	
	quantidade = int(input())

	frase = []
	for i in range(quantidade):

		frase = frase+(str(input()).split())
	valor = quantidade*2
	tudo = str()
	for i in range(valor):
		tudo += str(frase[i])
	print(tudo)
	#for letra in frase:
		#for i in range(len(letra)):
			#print(letra[i])
	



















main()