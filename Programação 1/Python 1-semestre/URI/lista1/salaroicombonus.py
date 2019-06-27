nome = str(input())
salario = float(input())
vendido = float(input())

bonus = ((vendido/100)*15)+salario

print("TOTAL = R$ %.2f" % bonus)