def main():
	
	matriz = []
	
	linha = int(input())
	
	operacao = str(input())
	
	soma = float(0.0)

	i = int(0)
	j = int(0)

	for i in range(12):
		matriz.append([])

		for j in range(12):
			valor = float(input())
			matriz[i].append(valor)
	
	i = int(0)
	j = int(0)

	for i in range(12):
		soma = soma+matriz[linha][i]

	if operacao == 'S':
		print("%0.1f" % soma)
	if operacao == 'M':
		media = float(0.0)
		media = (soma/12.0)
		print("%0.1f" % media)	
main()
