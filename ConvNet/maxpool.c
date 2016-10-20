#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
//#include "matrix.c"
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


void maxPoolingProcess(int *input, int *result, int *filter, int inputSize, int slices){	
	int startLine = -2, startCol = 0;
	for (int i = 0; i < slices*slices; ++i)
	{
		if(i%slices == 0) startLine = startLine+2;
		startCol = (i%slices)*2;
		makeFilter(input, inputSize, filter, startLine, startCol);
		result[i] = max(filter, FILTER_SIZE);
	}
}

//Make max pooling with 2x2 filters
void maxPooling(int *input, int *result, int inputSize){
	int slices = 0;	
	int * filter;
	filter = (int *) malloc(sizeof(int)*FILTER_SIZE); 
	//int *result = (int *) malloc(sizeof(int)*slices*slices);
	
	if(inputSize%2 == 0){
		printf("Here normal\n");		
		slices = (inputSize/2);
		maxPoolingProcess(input, result, filter, inputSize, slices);
	}
	else{						
		printf("Here padding\n");
		int inputZeroPadSize = inputSize+1;
		slices = inputZeroPadSize/2;
		int * inputZeroPad = (int *) malloc(sizeof(int)*inputZeroPadSize);		
		zeroPaddingLastLineCol(input, inputZeroPad, inputSize);		
		maxPoolingProcess(inputZeroPad, result, filter, inputZeroPadSize, slices);
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

	maxPooling(a, result, 5);

	//new matrix 6x6 zero padding
	//zeroPadding(a, zeroPaddingM, 4);
	//zeroPaddingLastLineCol(a, zeroPaddingM, 4);
	printf("%d\n", result[8]);

	//printf("%d\n", zeroPaddingM[0]);
	//printf("%d\n", zeroPaddingM[4]);

	free(result);
	return 0;
}