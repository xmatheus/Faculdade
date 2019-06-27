def main():

	#PARTE UM

	inicio = []
	inicio = str(input()).split()
	diai = int(inicio[1])
	

	horainicio = []
	horainicio = str(input()).split()
	hinicio = float(horainicio[0])
	minicio = float(horainicio[1])
	sinicio = float(horainicio[2])
	
	#PARTE DOIS

	fim = []
	fim = str(input()).split()
	diaf = int(fim[1])
	

	horafim = []
	horafim = str(input()).split()
	hfim = float(horafim[0])
	mfim = float(horafim[1])
	sfim = float(horafim[2])

	#colocando nos horarios certos

	hinicio = 24 - hinicio
	minicio = 60 - minicio
	sinicio = 60 - sinicio

	#convertendo em segundos

	hinicio = hinicio*3600
	minicio = minicio*60
	
	hfim = hfim*3600
	mfim = mfim*60


	diat = float(0)
	diat = (diaf-diai)-1
	diat = (diat*24)*3600

	dia = ((hinicio+minicio+hfim+mfim+sinicio+sfim+diat)//3600)//24

	print(dia)











main()