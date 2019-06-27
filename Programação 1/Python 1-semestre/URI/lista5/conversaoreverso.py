def main():
	
	quantidade = int(input())

	for q in range(1,quantidade+1):
		
		valores = str(input())
		n1,n2 = valores.split()
		
		totaldec = int()
		totalhex = str()
		totalbin = int()
		totalaux = int()
		reverso = str()
		vethex = []
		h = int(0)
		rodar = int(4)
		rodar1 = int(0)
		cont = int(0)
		cont1 = int(0)

		print('Case '+str(q)+':')

		if (n2 == 'bin'):
	
			reverso = list(n1[::-1])
			while (len(reverso)%2 != 0):
				reverso = list(reverso)+list('0')
			for b in reverso:
				
				
				totaldec = (int(b)*(2**h))+totaldec
				h = h+1
			print("dec " +str(totaldec))

			quantidadeBINHEX = int(len(reverso)//4)
			print('quantidadeBINHEX', quantidadeBINHEX)
			h = int(0)
			
			if (quantidadeBINHEX<1):
				quantidadeBINHEX = int(1)
			
			reverso = list(reverso[::-1])
			print('reverso',reverso)

			for i in range(quantidadeBINHEX):
				totalaux = int()
				
				for t in range(rodar1,rodar):
					

					totalaux = int(reverso[t])*(2**h)+totalaux
					h = h+1	
					
				print('totalaux', totalaux)
				vethex.append(totalaux)
				
				cont += 1
				
				for k in range(cont1,cont):
				
					if (int(vethex[k]) == 10 ):
						totalhex = totalhex+str('a')

					if (int(vethex[k]) == 11):
						totalhex = totalhex+str('b')

					if (int(vethex[k]) == 12):
						totalhex = totalhex+str('c')

					if (int(vethex[k]) == 13):
						totalhex = totalhex+str('d')

					if (int(vethex[k]) == 14):
						totalhex = totalhex+str('e')

					if (int(vethex[k]) == 15):
						totalhex = totalhex+str('f')
					
					elif(int(vethex[k]!=0 and vethex[k]!=10 and vethex[k]!=11 and vethex[k]!=12 and vethex[k]!=13 and vethex[k]!=14 and vethex[k]!=15 )):
						totalhex += str(vethex[k])
					print('totalhex', totalhex)
				cont1 += 1
				rodar +=4
				rodar1 +=4
				h =int(0)
			
			print("hex " +str(totalhex),)





		


		if (n2 == 'dec'):
			print('decimal')









		if (n2 == 'hex'):
			print('hexadecimal')










main()