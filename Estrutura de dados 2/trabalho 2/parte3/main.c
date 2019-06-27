#include <stdio.h>
#include <stdlib.h>
/*
 * ALgoritmo que chama 4 algortimos em c
 * 1 - algoritmo gera arquivos txt contendo inteiros(3 de 3k e 3 de 20k)
 * 2 - algoritmo cria a arvore binaria com esses arquivos de inteiros
 * 3 - algoritmo cria a arvore AVL com esses arquivos de inteiros
 * 4 - algoritmo cria a arvore Rubro negra com esses arquivos de inteiros
 * por fim salva as informacoes de altura e rotacoes no arquivo "info-arvores.txt"
 */
void grava_arq(int quantidade);//grava as informacoes no arquivo
void chama_arq(int quantidade,int valor);//chama os algoritmos de geracao e das arvores


void grava_arq(int quantidade){//grava as informacoes no arquivo
	FILE *file;
	
	if(!(file=fopen("info-arvores.txt","a"))){
		printf("Falha na abertura do arquivo 'info-ARVORES.txt'\n");
	}
	fprintf(file, "\n-= 3 ARQUIVOS DE %d:\n",quantidade);
	fclose(file);
	printf("[x]Informacoes gravadas\n");
}

void chama_arq(int quantidade,int valor){//chama os algoritmos de geracao e das arvores

	int k=0;
	char nomeA[1000],nomeB[1000];
	for (k = 0; k < quantidade; k++){

		sprintf(nomeB, "./B-arvore arquivos-INT/Arq[%d][%d].txt -G",k,valor);
		printf("nomearq %s\n",nomeB );
		system(nomeB);//chama a Binaria passando os arq gerados como parametro

		sprintf(nomeA, "./AVL arquivos-INT/Arq[%d][%d].txt -G",k,valor);
		printf("nomearq %s\n",nomeA );
		system(nomeA);//chama a AVL passando os arq gerados como parametro
		
		sprintf(nomeB, "./RN arquivos-INT/Arq[%d][%d].txt -G",k,valor);
		printf("nomearq %s\n",nomeB );
		system(nomeB);//chama a Rubro negra passando os arq gerados como parametro
		printf("[x]END\n");
	}
}


int main(int argc, char *argv[ ]){

	system("./Genarq 3 5000");//gera 3 de 5k
	grava_arq(5000);//escreve no arquivo que as proximas info sao sobre arq de 3k
	chama_arq(3,5000);//chama as arvores com o parametro sendo o nome desses arq
	
	system("./Genarq 3 20000");//gera 3 de 20k
	grava_arq(20000);//escreve no arquivo que as proximas info sao sobre arq de 20k
	chama_arq(3,20000);//chama as arvores com o parametro sendo o nome desses arq
}