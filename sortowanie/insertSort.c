#include <stdio.h>
#include <stdlib.h>

void insertSort(int A[], short n){
	for(short i = 1; i < n;i++){
	int insertVariable = A[i];
	short j = i - 1;
	for(; (j >= 0 && A[j] > insertVariable); j--)
		A[j+1] = A[j];
	A[j+1] = insertVariable;
	}
}


int main(){
	int **data;
	short *index;
	short numberOfSets;
	scanf("%d", &numberOfSets);
	data = malloc(numberOfSets * sizeof(*data));
	index = malloc(numberOfSets * sizeof(*index));
	for(short i = 0; i < numberOfSets; i++){
		scanf("%d", &index[i]);
		data[i] = malloc(index[i] * sizeof(**data));
		for(short j = 0; j < index[i]; j++)
			scanf("%d", &data[i][j]); 	
	}
	printf("Done!\n");
	for(short i = 0; i < numberOfSets; i++)
		insertSort(data[i], index[i]);
	
	for(short i = 0; i < numberOfSets; i++){
		for(short j = 0; j < index[i]; j++)
			printf("%d\n", data[i][j]); 	
		printf("\n");
	}
	
	for(short w = 0; w < numberOfSets; w++)
	free(data[w]);
	free(data);
	free(index);
}
