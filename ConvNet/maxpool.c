#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include "matrix.c"
#define FILTER_SIZE 4


int max(int * array, int dim){	
	int max = INT_MIN;
	for (int i = 0; i < dim; ++i)
	{
		if (array[i] > max) max = array[i];
	}
	return max;
}

//make filters 2x2 pointed to input
void makeFilter(int *input, int inputSize, int* filter, int startLine, int startCol){	
	int lineOne = startLine*inputSize;
	int lineTwo = (startLine+1)*inputSize;
	filter[0] = input[lineOne+startCol];
	filter[1] = input[lineOne+startCol+1];

	filter[2] = input[lineTwo+startCol];
	filter[3] = input[lineTwo+startCol+1];

	//return filter;
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

//Make max pooling with 2x2 filters
void maxPooling(int *input, int *result, int inputSize){
	int slices = 0, startLine = -2, startCol = 0;
	slices = (inputSize/2);

	int * filter = (int *) malloc(sizeof(int)*FILTER_SIZE); 
	//int *result = (int *) malloc(sizeof(int)*slices*slices);
	if(inputSize%2 == 0){
		
		for (int i = 0; i < slices*slices; ++i)
		{
			if(i%slices == 0) startLine = startLine+2;
			startCol = (i%slices)*2;
			makeFilter(input, inputSize, filter, startLine, startCol);
			result[i] = max(filter, FILTER_SIZE);
		}
	}
}


int main()
{
	int a[16] = {-3, -2 ,-6, -1,
				3, 2 ,6, 1,
				3, 2 ,6, 1,
				-3, 2 ,-6, -1};
	int *result = (int *) malloc(sizeof(int)*2*2);
	int *zeroPaddingM = (int *) malloc(sizeof(int)*6*6);

	//maxPooling(a, result, 4);

	//new matrix 6x6 zero padding
	zeroPadding(a, zeroPaddingM, 4);
	//printf("%d\n", result[3]);

	printf("%d\n", zeroPaddingM[0]);
	printf("%d\n", zeroPaddingM[8]);

	free(result);
	return 0;
}