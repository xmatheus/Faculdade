#include <stdio.h>
#include <stdlib.h>
#include <string.h>





void quickSort(int *vetor, int inicio, int fim){
   int k,i, j, meio, aux;
   printf("inciou\n");
   for(k=0;k<5;k++){
      printf("%d ",vetor[k] );
   }
   printf("\n");
   i = inicio;
   j = fim;
   meio = vetor[(inicio + fim) / 2];
   
   do{

      while(vetor[i] < meio){
         printf("i=%d ",i);
         i++;
         
      }
      while(vetor[j] > meio){
         printf("j=%d ",j);
         j--;
         
      }
      printf("\n");
      printf("meio i=%d j=%d\n",i,j);
      if(i <= j){
         aux = vetor[i];
         vetor[i] = vetor[j];
         vetor[j] = aux;
         i++;
         j--;
        
      }
      printf("saida i=%d j=%d\n",i,j);
   }while(i <= j);
   printf("Rj=%d\n",j);
   if(inicio < j){
      quickSort(vetor, inicio, j);
   }
   printf("Ri=%d\n",i);
   if(i < fim){
      quickSort(vetor, i, fim);
   }
}

int main(){
   int vet[5];
   vet[0]=3;
   vet[1]=10;
   vet[2]=30;
   vet[3]=1;
   vet[4]=13;
   
   quickSort(vet,0,4);
   for(int i=0;i<5;i++){
      printf("%d ",vet[i] );
   }
   printf("\n");
}
