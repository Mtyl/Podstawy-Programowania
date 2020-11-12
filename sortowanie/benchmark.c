#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define ES 20000
#define DI 3
#define IT 70

void swap(int A[], short i1, short i2){
	int buffer = A[i1];
	A[i1] = A[i2];
	A[i2] = buffer;
}

void initializeData(int data[][ES]){
	for(short i = 0; i < ES; i++){
		data[0][i] = rand() % 65535;
		data[1][i] = i * DI;
		data[2][i] = i * DI;
		data[3][i] = (ES * DI) - (i * DI);
		data[4][i] = (ES * DI) - (i * DI);
	}
	
	for(short i = 0; i < (ES/100); i++){
		short x = rand() % ES;
		short y = rand() % ES;
		swap(data[1], x, y);
		swap(data[3], x, y);
}}

void insertSort(int A[], short n){
	for(short i = 1; i < n;i++){
	int insertVariable = A[i];
	short j = i - 1;
	for(; (j >= 0 && A[j] > insertVariable); j--)
		A[j+1] = A[j];
	A[j+1] = insertVariable;
	}
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
	
void radixSort(int A[]){
		int result[ES];
		for(size_t pos = 0; pos < 16; pos++){
			short currentPosition = 0;
				for(short j = 0; j < ES; j++){
					if(!( A[j] & (1<<pos) ))
					{					
						result[currentPosition]=A[j];
						currentPosition++;	
					}
				}for(short j = 0; j < ES; j++){
					if( A[j] & (1<<pos) )
					{					
						result[currentPosition]=A[j];
						currentPosition++;	
					}
				}
			
			for(short n = 0; n < ES; n++)
			A[n]=result[n];
		}
	}
	
void printMode(short i, short j){
switch (j){
	case 0:
	printf("Proste wstawianie\t");break;
	case 1:
	printf("Sortowanie szybkie\t");break;
	case 2:
	printf("Sortowanie pozycyjne\t");break;
	}
switch (i){
	case 0:
	printf("Ciąg liczb losowych\t\t\t ");break;
	case 1:
	printf("Ciąg liczb prawie posortowanych rosnąco\t ");break;
	case 2:
	printf("Ciąg liczb posortowanych rosnąco\t ");break;
	case 3:
	printf("Ciąg liczb prawie posortowanych malejąco ");break;
	case 4:
	printf("Ciąg liczb posortowanych malejąco\t ");break;
	}

}

int main(){

srand(time(NULL));

int data[5][ES];

int testData[ES];
initializeData(data);

printf("Nazwa algorytmu \tTyp zestawu danych \t\t\t Czas wykonania\n");
for(short i = 0; i < 5; i++){
	for(short j = 0; j < 3; j++){
	printMode(i, j);
	double average = 0.0;
	int interval = 0;
	for(short it = 0; it < IT; it++){
		for(short n = 0; (n < ES && j < 2); n++)
			testData[n] = data[i][n];
		switch (j){
			case 0:
				interval = clock();
				insertSort(testData,ES);
				interval = clock() - interval;
			break;
			case 1:
				interval = clock();
				quickSort(testData,0,ES-1);
				interval = clock() - interval;
			break;
			case 2:
				interval = clock();
				radixSort(testData);
				interval = clock() - interval;
			break;
			}
		average += (double)interval;	
		}
	average = ((average / IT) / CLOCKS_PER_SEC);
	printf("%f\n", average);
	}
	
}

}
