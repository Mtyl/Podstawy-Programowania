#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
	short **matrix;
	short m,n;
	srand(time(NULL));
	
	printf("Podaj ilość wierszy:\n");
	scanf("%d", &n);
	
	printf("Podaj ilość kolumn:\n");
	scanf("%d", &m);
	
	matrix = malloc(n * sizeof(*matrix));
	for(short w = 0; w < n; w++)
	matrix[w] = malloc(m * sizeof(**matrix));
	
	for(short w = 0; w < n; ++w){
		for(short k = 0; k < m; ++k)
			matrix[w][k] = rand() % 100;}

	for(short w = 0; w < n; ++w){
		for(short k = 0; k < m; ++k)
			printf("%d\t", matrix[w][k]);
		printf("\n");}
	
	for(short w = 0; w < n; w++)
	free(matrix[w]);
	free(matrix);
	
}

