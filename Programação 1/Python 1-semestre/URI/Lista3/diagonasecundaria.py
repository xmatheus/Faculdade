def main():
	
	matriz = []
	
	operacao = str(input())
	
	soma = float(0.0)
	cont = int(0)
	i = int(0)
	j = int(0)
	

	for i in range(12):
		matriz.append([0]*12)
	for i in range(12):
		for j in range(12):
			matriz[i][j] = float(input())
	
	i = int(11)
	j = int(0)

	while i>0:
		cont = cont+1
		j = cont
		while j>=11:
			soma = soma+matriz[i][j]
			j = j+1
		i =i-1
	if operacao == 'S':
		print("%0.1f" % soma)
	if operacao == 'M':
		media = float(0.0)
		media = (soma/66)
		print("%0.1f" % media)	
main()
