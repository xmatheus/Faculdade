/*
	Trabalho de ed1
	Aluno: Matheus felipe Teodoro Correia
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




//struct arvore
struct arvore{
	char letra;
	char codigo[100];//meio desnecessario mas usado para printar o codigo na funcao pre-ordem
	struct arvore *ponto;
	struct arvore *traco;
};
typedef struct arvore tipo_arvore;

//------------------prototipos-------------
tipo_arvore* monta_arvore(tipo_arvore *arvore,char *vet,int pos,int tam,char letra);
tipo_arvore* decodifica(tipo_arvore *arvore_sec, char *vet,int pos,int tam);
void pre_ordem(tipo_arvore *arvore);

//------------funcoes----------------------
tipo_arvore *monta_arvore(tipo_arvore *arvore,char *vet,int pos,int tam,char letra){//funcao que controi a arvore separando-a em . a esqueda e - a direita
	int i=0;
	if(arvore == NULL){
		arvore=(tipo_arvore*) malloc(sizeof(tipo_arvore) );
		(arvore)->ponto=NULL;
		(arvore)->traco=NULL;
		(arvore)->letra='$';//caracter especial caso nao seja a letra no momento
		


	}
	if(pos<tam){//condicao para ler ate onde o vetor foi preenchido
		if(vet[pos]=='.'){
			//arvore->codigo='.';//apagar caso de merda
			arvore->ponto = monta_arvore((arvore)->ponto,vet,pos+1,tam,letra);//descendo a esquerda e criando arvore
			
			

		}
		if(vet[pos]=='-'){
			//arvore->codigo='-';//apagar caso de merda
			arvore->traco = monta_arvore((arvore)->traco,vet,pos+1,tam,letra);//descendo a direita e criando arvore
			
			
		}

	}
	else{
		(arvore)->letra=letra;
		vet[tam]='\0';//quebrando o vetor
		strcpy(arvore->codigo,vet);//copiando o vetor com o codigo para a estrutura para printar na funcao pre-ordem
	}
	
	return arvore;

	
}

void pre_ordem(tipo_arvore *arvore){//funcao que printa a arvore em forma de pre-ordem

	int j=0;

	if(arvore!=NULL){ // se a arvore nao for vazia printa em pre-ordem
		
		if (arvore->letra!= '$'){
			while(arvore->codigo[j]!='\0'){
				if(arvore->codigo[j]=='.' || arvore->codigo[j]=='-'){
					printf("%c",arvore->codigo[j]);//printa o codigo da letra e depois printa a letra com separacao de um tab
				}
				j++;
			}
			printf("\t%c\n", arvore->letra); //printa a letra
			
		}

		
		pre_ordem(arvore->ponto);//mostra a ponto (subárvore à esquerda) 
	
		pre_ordem(arvore->traco); //mostra a traco (subárvore à direita) 
		

		
	}
  
}

tipo_arvore *decodifica(tipo_arvore *arvore_sec, char *vet,int pos,int tam){//funcao que traduz codigo morse em letras/frases

	if(pos<tam){
		if((vet[pos]=='.')){//se for ponto ele vai descendo a esquerda
			arvore_sec->ponto  = decodifica(arvore_sec->ponto,vet,pos+1,tam);
		}
		if(vet[pos]=='-'){//se for traco ele vai descendo a direita
			arvore_sec->traco = decodifica(arvore_sec->traco,vet,pos+1,tam);
		}
	} else{//caso pos seja igual ao tamanho
		if(arvore_sec->letra!='$'){//para nao printar o caracter especial
			printf("%c",arvore_sec->letra);
		}

	}
	return arvore_sec;
}

//-----------------------principal---------------------------------------------
int main(){
	FILE *file_tabmorse;
	char simbolo,simbolo2,simbolo3,letra;
	char vet[100];
	int tam,i=0;
	tipo_arvore *arvore;

	//iniciar a raiz para nao dar erro de segmentacao
	arvore=(tipo_arvore*)malloc(sizeof(tipo_arvore));
	arvore->ponto=NULL;
	arvore->traco=NULL;
	arvore->letra='$';
	arvore->codigo[0]='$';
	/*abertura do arquivo com codigos e letras caso queira mudar o arquivo precisa ter
	o "codigo  espaco letra: exemplo .. e mas outros modelos tbm funcionam"
	*/
	file_tabmorse=fopen("tabinvertida.txt","r");
	if(file_tabmorse == NULL){//teste erro2
		printf("Erro na abertura do arquivo!\n");
	}

	while (fscanf(file_tabmorse,"%c",&simbolo) != EOF){//chamada da funcao no main para'alocar somente . e - no vetor
		int j=0;
		if(simbolo == ' '){//teste para ter ceerteza que so foi os pontos e tracos
			
			fscanf(file_tabmorse,"%c",&letra);
			arvore=monta_arvore(arvore,vet,0,i,letra);
			
			i=0;
			
		}
		else if( simbolo != '\n'){//preenchimento do vetor
			vet[i]=simbolo;
			i++;
		}
		


	}
	fclose(file_tabmorse);//fechamento arq
	
	
	FILE *file_arqmorse;

//--------------------------------------
	int valor;
	system("clear");
	//parte meio grafica do algoritmo
	do{
		printf("Tradutor de código morse\n(MORSE->PT-BR)\n");
		printf("\n1-Traduz arquivo\n2-Imprime arvore em pre-ordem\n3-nome dos arquivos de tabela morse e do código morse\n4-sair\n");
		scanf("%d",&valor);
		switch(valor){
			case 1:
				system("clear");
				file_arqmorse=fopen("codigomorse.txt","r");
				if(file_arqmorse == NULL){//teste  de erro
					printf("Erro na abertura do arquivo!\n");
				}

				i=0;
				

				char vet2[100];
				printf("Tradução do arquivo: \n");
				while ( fscanf(file_arqmorse,"%c",&simbolo2) != EOF){
					
					
					
					if( simbolo2 == '.' || simbolo2=='-'){//certificando que seja passado somente o codigo morse com . e -
				
						vet2[i]=simbolo2;
						i++;
					}
					else if (simbolo2 == '/'){//separacao de letra na traducao
							
						printf(" ");
					}
					else if (simbolo2 == ' '){//caso seja uma letra ele traduz
						arvore = decodifica(arvore,vet2,0,i);
						i = 0;

					}
					else if(simbolo2=='\n' && (simbolo3!='\n' || simbolo3!= ' ')){//a ultima letra pode ser separada por \n
						arvore = decodifica(arvore,vet2,0,i);
						i=0;
						printf("\n");

					}
					simbolo3=simbolo2;//variavel de controle que fica um paso atras para nao printar a ultima letra caso tenho varios \n
					
				}
				if (simbolo2==EOF){//nao se juntar as informacoes do terminal
					printf("\n");
				}
			
				break;
			case 2:
				system("clear");//comando para limpar o terminal
				pre_ordem(arvore);
				break;
			case 3:
				system("clear");
				printf("Codigo morse->nome do arquivo-> 'tabinvertida.txt' \n");//caso queira altera linha 120
				printf("Arvore->nome do arquivo-> 'codigomorse.txt' \n");//caso queira altera linha 167
				break;
			default:
			
				break;
		}
		
	}while(valor!=4);
	system("clear");


	return 0;

}