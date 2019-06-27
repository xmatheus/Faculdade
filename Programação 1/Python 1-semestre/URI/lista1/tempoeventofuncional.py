#algoritmo calculo de tempo de evento em segundos
# feito por Matheus Felipe
#C.comp 2017





def main():


	#PARTE UM
	inicio = []
	inicio = str(input()).split()
	diai = int(inicio[1])
	

	horainicio = []
	horainicio = str(input()).split()
	hinicio = int(horainicio[0])
	minicio = int(horainicio[2])
	sinicio = int(horainicio[4])
	
	#PARTE DOIS

	fim = []
	fim = str(input()).split()
	diaf = int(fim[1])
	

	horafim = []
	horafim = str(input()).split()
	hfim = int(horafim[0])
	mfim = int(horafim[2])
	sfim = int(horafim[4])

	#colocando nos horarios certos

	qt1 = int(0)
	qt2 = int(0)

	qt1 = (sinicio + (minicio*60) + (hinicio*60*60) + (diai*60*60*24))
	qt2 = (sfim + (mfim*60) + (hfim*60*60) + (diaf*60*60*24))

	tempo=int(0)
	tempo=(qt2-qt1)	#final menos inicial
	
	#comeca a brincadeira
	#mostra ao usuario

	a1=int(0)

	adia=tempo//86400	#divisao inteira

	print (str(adia)+ " dia(s)")

	tempo=tempo%86400	#resto

	ahora=tempo//3600	#divisao inteira

	print (str(ahora)+ " hora(s)")

	tempo=tempo%3600	#resto
	aminuto=tempo//60	#divisao inteira
	
	print (str(aminuto)+ " minuto(s)")

	a1=tempo%60	#resto

	print (str(a1)+ " segundo(s)")

main()