#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"


int mult(int a, int b){
	return a*b;
}

int maxVal(int a, int b){
	return (a > b) ? a : b;
}

int minVal(int a, int b){
	return (a < b) ? a : b;
}

//Return the input image envolved with zero padding 
// input[i][j] -> matrixSize[i+1][j+1]
void zeroPadding(int *input, int *inputZeroPad, int inputSize){
	int arraySize = (inputSize+2);	
	//int *inputZeroPad = (int *) malloc(sizeof(int)*arraySize);
	int k = 0, k2 = 0;
	for (int i = 0; i < arraySize; ++i)
	{
		//offsets
		k = i*arraySize;
		k2 = (i-1)*inputSize;
		for (int j = 0; j < arraySize; ++j)
		{
			if((i != 0 && i != arraySize-1) && (j != 0 && j != arraySize-1)){				
				inputZeroPad[k+j] = input[k2+(j-1)];
			}
			else{
				inputZeroPad[k+j] = 0;
			}
		}				
	}
}


//Return the input image with zero padding in the both last line and column
//The gols is to resize the odd inputSize to an even value
void zeroPaddingLastLineCol(int *input, int *inputZeroPad, int inputSize){
	int arraySize = (inputSize+1);	
	//int *inputZeroPad = (int *) malloc(sizeof(int)*arraySize);
	int k = 0, k2 = 0;
	for (int i = 0; i < arraySize; ++i)
	{
		//offsets
		k = i*arraySize;
		k2 = i*inputSize;
		for (int j = 0; j < arraySize; ++j)
		{
			if(i != arraySize-1 && j != arraySize-1){
				inputZeroPad[k+j] = input[k2+j];
			}
			else{
				inputZeroPad[k+j] = 0;
			}
		}				
	}		
}

/* Operacao de convolucao com duas matrizes a e b */
int convolv(int* a, int* b, int fSize){
	int i, j, result = 0;
	for(i = 0; i < fSize; i++){
		result += a[i]*b[i];
	}
	return result;
}

void initVector(int* a, int dim){
	for(int i = 0; i < dim; ++i){
		a[i] = 0;
	}
}

int* sumVectors(int* a, int* b, int dim){
	int* res;
	res = malloc(dim * sizeof(int*));
	int cont;
	for (cont = 0; cont < dim; cont++){
		res[cont] = a[cont] + b[cont];
	}
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

void testFunc(int a, int *res){
	*res = a+1;
}


// int main(){
// 	int res = 0;
// 	testFunc(2, &res);
// 	printf("%d\n", res);
// 	return 0;
// }
