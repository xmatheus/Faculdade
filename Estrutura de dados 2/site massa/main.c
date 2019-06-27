/* Conjunto de funcoes para manipular arvore binaria de busca com balanceamento AVL.
Uma arvore binaria pode ser definida como segue:
- Consiste de um conjunto de nos, cada um ligado a no maximo um no pai e no maximo dois nos filhos, um aah esquerda e outra aah direita;
- Ha apenas um no sem pai
- Os filhos de cada no sao distintos
- Todos os nós de uma árvore AVL possui diferenças entre alturas (esq - dir) entre -1 e 1. 
*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define invalido -1

typedef struct no {
  int chave;
  int altura;     // altura do no na arvore
  struct no *dir,*esq;
  
} tipoNo;

//Variaveis globais
int rotacao_count=0;
bool teste;


// Retornar a altura do nó
int qualAltura(tipoNo* x) {
  if (x == NULL) return -1; 
  else return x->altura;
}
/*
Operacao de rotacao para direita. O no x eh a raiz da sub-arvore a ser rotacionada
*/
tipoNo* rotacaoDir(tipoNo *p) {

  tipoNo* q = p->esq;

  p->esq = q->dir;
  q->dir = p;

  q->altura = 1 + MAX(qualAltura(p->esq),qualAltura(p->dir));
  p->altura = 1 + MAX(qualAltura(q->esq),qualAltura(q->dir));
  if (teste)rotacao_count++;
  return q;
  
}

/*
Operacao de rotacao para esquerda. O no x eh a raiz da sub-arvore a ser rotacionada
*/
tipoNo* rotacaoEsq(tipoNo *p) {

  tipoNo* q = p->dir;

  p->dir = q->esq; //seria o temp do slide
  q->esq = p;

  p->altura = 1 + MAX(qualAltura(p->esq),qualAltura(p->dir));
  q->altura = 1 + MAX(qualAltura(q->esq),qualAltura(q->dir));
  if (teste)rotacao_count++;
  return q;
  
}

/*
Aloca espaco para uma nova chave a ser inserida na arvore, devolvendo o ponteiro para o no correspondente
 */
tipoNo* criaNo(int chave) {

    tipoNo* novoNo = malloc(sizeof(tipoNo));
    
    novoNo->chave = chave;
    novoNo->esq = NULL;
    novoNo->dir = NULL;

    novoNo->altura = 0;
    return novoNo;
}
    // apos insercao de um novo noh, ajusta-se a altura e verifica a necessidade de balanceamento
    // o +1 é pq estamos ajustando a altura do pai pela altura do filho
tipoNo* bal (tipoNo* raiz)  {
  int fBal, fBalFilho;
    raiz->altura = 1 + MAX(qualAltura(raiz->esq),qualAltura(raiz->dir));

    fBal = qualAltura(raiz->esq) - qualAltura(raiz->dir); // fator de balanceamento do noh

    if (fBal == 2) { // desbalanceamento pela esquerda
      fBalFilho = qualAltura(raiz->esq->esq) - qualAltura(raiz->esq->dir);
      if (fBalFilho == 1) // filho desbalanceado pela esquerda
	      raiz = rotacaoDir(raiz); 
      else if (fBalFilho == -1) { // filho desbalanceado pela direita
	      raiz->esq = rotacaoEsq(raiz->esq); 
	      raiz = rotacaoDir(raiz);
      }
    } else if (fBal == -2) { // desbalanceamento pela direita
        fBalFilho = qualAltura(raiz->dir->esq) - qualAltura(raiz->dir->dir);
      if (fBalFilho == -1)  // filho desbalanceado pela direita
	      raiz = rotacaoEsq(raiz);
      else if (fBalFilho == 1) { // filho desbalanceado pela esquerda
	      raiz->dir = rotacaoDir(raiz->dir);
	      raiz = rotacaoEsq(raiz);
      }
    }return raiz;
  }
  
  
/*
Insere um novo no. A implementacao eh recursiva (nao ha necessidade de ter ponteiro para no pai).
 */
tipoNo* insereAVL(int chave, tipoNo *raiz) {

  int fBal, fBalFilho;

  if (raiz == NULL) { // insercao de um novo no como folha (caso base da recursao)
    return bal(criaNo(chave));
    
  }
  else { // descida na arvore para insercao

    if (chave < raiz->chave) {
       raiz->esq = insereAVL(chave,raiz->esq);
    } else if (chave > raiz->chave) {
       raiz->dir = insereAVL(chave,raiz->dir);
    } else {
      return raiz;
    }
    raiz=bal(raiz);
  }return raiz;
}

