#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include "matrix.c"
//#include "conv.c"
#define FILTER_SIZE 4


int max(int * array, int dim){	
	int max = INT_MIN;
	for (int i = 0; i < dim; ++i)
	{
		if (array[i] > max) max = array[i];
	}
	return max;
}

int avg(int * array, int dim){
	int result = 0;
	for (int i = 0; i < dim; ++i)
	{
		result += array[i];
	}
	return result/dim;
}

//make filters 3x3 pointed to input
void makeFilter3x3(int *input, int inputSize, int* filter, int startLine, int startCol){
	int lineOne = startLine*inputSize;
	int lineTwo = (startLine+1)*inputSize;
	int lineThree = (startLine+2)*inputSize;

	filter[0] = input[lineOne+startCol];
	filter[1] = input[lineOne+startCol+1];
	filter[2] = input[lineOne+startCol+2];
	
	filter[3] = input[lineTwo+startCol];	
	filter[4] = input[lineTwo+startCol+1];	
	filter[5] = input[lineTwo+startCol+2];	

	filter[6] = input[lineThree+startCol];
	filter[7] = input[lineThree+startCol+1];
	filter[8] = input[lineThree+startCol+2];

}

//make filters 2x2 pointed to input
void makeFilter2x2(int *input, int inputSize, int* filter, int startLine, int startCol){	
	int lineOne = startLine*inputSize;
	int lineTwo = (startLine+1)*inputSize;
	filter[0] = input[lineOne+startCol];
	filter[1] = input[lineOne+startCol+1];

	filter[2] = input[lineTwo+startCol];
	filter[3] = input[lineTwo+startCol+1];

	//return filter;
}


//Option refers to max or avg pooling. Option equal to 1 than the function process the max pooling 
//otherwise make avg pooling
void poolingProcess(int *input, int *result, int *filter, int inputSize, int filterSize, int slices, int option){	
	int startLine = -filterSize, startCol = 0;
	for (int i = 0; i < slices*slices; ++i)
	{
		if(i%slices == 0) startLine = startLine+filterSize;
		startCol = (i%slices)*2;

		if(filterSize == 2) makeFilter2x2(input, inputSize, filter, startLine, startCol);
		else if(filterSize == 3) makeFilter3x3(input, inputSize, filter, startLine, startCol);

		if(option) result[i] = max(filter, filterSize);
		else result[i] = avg(filter, filterSize);
	}
}

//Make max pooling with 2x2 filters
void pooling(int *input, int *result, int inputSize, int filterSize, int stride, int option){
	int slices = 0;	
	int * filter;
	filter = (int *) malloc(sizeof(int)*filterSize); 
	if(((inputSize - filterSize)/stride)%2 == 0)
		slices = spatialSize(inputSize, filterSize, 0, stride);
		printf("Here normal\n");				
		poolingProcess(input, result, filter, inputSize, slices);
	else {
		slices = spatialSize(inputSize, filterSize, 1, stride);
		zeroPaddingLastLineCol(input, inputZeroPad, inputSize);
		printf("Here padding\n");
		int inputZeroPadSize = inputSize+1;	
		int * inputZeroPad = (int *) malloc(sizeof(int)*inputZeroPadSize);					
		poolingProcess(inputZeroPad, result, filter, inputZeroPadSize, slices);
	}
		
}


void poolingDepths(int **input, int **result, int inputSize, int filterSize, int stride, int depths, int option){
	for (int i = 0; i < depths; ++i)
	{
		pooling(input[i], result[i], inputSize, filterSize, stride, option);
	}
}


int main()
{		
	int a[25] = {-3, -2 ,-6, -1, 1,
				3, 2 ,6, 1, 1,
				3, 2 ,6, 1, 1,
				3, 2 ,6, 1, 1,
				-3, 2 ,-6, -1, 1};
	int slices = 3;
	int *result = (int *) malloc(sizeof(int)*3*3);
	//int *zeroPaddingM = (int *) malloc(sizeof(int)*5*5);
	
	//pooling(a, result, 5);

	//new matrix 6x6 zero padding
	//zeroPadding(a, zeroPaddingM, 4);
	//zeroPaddingLastLineCol(a, zeroPaddingM, 4);
	printf("%d\n", result[8]);

	//printf("%d\n", zeroPaddingM[0]);
	//printf("%d\n", zeroPaddingM[4]);

	free(result);
	return 0;
}