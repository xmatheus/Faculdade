def main():
	frase = str(input())
	frase_alterada = str()
	if (frase[0] == frase[0].upper()):
		contador = int(2)
	else:
		contador = int(1)
	for letra in frase:
		if letra == " ":
			frase_alterada = frase_alterada+" "
		if letra == "-":
			frase_alterada = frase_alterada+"-"
		elif contador%2 == 0:
			contador += 1
			frase_alterada = frase_alterada+letra.upper()
		else:
			contador -= 1
			frase_alterada = frase_alterada+letra.lower()

	print(frase_alterada)

main()