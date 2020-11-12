  /* Local Variables:  */
  /* compile-command: "gcc zad1.c -ggdb -o 
zad1" */
  /* End:              */
#define N1 23
#define N2 17
#define N 23
#define NS ((N1)+(N2))
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int t1[N1];
int t2[N2];
int buffer[NS];

void reverse(){
  short ctr = 0;
  int buffer = 0;
  while(((N1-1)-ctr)>ctr){
    buffer = t1[ctr];
    t1[ctr] = t1[(N1-1)-ctr];
    t1[(N1-1)-ctr] = buffer;
    ctr++;
  }
  return;
}

void printArrays(){
   printf("t1:{ ");
   for(short i = 0; i < N1; i++){
   	printf("%d ", t1[i]);
   }
   printf("}\nt2:{ ");
   for(short i = 0; i < N2; i++){
   	printf("%d ", t2[i]);
   }
   printf("}\n");
}

void initializeArrays(){
   for(short i = 0; i < N1; i++){
   	t1[i] = (rand() % 10) + 1;
   }
   for(short i = 0; i < N2; i++){
	t2[i] = (rand() % 10) + 1;
   }
}

void merge(int data[], short first, short mid, short last){
   short iterator = first;	
   while(iterator<=last){
   	buffer[iterator] = data[iterator];
   	iterator++;
   }
   short index1 = first;
   short index2 = mid + 1;
   short indexOutput = first;
   while(index1<=mid && index2<=last){
      if(buffer[index1] < buffer[index2]){
         data[indexOutput] = buffer[index1];
         index1++;
      }
      else{
         data[indexOutput] = buffer[index2];
         index2++;
      }
   indexOutput++;
   }
   
   while(index1<=mid){
      data[indexOutput] = buffer[index1];
      indexOutput++;index1++;}
      
   while(index2<=last){
      data[indexOutput] = buffer[index2];
      indexOutput++;index2++;}
}

void mergeSort(int data[], short first, short last){
   short mid = (first+last)/2;
   if(first < last){
   mergeSort(data, first, mid);
   mergeSort(data, mid+1, last);
   merge(data, first, mid, last);
   }
}

int one_two (int one[], int one_length, int two[], int two_length){

   short index1 = 0;
   short index2 = 0;
   short indexOutput = 0;

   if(one[index1] < two[index2]){
      buffer[indexOutput]=one[index1];
      index1++;indexOutput++;
   }else{
      buffer[indexOutput]=two[index2];
      index2++;indexOutput++;
   }
   
   while(index1<one_length && index2<two_length){
      if(one[index1] < two[index2]){
         if(buffer[indexOutput-1] != one[index1]){;
            buffer[indexOutput] = one[index1];
            indexOutput++;
         }   
         index1++;
      }
      else if(one[index1] >= two[index2]){
         if(buffer[indexOutput-1] != two[index2]){;
            buffer[indexOutput] = two[index2];
            indexOutput++;
         }   
         index2++;
      } 
   
   }
   
   while(index1<one_length){
      if(buffer[indexOutput-1] != one[index1]){
            buffer[indexOutput] = one[index1];
            indexOutput++;
         }
         index1++;
      }
   while(index2<two_length){
      if(buffer[indexOutput-1] != two[index2]){
            buffer[indexOutput] = two[index2];
            indexOutput++;
         }
         index2++;
      }
    
    
    printf("buffer:{ ");
    short i = 0;
   while(i < indexOutput){
   	printf("%d ", buffer[i]);
        i++;
   }
   printf("}\n");
  
  return indexOutput;
}

void statistics(){
short int T[N];
short int result[21]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
printf("T:{ ");
for(short i = 0; i < N; i++){
	short x = rand() % 2 ? -1 : 1;
   	T[i] = (rand() % 11) * x;
   	printf("%d ", T[i]);
   	(result[(10+T[i])])++;
   }
printf("}\n");
float percent = 0.0;
for(short i = 0; i < 21; i++){
	percent = 100.00*result[i]/N;
  	printf("%d: %f\% \n", i-10, percent);
   }
}

int main(){
  srand(time(NULL));
  initializeArrays();
  printf("Wartości wejściowe:\n");
  printArrays();
  printf("Tablica t1 odwrócona:\n");
  reverse();
  printArrays();
  printf("Tablice posortowane:\n");
  mergeSort(t1, 0, (N1 - 1));
  mergeSort(t2, 0, (N2 - 1));
  printArrays();
  printf("Suma tablic bez powtórzeń:\n");
  printf("Długość tablicy = %d \n",one_two(t1,N1,t2,N2));
  printf("Rozkład statystyczny:\n");
  statistics();
  return 0;
}

