'''
					PYTHON3							
'''



def main():
	from random import randint
	import os
	cyanClaro="\033[1;36m"
	vermelho = '\033[31;1m'
	verde = '\033[32;1m'
	azul = '\033[34;1m'
	normal = '\033[0;0m'
	purpleClaro= '\033[1;35m'
	amarelo= '\033[1;33m'
	ciano='\033[46m'
	magenta='\033[45m'
	normal = '\033[0;0m'
	os.system('clear')

	BANNER = """
  _____                    _                  _         _____ _____  ______ 
 / ____|                  | |                | |       / ____|  __ \|  ____|
| |  __  ___ _ __ __ _  __| | ___  _ __    __| | ___  | |    | |__) | |__   
| | |_ |/ _ \ '__/ _` |/ _` |/ _ \| '__|  / _` |/ _ \ | |    |  ___/|  __|  
| |__| |  __/ | | (_| | (_| | (_) | |    | (_| |  __/ | |____| |    | |     
 \_____|\___|_|  \__,_|\__,_|\___/|_|     \__,_|\___|  \_____|_|    |_|     
	"""
	

	print(BANNER)
	arquivo = open('cpf1.txt','w')
	vetor = []
	quantidade = int(input(vermelho+'Quantidade de cpf a serem gerados: '))
	for i in range(11):
		vetor.append(0)
	qt = int(9)
	mu = int(10)
	total = int(0)
	t = int(9)
	
	for z in range(quantidade):
		
		for x in range(9):
			vetor[x]=randint(0,9)
			
		for y in range(2):
			
			for i in range(qt):
				
				total = total+(vetor[i]*mu)
				mu = mu-1
			
			if (total%11 < 2):
				vetor[t] = int(0)
			elif (total%11 >= 2):
				vetor[t] = 11-(total%11)
			
			
			t = int(10)
			mu = int(11)
			qt = int(10)
			total = int(0)
		
		qt = int(9)
		mu = int(10)
		total = int(0)
		t = int(9)
		
		arquivo.write(str(vetor[0])+str(vetor[1])+str(vetor[2])+'.'+str(vetor[3])+str(vetor[4])+str(vetor[5])+'.'+str(vetor[6])+str(vetor[7])+str(vetor[8])+'-'+str(vetor[9])+str(vetor[10])+ '\n')	
			
	
	arquivo.close()
	
	
	clear = lambda: os.system('clear')
	clear()
	import time, sys
	carregamento = str()
	for l in range(80):
		
		carregamento = carregamento+str('#')
		sys.stdout.write("\r{}".format(carregamento))
		sys.stdout.flush()
		time.sleep(0.020)
		
	
	print( '\nArquivo cpf1.txt gerado contendo %s CPFS' %(quantidade))
	carregamento = str()
	for l in range(80):
		
		carregamento = carregamento+str('#')
		sys.stdout.write("\r{}".format(carregamento))
		sys.stdout.flush()
		time.sleep(0.015)
	print('\n')
	time.sleep(0.5)
	clear = lambda: os.system('clear')
	clear()
main()