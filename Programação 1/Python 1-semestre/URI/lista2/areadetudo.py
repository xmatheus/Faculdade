def main():

	entrada = []
	entrada= str(input()).split()
	A = float(entrada[0])
	B = float(entrada[1])
	C = float(entrada[2]) 

	

	Atriangulo = float((A*C)/2)

	Acirculo = float(3.14159*(C*C))

	Atrapezio = float(((A+B)*C)/2)

	Aquadrado = float(B*B)

	Aretangulo = float(B*A)

	print("TRIANGULO: %.3f" %Atriangulo)

	print("CIRCULO: %.3f" %Acirculo)

	print("TRAPEZIO: %.3f" %Atrapezio)

	print("QUADRADO: %.3f" %Aquadrado)

	print("RETANGULO: %.3f" %Aretangulo)


main()