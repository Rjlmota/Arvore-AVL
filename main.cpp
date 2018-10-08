#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <string>
using namespace std;

typedef struct tipo_no{
  int chave;
  struct tipo_no *esq;
  struct tipo_no *dir;
  int fb;
}no;

void inserirNo(no **p0, int chave);
void balancear(no **p0);
int altura(no *p0);
void rotacaoDireita(no **p0);
void rotacaoEsquerda(no **p0);
no *removerNo(no **p0, int chave);
void *buscarNo(no *p0, int chave);
void print_arv(no* p, int espaco);

int main() {
  no *p0=NULL;

}

void inserirNo(no **p0, int chave){
  no *p1=NULL, *p2=NULL;
  p1 = *p0;
  if (p1 == NULL){
    p1 = (no*)malloc(sizeof(no));
    p1->chave = chave;
    p1->esq = NULL;
    p1->dir = NULL;
    p1->fb = 0;
    *p0 = p1;
  }else{
    while (p1!=NULL){
      p2 = p1;
      if (chave > p1->chave)
        p1 = p1->dir;
      else
        p1 = p1->esq;
    }
    p1 = (no*)malloc(sizeof(no));
    p1->chave = chave;
    p1->esq = NULL;
    p1->dir = NULL;
    p1->fb = 0;
    if (chave > p2->chave)
      p2->dir = p1;
    else
      p2->esq = p1;
  }
  print_arv(*p0, 0);
  balancear(p0);
  cout << " ----- " << endl;
}

void balancear(no **p0){
  if ((*p0) != NULL){
    balancear(&((*p0)->esq));
    balancear(&((*p0)->dir));
    (*p0)->fb = altura((*p0)->esq) - altura((*p0)->dir);
    if ((*p0)->fb > 1){
      cout << "\nBalanceando...\n";
      if ((*p0)->esq->fb == -1)
        rotacaoEsquerda(&((*p0)->esq));
      rotacaoDireita(p0);
    }else if ((*p0)->fb < -1){
      cout << "\n -----\nBalanceando...\n";
      if ((*p0)->dir->fb == 1)
        rotacaoDireita(&((*p0)->dir));
      rotacaoEsquerda(p0);
    }
  }
}

int altura(no *p0){
  int esq, dir;
  if (p0 == NULL){
    return 0;
  }else{
    esq = 1 + altura(p0->esq);
    dir = 1 + altura(p0->dir);
    if (esq>dir)
      return esq;
    return dir;
  }
}

void rotacaoDireita(no **p0){
  no *p1=NULL, *p2=NULL;
  p1 = (*p0)->esq;
  p2 = p1->dir;
  p1->dir = (*p0);
  (*p0)->esq = p2;
  (*p0)->fb = 0;
  p1->fb = 0;
  (*p0) = p1;
}

void rotacaoEsquerda(no **p0){
  no *p1=NULL, *p2=NULL;
  p1 = (*p0)->dir;
  p2 = p1->esq;
  p1->esq = (*p0);
  (*p0)->dir = p2;
  (*p0)->fb = 0;
  p1->fb = 0;
  (*p0) = p1;
}

no *removerNo(no **p0, int chave){
  no *p1=NULL;
  if ((*p0) == NULL){
    cout << "\nNo nao existe\n\n";
  }else if (chave < (*p0)->chave){
    (*p0)->esq = removerNo(&((*p0)->esq), chave);
  }else if (chave > (*p0)->chave){
    (*p0)->dir = removerNo(&((*p0)->dir), chave);
  }else{
    if(((*p0)->esq==NULL)||((*p0)->dir==NULL)){
      if ((*p0)->esq!=NULL)
        p1 = (*p0)->esq;
      else
        p1 = (*p0)->dir;
      if (p1==NULL){
        p1 = (*p0);
        (*p0) = NULL;
      }else{
        **p0 = *p1;
      }
      free(p1);
    }else{
      p1 = (*p0)->dir;
      while(p1->esq!=NULL)
        p1 = p1->esq;
      (*p0)->chave = p1->chave;
      (*p0)->dir = removerNo(&((*p0)->dir), p1->chave);
    }
  }
  print_arv((*p0), 0);
  balancear(p0);
  cout << " ----- " << endl;
  return (*p0);
}

void *buscarNo(no *p0, int chave){
  string caminho = "Raiz";
  while(p0!=NULL){
    if (p0->chave == chave){
      break;
    }else if (chave > p0->chave){
      p0 = p0->dir;
      caminho += " - Direita";
    }else if (chave < p0->chave){
      p0 = p0->esq;
      caminho +=" - Esquerda";
    }
  }
  if (p0==NULL){
    cout << "\nNo Nao Existe.\n\n";
  }else{
    cout << "\n" << caminho << ".\n\n";
  }
}

void print_arv(no *p0, int espaco){
  if(p0!=NULL){
    if(p0->dir)
        print_arv(p0->dir, espaco+5);
    if (espaco)
        cout << setw(espaco) << ' ';
    if (p0->dir) cout<<" /\n" << setw(espaco) << ' ';
    cout << p0->chave << "\n ";
    if(p0->esq){
        cout << setw(espaco) << ' ' <<" \\\n";
        print_arv(p0->esq, espaco+5);
    }
  }
}
