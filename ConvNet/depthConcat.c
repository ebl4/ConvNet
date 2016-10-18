#include <stdio.h>
#include <stdlib.h>
#include "matrix.c"

int ** maxOutputLayear(int** outputA, int outputB, int dimA, int dimB){
	return (dimA > dimb) ? outputA : outputB;
}

void paddingLayer(int** output, int depth, int outputSize, int numPaddings){

	//external padding
	int paddingMatrixSize = outputSize+numPaddings*2;
	int** paddingMatrix = (int**) malloc(sizeof(int*)*paddingMatrixSize);
	for (int i = 0; i < depth; ++i)
	{
		for (int j = 0; j < numPaddings; ++j)
		{
			zeroPadding(output[i], paddingMatrix, outputSize);
		}
	}
	return paddingMatrix;
}

void paddingLayerFromInside(int** output, int depth, int outputSize, int numPaddings){

	//internal padding
	int paddingMatrixSize = outputSize+numPaddings;
	int** paddingMatrix = (int**) malloc(sizeof(int*)*paddingMatrixSize);
	for (int i = 0; i < depth; ++i)
	{
		for (int j = 0; j < numPaddings; ++j)
		{
			zeroPaddingLastLineCol(output[i], paddingMatrix, outputSize);
		}
	}
	return paddingMatrix;
}

void concatLayers(int** outputA, int** outputB, int depth){
	int** outputConcat;
	for (int i = 0; i < depth; ++i)
	{
		outputConcat[i] = outputA[i];
	}
	for (int i = depth; i < depth*2; ++i)
	{
		outputConcat[i] = outputB[i];
	}

}

//Attention to A and B because they have diferent depths
void depthConcatLayers(int** outputA, int** outputB, int depth, int dimA, int dimB){
	int maxVal = max(dimA, dimB), minVal = min(dimA, dimB);
	int dif = maxVal - minVal, numPaddings;
	int* maxOutput = maxOutputLayear(outputA, outputB, dimA, dimB);
	int* paddingMatrix;

	//only external zero paddings
	if(dif%2 == 0){
		numPaddings = dif/2;
		if(minVal == dimA){
			paddingMatrix = paddingLayer(outputA, depth, dimA, numPaddings);
		}
		else{
			paddingMatrix = paddingLayer(outputB, depth, dimB, numPaddings);
		}
		
	}
	//first zero padding is internal and the others are external
	else{
		numPaddings = 1+(dif-1)/2;
		if(minVal == dimA){
			int** outputAux = paddingLayerFromInside(outputA, depth, dimA, 1);
			numPaddings--;
			for (int i = 0; i < numPaddings; ++i)
			{
				paddingMatrix = paddingLayer(outputAux, depth, dimA+1, numPaddings);
			}
		}
		else{
			int** outputAux = paddingLayerFromInside(outputB, depth, dimB, 1);
			numPaddings--;
			for (int i = 0; i < numPaddings; ++i)
			{
				paddingMatrix = paddingLayer(outputAux, depth, dimB+1, numPaddings);
			}
		}
	}
	concatLayers(maxOutput, paddingMatrixSize);

}