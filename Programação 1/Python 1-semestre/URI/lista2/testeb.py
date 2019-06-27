def main():
	from decimal import Decimal

	i = 0
	j = 1
	while(i <= 2):

		
		if (j==1):
			j = int(1)
		if (j==2):
			j = int(2)
		if (j==3):
			j = int(3)
		if (j==4):
			j = int(4)
		if (j==5):
			j = int(5)
		if (i==2):
			i = int(2)
		if (i==1):
			i = int(1)

		print('I={} J={}'.format(i, j))
		j = j + 1
		
		if(j == (i + 4)):
			i = i+Decimal('0.2')
			j = j-Decimal('2.8')
main()