from bs4 import BeautifulSoup
import requests

url = 'http://g1.com.br/'
header = {'user-agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) '
                        'AppleWebKit/537.36 (KHTML, like Gecko) '
                        'Chrome/51.0.2704.103 Safari/537.36'}



req = requests.get(url,headers= header)

html = req.text

soup = BeautifulSoup(html,'html.parser')

colecao = soup.find_all("feed-post-body-title gui-text-title gui-color-primary gui-color-hover") #div eh texto

for item in colecao:
  print(item.get_text())