def main():
    n = int(input())
    for i in range(n):
        s = str(input())
        s = s.split(" ")
 
 
        if s[1]=='dec':
            decimal = int(s[0])
            deci=bin(decimal)
            hexa=hex(decimal)
            deci=deci.split('b')
            hexa=hexa.split('x')
            print('Case %d:\n%s hex\n%s bin\n'%(i+1,hexa[1],deci[1]))
 
 
        elif s[1]=='hex':
            hexadecimal='0x'+s[0]
            deci=int(hexadecimal,16)
            bina=bin(deci)
            bina=bina.split('b')
            print('Case %d:\n%s dec\n%s bin\n'%(i+1,deci,bina[1]))
 
 
        else:
            binario='0b'+s[0]
            deci=int(binario,2)
            hexa = hex(deci)
            hexa = hexa.split('x')
            print('Case %d:\n%s dec\n%s hex\n'%(i+1,deci,hexa[1]))
 
main()