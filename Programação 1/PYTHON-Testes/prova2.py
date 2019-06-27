#funcao teste se valor>10 entao divide por 3 ate ser menor que 10 senao se valor<10 funcao multiplica por 2 e retorna
def funcao(valor):
	
	if(valor<=10):
		
		return(valor*2)

	else:
		
		return (funcao(valor//3))		

#funcao principal
def main():

	numero = int()
	
	if (numero<=0):
	
		numero = int(input())
	
	print(funcao(numero))



main()
