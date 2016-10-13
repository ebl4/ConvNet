#include <stdio.h>
#include <stdlib.h>
#include "matrix.c"

int testConv(int** a, int** b, int vDepth, int fSize){
	int result = 0;
	for (int i = 0; i < vDepth; ++i)
	{
		int *v, *f;
		v = (int *) malloc(sizeof(int)*fSize*fSize);
		f = (int *) malloc(sizeof(int)*fSize*fSize);

		v = a[i];
		f = b[i];
		result += convolv(v,f,fSize*fSize);
	}
	return result;
}

int main(int argc, char const *argv[])
{
	/* code */
	int res;
	int **a, **b;
	int *m1, *m2, *m3, m = 2, n = 2;
	m1 = (int *) malloc(sizeof(int)*m*n);
	m2 = (int *) malloc(sizeof(int)*m*n);
	m3 = (int *) malloc(sizeof(int)*m*n);

	a = (int **) malloc(sizeof(int*));
	b = (int **) malloc(sizeof(int*));


	m1[0] = 2;
	m1[1] = 3;
	m1[2] = 2;
	m1[3] = 3;

	m2[0] = 2;
	m2[1] = 3;
	m2[2] = 2;
	m2[3] = 3;

	a[0] = m1;
	b[0] = m2;
	//res = convolv(m1, m2, 4);
	res = testConv(a, b, 1, 2);

	printf("%d\n", res);

	return 0;
}