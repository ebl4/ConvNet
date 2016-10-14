#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"


int mult(int a, int b){
	return a*b;
}

/* Operacao de convolucao com duas matrizes a e b */
int convolv(int* a, int* b, int fSize){
	int i, j, result = 0;
	for(i = 0; i < fSize; i++){
		result += a[i]*b[i];
	}
	return result;
}

int* sumVectors(int* a, int* b, int dim){
	int* res;
	res = malloc(dim * sizeof(int*));
	int cont;
	for (cont = 0; cont < dim; cont++){
		res[cont] = a[cont] + b[cont];
	}
	free(res);
	return res;
}

void sumMatrix(int* a, int* b, int* c, int m, int n){
	int i, j, k;
	for (i = 0; i < m; i++){
		k = i*n;
		for (j = 0; j < n; j++){
			c[k+j] = a[k+j] + b[k+j];
		}
	}
}

void multMatrix(int* a, int* b, int* c, int m, int n, int p){
	int i, j, l, k, somaprod;
	for(l = 0; l < m; l++){
		for (i = 0; i < n; i++){
			somaprod = 0;
			for (j = 0; j < p; j++){
				somaprod += a[l*m+j]*b[i+j*p];
			}
			c[m*l+i] = somaprod;
		}
	}
}
