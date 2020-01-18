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
    
    //strcpy(answer, "bobson");//to make it copy one single word
    int lives = 6;
    int size = strlen(answer);
    int check[size];//checking array
    int correct = 1;//correct status of guess
    for (int i=0; i < size; ++i) {
      check[i] = 0;
    }
    int w = 0;//wordbank index
    char wordbank[100];
    while (lives > 0) {
      clear();
      if(!correct)
      {
        printf("Your guess is incorrect\n");
      }
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

      for(int k=0; k < size; ++k) {
        if (answer[k] == guess && !check[k]) {
	   printf("Correct letter!\n");
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
      correct = 0;
      if (correct == 0){
        lives--;
	if(strchr(wordbank, guess))//if strchr is not 0
	{
        	wordbank[w] = guess;
        	wordbank[w+1] = '\0';
        	//printf("%s\n", &wordbank[w]);
        	//w = w + 2;
		w++;
        }
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