tipoNo* buscaMax (tipoNo *p){
  tipoNo *aux=p;
  if(p->esq==NULL) {return p;}
  else{
    p=p->esq;     
    buscaMax(p);
  }
}

tipoNo* removeAVL (int chave, tipoNo *raiz){

  if(raiz==NULL) return raiz;
  if(chave<raiz->chave) raiz->esq = removeAVL(chave, raiz->esq);
  else
  if(chave>raiz->chave) raiz->dir = removeAVL(chave, raiz->dir);
  else {
    // Achou a chave
    if(raiz->esq==NULL){
      tipoNo *ptr = raiz;
      raiz = raiz->dir;
      free(ptr);
    }
    else{
      tipoNo *suc = buscaMax(raiz->esq);
      if(suc == raiz->esq){
        tipoNo *ptr = raiz;
        suc->dir = raiz->dir;
        raiz = suc;
        free (ptr);
      } 
      else{
        raiz->chave = suc->chave;
        raiz->esq = removeAVL(raiz->chave, raiz->esq);
      }
    }
  } return raiz;
}
//Retorna a altura máxima da raiz
int altura2(tipoNo* raiz) {

  if (raiz) {
    return (1 + MAX(altura2(raiz->esq), altura2(raiz->dir)));   
  } else return 0;

}

void imprimePorNivel(tipoNo *raiz) {

  int n = pow(2,altura2(raiz)+1); // aloca espaço para uma árvore chei
  printf("\n n=%d\n",n);
  tipoNo *fila[n];
  int i = 0, f=0, j, l=1 , nl;
  int nonNULL = 0;
  fila[0] = raiz;
  nl = 1;
  for (; i<=f ; i++) {

    if (fila[i]) {
      printf("%d:(%d,%d)",l,fila[i]->chave,fila[i]->altura);
      fila[++f] = fila[i]->esq;
      fila[++f] = fila[i]->dir;
    } else {
    }
    if (i+1 == nl) {
      l++;
      nl = pow(2,l-1)+nl;
      printf("\n");
    }
  }
  j = 0;

}

tipoNo* inserir (tipoNo *tree){
  int x;
  
  FILE *file;
  file = fopen("inclui.txt", "r");
  
  if(file != NULL){
    while ( fscanf(file, "%i", &x) != invalido){
      printf("\n__Inserindo %d__ ",x);
      tree = insereAVL(x,tree);
      imprimePorNivel(tree);
    }
    printf(" \n__Fim do arquivo ""inclui.txt""__ \n");
  } 
  else {
    printf("Arquivo não pode ser aberto.");
  } 
  fclose(file);
  return tree;
}

tipoNo* remover (tipoNo *tree){
  
  int x;
  
  FILE *file;
  file = fopen("remove.txt", "r");
  
  if(file != NULL){
    while (fscanf(file, "%i", &x) != invalido){
      printf("\n __Removendo %d__",x);
      tree = removeAVL(x,tree);
      tree=bal(tree);
      imprimePorNivel(tree);
    }
    printf(" \n__Fim do arquivo ""remove.txt""__\n");
  } 
  else {
    printf("Arquivo não pode ser aberto. ");
  } 
  fclose(file);
  return tree;
}

void experimento (tipoNo *tree){
  int x;
  FILE *file;
  file = fopen("experimento.txt", "r");
  teste = 1;
  
  if(file != NULL){
    while (fscanf(file, "%i", &x) != invalido){
      printf("\n __Experimentando %d__",x);
      tree = insereAVL(x,tree);
    }
    printf(" \n__Fim do arquivo ""experimento.txt""__ \n");
  } 
  else {
    printf("Arquivo não pode ser aberto. ");
  } 
  fclose(file);
  printf("Foram feitas %d rotacoes", rotacao_count);
  teste=0;
  
}

int main () {
  char opcao;
  tipoNo *tree = NULL;
  printf("Funçâo desejada: \n");
  
  while(1){ 
   opcao=getc(stdin);
  switch(opcao){
      case 'i': 
        printf("\n_Inserção__ \n");
        tree=inserir(tree);
        break;
      case 'r': 
        printf("\n_Remoção__ \n");
        tree=remover(tree);
        break;
      case 'p': 
        printf("__Impressão__ \n");
        imprimePorNivel(tree);
        break;
      case 'e':
        printf("\n__Experimento__\n");
        teste=1;
        experimento(tree);
        rotacao_count=0;
        teste=0;
        break;
  }
 }
}