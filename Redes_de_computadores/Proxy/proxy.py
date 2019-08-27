#!/usr/bin/env python

#	Universidade Federal do Mato Grosso
# 	web proxy
#	disciplina de redes de computadores
#	Aluno = Matheus Felipe Teodoro Correia

import sys
import threading
from socket import *

buffer_size = 8192
connec_max = 1050

GlobalIp = ""					  # ip para inicializar o proxy	
GlobalPorta = 8080				  # porta para inicializar o proxy	
blackList = ["araguaia.ufmt.br"]  # host que nao podem ser acessados

def start():
	try:
		# listen_port = int(input("Entre com a porta:"))
		endereco = (GlobalIp, GlobalPorta)  # comunicacao local

		sck = socket(AF_INET, SOCK_STREAM)  # ipv4 e tcp

		sck.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)

		# socket associando ip e porta
		sck.bind(endereco)

		# coloca na fila ate N conexoes
		sck.listen(connec_max)
		print("\n[x] Conectado no endereco: "+str(endereco)+"\n[x] Buffer_size: "+str(buffer_size)+"\tmax_connection: "+str(connec_max))

	except Exception:
		print('\n[x] Deu erro na hora de inicializar o socket\n'+Exception)
		sys.exit(1)

	while(True):
			
		try:
			conexao, end_local = sck.accept()

			dados = conexao.recv(buffer_size)

			thr = threading.Thread( target = filtraTudo, args = ( conexao, end_local, dados ) )
			thr.setDaemon(True)
			thr.start()

		except KeyboardInterrupt:
			print('[x] Tchau...')
			sys.exit(0)


def filtraTudo(conexao, endereco, dados):

	try:

		print("\n[!] Nova requisição")
		
		#separa o host
		a = dados.decode()		
		c = a.split('Host: ')[1].split('\r')
		host = c[0]
		
		if(host.find(':') > 0):
    		#tem porta, separa o host e a porta
			sp = host.split(":")
			host = sp[0]
			porta = sp[1]
		else:
    		#nao tem porta definida no escopo, seta para a 8080
			porta = str(80)

		print("[x] Host : "+host.split(':')[0])
		print("[x] Porta: "+porta)

		if(identificaHost(host.split(':')[0])):
			respondeTudo(host, porta, conexao, endereco, dados)
		else:	# responde uma pag html caso a conexao for negada
			file = open("bloq.html",'rb')
			l = file.read(1024)
			while (l):
				conexao.send(l)
				print("[X] Enviando pag HTML de bloqueio")
				l = file.read(1024)
			file.close()
		conexao.close()
			
		
	except Exception as identifier:
		print(identifier)
		conexao.close()


def identificaHost(host): # verifica se o host esta na blacklist
	
	for x in blackList:
		if( x == host ):
			print("[X] Host bloqueado: "+host)
			return False		# False para negar o acesso
	
	return True		# true para liberar o envio da pag solicitada


def respondeTudo(dHost, dPorta, conexao, endereco, dados):	# faz a req da pag e responde para o cliente
    	
	try:
		
		dSocket = socket(AF_INET, SOCK_STREAM)  # ipv4 e tcp
		
		endF = (str(dHost), int(dPorta))
		
		dSocket.connect(endF)
		
		dSocket.send(dados)

		dadosFora = dSocket.recv(buffer_size)


		while(len(dadosFora) > 0):
			print("[x] recebendo( "+endereco[0]+" ) e envidando( "+str(dHost)+" )")
			conexao.send(dadosFora)
			dadosFora = dSocket.recv(buffer_size)
		
		dSocket.close()
		conexao.close()
	except Exception as e:
		dSocket.close()
		conexao.close()
		print("Erro")
		print(e)
		

start()
