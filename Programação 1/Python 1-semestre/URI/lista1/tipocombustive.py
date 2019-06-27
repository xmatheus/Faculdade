def main():
	a =int(0)
	Alcool=int(0)
	Gasolina=int(0)
	Diesel=int(0)
	while (a!=4):
		a = int(input())
		
		while a>4 or a<=0:
			
			a = int(input())

		if (a == 1):
			Alcool=Alcool+1

		if (a == 2):
			Gasolina = Gasolina+1
		if (a == 3):
			Diesel=Diesel+1

	print("MUITO OBRIGADO")
	print("Alcool: " +str(Alcool))
	print("Gasolina: " +str(Gasolina))
	print("Diesel: " +str(Diesel))	















main()