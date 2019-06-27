lista  = [6, 10, 4, 21, 9]
iMaior = 0
iMenor = 0

i = 0
while i < len(lista):

    if lista[i] > lista[iMaior]:
        iMaior = i

    if lista[i] < lista[iMenor]:
        iMenor = i

    i = i + 1

print (lista)
print(iMenor)
print(iMaior)