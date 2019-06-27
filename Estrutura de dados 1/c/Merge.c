

#include <stdio.h>
#include <stdlib.h>

// faz o merge e volta as galhas ordenando
void Merge(int vet[],int inicio, int meio, int fim){
        int *vetAux,tam;
        int i,j,k;
        
        tam = (fim - inicio) + 1;
        
        vetAux = (int*) malloc(sizeof(int)*tam);
        // i com o inicio do subvetor a esquerda
        i=inicio;
        // j com o inicio do subvetor a direita
        j=meio+1;
        // tamanho do vetor inicial
        for(k=0; k <= tam; k++){
            // verifica se os lados dos meus subvetores ainda tem valores a direita
            if(i < (meio+1) && j <= fim){
                // faz a ordenacao crescente
                if(vet[i] < vet[j]){
                    
                    vetAux[k] = vet[i++];
                    
                }else{
                    
                    vetAux[k] = vet[j++];
                    
                }
                
            // se um dos subvetores chegou ao fim completa com o outro
            }else if(i < (meio+1) && j > fim){
                
                vetAux[k] = vet[i++];
                
            }else{
                
                vetAux[k] = vet[j++];
                
            }
                
        }
        i = 0;
        for(k=inicio; k <= fim; k++){
            vet[k] = vetAux[i++];
            
        }
        free(vetAux);
            
}

void Sort(int vet[],int inicio, int fim){
    int meio;
    if( inicio < fim){
        meio = ( (inicio + fim)/ 2);
        // quebra pro lado esquerdo
        Sort(vet, inicio, meio);
        // quebra pro lado direito
        Sort(vet, meio+1, fim);
        // faz o merge
        Merge(vet,inicio, meio, fim);
    }
    
}



int main(){
    int vet[10];
    int i;
    for(i=0; i < 10; i++){
        scanf("%d",&vet[i]);
    }
    // o parametro passado como fim eh o ultimo indice valido ou seja
    Sort(vet,0,9);
    for(i=0; i < 10; i++){
        printf("[%d]", vet[i]);
    }
    puts("");
    
    
    
    
    return 0;   
}





































