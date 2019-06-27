def main():
	
	quantidade = int(input())

	for q in range(1,quantidade+1):
		
		valores = str(input())
		n1,n2 = valores.split()
		
		totalhexdec = str()
		totaldec = int()
		totalhex = str()
		totalbin = int()
		totalaux = int()
		reverso = str()
		vethex = []
		h = int(0)
		menor = int(0)
		maior = int(0)
		cont = int(0)
		cont1 = int(0)

		print('Case '+str(q)+':')
#-------------------------------------------------------BINARIO---------------------------------------------------------------------------
		if (n2 == 'bin'):
	
			
			reverso = list(n1[::-1])
			while (len(reverso)%2 != 0):
				reverso = list(reverso)+list('0')
			for b in reverso:
				
				
				totaldec = (int(b)*(2**h))+totaldec
				h = h+1
			print(str(totaldec)+ " dec ",)

			quantidadeBINHEX = int(len(reverso)//4)
			
			h = int(3)
			
			if (quantidadeBINHEX<1):
				quantidadeBINHEX = int(1)
			
			
	
			reverso = list(reverso[::-1])
			

			maior = int(0)
			menor = int(0)
			

			for i in range(quantidadeBINHEX):
				totalaux = int()
				
				maior = maior+4
				for t in range(menor,maior):	

					totalaux = int(reverso[t])*(2**h)+totalaux
					h = h-1	
					
				menor = menor+4
					
				
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
					
				cont1 += 1 
				
				h =int(3)
			
			print(str(totalhex)+ " hex ",)
#-------------------------------------------------------BINARIO---------------------------------------------------------------------------
#-------------------------------------------------------DECIMAL---------------------------------------------------------------------------
		elif (n2 == 'dec'):
			dividir = int(n1)
			valor = []
			
			a = list()
			while (dividir//16 >0):
				valor.append(dividir%16)
				dividir = dividir//16
				if (dividir<16):
					valor.append(str(dividir))
				
			a = list(valor[::-1])
				
			for k in range(len(a)):
				
					if (int(a[k]) == 10 ):
						totalhexdec = totalhexdec+str('a')

					if (int(a[k]) == 11):
						totalhexdec = totalhexdec+str('b')

					if (int(a[k]) == 12):
						totalhexdec = totalhexdec+str('c')

					if (int(a[k]) == 13):
						totalhexdec = totalhexdec+str('d')

					if (int(a[k]) == 14):
						totalhexdec = totalhexdec+str('e')

					if (int(a[k]) == 15):
						totalhexdec = totalhexdec+str('f')
					
					elif(int(a[k])!=0 and int(a[k])!=10 and int(a[k])!=11 and int(a[k])!=12 and int(a[k])!=13 and int(a[k]) !=14 and int(a[k])!=15):
						totalhexdec += str(a[k])

			print(str(totalhexdec)+ " hex ",)
			
			dividir1 = int(n1)
			valor1 = []
			a1texto = str()
			
			while (dividir1//2 > 0):
				valor1.append(dividir1%2)
				dividir1 = dividir1//2
				if (dividir1<2):
					valor1.append(str(dividir1))
				
				
			for y in range(len(valor1)):
				a1texto = str(valor1[y])+a1texto
			(str(a1texto)+ " bin ",)
				
				
				








#-------------------------------------------------------DECIMAL---------------------------------------------------------------------------
#-------------------------------------------------------HEXADECIMAL---------------------------------------------------------------------------
		elif (n2 == 'hex'):
			

			b = list(n1[::-1])
			totaldec1 = []
			
			for p in range(len(b)):
				
					if (str(b[p]) == 'a' ):
						totaldec1.append(str(10))

					if (str(b[p]) == 'b'):
						totaldec1.append(str(11))

					if (str(b[p]) == 'c'):
						totaldec1.append(str(12))

					if (str(b[p]) == 'd'):
						totaldec1.append(str(13))

					if (str(b[p]) == 'e'):
						totaldec1.append(str(14))

					if (str(b[p]) == 'f'):
						totaldec1.append(str(15))

					if (str(b[p]) != 'a' and str(b[p]) != 'b' and str(b[p]) != 'c' and str(b[p]) != 'd' and str(b[p]) != 'e' and str(b[p]) != 'f'):
						
						totaldec1.append(str(b[p]))
			
			
			totalhexdec1 = int()
			h = int(0)
			for f in totaldec1:
				totalhexdec1 = (int(f)*(16**h))+totalhexdec1
				h = h+1
			print(str(totalhexdec1)+' dec',)

			totaldec1 = list(totaldec1[::-1])
			
			
			


			
			resto = []
			a2texto = str()
			dividir2 = int()
			tst = list()
			
			
			for m in range(len(totaldec1)):
				
				dividir2 = int(totaldec1[m])
				
				while (int(dividir2 // 2 > 0)):
					resto.append(str(int(dividir2%2)))
					dividir2 = int(dividir2)//2
					if (dividir2<2):
						resto.append(str(dividir2))
					
				tst = tst+list(resto[::-1])
				resto = []		
				
			for y in range(len(tst)):
				a2texto = a2texto+str(tst[y])
			
				
			print(str(a2texto)+ " bin ",)
			
#-------------------------------------------------------HEXADECIMAL---------------------------------------------------------------------------
main()