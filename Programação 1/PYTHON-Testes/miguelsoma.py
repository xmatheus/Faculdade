def main():
	entrada = raw_input()
	x,y = entrada.split()
	x = int(x)
	y = int(y)

	while x>0 and y>0:
		soma = 0
		if(x>y):
			aux =x
			x = y
			y = aux
		for i in range(x,y+1):
			soma = i+soma
			print str(i) + "",
		print("Sum=" + str(soma))
		entrada = raw_input()
		x,y = entrada.split()
		x = int(x)
		y = int(y)

main()