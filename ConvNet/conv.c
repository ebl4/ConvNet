#include <stdio.h>
#include <stdlib.h>
#include "matrix.c"

/*
This code follow the examples obtained from Convolutinal Neural
Networks Stanford Course present here http://cs231n.github.io/convolutional-networks/
*/

int testConv(int** a, int** b, int vDepth, int fSize){
	int result = 0;
	int *v, *f;
	v = (int *) malloc(sizeof(int)*fSize*fSize);
	f = (int *) malloc(sizeof(int)*fSize*fSize);
	for (int i = 0; i < vDepth; ++i)
	{
		v = a[i];
		f = b[i];
		result += convolv(v,f,fSize*fSize);
	}
	free(v);free(f);
	return result;
}

/* Representa a dimensao do vetor de saída 
E corresponde ao numero de passos no slide horizontal e vertical
Return -1 if slide does not match
*/
int spatialSize(int inputWidth, int filterSize, int zeroPad, int stride){
	int result = 0;
	result = (inputWidth-filterSize+2*zeroPad)/stride + 1;
	return result;
}

void initSlice(int* v, int start, int end){

}

int* initFilter(int** filter, int depth, int filterSize){
	int *f;
	f = (int *) malloc(sizeof(int)*filterSize*filterSize);
	f = filter[depth];
//	free(f);
	return f;
}


int * convolution(int** input, int** filter, int inputSize, int filterSize, int depth, int stride){
	int result = 0, cont = 0, offset = 0, l1, l2;		

	int slide = spatialSize(inputSize, filterSize, 0, stride);
	int slideVector = slide*slide;
	
	int *resultM;
	int *v, *f, *matrix;

	matrix = (int *) malloc(sizeof(int)*inputSize*inputSize);
	v = (int *) malloc(sizeof(int)*filterSize*filterSize);
	f = (int *) malloc(sizeof(int)*filterSize*filterSize);
	resultM = (int *) malloc(sizeof(int)*slideVector);

	
	//recupera a matriz de entrada no nivel depth
	matrix = input[depth];

	//inicializa a matriz do filtro
	f = initFilter(filter, depth, filterSize);

	//inicializando v, fatia da matriz de entrada com tamanho do
	// filtro
	for (int r = 0; r < slide; ++r){
		offset = r*inputSize;
		printf("Slide colum %d\n", r+1);

		for (int i = 0; i < slide; ++i)
		{
			int start = offset+i, end = start+filterSize-1;

			printf("Slide line %d\n", i+1);

			printf("Start in %d\n", start);
			printf("End in %d\n", end);
										
			//offsets
			l1 = inputSize;			
			for (int k = 0; k < filterSize*filterSize; ++k)
			{
				if(k < filterSize){
					v[k] = matrix[k+start];
				}
				else{
					l2 = (k+1)%filterSize;
					v[k] = matrix[(l1+start)+l2];
				}				
			}
			
		result = convolv(v, f, filterSize*filterSize);
		resultM[cont++] = result;
		printf("%d\n", result);
		}
	}
	//warning - free memory in resultM
	free(f);free(v);
	return resultM;
}

void adjustBias(int* result, int bias, int dim){
	for (int i = 0; i < dim*dim; ++i)
	{
		result[i] += bias;
	}
	//return result;
}

int * simpleFilterConvolution(int** input, int** filter, int bias, int inputSize, int filterSize, int depths, int stride){
	int slide = spatialSize(inputSize, filterSize, 0, stride);
	int **matrix; 
	int *result;
	matrix = (int **) malloc(sizeof(int*)*depths);
	result = (int *) malloc(sizeof(int*)*slide*slide);
	initVector(result, slide*slide);
	
	for (int i = 0; i < depths; ++i)
	{
		matrix[i] = convolution(input, filter, inputSize, filterSize, i, stride);
	}
	
	printf("After %d\n", result[0]);
	
	for (int i = 0; i < depths; ++i)
	{
		result = sumVectors(result, matrix[i], slide*slide);
	}

	adjustBias(result, bias, slide);
	
	printf("Before %d\n", result[0]);
	printf("Before %d\n", result[3]);


	return result;
}


int** multiFilterConvolution(int** input, int*** filter, int* biases, int numFilters, int inputSize, int filterSize, int depths, int stride){	
	int **result;
	result = (int **) malloc(sizeof(int*)*numFilters);
	for (int i = 0; i < numFilters; ++i)
		{			
			result[i] = simpleFilterConvolution(input, filter[i], biases[i], inputSize, filterSize, depths, stride);
		}			
	printf("Before %d\n", result[0][0]);
	printf("Before %d\n", result[1][0]);

	return result;
}

int * allocateMatrix(int *a, int dim){
	int size = dim*dim;
	a = (int *) malloc(sizeof(int)*size);
	for (int i = 0; i < size; ++i)
	{
		a[i] = 1;
	}

	return a;
}

// Method for instantiate depth matrixs with randon numbers
// between 0 and 2
int ** allocateAllMatrix(int depths, int dim){
	int **m;
	m = (int **) malloc(sizeof(int*)*depths);
	for (int i = 0; i < depths; ++i)
	{
		m[i] = allocateMatrix(m[i], dim);
	}
	return m;
}

// int main()
// {
// 	/* code */
// 	int res, depths = 2, stride = 1, numFilters = 2;
// 	int **a, **b, ***c;
// 	int *m1, *m2, *m3, *biases, m = 3, n = 2;
// 	m1 = (int *) malloc(sizeof(int)*m*m);
// 	m2 = (int *) malloc(sizeof(int)*n*n);
// 	biases = (int *) malloc(sizeof(int)*numFilters);
// 	//m3 = (int *) malloc(sizeof(int)*n*n);

// 	//a = (int **) malloc(sizeof(int*));
// 	//b = (int **) malloc(sizeof(int*));
// 	c = (int ***) malloc(sizeof(int**)*2);


// 	m1[0] = 2;m1[1] = 3;m1[2] = 3;	
// 	m1[3] = 2;m1[4] = 3;m1[5] = 2;		
// 	m1[6] = 3;m1[7] = 2;m1[8] = 2;		

// 	m2[0] = 2;
// 	m2[1] = 3;
// 	m2[2] = 2;
// 	m2[3] = 3;
	
// 	//m3[0] = 2;
// 	//m3[1] = 3;
// 	//m3[2] = 2;
// 	//m3[3] = 3;

// //	m3 = allocateMatrix(m3, n);

// 	biases[0] = 1;biases[1] = 2; 
// 	b = allocateAllMatrix(depths, n);
// 	a = allocateAllMatrix(depths, m);
// 	c[0] = allocateAllMatrix(depths, n);
// 	c[1] = allocateAllMatrix(depths, n);
// 	//res = convolv(m1, m2, 4);
// 	//res = testConv(a, b, 1, 2);

// 	//convolution(a, b, 3, 2, 1);

// //	res = spatialSize(3,2,0,1);

// 	//m3 = sumVectors(m2, m3, n*n);
	
// 	//initVector(m3, n*n);

// 	//printf("%d\n", res);
// 	printf("%d\n", b[0][1]);
// 	printf("%d\n", b[1][1]);
// 	printf("%d\n", a[1][2]);
	
// 	//simpleFilterConvolution(a, b, m, n, depths, stride);
// 	multiFilterConvolution(a, c, biases, numFilters, m, n, depths, stride);

// 	free(b);free(a);
// 	free(m1);free(m2);

// 	return 0;
// }