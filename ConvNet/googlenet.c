#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "inceptionModule.c"
#define NUM_OUTPUTS 9
#define FILTER_SIZE_MP_OUTPUT 7
#define FILTER_SIZE_MP_AUX 5
#define STRIDE_MPC 1
#define STRIDE_MP_AUX 3
#define AGV_POOL_OPT 0


int sumExponetial(int *array, int dim){
	int result = 0;
	for (int i = 0; i < dim; ++i)
	{
		result += exp(array[i]);
	}

	return result;
}

void softmax(int* array, int *newArrayNorm, int elto, int dim){
	int sumExponetialResult = sumExponetial(array, newArrayNorm, elto, dim);
	for (int i = 0; i < dim; ++i)
	{
		newArrayNorm[i] = array[i]/sumExponetial;
	}
}

void initOutputSize(int *outputSize, int numOutputs){
	for (int i = 0; i < numOutputs; ++i)
	{
		outputSize[i] = 0;
	}
}


void auxiliarClassifier(){
	pooling(input, output, inputSize, FILTER_SIZE_MPC, STRIDE_MPC, AGV_POOL_OPT);
	multiFilterConvolution();
	fc(input, filter, biases, numFilters, inputSize, filterSize, depths, stride);
	fc(input, filter, biases, numFilters, inputSize, filterSize, depths, stride);			
}

void outputClassifier(int **input, int **output, int inputSize, int ***filters, int numFilters, int* filterSize, int depths, int *biases){
	pooling(input, output, inputSize, FILTER_SIZE_MPC, STRIDE_MPC, AGV_POOL_OPT);	
	fc(input, filter, biases, numFilters, inputSize, filterSize, depths, stride);		
}

void description(int **input, int **output, int inputSize, int ****filters, int *numFilters, int numWeigths, int* filterSize, int* depths, int **biases){
	int **outputs = (int**) malloc(sizeof(int*)*NUM_OUTPUTS);
	int *outputSize = (int*) malloc(sizeof(int)*NUM_OUTPUTS);
	initOutputSize(outputSize, NUM_OUTPUTS);


	inception(input, output, inputSize, &outputSizeAux, ****filters, *numFilters, numWeigths,* filterSize, * depths,  **biases);
	int outputSizeAux = 0;

	for (int i = 0; i < count; ++i)
	{

		if(i == 2 || i == 7){
			//maxpool input
		}

		int **newOutput = (int**) malloc(sizeof(int)*outputSizeAux);

		if(i == 0){
			inception(input, outputs[0], inputSize, &outputSizeAux, filters, numFilters, numWeigths, filterSize, depths, biases);
		}
		else{
			inputSize = outputSize[i-1];
			outputSizeAux = outputSize[i];
			inception(outputs[i-1], outputs[i], inputSize, &outputSizeAux, filters, numFilters, numWeigths, filterSize, depths, biases);

		}
		outputSize[i] = outputSizeAux;

	}

	inception(output,  **output2,  outputSize,  ****filters,  *numFilters,  numWeigths, * filterSize, * depths,  **biases);

}