#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void armazenaAleatorios(char vetor[]){
    int i;
    for(i=0; i<10; i++){
        vetor[i]= 'a' + (char)(rand()%26);
    }
}

void apresenta(char vetor[]){
    printf("\n");
    int i;
    for (i=0; i<10; i++)
        printf("%c",vetor[i]);
    printf("\n");
}
int main(){ 
    srand((unsigned)time(NULL));
    char vetor[10];
    armazenaAleatorios(vetor);
    apresenta(vetor);
}