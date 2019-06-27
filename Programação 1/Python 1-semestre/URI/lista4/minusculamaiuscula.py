def main():
	palavra = str(input('String: '))
	modificado = []
	tamanho = int(len(palavra))

	i = int(0)
	modificado.append(palavra[0])
	for i in range(tamanho):
		print(i)
		if (palavra[i] != ' ' or palavra[i]!='-'):
			if ( i != 0 ):
				if (palavra[i-1].upper() == palavra[i-1]):
					modificado.append(palavra[i].lower())
				elif (palavra[i-1].lower() == palavra[i-1]):
					modificado.append(palavra[i].upper())
				
		else:
			modificado.append(palavra[i])
	print(modificado)

			
	











main()