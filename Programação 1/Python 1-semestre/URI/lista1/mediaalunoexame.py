def main():
	entrada=str(input())
	N1,N2,N3,N4 = entrada.split()
	N1 = float(N1)
	N2 = float(N2)
	N3 = float(N3)
	N4 = float(N4)


	media= ((N1*2.0)+(N2*3.0)+(N3*4.0)+(N4*1))/10
		
	print("Media: %.1f" % media)

	if media>=7:
			print("Aluno aprovado.")
	if media<5:
			print("Aluno reprovado.")
	if media>=5 and media<=6.9:
		print("Aluno em exame.")
		Nexame = float(input())
		print("Nota do exame: %.1f" % Nexame)
			
		recalculada = (Nexame+media)/2

		if recalculada>=5:
			print("Aluno aprovado.")

		else:
			print("Aluno reprovado.")

		print("Media final: %.1f" % recalculada)
main()