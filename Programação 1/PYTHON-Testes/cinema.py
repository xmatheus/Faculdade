#Python 3
#Matheus Felipe
#Verifica filmes

import requests
import json
import os

page=None
apikey = ''
def requisicao(filme):
	try:
		
		page = requests.get("http://www.omdbapi.com/?t="+str(filme)+"&apikey="+apikey)#faz o download da pagina html
		dicionario = json.loads(page.text)#carrega a pagina como um dicionario=json
		return dicionario
	except:#se der erro
		print("erro de conexao")
		return None

def mostrar(filme):#mostra as informacoes do filme presentes na variavel filme que esta como dicionario
	os.system('clear')
	#print(filme)#ver todo o arquivo JSON
	print("Titulo: "+str(filme[u'Title']))
	print("Poster url: "+str(filme[u'Poster']))
	print("Bilheteria: "+str(filme[u'BoxOffice']))
	print("Ano de lancamento: "+str(filme[u'Released']))
	print("Duracao do filme: "+str(filme[u'Runtime']))
	print("Genero: "+str(filme[u'Genre']))
	print("Producao: "+str(filme[u'Production']))
	print("Site: "+str(filme[u'Website']))
	print('')

sair=False
while(sair!=True):
	#decisao=raw_input("Nome do filme ou 'SAIR' para fechar:  ")
	decisao=str(input("Nome do filme ou 'SAIR' para fechar:  "))
	if(decisao=='SAIR'):
		os.system('clear')
		sair=True
	else:

		filme=requisicao(decisao)
		if(filme[u'Response']=='False'):
			print('Filme nao encontrado')
		else:
			mostrar(filme)
		