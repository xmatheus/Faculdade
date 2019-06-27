def main():
	x = int(input())
	y = int(input())
	c = int(0)
	
	if y>x:
		c = y
		y = x
		x = c

	impar = int(0)	
	if y<0:
		y=y+1
		
	while y<x:
		if y%2 != 0:
			impar = y+impar
		y=y+1
	print(impar)

main()