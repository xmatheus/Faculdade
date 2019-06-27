def main():
	from math import sqrt
	entrada = []
	entrada = str(input()).split()
	X1 = float(entrada[0])
	Y1 = float(entrada[1])

	entradaT = []
	entradaT = str(input()).split()
	X2 = float(entradaT[0])
	Y2 = float(entradaT[1])

	S1 = float(X2-X1)*(X2-X1)
	S2 = float(Y2-Y1)*(Y2-Y1)
	ST = float(sqrt(S1+S2))

	print("%.4f" % ST)


main()