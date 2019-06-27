import sys
def main():
	for palavra in sys.stdin:
		flag = True
		palavraD = str()

		for letra in palavra:
			if (letra != " " and letra.isalpha()):
				if (flag == True):
					letra = letra.upper()
					flag = False
				else:
					letra = letra.lower()
					flag = True
			palavraD = palavraD+letra

		print(palavraD),
main()

	