#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include "function.h"
#include <time.h>


  int main() {
    srand(time(0));
    char answer[128];
    strcpy(answer, generate_word());
    int lives = 6;
    int size = strlen(answer) - 1;
    int check[size];
    for (int i=0; i < size; ++i) {
      check[i] = 0;
    }
    while (lives > 0) {
      printf("Current word: ");
      for(int i = 0; i < size; i++) {
        if (check[i]) {
          printf("%c", answer[i]);
        }
        else {
          printf("*");
        }
      }
      printf("\n");

      // Get guess
      char guess;
      printf("Letter? ");
      scanf(" %c", &guess);


      // check if guess is right
      int correct = 0;
      for(int k=0; k < size; ++k) {
        if (answer[k] == guess) {
  	       check[k] = 1;
           correct = 1;
        }
      }
      if (correct == 0){
        lives--;
        printf("%d\n", lives);
      }
      int win = 0;
      // Check if user win
      for(int m = 0; m < size; ++m) {
        if (check[m] == 1) {
        win++;
        }
      }
      if (win == size){
        printf("win\n");
        return 0;
      }
    }

    //no more lives
    printf("Ran out of lives :(\n");

    return 0;
  }
