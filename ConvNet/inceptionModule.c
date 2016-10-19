#include <stdio.h>
#include <stdlib.h>
#include "conv.c"

void naiveInception(int **input, int **output, int*** filters, int* filterSize, int* depths, int numFilters){
	//5x5 convolution
	simpleFilterConvolution(input, filter[0], 0, inputSize, filterSize[0], depths[0], 1);
	//3x3 convolution
	simpleFilterConvolution(input, filter[1], 0, inputSize, filterSize[1], depths[1], 1);
	//1x1 convolution
	simpleFilterConvolution(input, filter[2], 0, inputSize, filterSize[2], depths[2], 1);
	
	for(int i = 0; i < numFilters; ++i){
		
	}
}

int main(){

}