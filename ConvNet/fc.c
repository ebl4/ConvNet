#include <stdio.h>
#include <stdlib.h>
#include "conv.c"

int fullyConnected(int** input, int** filter, int bias, int inputSize, int filterSize, int depths, int stride){
	int *resultM;
	int slide = spatialSize(inputSize, filterSize, 0, stride);
	int slideVector = slide*slide, result = 0;
	resultM = (int *) malloc(sizeof(int)*slideVector);

	resultM = simpleFilterConvolution(input, filter, bias, inputSize, filterSize, depths, stride);
	
	for(int i = 0; i < slideVector; ++i){
		result += resultM[i];
		printf("Element matrix %d\n", resultM[i]);

	}
	return result;
}

void fullyConnectedLayer(int** input, int*** filter, int* biases, int numFilters, int inputSize, int filterSize, int depths, int stride){
	int *result;
	result = (int *) malloc(sizeof(int)*numFilters);
	for (int i = 0; i < numFilters; ++i)
		{			
			result[i] = fullyConnected(input, filter[i], biases[i], inputSize, filterSize, depths, stride);
		}			
	printf("Before %d\n", result[0]);
	printf("Before %d\n", result[1]);
}


int main(){

	int res, depths = 2, stride = 1, numFilters = 2;
	int **a, **b, ***c;
	int *m1, *m2, *m3, *biases, m = 3, n = 2;
	m1 = (int *) malloc(sizeof(int)*m*m);
	m2 = (int *) malloc(sizeof(int)*n*n);
	biases = (int *) malloc(sizeof(int)*numFilters);
	c = (int ***) malloc(sizeof(int**)*2);

	m1[0] = 2;m1[1] = 3;m1[2] = 3;	
	m1[3] = 2;m1[4] = 3;m1[5] = 2;		
	m1[6] = 3;m1[7] = 2;m1[8] = 2;	

	biases[0] = 1;biases[1] = 2; 
	b = allocateAllMatrix(depths, n);
	a = allocateAllMatrix(depths, m);
	c[0] = allocateAllMatrix(depths, n);
	c[1] = allocateAllMatrix(depths, n);

	fullyConnectedLayer(a, c, biases, numFilters, m, n, depths, stride);

	free(b);free(a);
	free(m1);free(m2);

	return 0;

}