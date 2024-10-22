#include "mat.h"
#include "msgassert.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

void criaMatriz(mat_tipo * mat, int tx, int ty, int id) {
  
  erroAssert(tx>0,"Dimensao nula");
  erroAssert(ty>0,"Dimensao nula");
  erroAssert(tx<=MAXTAM,"Dimensao maior que permitido");
  erroAssert(ty<=MAXTAM,"Dimensao maior que permitido");

  
  mat->tamx = tx;
  mat->tamy = ty;
  
  mat->id = id;
}

void inicializaMatrizNula(mat_tipo * mat) {

  int i, j;
  
  for (i=0; i<MAXTAM; i++){
    for(j=0; j<MAXTAM; j++){
      mat->m[i][j] = 0;
    }
  }
}

void inicializaMatrizAleatoria(mat_tipo * mat) {
  int i, j;
  
  inicializaMatrizNula(mat);

  for (i=0; i<mat->tamx; i++){
    for(j=0; j<mat->tamy; j++){
      mat->m[i][j] = drand48()*INITRANDOMRANGE;
    }
  }
}

double acessaMatriz(mat_tipo * mat) {

  int i, j;
  double aux, s=0.0;
  for (i=0; i<mat->tamx; i++){
    for(j=0; j<mat->tamy; j++){
      aux = mat->m[i][j];
      s+=aux;
    }
  }
  return s; 
}

void imprimeMatriz(mat_tipo * mat) {
  int i,j;

  erroAssert(mat->tamx<=MAXTAM,"Dimensao maior que permitido");
  erroAssert(mat->tamy<=MAXTAM,"Dimensao maior que permitido");

  printf("%9s"," ");
  for(j=0; j<mat->tamy; j++)
    printf("%8d ",j);
  printf("\n");

  for (i=0; i<mat->tamx; i++){
    printf("%8d ",i);
    for(j=0; j<mat->tamy; j++){
      printf("%8.2f ",mat->m[i][j]);
    }
    printf("\n");
  }
}

void salvaMatriz(mat_tipo * mat, FILE * out) {
  int i,j;

  erroAssert(mat->tamx<=MAXTAM,"Dimensao maior que permitido");
  erroAssert(mat->tamy<=MAXTAM,"Dimensao maior que permitido");

  fprintf(out,"%d %d\n",mat->tamx,mat->tamy);
 
  for (i=0; i<mat->tamx; i++){
    for(j=0; j<mat->tamy; j++){
      fprintf(out, "%.6f ",mat->m[i][j]);
    }
    fprintf(out,"\n");
  }
}

void escreveElemento(mat_tipo * mat, int x, int y, double v) {

  erroAssert((x<0)||(x>=mat->tamx),"Indice invalido");
  erroAssert((y<0)||(y>=mat->tamy),"Indice invalido");

  mat->m[x][y] = v;
}

double leElemento (mat_tipo * mat, int x, int y) {

  erroAssert((x<0)||(x>=mat->tamx),"Indice invalido");
  erroAssert((y<0)||(y>=mat->tamy),"Indice invalido");

  return mat->m[x][y];
}

void copiaMatriz(mat_tipo *src, mat_tipo * dst, int dst_id) {

  int i,j;

  criaMatriz(dst,src->tamx, src->tamy,dst_id);

  inicializaMatrizNula(dst);

  for (i=0; i<src->tamx; i++){
    for(j=0; j<src->tamy; j++){
      dst->m[i][j] = src->m[i][j];
    }
  }
}

void somaMatrizes(mat_tipo *a, mat_tipo *b, mat_tipo *c) {

  int i,j;

  erroAssert(a->tamx==b->tamx,"Dimensoes incompativeis");
  erroAssert(a->tamy==b->tamy,"Dimensoes incompativeis");


  criaMatriz(c,a->tamx, a->tamy, c->id);
  inicializaMatrizNula(c);

  for (i=0; i<a->tamx; i++){
    for(j=0; j<a->tamy; j++){
      c->m[i][j] = a->m[i][j]+b->m[i][j];
    }
  }
}

void multiplicaMatrizes(mat_tipo *a, mat_tipo *b, mat_tipo *c) {

  int i,j,k;
  
  erroAssert(a->tamy==b->tamx,"Dimensoes incompativeis");

  criaMatriz(c,a->tamx, b->tamy,c->id);
  inicializaMatrizNula(c);

  for (i=0; i<c->tamx;i++){
    for (j=0; j<c->tamy;j++){
      for (k=0; k<a->tamy;k++){
        c->m[i][j] += a->m[i][k]*b->m[k][j];
      }
    }
  }
}

void transpoeMatriz(mat_tipo *a) {
  int i,j,dim;
  
  dim = (a->tamx>a->tamy?a->tamx:a->tamy);

  for (i=0; i<dim; i++){
    for(j=i+1; j<dim; j++){
      ELEMSWAP((a->m[i][j]),(a->m[j][i]));
    }
  }

  ELEMSWAP(a->tamx,a->tamy);
}

void destroiMatriz(mat_tipo *a) {

  avisoAssert(((a->tamx>0)&&(a->tamy>0)),"Matriz já foi destruida");

  a->id = a->tamx = a->tamy = -1;
}
