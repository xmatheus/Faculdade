#include <stdio.h>
#include <stdlib.h>

#ifndef tipo_mtx
#define tipo_mtx
struct mtz_esparsa{
	struct cabecalho *linha;
	struct cabecalho *coluna;
};
typedef struct mtz_esparsa tipo_esparsa;

struct cabecalho{
	int indice;
	struct cabecalho *cab_prox;
	struct noh *noh_prox;
};
typedef struct cabecalho tipo_cabecalho;

struct noh{
	int valor;
	int indice_linha;
	int indice_coluna;
	struct noh *prox_linha;
	struct noh *prox_coluna;
};
typedef struct noh tipo_noh;
#endif

void cria_cabecalho(tipo_esparsa **esparsa, int linha,int coluna);
void mostra_td(tipo_esparsa *esparsa);
void insere_mtz(tipo_esparsa **esparsa,int linha,int coluna, int valor);
tipo_cabecalho *aloca_cabecalho(tipo_cabecalho *cabecalho,int indice);
tipo_noh *aloca_noh(tipo_noh *noh, int valor,int linha,int coluna);
void anda(tipo_esparsa *esparsa);
void opcao(tipo_esparsa *esparsa);



tipo_cabecalho *aloca_cabecalho(tipo_cabecalho *cabecalho,int indice){//funcao que aloca memoria com o tipo_cabecalho
	cabecalho=(tipo_cabecalho*)malloc(sizeof(tipo_cabecalho));
	cabecalho->indice=indice;
	cabecalho->cab_prox=NULL;
	cabecalho->noh_prox=NULL;
	return cabecalho;
}
tipo_noh *aloca_noh(tipo_noh *noh,int valor,int linha,int coluna){//funcao que aloca memoria com o tipo_noh
	noh->valor=valor;
	noh->indice_linha=linha;
	noh->indice_coluna=coluna;
	noh->prox_linha=NULL;
	noh->prox_coluna=NULL;
	return noh;

}
void cria_cabecalho(tipo_esparsa **esparsa, int linha,int coluna){//funcao que cria o cabecalho
	//printf("Linha(%d) Coluna(%d)\n",linha,coluna);
	
	tipo_cabecalho *cabecalho,*cabecalho_ant,*aux,*cabecalho_col,*cabecalho_col_ant,*aux_col;
	
	int flag=0,flag_coluna=0,flag_linha=0;
	
	if((*esparsa)->linha==NULL){//se a linha do corner estiver vazia
		(*esparsa)->linha=aloca_cabecalho((*esparsa)->linha,linha);
		flag_linha=1;
	}
	
	if((*esparsa)->coluna==NULL){//se a linha da coluna estiver vazia
		(*esparsa)->coluna=aloca_cabecalho((*esparsa)->coluna,coluna);
		flag_coluna=1;
	}
	
	
	if((*esparsa)->linha!=NULL && flag_linha == 0){//1 parte, criacao da linha
		cabecalho=aloca_cabecalho(cabecalho,linha);
		cabecalho=(*esparsa)->linha;
		
		if(linha < (cabecalho->indice)){//se a linha for menor que a linha ja alocada
			aux=aloca_cabecalho(aux,linha);
			aux->cab_prox=cabecalho;
			aux->noh_prox=NULL;
			(*esparsa)->linha=aux;
			flag=1;
		}
		while(flag!=1){
			

			if(cabecalho->indice==linha){//se o cabecalho ja foi criado antes
				flag=1;
				break;
			}

			else{
				if(cabecalho->cab_prox!=NULL){//inicializando o ponteiro com a estrutura anterior para ir comparando de dois a dois
					cabecalho_ant=aloca_cabecalho(cabecalho_ant,0);
					cabecalho_ant=cabecalho;
					cabecalho=cabecalho->cab_prox;
				}
				else{//se so existir um cabecalho
					if(linha > cabecalho->indice){//e o novo cabecalho ser maior que o anterior ja alocado
						aux=aloca_cabecalho(aux,linha);
						aux->cab_prox=NULL;
						aux->noh_prox=NULL;
						cabecalho->cab_prox=aux;
						flag=1;
					}
				}
			}
			if((flag!=1) && (linha>cabecalho_ant->indice) && (linha<cabecalho->indice)){//colocando o novo cabecalho entre dois cabecalhos ja criados
				aux=aloca_cabecalho(aux,linha);
				aux->cab_prox=cabecalho;
				aux->noh_prox=NULL;
				cabecalho_ant->cab_prox=aux;
				flag=1;
			}
		}
	}
	

	if((*esparsa)->coluna!=NULL && flag_coluna == 0){//2 parte, criacao da coluna		
		flag=0;
		cabecalho_col=aloca_cabecalho(cabecalho_col,0);
		cabecalho_col=(*esparsa)->coluna;
		
		if(coluna<cabecalho_col->indice){//se a coluna for menor que a coluna ja alocada
			aux_col=aloca_cabecalho(aux_col,coluna);	
			aux_col->cab_prox=cabecalho_col;
			aux_col->noh_prox=NULL;
			(*esparsa)->coluna=aux_col;
			flag=1;		
		}
		while(flag!=1){
			

			if(cabecalho_col->indice==coluna){//se o cabecalho ja foi criado antes
				flag=1;
				break;
			}

			else{//se nao foi criado
				if(cabecalho_col->cab_prox!=NULL){//inicializando o ponteiro com a estrutura anterior para ir comparando de dois a dois
					cabecalho_col_ant=aloca_cabecalho(cabecalho_col,0);
					cabecalho_col_ant=cabecalho_col;
					cabecalho_col=cabecalho_col->cab_prox;
				}
				else{//se so existir um cabecalho
					if(coluna>cabecalho_col->indice){//e o novo cabecalho ser maior que o anterior ja alocado					
						aux_col=aloca_cabecalho(aux_col,coluna);
						aux_col->cab_prox=NULL;
						aux_col->noh_prox=NULL;
						cabecalho_col->cab_prox=aux_col;
						flag=1;	
					}
				}
			}
			if((flag!=1) && (cabecalho_col->indice>coluna) && (coluna>cabecalho_col_ant->indice)){//colocando o novo cabecalho entre dois cabecalhos ja criados
				aux_col=aloca_cabecalho(aux_col,coluna);
				aux_col->cab_prox=cabecalho_col;
				aux_col->noh_prox=NULL;
				cabecalho_col_ant->cab_prox=aux_col;
				flag=1;	
			}
		}
	}
	//printf("Cabecalho criado\n");
}
void mostra_td(tipo_esparsa *esparsa){//funcao que mostra os cabecalhos e as cedulas das linhas
	tipo_cabecalho *linha;
	tipo_cabecalho *coluna;
	tipo_noh *noh;
	printf("# ");
	if(esparsa->coluna !=NULL){//mostra toda a coluna
		coluna=aloca_cabecalho(coluna,0);
		coluna=esparsa->coluna;	
		while(coluna!=NULL){
			printf("%d------------",coluna->indice);
			coluna=coluna->cab_prox;
		}
		printf("\n");	
	}
	else{
		printf("Coluna vazia\n");
	}
	if(esparsa->linha!=NULL){//mostra todas as linhas e cedulas ja criadas
		linha=aloca_cabecalho(linha,0);
		linha=esparsa->linha;
		
		while(linha!=NULL){
			printf("%d ",linha->indice);
			noh=linha->noh_prox;
			linha=linha->cab_prox;
			while(noh!=NULL){
				printf("(%d,%d)%d",noh->indice_linha,noh->indice_coluna,noh->valor);
				noh=noh->prox_coluna;
			}
			printf("\n\n \n\n");
		}
	}
	else{
		printf("Linha vazia\n");
	}
	printf("\n");
}
void insere_mtz(tipo_esparsa **esparsa,int linha,int coluna, int valor){//funcao que insere valores na matriz
	cria_cabecalho(esparsa,linha,coluna);//cria o cabecalho
	tipo_cabecalho *cab_linha=NULL;
	tipo_cabecalho *cab_coluna=NULL;
	
	tipo_noh *Lnoh=NULL;
	tipo_noh *Lnoh_ant=NULL;
	
	tipo_noh *Cnoh=NULL;
	tipo_noh *Cnoh_ant=NULL;

	tipo_noh *noh_new=(tipo_noh*)malloc(sizeof(tipo_noh));
	

	int flag=0,flag_L=0,flag_C=0,flag_T=0,flag_Y=0,flag_X=0;
	cab_linha=(*esparsa)->linha;
	cab_coluna=(*esparsa)->coluna;

	while(cab_linha->indice!=linha){//vai ate a linha passada como parametro
		cab_linha=cab_linha->cab_prox;
	}
	while(cab_coluna->indice!=coluna){//vai ate a coluna passada como parametro
		cab_coluna=cab_coluna->cab_prox;
	}
	if((cab_linha->noh_prox == NULL) && (cab_coluna->noh_prox == NULL)){//se a linha e a coluna nao tiver uma cedula, a cedula eh alocado
		noh_new=aloca_noh(noh_new,valor,linha,coluna);
		cab_linha->noh_prox=noh_new;
		cab_coluna->noh_prox=noh_new;
		flag=1;
	}	
	if(flag!=1){//se nada foi alocado ainda
		Lnoh=cab_linha->noh_prox;//variavel que recebera as cedulas da linha, e navegara pelas colunas da linha
		Cnoh=cab_coluna->noh_prox;//variavel que recevera as cedulas da coluna, e navegara pelas linhas da coluna
		if((Lnoh!=NULL) && (coluna<Lnoh->indice_coluna)){
			flag_T=1;
		}
		if((Cnoh!=NULL) && (linha<Cnoh->indice_linha)){
			flag_Y=1;
		}
		if((Cnoh!=NULL) && (linha == Cnoh->indice_linha)){
			flag_C=1;
		}
		if((Lnoh!=NULL) && (coluna == Lnoh->indice_coluna)){
			flag_L=1;
		}
		if((Lnoh!=NULL) && (Cnoh!=NULL) && (linha<Cnoh->indice_linha) && (coluna<Lnoh->indice_coluna)){//se a nova cedula possuir indices menores do que as ja criadas, ela sera a primeria da coluna e linha
			noh_new=aloca_noh(noh_new,valor,linha,coluna);
			noh_new->prox_coluna=Lnoh;
			noh_new->prox_linha=Cnoh;
			cab_linha->noh_prox=noh_new;
			cab_coluna->noh_prox=noh_new;
			flag=1;
		}
	}	
	while(flag!=1){//se nada foi alocado
		if((Cnoh!=NULL) && (Lnoh!=NULL)){//cedulas da coluna e linha diferentes de nulo
			if((flag!=1) && (linha == Cnoh->indice_linha) && (coluna == Lnoh->indice_coluna)){//caso a cedula ja tenha sido criada ele apenas sobreescreve
				printf("[X]Parece que ja passamos por esse caminho...\n");
				Lnoh->valor=valor;
				Cnoh->valor=valor;
				flag=1;
			}
			if((flag!=1) && (Lnoh_ant==NULL) && (coluna<Lnoh->indice_coluna) && (linha>Cnoh->indice_linha) && (Cnoh->prox_linha ==  NULL)){//se minha linha e coluna possuir apenas uma cedula, e a nova for menor que a existente, e a nova cedeula possuir indices maiores do que a da coluna
				noh_new=aloca_noh(noh_new,valor,linha,coluna);
				noh_new->prox_coluna= Lnoh;
				noh_new->prox_linha= NULL;
				Cnoh->prox_linha=noh_new;
				cab_linha->noh_prox=noh_new;
				flag=1;
			}
			if((flag!=1) && (Cnoh_ant==NULL) && (linha<Cnoh->indice_linha) && (coluna>Lnoh->indice_coluna) && (Lnoh->prox_coluna ==  NULL)){//se minha coluna e coluna possuir apenas uma cedula, e a nova for menor que a existente, e a nova cedeula possuir indices maiores do que a da linha
				noh_new=aloca_noh(noh_new,valor,linha,coluna);
				noh_new->prox_linha= Cnoh;
				noh_new->prox_coluna= NULL;
				Lnoh->prox_coluna=noh_new;
				cab_coluna->noh_prox=noh_new;
				flag=1;
			}
			if((flag!=1)  && (coluna>Lnoh->indice_coluna) && (Lnoh->prox_coluna == NULL) && (linha<Cnoh->indice_linha)){//se minha cedula for menor que minha cedula da linha,se minha nova celula possuir o indice da linha menor do que o indice atual do cabecalho-coluna
				noh_new=aloca_noh(noh_new,valor,linha,coluna);
				noh_new->prox_coluna=NULL;
				noh_new->prox_linha=Cnoh;
				cab_coluna->noh_prox=noh_new;
				Lnoh->prox_coluna=noh_new;
				flag=1;
			}
			if((flag!=1) && (linha>Cnoh->indice_linha) && (Cnoh->prox_linha == NULL) && (coluna<Lnoh->indice_coluna)){//indice linha da nova cedula for maior que o indice da cedula-coluna, e a proxima cedula for vazia
				noh_new=aloca_noh(noh_new,valor,linha,coluna);
				noh_new->prox_coluna=Lnoh;
				noh_new->prox_linha=NULL;
				cab_linha->noh_prox=noh_new;
				Cnoh->prox_linha=noh_new;
				flag=1;
			}
			if((flag!=1) && (linha<Cnoh->indice_linha) && (Cnoh->prox_linha == NULL) && (coluna<Lnoh->indice_coluna)){//indice linha da nova cedula for menor que o indice linha da cedula-coluna, e a proxima cedula for vazia
				noh_new=aloca_noh(noh_new,valor,linha,coluna);
				noh_new->prox_coluna=Lnoh;
				noh_new->prox_linha=Cnoh;
				cab_linha->noh_prox=noh_new;
				cab_coluna->noh_prox=noh_new;
				flag=1;
			}
			if((flag!=1) && (Lnoh_ant==NULL) && (Cnoh_ant!=NULL) && (coluna>Lnoh->indice_coluna) && (Lnoh->prox_coluna==NULL) && (linha>Cnoh_ant->indice_linha) && (linha>Cnoh->indice_linha) && (Cnoh->prox_linha == NULL)){
				//indice coluna da nova cedula for maior que o indice coluna da cedula-linha, a proxima cedula da cedula-linha for vazia, o indice linha da nova cedula for maior que o indice linha da cedula-coluna anterior, o indice linha da nova cedula for maior que o da cedula-colunha e a proxima cedula linha for vazia
				noh_new=aloca_noh(noh_new,valor,linha,coluna);
				Cnoh->prox_linha=noh_new;
				Lnoh->prox_coluna=noh_new;
				flag=1;
			}
			if((flag!=1) && (Lnoh_ant!=NULL) && (coluna>Lnoh_ant->indice_coluna) && (coluna>Lnoh->indice_coluna) && (Lnoh->prox_coluna==NULL) && (Cnoh_ant==NULL) && (linha>Cnoh->indice_linha) && (Cnoh->prox_linha==NULL)){
				//indice coluna for maior que o da cedula-linha anterior, indice coluna for maior que o indice da cedula-linha, e a proxima cedula da cedula-linha for vazia, cedula-coluna anterior for vazia, indice linha for maior que o da cedula-coluna e a proxima cedula linha for vazia
				noh_new=aloca_noh(noh_new,valor,linha,coluna);
				Lnoh->prox_coluna=noh_new;
				Cnoh->prox_linha=noh_new;
				flag=1;
			}
			if((flag!=1) &&  (Cnoh_ant!=NULL) && (linha>Cnoh_ant->indice_linha) && (linha>Cnoh->indice_linha) && (Cnoh->prox_linha==NULL) && (Lnoh_ant==NULL) && (coluna>Lnoh->indice_coluna) && (Lnoh->prox_coluna==NULL)){
				//indice linha for maior que da cedula-coluna anterior, indice linha for maior que o da cedula-coluna, cedula-coluna proxima linha for vazia, cedula-linha anterior for vazia, indice coluna for maior que o da cedula-linha e a proxima linha for vazia
				noh_new=aloca_noh(noh_new,valor,linha,coluna);
				Lnoh->prox_coluna=noh_new;
				Cnoh->prox_linha=noh_new;
				flag=1;
			}
		}
		if((flag_T!=1) && (flag!=1) && (flag_L==0) && (Lnoh!=NULL) && (Lnoh->prox_coluna!= NULL)){//flag_T= indice coluna for menor que a primeira cedula na frente do cabecalho selecionado,flag_L=1, caso o intervalo de insercao tenha sido achado na linha 
			//teste ter sempre uma cedula-linha anterior e uma na frente para ir comparando
			Lnoh_ant=Lnoh;
			Lnoh=Lnoh->prox_coluna;	
		}	
		if((flag_Y!=1) && (flag!=1) &&(flag_C==0) && (Cnoh!=NULL) && (Cnoh->prox_linha!= NULL)){//flag_Y= indice linha for menor que a primeira cedula na frente do cabecalho celecionado,flag_C=1, caso o intervalo de insercao tenha sido achado na coluna
			//teste ter sempre uma cedula-coluna anterior e uma na frente para ir comparando
			Cnoh_ant=Cnoh;
			Cnoh=Cnoh->prox_linha;		
		}	
		if((flag!=1) && (Lnoh != NULL) && (coluna>Lnoh->indice_coluna) && (Lnoh->prox_coluna == NULL) && (cab_coluna->noh_prox==NULL)){
			//indice coluna for maior que o da cedula-linha e a proxima cedula na coluna seja vazia, e a cedula do cabecalho coluna nao tenha sido criada
			noh_new=aloca_noh(noh_new,valor,linha,coluna);
			noh_new->prox_coluna=NULL;
			noh_new->prox_linha=NULL;
			Lnoh->prox_coluna=noh_new;
			cab_coluna->noh_prox=noh_new;
			flag=1;
		}
		if((flag!=1) && (Cnoh != NULL ) && (linha>Cnoh->indice_linha) && (Cnoh->prox_linha == NULL) && (cab_linha->noh_prox==NULL)){
			//indice linha for maior que o da cedula-coluna e a a cedula da proxima linha seja vazia, e o cabecalho da linha nao tenha uma cedula
			noh_new=aloca_noh(noh_new,valor,linha,coluna);
			noh_new->prox_coluna=NULL;
			noh_new->prox_linha=NULL;
			Cnoh->prox_linha=noh_new;
			cab_linha->noh_prox=noh_new;
			flag=1;
		}
		if((flag!=1) && (Cnoh!=NULL) && (cab_linha->noh_prox == NULL) && (cab_coluna->noh_prox != NULL) && (linha<Cnoh->indice_linha) && (Cnoh_ant == NULL)){
			//cedula do cabecalho linha nao tenha sido criada e o do cabecalho coluna ja tenha sido alocado, indice linha for menor que o da cedula-coluna e a cedula-coluna anterior seja vazia
			noh_new=aloca_noh(noh_new,valor,linha,coluna);
			noh_new->prox_linha=Cnoh;
			noh_new->prox_coluna=NULL;
			cab_linha->noh_prox=noh_new;
			cab_coluna->noh_prox=noh_new;
			flag=1;
		}
		if((flag!=1) && (Lnoh != NULL) && (cab_coluna->noh_prox == NULL) && (cab_linha->noh_prox != NULL) && (coluna<Lnoh->indice_coluna) && (Lnoh_ant == NULL)){
			//cedula do cabecalho coluna nao tenha sido criado e o do cabecalho linha ja tenha sido alocado, e o indice coluna for menor que o da cedula-linha e a cedula-linha anterior seja vazia
			noh_new=aloca_noh(noh_new,valor,linha,coluna);
			noh_new->prox_coluna=Lnoh;
			noh_new->prox_linha=NULL;
			cab_coluna->noh_prox=noh_new;
			cab_linha->noh_prox=noh_new;
			flag=1;
		}
		if((Cnoh!=NULL) && (linha==Cnoh->indice_linha)){
			//cedula-coluna nao seja vazio, e a linha seja igual ao da cedula-coluna
			flag_C=1;
		}
		if((Lnoh!=NULL) && (coluna==Lnoh->indice_coluna)){
			//cedula-linha nao seja vazia, e a coluna seja igual ao da cedula-linha
			flag_L=1;
		}
		if((Lnoh_ant!=NULL) && (Lnoh != NULL) && (coluna>Lnoh_ant->indice_coluna) && (coluna<Lnoh->indice_coluna)){//coluna parou no lugar certo
				
			flag_L=1;	
		}
		if((Cnoh_ant!=NULL) && (Cnoh != NULL) && (linha>Cnoh_ant->indice_linha) && (linha<Cnoh->indice_linha)){//linha parou no lugar certo	
			flag_C=1;	
		}
		if((flag!=1) && (Cnoh!=NULL) && (Lnoh!=NULL) && (linha == Cnoh->indice_linha) && (coluna == Lnoh->indice_coluna)){
			//impedir um erro de encadeadameno caso a posicao necessaria ja tenha sido alocada e precise apenas sobreescrever, no caso conflito entre testes
			flag_X=1;
		}
		if((flag!=1) && (flag_L==1) && (cab_coluna->noh_prox == NULL)){
			//minha posicao da cedula nova ja tenha sido achada na linha e o cabecalho da coluna nao tenha cedula alocada
			noh_new=aloca_noh(noh_new,valor,linha,coluna);
			noh_new->prox_coluna=Lnoh;
			noh_new->prox_linha=NULL;
			Lnoh_ant->prox_coluna=noh_new;
			cab_coluna->noh_prox=noh_new;
			flag=1;	
		}
		if((flag!=1) && (flag_C==1) && (cab_linha->noh_prox == NULL)){
			//minha posiicao da cedula nova ja tenha sido achada na coluna e meu cabecalho linha nao tenha cedula alocada
			noh_new=aloca_noh(noh_new,valor,linha,coluna);
			noh_new->prox_linha=Cnoh;
			noh_new->prox_coluna=NULL;
			Cnoh_ant->prox_linha=noh_new;
			cab_linha->noh_prox=noh_new;
			flag=1;	
		}	
		if((Lnoh_ant!=NULL) && (Cnoh_ant!=NULL)){//as cedulas anteriores sejam vazia, apenas uma cedula na linha e coluna
			if((flag!=1) && (Lnoh != NULL ) && (Cnoh != NULL) && (Lnoh->prox_coluna==NULL) && (coluna>Lnoh->indice_coluna) && (Cnoh->prox_linha==NULL) && (linha>Cnoh->indice_linha)){
				//linha e coluna vazia				
				noh_new=aloca_noh(noh_new,valor,linha,coluna);
				noh_new->prox_coluna=NULL;
				noh_new->prox_linha=NULL;
				Lnoh->prox_linha=noh_new;
				Cnoh->prox_coluna=noh_new;
				flag=1;		
			}
			if((flag!=1) && (flag_X!=1) && (flag_L == 1) && (flag_C == 1)){//posicao certa tenha sido achada
				noh_new=aloca_noh(noh_new,valor,linha,coluna);
				noh_new->prox_coluna=Lnoh;
				Cnoh_ant->prox_linha=noh_new;
				noh_new->prox_linha=Cnoh;
				Lnoh_ant->prox_coluna=noh_new;
				flag=1;
			}
			if((flag!=1) &&(Lnoh != NULL) && (Lnoh->prox_coluna==NULL) && (coluna>Lnoh->indice_coluna) && flag_C==1){
				//inserindo em uma linha com a proxima coluna vazia e a coluna com proxima linha preenchida
				noh_new=aloca_noh(noh_new,valor,linha,coluna);
				noh_new->prox_linha=Cnoh;
				Cnoh_ant->prox_linha=noh_new;
				noh_new->prox_coluna=NULL;
				Lnoh->prox_coluna=noh_new;
				flag=1;
			}
			if((flag!=1) &&(Cnoh != NULL) && (Cnoh->prox_linha==NULL) && (linha>Cnoh->indice_linha) && flag_L==1){
				//inserindo em uma coluna com a proxima linha vazia e a linha com proxima coluna preenchida
				noh_new=aloca_noh(noh_new,valor,linha,coluna);
				noh_new->prox_coluna=Lnoh;
				Lnoh_ant->prox_coluna=noh_new;
				noh_new->prox_linha=NULL;
				Cnoh->prox_linha=noh_new;
				flag=1;	
			}
		}
		if((Lnoh_ant == NULL) && (Cnoh_ant == NULL) && (flag!=1) &&(Cnoh!=NULL) && (Lnoh !=NULL) && (linha>Cnoh->indice_linha) && (Cnoh->prox_linha==NULL) && (coluna>Lnoh->indice_coluna) && (Lnoh->prox_coluna==NULL)){
			//indice linha for maior que o da cedula-coluna e a proxima linha da cedula seja vazia, indice coluna seja maior que o da cedula-linha e a proxima cedula linha seja vazia
			noh_new=aloca_noh(noh_new,valor,linha,coluna);
			noh_new->prox_linha=NULL;
			noh_new->prox_coluna=NULL;
			Lnoh->prox_coluna=noh_new;
			Cnoh->prox_linha=noh_new;
			flag=1;
		}
		if((flag!=1) && (Cnoh_ant == NULL) && (Cnoh!=NULL) && (linha<Cnoh->indice_linha) && (flag_L == 1)){
			//indice linha seja menor que o da cedula-coluna e a posicao certa na linha ja tenha sido encontrada
			noh_new=aloca_noh(noh_new,valor,linha,coluna);
			noh_new->prox_linha=Cnoh;
			noh_new->prox_coluna=Lnoh;
			Lnoh_ant->prox_coluna=noh_new;
			cab_coluna->noh_prox=noh_new;
			flag=1;
		}
		if((flag!=1) && (Lnoh_ant == NULL) && (Lnoh != NULL) && (coluna<Lnoh->indice_coluna) && (flag_C == 1)){
			//indice coluna seja menor que o da cedula-linha e a posicao na coluna ja tenha sido achada
			noh_new=aloca_noh(noh_new,valor,linha,coluna);
			noh_new->prox_linha=Cnoh;
			noh_new->prox_coluna=Lnoh;
			Cnoh_ant->prox_linha=noh_new;
			cab_linha->noh_prox=noh_new;
			flag=1;
		}
		if((flag!=1) && (flag_X!=1) && (Lnoh_ant == NULL) && (flag_C == 1)){//linha so possui uma cedula
			noh_new=aloca_noh(noh_new,valor,linha,coluna);
			noh_new->prox_linha=Cnoh;
			noh_new->prox_coluna=NULL;
			Cnoh_ant->prox_linha=noh_new;
			Lnoh->prox_coluna=noh_new;
			flag=1;
		}
		if((flag!=1) && (flag_X!=1) && (Cnoh!=NULL) && (Cnoh_ant == NULL) && (flag_L ==1)){//coluna so possui uma cedula
			noh_new=aloca_noh(noh_new,valor,linha,coluna);
			noh_new->prox_coluna=Lnoh;
			noh_new->prox_linha=NULL;
			Lnoh_ant->prox_coluna=noh_new;
			Cnoh->prox_linha=noh_new;
			flag =1;	
		}
		if((flag!=1) &&(Cnoh_ant == NULL) && (cab_linha->noh_prox == NULL) && (cab_coluna->noh_prox != NULL)){
			//cabecalho linha nao possui cedula e a cedula do cabecalho coluna ja tenha sido alocada
			noh_new=aloca_noh(noh_new,valor,linha,coluna);
			noh_new->prox_linha=NULL;
			noh_new->prox_coluna=NULL;
			cab_linha->noh_prox=noh_new;
			cab_coluna->noh_prox=noh_new;
			flag=1;
		}
	}
	printf("[X]Movimento efetuado\n");
	                          
}

