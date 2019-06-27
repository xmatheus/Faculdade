def main():
	valor = int(input())
	contador = int(0)
	i = int(0)

	while contador<6:

		if valor%2 != 0:

			contador = contador+1
			
			print(valor)
		
		valor=valor+1


main()