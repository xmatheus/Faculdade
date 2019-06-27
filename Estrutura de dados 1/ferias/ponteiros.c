#include <stdio.h>
#include <stdlib.h>


int main(){
	int x=10;//x recebendo o valor de 10
	int *p=&x;// ponteiro p recebendo o endereco de memoria de x
	int **p2=&p;//ponteiro de ponteiro p2 recebendo o endereco de memoria de p que eh o mesmo ende
	
	printf("&x\t%d\n",&x );
	printf("x\t%d\n",x );
	printf("p\t%d\n",p );
	printf("&p\t%d\n",&p);
	printf("*p\t%d\n",*p);
	printf("p2\t%d\n",p2);
	printf("&p2\t%d\n",&p2);
	printf("*p2\t%d\n",*p2 );
	printf("**p2\t%d\n",**p2);
	printf("%d\n",sizeof(**p2) );
	
	
	
	
	



	return 0;
}