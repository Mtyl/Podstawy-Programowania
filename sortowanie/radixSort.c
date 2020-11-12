#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	char ***data;
	short *index;
	short *digits;
	short numberOfSets;
	
	scanf("%d", &numberOfSets);
	data = malloc(numberOfSets * sizeof(*data));
	index = malloc(numberOfSets * sizeof(*index));
	digits = malloc(numberOfSets * sizeof(*digits));
	
	/*INITIALIZE DATA*/
	for(short i = 0; i < numberOfSets; i++){
		scanf("%d %d", &index[i], &digits[i]);
		data[i] = malloc(index[i] * sizeof(**data));
		for(short j = 0; j < index[i]; j++){
			data[i][j] = malloc(index[i] * sizeof(**data));
			scanf("%s", data[i][j]);
			} 	
	}
	
	/* RADIX SORT */
	for(short n = 0; n < numberOfSets; n++){
	
		char **result = malloc(index[n] * sizeof(*result));
		for(short i = 0; i < index[n]; i++)
		result[i] = malloc(digits[n] * sizeof(**result));
		
		for(short i = digits[n] - 1 ; i >= 0; i--){
			short currentPosition = 0;
			
			for(short digit = 0; digit < 10; digit++){
				for(short j = 0; j < index[n]; j++){
					if(data[n][j][i] == digit+48){
						strcpy(result[currentPosition],data[n][j]);
						currentPosition++;
					}	
				}
			}
			
			for(short k = 0; k < index[n]; k++)
			strcpy(data[n][k],result[k]);
		}
		
		for(short i = 0; i < index[n]; i++)
		free(result[i]);
		free(result);
	}
	/* PRINT DATA */
	for(short i = 0; i < numberOfSets; i++){
		for(short j = 0; j < index[i]; j++)
			printf("%s\n", data[i][j]); 	
		printf("\n");
	}
	
	/* CLEAN UP */
	for(short w = 0; w < numberOfSets; w++)
	free(data[w]);
	free(data);
	free(index);
}
