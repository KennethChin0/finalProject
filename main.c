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
//#include <graphics.h>
//d

int main(int argC, char * argV[]) {
  int * check;
  char * wordbank;
  int checkid = shmsetup(CHECK_KEY, &check);
  int bankid = shmsetup(BANK_KEY, &wordbank);
  int semid = semsetup();
  srand(time(0));

  char answer[100];
  //strcpy(answer, generate_word());
  strcpy(answer, "bobson");//to make it copy one single word
  printf("answer is %ld\n", answer);
  printf("*answer is %ld\n", *answer);
  int size = strlen(answer);//may need hardcoding to make sure generate_word() works
  for (int i=0; i < size; ++i) {
    check[i] = 0;
  }

  int lives = 6;
  int win = 0;//check win status
  int correct = 1;//correct status of guess
  int w = 0;//wordbank index
  strcpy(wordbank, "abcdefghijklmnopqrstuvwxyz");

  while (lives > 0) {
    signal(SIGINT, sighandler);
    // Check if user win
    for(int m = 0; m < size; ++m) {
      if (check[m] == 1) {
        win++;
      }
    }
    if (win == size){
      break;
    }

    printf("waiting for your turn...\n");
    struct sembuf sb;
    sb.sem_num = 0;
    sb.sem_op = -1;
    semop(semid, &sb, 1);
    printf("It's now your turn!\n");
    sleep(1);

    clear();
    if(!correct)
    {
      printf("Your guess is incorrect\n");
    }

    //set correct status back to incorrect
    correct = 0;
    //set win status back to none
    win = 0;
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
    printf("answer is %s\n", answer);

    printf("Lives: %d\n", lives);
    //draw
    draw(lives);
    // words(wordbank);
    printf("{%s}\n", wordbank);

    // Get guess
    printf("Your Guess: ");
    char guess;
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
    if (correct == 0){
      lives--;
    }

    int x = 0;
    while(x < 27){
      if (wordbank[x] == guess){
        wordbank[x] = '_';
      }
        x++;
    }

    // Check if user win
    // for(int m = 0; m < size; ++m) {
    //   if (check[m] == 1) {
    //     win++;
    //   }
    // }
    // if (win == size){
    //   break;
    // }
    sb.sem_op = 1;
    semop(semid, &sb, 1);
    printf("Your turn has ended\n");
    sleep(1);
  }

  shmdt(check);
  printf("shared memory detached!\n");
  shmctl(checkid, IPC_RMID, 0);
  printf("shared memory removed!\n");
  semctl(semid, IPC_RMID, 0);
  printf("semaphore removed!\n");
  if(win == size)
  {
    printf("win\n");
    return 0;
  }
  //no more lives
  draw(lives);
  printf("Ran out of lives :(\n");

  return 0;
}
