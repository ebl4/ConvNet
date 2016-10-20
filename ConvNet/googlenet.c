#include <stdio.h>
#include <stdlib.h>
#define NUM_OUTPUTS 9


void initOutputSize(int *outputSize, int numOutputs){
	for (int i = 0; i < numOutputs; ++i)
	{
		outputSize[i] = 0;
	}
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