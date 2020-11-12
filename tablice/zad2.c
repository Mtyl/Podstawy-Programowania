#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define LEN 8

void randomData(short table[LEN][LEN]){
	for(int w = 0; w < LEN; w++){
		for(int k = 0; k < LEN; k++)
		table[w][k] = rand() % 1000;
	}
}

void printData(short table[LEN][LEN]){
	for(int w = 0; w < LEN; w++){
		for(int k = 0; k < LEN; k++)
		printf("%d\t", table[w][k]);
		printf("\n");
	}
}

void function1(short table[LEN][LEN]){
	/*SUMA ELEMENTÓW PRZEKĄTNEJ*/
	int sum = 0;
	for(int d=0; d < LEN; d++)
	sum += table[d][d];
	printf("Suma na przekątnej: %d\n", sum);
	
	/*SUMA KOLUMN*/
	printf("Suma kolumn:\n");
	for(int k = 0; k < LEN; k++){
		sum = 0;
		for(int w = 0; w < LEN; w++)
		sum += table[w][k];
		printf("%d\t", sum);
	}
	
	/*SUMA ELEMENTÓW*/
	sum = 0;
	for(int w = 0; w < LEN; w++){
		for(int k = 0; k < LEN; k++)
		sum += table[w][k];
	}
	printf("\nSuma elementów:%d\n\n", sum);
}

void multiply(short a[LEN][LEN], short b[LEN][LEN]){
	printf("Iloczyn macierzy\n");
	int out = 0;
	for(int w = 0; w < LEN; w++){
		for(int k = 0; k < LEN; k++){
			out = 0;
			for(int i = 0; i < LEN; i++)
			out += a[w][i]*b[i][k];
			printf("%d\t", out);
		}
		printf("\n");
	}
}

int main(){
	srand(time(NULL));
	short first[LEN][LEN];
	short second[LEN][LEN];
	randomData(first);
	randomData(second);
	printf("FIRST\n");
	printData(first);
	function1(first);
	printf("SECOND\n");
	printData(second);
	function1(second);
	multiply(first, second);
}
