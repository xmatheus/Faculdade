A = int(input())
ano=int(0)
meses=int(0)

while A >= 365:
	A=A-365
	ano=ano+1
while A >= 30:
	A=A-30
	meses=meses+1
print(str(ano)+ " ano(s)")
print(str(meses)+ " mes(es)")
print(str(A)+ " dia(s)")
