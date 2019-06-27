from bs4 import BeautifulSoup
import requests


page = requests.get("https://www.climatempo.com.br/previsao-do-tempo/cidade/755/barradogarcas-mt")
soup = BeautifulSoup(page.content, 'html.parser')
seven_day = soup.find(id="current-weather-row")
forecast_items = seven_day.find_all(id="momento-localidade")
forecast_items2 = seven_day.find_all(class_="left left10 txt-gray-cw bold text-left condicoes-momento")
tonight = forecast_items[0].get_text()
tonight2 = forecast_items2[0]
#nome_cidade = tonight.find(id="momento-localidade").get_text()
temperatura = tonight2.find(id="momento-sensacao").get_text()
pressao = tonight2.find(id="momento-pressao").get_text()
humidade = tonight2.find(id="momento-humidade").get_text()

print(tonight)
print(temperatura)
print(pressao)
print(humidade)