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

int main(int argC, char * argV[]) {
  int bigbrain = 0;

  int * check;//array same size of answer to check the progress on guessing the word
  char * wordbank;
  char * answer;
  int * won;//not to be confused with "win". won stores if the game has been won already
  int * lost;

  int checkid = shmsetup(CHECK_KEY, (void*)&check);
  int bankid = shmsetup(BANK_KEY, (void*)&wordbank);
  int answerid = shmsetup(ANSWER_KEY, (void*)&answer);
  int wonid = shmsetup(WON_KEY, (void*)&won);
  int lostid = shmsetup(LOST_KEY, (void*)&lost);

  int semid = semsetup();
  srand(time(0));

  //this works because
  //"When the shared memory segment is created,
  //it shall be initialized with all zero values."
  if(!strlen(answer))
    strcpy(answer, generate_word());

  int size = strlen(answer);//may need hardcoding to make sure generate_word() works
  for (int i=0; i < size; ++i) {
    check[i] = 0;
  }

  int lives = 6;
  int win = 0;//check win status
  int correct = 1;//correct status of guess
  int w = 0;//wordbank index
  int youLostAllLives = 0;//special integer to check if you lost from losing all your lives
  int debugIterationCounter = 0;
  strcpy(wordbank, "abcdefghijklmnopqrstuvwxyz");

  while (lives > 0) {
    //to get interrupt signal from player and ask player to exit instead
    signal(SIGINT, sighandler);
    signal(SIGQUIT, sighandler);

    clear();
    disasterPreventionText();
    printf("\nLives: %d\n", lives);

    //draw the person
    draw(lives);

    //waiting for turn
    printf("waiting for your turn...\n\n\n\n\n\n\n\n");
    printf("Hint: If you get stuck on this screen, press Control + C to get yourself moving again\n");
    printf("If you must do this, a disaster likely occured. Follow the Disaster Protocol\n");
    struct sembuf sb;
    sb.sem_num = 0;
    sb.sem_op = -1;
    semop(semid, &sb, 1);

    //text to notify the player it is their turn
    clear();
    disasterPreventionText();
    printf("It's now your turn!\n");
    sleep(1);

    clear();
    disasterPreventionText();
    //if the game has been lost already, then you win
    if(*lost)
      break;
    //if the game has been won already, then you lose
    if(*won)
      break;

    //set correct status back to incorrect
    correct = 0;
    //set win status back to none
    win = 0;
    //printf("debugIterationCounter is %d\n", debugIterationCounter);

    clear();
    disasterPreventionText();
    printf("\nLives: %d\n", lives);
    //draw
    draw(lives);
    printf("\n");
    printf("Viewing begins in 3 seconds (press Control + C to skip)\n");
    sleep(3);
    //printf("3 seconds\n");
    //sleep(1);
    //printf("2 seconds\n");
    //sleep(1);
    //printf("1 second\n");
    //sleep(1);

    clear();
    disasterPreventionText();
    //view the word progress and bank
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
    //printf("answer is %s\n", answer);
    // word bank printing
    printf("\n{%s}\n", wordbank);
    printf("\n");
    printf("Viewing will end in 3 seconds (press Control + C to skip)\n");
    sleep(3);

    //stop viewing
    clear();
    disasterPreventionText();
    printf("\nLives: %d\n", lives);
    //draw
    draw(lives);

    // Get guess
    printf("Your Guess (type a letter or a word): ");
    char word[100];
    char guess;
    scanf("%s", word);
    if (strlen(word) > 1) {
      if(!strcmp("exit", word))//if the user wants to force exit the game
      {
        printf("user wants to exit\n");
        break;
      }
      else if (!strcmp("answer123", word))//hack for the tester to see the answer
      {
        printf("the answer is \"%s\"\n", answer);
        correct = 1;
        sleep(1);
      }
      else if (strcmp(word,answer) == 0)//if the whole word is guessed
      {
        printf("winner winner chicken dinner\n");
        bigbrain = 200;//this counts as a win
        *won = 1;
        break;
      }
      else{
        printf("wrong\n");
      }
    }
    else {
      guess = word[0];
    }

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
      printf("Your guess is incorrect\n");
      lives--;
    }

    int x = 0;
    while(x < 26){
      if (wordbank[x] == guess){
        wordbank[x] = '_';
      }
        x++;
    }

    // If the game has not been won already
    if(!*won)
    {
      for(int m = 0; m < size; ++m) {
        if (check[m] == 1) {
          win++;
        }
      }
      if (win == size){
        *won = 1;
        break;
      }
    }

    if(!lives)
    {
      *lost = 1;
      youLostAllLives = 1;
    }

    sb.sem_op = 1;
    semop(semid, &sb, 1);
    printf("\nYour turn has ended\n");
    sleep(1);
    debugIterationCounter ++;
  }

  int gameHasBeenWon = *won;
  int gameHasBeenLost = *lost;
  char theAnswer[100];
  strcpy(theAnswer, answer);
  shmdt(check);
  shmctl(checkid, IPC_RMID, 0);
  shmdt(wordbank);
  shmctl(bankid, IPC_RMID, 0);
  shmdt(answer);
  shmctl(answerid, IPC_RMID, 0);
  shmdt(won);
  shmctl(wonid, IPC_RMID, 0);
  shmdt(lost);
  shmctl(lostid, IPC_RMID, 0);

  semctl(semid, IPC_RMID, 0);
//  printf("semaphore removed!\n");

  if(win == size)//if game was won because all the letters were guessed
  {
    printf("The answer was \"%s\"\n", theAnswer);
    printf("You won!\n");
    return 0;
  }

  if(bigbrain)//if game was won because the full word was guessed, win message is in the while loop
  {
    return 0;
  }

  if(gameHasBeenWon)
  {
    printf("You lost because the other player won first!\n");
    printf("The answer was \"%s\"\n", theAnswer);
    return 0;
  }

  //no more lives but the game hasn't been won yet
  if (youLostAllLives){
    draw(lives);
    printf("Ran out of lives :(\n");
    printf("The answer was \"%s\"\n", theAnswer);
    return 0;
  }

  if(gameHasBeenLost)
  {
    printf("You won because the other player lost all their lives\n");
    printf("The answer was \"%s\"\n", theAnswer);
    return 0;
  }

  printf("Exited for some abnormal reason\n");
  printf("The answer was \"%s\"\n", theAnswer);
  return 0;
}
