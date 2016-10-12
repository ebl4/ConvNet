#include <stdio.h>
#include <stdlib.h>
#include "matrix.c"

// Método que verifica se o stride pode ser realizado
int stride(int W, int F, int P,  int S){
	return ((W-F+2*P)/S)%2 == 0? 1:-1;
}

int main(){
	int *m1, *m2, *m3, m = 2, n = 2;
	m1 = (int *) malloc(sizeof(int)*m*n);
	m2 = (int *) malloc(sizeof(int)*m*n);
	m3 = (int *) malloc(sizeof(int)*m*n);

	m1[0] = 2;
	m1[1] = 3;
	m1[2] = 2;
	m1[3] = 3;

	m2[0] = 2;
	m2[1] = 3;
	m2[2] = 2;
	m2[3] = 3;
	multMatrix(m1,m2,m3,m,n,n);
	int i, j, k;
	for(i = 0; i < m; i++){
		k = i*n;
		for(j = 0; j < n; j++){
			printf("%d", m3[k+j]);
		}
			printf("\n");
		
	}
//	printf("%d\n", result);
	return 0;
}

