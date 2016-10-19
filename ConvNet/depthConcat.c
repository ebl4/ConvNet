#include <stdio.h>
#include <stdlib.h>
#include "matrix.c"

int ** maxOutputLayear(int** outputA, int** outputB, int dimA, int dimB){
	return (dimA > dimB) ? outputA : outputB;
}

int ** paddingLayer(int** output, int depth, int outputSize, int numPaddings){

	//external padding
	int paddingMatrixSize = outputSize+numPaddings*2;
	int** paddingMatrix = (int**) malloc(sizeof(int*)*paddingMatrixSize);
	for (int i = 0; i < depth; ++i)
	{
		for (int j = 0; j < numPaddings; ++j)
		{
			zeroPadding(output[i], paddingMatrix[i], outputSize);
		}
	}
	return paddingMatrix;
}

int ** paddingLayerFromInside(int** output, int depth, int outputSize, int numPaddings){

	//internal padding
	int paddingMatrixSize = outputSize+numPaddings;	
	int** paddingMatrix = (int**) malloc(sizeof(int*)*depth);
	for (int i = 0; i < depth; ++i)
	{
		for (int j = 0; j < numPaddings; ++j)
		{
			zeroPaddingLastLineCol(output[i], paddingMatrix[i], outputSize);
			printf("Hey Enter here\n");

		}
	}
	return paddingMatrix;
}

void concatLayers(int** outputA, int** outputB, int** outputConcat, int depthA, int depthB){	
	for (int i = 0; i < depthA; ++i)
	{
		outputConcat[i] = outputA[i];
	}
	for (int i = depthA; i < depthB; ++i)
	{
		outputConcat[i] = outputB[i];
	}

}

//Attention to A and B because they have diferent depths
void depthConcatLayers(int** outputA, int** outputB, int** outputConcat, int depthA, int depthB, int dimA, int dimB){
	int maxVal = max(dimA, dimB), minVal = min(dimA, dimB);
	int dif = maxVal - minVal, numPaddings;	
	int** paddingMatrix;

	//only external zero paddings
	if(dif%2 == 0){
		numPaddings = dif/2;
		if(minVal == dimA){
			paddingMatrix = paddingLayer(outputA, depthA, dimA, numPaddings);
		}
		else{
			paddingMatrix = paddingLayer(outputB, depthB, dimB, numPaddings);
		}
		
	}
	//first zero padding is internal and the others are external
	else{		
		numPaddings = 1+(dif-1)/2;
		if(minVal == dimA){
			int** outputAux = paddingLayerFromInside(outputA, depthA, dimA, 1);
			numPaddings--;
			for (int i = 0; i < numPaddings; ++i)
			{
				paddingMatrix = paddingLayer(outputAux, depthA, dimA+1, numPaddings);
			}
		}
		else{			
			int** outputAux = (int**) malloc(sizeof(int*)*(minVal+1));
			printf("Dim B = %d\n", dimB);
			printf("depth B = %d\n", depthB);
			printf("%d\n", outputB[0][2]);
			printf("%d\n", outputB[0][3]);
			outputAux = paddingLayerFromInside(outputB, depthB, dimB, 1);
			printf("Enter here\n");
			numPaddings--;
			for (int i = 0; i < numPaddings; ++i)
			{
				paddingMatrix = paddingLayer(outputAux, depthA, dimB+1, numPaddings);
			}
		}
	}
	if(maxVal == dimA){
		concatLayers(outputA, paddingMatrix, outputConcat, depthA, depthB);
	}
	else{
		concatLayers(outputB, paddingMatrix, outputConcat, depthB, depthA);	
	}

}



int main(){

	int *m1, *m2, *m3, *biases, m = 3, n = 2;
	int **a, **b, **c;
	m1 = (int *) malloc(sizeof(int)*m*m);
	m2 = (int *) malloc(sizeof(int)*n*n);
	m3 = (int *) malloc(sizeof(int)*m*m);

	a = (int **) malloc(sizeof(int*));
 	b = (int **) malloc(sizeof(int*));
 	c = (int **) malloc(sizeof(int*));


	m1[0] = 2;m1[1] = 3;m1[2] = 3;	
	m1[3] = 2;m1[4] = 3;m1[5] = 2;		
	m1[6] = 3;m1[7] = 2;m1[8] = 2;		

	m2[0] = 2;
	m2[1] = 3;
	m2[2] = 2;
	m2[3] = 3;

	a[0] = m1;
	b[0] = m2;

	depthConcatLayers(a, b, c, 1, 1, m, n);
	printf("%d\n", c[0][0]);

}