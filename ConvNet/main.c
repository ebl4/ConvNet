#include <stdio.h>
#include <stdlib.h>


// Método que verifica se o stride pode ser realizado
int stride(int W, int F, int P,  int S){
	return ((W-F+2*P)/S)%2 == 0? 1:-1;
}

int main(){
	printf("%s", "Hello world!\n");
	int res = stride(5,3,1,3);
	printf("%d\n", res);
	return 0;
}

