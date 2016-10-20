#include <stdio.h>
#include <stdlib.h>
#include "depthConcat.c"
#include "matrix.c"
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

void initStrides(int *strides, int stridesArraySize, int numStrides){
	for(int i = 0; i < stridesArraySize; ++i){
		strides[i] = numStrides;
	}
}

void initPaddings(int *paddings, int paddingArraySize, int numPaddings){
	for(int i = 0; i < paddingArraySize; ++i){
		paddings[i] = numPaddings;
	}
}

void initSlices(int *slices, int inputSize, int numSlices, int *filterSize, int *paddings, int *strides){
	for(int i = 0; i < numSlices; ++i){
		slices[i] = spatialSize(inputSize, filterSize[i], paddings[i], strides[i]);
	}
}

void naiveInception(int **input, int **output, int inputSize, int ****filters, int *numFilters, int numWeigths, int* filterSize, int* depths, int **biases){
	int numWeigthsPerConv, numWeigthsConvOne = 0, remain = 0, stride = 1, dimOutputConcat = 0, numFiltersConcat = 0;
	//int *numFilters = (int *) malloc(sizeof(int)*NUM_CONV);
	int ***result = (int ***) malloc(sizeof(int**)*NUM_CONV);
	int *slices = (int *) malloc(sizeof(int**)*NUM_CONV);
	int *strides = (int *) malloc(sizeof(int**)*NUM_CONV);
	int *paddings = (int *) malloc(sizeof(int**)*NUM_CONV);
	int ***outputConcat = (int ***) malloc(sizeof(int**)*(NUM_CONV-1));

	if(numWeigths%MULT_SIZE_WEIGTHS == 0){
		numWeigthsPerConv = numWeigths/MULT_SIZE_WEIGTHS;
		///initNumFilters(numFilters);
	}
	else{
		remain = numWeigths%MULT_SIZE_WEIGTHS;
		numWeigthsPerConv = (numWeigths - remain)/MULT_SIZE_WEIGTHS;
	}	
	numWeigthsConvOne = numWeigthsPerConv+remain;
	
	initStrides(strides, NUM_CONV, 1);
	initPaddings(paddings, NUM_CONV, 0);
	initSlices(slices, inputSize, NUM_CONV, filterSize, paddings);

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

	output = outputConcat[1];
}

// This function assumes no zero padding in any input and the same stride value for each convolution
// And all input has depth equal to 3 as such as every filter in RGB color
void inception(int **input, int **output, int inputSize, int *outputSize, int ****filters, int *numFilters, int numWeigths, int* filterSize, int* depths, int **biases){
	int numWeigthsPerConv, numWeigthsConvOne = 0, remain = 0, stride = 1, dimOutputConcat = 0, numFiltersConcat = 0;
	//int *numFilters = (int *) malloc(sizeof(int)*NUM_CONV);
	int ***result = (int ***) malloc(sizeof(int**)*NUM_CONV);
	int *slices = (int *) malloc(sizeof(int**)*NUM_CONV);
	int *strides = (int *) malloc(sizeof(int**)*NUM_CONV);
	int *paddings = (int *) malloc(sizeof(int**)*NUM_CONV);
	int ***outputConcat = (int ***) malloc(sizeof(int**)*(NUM_CONV-1));

	if(numWeigths%MULT_SIZE_WEIGTHS == 0){
		numWeigthsPerConv = numWeigths/MULT_SIZE_WEIGTHS;
		///initNumFilters(numFilters);
	}
	else{
		remain = numWeigths%MULT_SIZE_WEIGTHS;
		numWeigthsPerConv = (numWeigths - remain)/MULT_SIZE_WEIGTHS;
	}	
	numWeigthsConvOne = numWeigthsPerConv+remain;
	
	initStrides(strides, NUM_CONV, 1);
	initPaddings(paddings, NUM_CONV, 0);
	initSlices(slices, inputSize, NUM_CONV, filterSize, paddings);

	//1x1 convolution
	result[0] = multiFilterConvolution(input, filters[0], biases[0], numFilters[0], inputSize, 1, depths[0], stride);

	//second 1x1 convolution
	result[1] = multiFilterConvolution(input, filters[1], biases[1], numFilters[1], inputSize, 1, depths[1], stride);

	//thrid convolution 1x1
	result[2] = multiFilterConvolution(input, filters[2], biases[2], numFilters[2], inputSize, 1, depths[2], stride);

	//maxpool 3x3 1(S)
	//result[3] = maxPooling(int *input, int *result, int inputSize);

	int resultSizeConv1 = spatialSize(inputSize, 1, 0, stride);

	int resultSizeMaxPool = spatialSize(inputSize, 3, 0, stride);

	//3x3 convolution
	result[4] = multiFilterConvolution(result[1], filters[4], biases[4], numFilters[4], resultSizeConv1, 3, depths[4], stride);


	//5x5 convolution
	result[5] = multiFilterConvolution(result[2], filters[5], biases[5], numFilters[5], resultSizeConv1, 5, depths[5], stride);
	
	//1x1 convolution
	result[6] = multiFilterConvolution(result[3], filters[6], biases[6], numFilters[6], resultSizeMaxPool, 1, depths[6], stride);
	//3x3 max pooling

	
	depthConcatLayers(result[0], result[4], outputConcat[0], numFilters[0], numFilters[4], slices[0], slices[4]);
	depthConcatLayers(result[5], result[6], outputConcat[1], numFilters[5], numFilters[6], slices[5], slices[6]);


	dimOutputConcat1 = max(slices[0], slices[4]);
	dimOutputConcat2 = max(slices[5], slices[6]);
	dimOutputConcatRes = max(dimOutputConcat1, dimOutputConcat2);

	numFiltersConcat1 = numFilters[0] + numFilters[4];	
	numFiltersConcat2 = numFilters[5] + numFilters[6];	
	numFiltersConcatSum = numFiltersConcat1 + numFiltersConcat2;


	outputConcat[2] = (int **) malloc(sizeof(int*)*numFiltersConcatSum);


	depthConcatLayers(outputConcat[0], outputConcat[1], outputConcat[2], numFiltersConcat1, numFiltersConcat2, dimOutputConcat1, dimOutputConcat2);

	output = outputConcat[2];
	*outputSize = dimOutputConcatRes;
}

int main(){

return 0;
}