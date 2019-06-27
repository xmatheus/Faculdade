def main():
	entrada = []
	entrada = str(input()).split()
	A = float(entrada[0])
	B = float(entrada[1])
	C = float(entrada[2])
	D = float(entrada[3])

	if (B>C and D>A and C+D>B+A and C>0 and D>0 and A%2==0):
		print("Valores aceitos")
	else:
		print("Valores nao aceitos")

main()