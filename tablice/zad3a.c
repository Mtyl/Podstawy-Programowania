#include <stdio.h>
#include <stdlib.h>

int main(){
	int **matrix;
	short n;

	printf("Podaj rozmiar macierzy kwadratowej:\n");
	scanf("%d", &n);
	
	matrix = malloc(n * n * sizeof(*matrix));
	/* for(short w = 0; w < n; w++)
	matrix[w] = malloc(n * sizeof(**matrix))*/;
	
	for(short w = 0; w < n; ++w){
		for(short k = 0; k < n; ++k)
			scanf("%d", (matrix + (8*w) + k));}

	for(short w = 0; w < n; ++w){
		for(short k = 0; k < n; ++k)
			printf("%d\t", *(matrix + (8*w) + k));
		printf("\n");}
	
	char condition = 1;
	for(short w = 0; w < n && condition ; ++w){
		for(short k = n; k > w && condition ; --k){
			if(*(matrix + (8*w) + k) != 0){
				printf("Nie jest to macierz trójkątna dolna\n");
				condition = 0;
			}}}
	if(condition)
	printf("To jest macierz trójkątna dolna\n");
	
	free(matrix);
	
}
