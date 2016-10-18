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