#include <stdio.h>
#include <stdlib.h>

void swap(int A[], short i1, short i2){
	int buffer = A[i1];
	A[i1] = A[i2];
	A[i2] = buffer;
}

short divideArray(int A[], short l, short r){
	short divideIndex = (l+r)/2;
	int divideValue = A[divideIndex];
	swap(A, divideIndex, r);
	short currentPosition = l;
	for(short i = l; i < r; i++){
		if(A[i] < divideValue){
			swap(A,i,currentPosition);
			currentPosition++;
		}

	}
	swap(A, currentPosition, r);
	return currentPosition;
}

void quickSort(int A[], short l, short r){
	if(l < r){
	short i = divideArray(A, l, r);
	quickSort(A, l, i);
	quickSort(A, i+1, r);
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
	for(short i = 0; i < numberOfSets; i++)
		quickSort(data[i], 0, ((index[i])-1));
	
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
