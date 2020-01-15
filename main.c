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


  int main(int argC, char * argV[]) {
	int shmid = shmget(SHMKEY, SIZE, IPC_CREAT | 0644);
	char * answer;
	answer = shmat(shmid, 0, 0);

    srand(time(0));
    strcpy(answer, generate_word());
    int lives = 6;
    int size = strlen(answer);
    int check[size];
    for (int i=0; i < size; ++i) {
      check[i] = 0;
    }
    int w = 0;
    char wordbank[27];
    while (lives > 0) {
      clear();
      printf("\nCurrent word: ");
      for(int i = 0; i < size; i++) {
        if (check[i]) {
          printf("%c", answer[i]);
        }
        else {
          printf("*");
        }
      }
      printf("\n");

	     //draw
	     draw(lives);
       words(wordbank);

      // Get guess
      char guess;
      printf("Your Guess: ");
      scanf(" %c", &guess);

      // check if guess is right
      int correct = 0;
      for(int k=0; k < size; ++k) {
        if (answer[k] == guess && !check[k]) {
  	   	   check[k] = 1;
           correct = 1;

        }
	    else if (answer[k] == guess && check[k] == 1)
	      {
		//if you guess a previously guessed correct letter
		  correct = 1;
	 	 printf("You already chose this letter\n");
	     	 sleep(1);
	      }
      }
      if (correct == 0){
        lives--;
        // printf("%d\n", lives);
        wordbank[w] = guess;
        w++;
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
    draw(lives);
    printf("Ran out of lives :(\n");

    return 0;
  }
