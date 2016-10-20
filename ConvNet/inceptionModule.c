#include <stdio.h>
#include <stdlib.h>
#include "depthConcat.c"
#define MULT_SIZE_WEIGTHS 132
#define NUM_CONV 4

//MULT_SIZE_WEIGTHS represents the size factor of filters in all convolution

// void initWeigthsConv(int **weigths, int weigthsSize, int numWeigths, int start, int end, int dimConv, int depths){
// 	int total = end-start;
// 	int filterSize = dimConv*dimConv;
// 	for (int i = 0; i < depths; ++i)
// 	{
// 		for (int j = 0; j < filterSize; ++j)
// 		{
// 			filter[] = weigths[]
// 		}
// 	}
// }


void initNumFilters(int *numFilters, int numWeigths, int numFiltersSize){
	for (int i = 0; i < numFiltersSize; ++i)
	{
		numFilters[i] = numWeigths;
	}
}

void convolutionPart(int** input, int*** filter, int* biases, int numFilters, 
	int inputSize, int filterSize, int depths, int stride){	

}

void naiveInception(int **input, int **output, int inputSize, int ****filters, int *numFilters, int numWeigths, int* filterSize, int* depths, int **biases){
	int numWeigthsPerConv, numWeigthsConvOne = 0, remain = 0, stride = 1, dimOutputConcat = 0, numFiltersConcat = 0;
	//int *numFilters = (int *) malloc(sizeof(int)*NUM_CONV);
	int ***result = (int ***) malloc(sizeof(int**)*NUM_CONV);
	int *slices;
	int ***outputConcat;

	if(numWeigths%MULT_SIZE_WEIGTHS == 0){
		numWeigthsPerConv = numWeigths/MULT_SIZE_WEIGTHS;
		///initNumFilters(numFilters);
	}
	else{
		remain = numWeigths%MULT_SIZE_WEIGTHS;
		numWeigthsPerConv = (numWeigths - remain)/MULT_SIZE_WEIGTHS;
	}	
	numWeigthsConvOne = numWeigthsPerConv+remain;

	//5x5 convolution
	result[0] = multiFilterConvolution(input, filters[0], biases[0], numFilters[0], inputSize, filterSize[0], depths[0], stride);
	//3x3 convolution
	result[1] = multiFilterConvolution(input, filters[1], biases[1], numFilters[1], inputSize, filterSize[1], depths[1], stride);
	//1x1 convolution
	result[2] = multiFilterConvolution(input, filters[2], biases[2], numFilters[2], inputSize, filterSize[2], depths[2], stride);
	//3x3 max pooling
	
	depthConcatLayers(result[0], result[1], outputConcat[0], numFilters[0], numFilters[1], slices[0], slices[1]);
	dimOutputConcat = max(slices[0], slices[1]);
	numFiltersConcat = numFilters[0] + numFilters[1];	
	outputConcat[1] = (int **) malloc(sizeof(int*)*(numFiltersConcat + numFilters[2]));
	depthConcatLayers(outputConcat[0], result[2], outputConcat[1], numFiltersConcat, numFilters[2], dimOutputConcat, slices[2]);

}


int main(){

return 0;
}