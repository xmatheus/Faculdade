def main():
	
	frase = str(input())
	
	frase_modificada = str()
	
	letra = str()

	contador = int(2)


	for letra in frase:
		
		if (letra == ' ' or letra.isdigit()==True):
			frase_modificada= frase_modificada+letra

		elif (type(letra)==str and contador%2 == 0):
			frase_modificada= frase_modificada+letra.upper()
			contador += 1
		elif (type(letra)==str and contador%2 != 0):
			frase_modificada= frase_modificada+letra.lower()
			contador += 1

	
	print(frase_modificada)


main()