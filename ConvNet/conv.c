#include <stdio.h>
#include <stdlib.h>
#include "matrix.c"

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
	return ((result = inputWidth-filterSize+2*zeroPad)/stride)%2 == 0? result:-1;
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

void convolution(int** input, int** filter, int inputSize, int filterSize, int stride)){
	int result = 0;
	int slide = spatialSize(inputSize, filterSize, 0, stride);
	int *v, *f, *matrix;
	int depth = 0;

	matrix = (int *) malloc(sizeof(int)*inputSize*inputSize);
	v = (int *) malloc(sizeof(int)*filterSize*filterSize);
	f = (int *) malloc(sizeof(int)*filterSize*filterSize);

	
	matrix = input[depth];
	f = initFilter(filter, depth, filterSize);

	//inicializando v, fatia da matriz de entrada	
	for (int r = 0; r < slide; ++r){
		offset = r*inputSize;
		for (int i = 0; i < slide; ++i)
		{
			int start = offset+i, end = start+filterSize-1;
			for (int j = start; j < end; ++j)
			{
				//offsets
				l1 = j*inputSize;
				l2 = j*filterSize;
				for (int k = 0; k < filterSize; ++k)
				{
					v[l2+k] = matrix[start+l1+k];
				}
			}
			result = convolv(v, f, filterSize, filterSize);
			printf("%d\n", result);
		}
	}

}

int main(int argc, char const *argv[])
{
	/* code */
	int res;
	int **a, **b;
	int *m1, *m2, *m3, m = 3, n = 2;
	m1 = (int *) malloc(sizeof(int)*m*m);
	m2 = (int *) malloc(sizeof(int)*n*n);
	//m3 = (int *) malloc(sizeof(int)*m*n);

	a = (int **) malloc(sizeof(int*));
	b = (int **) malloc(sizeof(int*));


	m1[0] = 2;m1[1] = 3;m1[2] = 3;	
	m1[3] = 2;m1[4] = 3;m1[5] = 2;		
	m1[6] = 3;m1[7] = 2;m1[8] = 2;


	m2[0] = 2;
	m2[1] = 3;
	m2[2] = 2;
	m2[3] = 3;

	a[0] = m1;
	b[0] = m2;
	//res = convolv(m1, m2, 4);
	//res = testConv(a, b, 1, 2);

	convolution(a, b, 3, 2, 1);

	free(m1);free(m2);free(m3);free(a);free(b);

	//printf("%d\n", res);

	return 0;
}