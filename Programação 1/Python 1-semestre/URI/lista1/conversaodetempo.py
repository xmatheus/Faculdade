A = int(input())
	
if A//3600 !=0:
	hora = A//3600
else:
		hora = 0
if A/60 !=0:
	minutos = A//60
	minutos = minutos%60
else:
	minutos = 0
if (A%60)!=0:
	segundos = A%60
else:
	segundos = 0
print(str(hora)+ ":" +str(minutos)+ ":" +str(segundos))