valor = -1
	
while valor<0 or valor>1000000:
		 
	valor = int(input())

valor1 = valor
	
nota100=int(0)
nota50=int(0)
nota20=int(0)
nota10=int(0)
nota5=int(0)
nota2=int(0)
nota1=int(0)

while valor1 >= 100:
	valor1=valor1-100
	nota100=nota100+1

while valor1 >= 50:
	valor1=valor1-50
	nota50=nota50+1

while valor1 >=20:
	valor1=valor1-20
	nota20= nota20+1

while valor1 >=10:
	valor1=valor1-10
	nota10= nota10+1

while valor1 >=5:
	valor1=valor1-5
	nota5= nota5+1

while valor1 >=2:
	valor1=valor1-2
	nota2= nota2+1

while valor1 >=1:
	valor1=valor1-1
	nota1= nota1+1

print(valor)
print (str(nota100) + " nota(s) de R$ 100,00")
print (str(nota50) + " nota(s) de R$ 50,00")
print (str(nota20) + " nota(s) de R$ 20,00")
print (str(nota10) + " nota(s) de R$ 10,00")
print (str(nota5) + " nota(s) de R$ 5,00")
print (str(nota2) + " nota(s) de R$ 2,00")
print (str(nota1) + " nota(s) de R$ 1,00")