void anda(tipo_esparsa *esparsa){//funcao para andar com o personagem pela matriz
	FILE *file;
	char letra;
	int linha=0,coluna=0,cont=0,flag=0;
	file=fopen("passos-mtz.txt","w");
	fclose(file);
		
		
	while (flag!=1){
		printf("\n");
		printf("Painel de controle do personagem\n\tW=Andar pra cima\n\tA=Andar para a esquerda\n\tS=Andar pra baixo\n\tD=Andar para a direita\n\tE=Terminar caminhada\n");
	
		printf("Digite a letra correspondente a direcao: ");
		scanf(" %[^\n]s",&letra);
		
		file=fopen("passos-mtz.txt","a");
		switch(letra){
			case 'W'://para cima
				system("clear");
				linha--;
				if(linha<0){//posicao invalida < 0
					printf("[CUIDADO]Territorio inimigo\n[X]Movimento nao efetuado\n");
					linha++;
				}
				else{
					insere_mtz(&esparsa,linha,coluna,0);
				}
				fprintf(file,"[↑]Linha[%d]Coluna[%d]\n",linha,coluna);
				cont++;
				fclose(file);
				break;
			case 'A'://para a esquerda
				system("clear");
				coluna--;
				if(coluna<0){//posicao invalida < 0
					printf("[CUIDADO]Territorio inimigo\n[X]Movimento nao efetuado\n");
					coluna++;
				}
				else{
					insere_mtz(&esparsa,linha,coluna,0);
				}
				fprintf(file,"[←]Linha[%d]Coluna[%d]\n",linha,coluna);
				cont++;
				fclose(file);
				break;
			case 'S'://para baixo
				system("clear");
				linha++;
				insere_mtz(&esparsa,linha,coluna,0);
				fprintf(file,"[↓]Linha[%d]Coluna[%d]\n",linha,coluna);
				cont++;
				fclose(file);
				break;
			case 'D'://para a direita
				system("clear");
				coluna++;
				insere_mtz(&esparsa,linha,coluna,0);
				fprintf(file,"[→]Linha[%d]Coluna[%d]\n",linha,coluna);
				cont++;
				fclose(file);
				break;
			case 'E'://termina o percurso
				system("clear");
				printf("[X]Sua aventura chegou ao fim\n[X]Posicoes percorridas salvas no arquivo 'passos-mtz.txt'\n");
				flag=1;
				fclose(file);
				break;
		}

	}
	printf("\n");
	file=fopen("passos-mtz.txt","a");
	fprintf(file,"Total de movimentos[%d]\n",cont);
	fclose(file);

}
void opcao(tipo_esparsa *esparsa){
	int linha,coluna,opcao,valor;
	do{
			printf("1-Jogar\n2-Sair\n");
			printf("Opcao :");
			scanf("%d",&opcao);
			system("clear");
			switch(opcao){
				case 1:
					system("clear");
					anda(esparsa);
					break;
			}
		}while(opcao!=2);
}

					