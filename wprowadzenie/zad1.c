#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(){
  srand(time(NULL));
  
  short randomNumber = (rand() % 101);
  short countGuess = 0;
  char userInput[4] = {0};
  short guess = 101;
  while(guess != randomNumber){
    printf("Podaj liczbę\n");
    fgets(userInput, 4, stdin);
    countGuess++;
    guess = atoi(userInput);
    if(guess == randomNumber){
      printf("Brawo, zgadłeś liczbę po %d próbach\n", countGuess);
    }else if(guess > randomNumber){
      printf("Wylosowana liczba jest mniejsza, zgaduj dalej\n");
    }else if(guess < randomNumber){
      printf("Wylosowana liczba jest większa, zgaduj dalej\n");
    }

  }
}
