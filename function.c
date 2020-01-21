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
#include "time.h"

int counter = 0;

void sighandler(int signal){
  if(signal == SIGQUIT)
  {
    if(counter < 3)
    {
      printf("Warning! You are trying to force end the program!\n");
      printf("This may cause a disaster!\n");
      printf("To end the program safely, follow Disaster Protocol until step 2\n");
      printf("Press Control + \\ %d more time(s) to force end the program\n", 3 - counter);
      counter ++;
    }
    else
    {
      printf("You are about to force end the program.\n");
      printf("This creates a disaster.\n");
      printf("To obtain protocol for repairing a disaster,\n");
      printf("Type \"make run\"\n");
      int status;
      exit(status);
    }
  }
  else if(signal == SIGINT)
  {
    printf("If you are trying to exit the program, type \"exit\" for your guess\n");
  }
}

int shmsetup(key_t key, void ** pointer){
  int shmid = shmget(key, SIZE, IPC_CREAT | IPC_EXCL | 0644);
  if(shmid < 0)
  {
    shmid = shmget(key, SIZE, 0644);
  }

  * pointer = shmat(shmid, 0, 0);//checking array to be shared between players
  return shmid;
}

int semsetup(){
  int semid = semget(SEMKEY, 1, IPC_CREAT | IPC_EXCL | 0644);
  int semidExistedBefore = 0;
  if(semid < 0)
  {
    semid = semget(SEMKEY, 1, 0644);
    printf("\n");
    if(semid >= 0)
      semidExistedBefore = 1;
  }
  if(!semidExistedBefore)
  {
    struct sembuf sb;
    sb.sem_num = 0;
    sb.sem_op = 1;
    semop(semid, &sb, 1);
    int semval = semctl(semid, 0, GETVAL, 0);
  }
  else
  {
    int semval = semctl(semid, 0, GETVAL, 0);
  }
  return semid;
}

void clear(){
  char ** args = parse_args("clear");
  int child = fork();
  int * status;
  if(child < 0)
  {
    printf("error %d: %s\n", errno, strerror(errno));
  }
  else if(child == 0)
  {
    execvp("clear", args);
    exit(*status);
  }
  else if(child > 0)
  {
    wait(status);
  }

}

int draw(int lives){
  if (lives <= 6){
    printf("\n" );
    if (lives <= 5){
      printf(" O\n" );
      if (lives <= 4){
        printf("/" );
        if (lives <= 3){
          printf("|" );
          if (lives <= 2){
            printf("\\\n" );
            if (lives <= 1){
              printf("/ " );
              if (lives <= 0){
                printf("\\\n" );
              }
            }
          }
        }
      }
    }
  }
  printf("\n");
}


char * generate_word(){
  FILE * f = fopen("words.txt", "r");
  if (f < 0) {
    printf("%s\n", strerror(errno));
  }
  int nLines = 0;
  char line[1024];
  int randLine;
  int i;
  while(!feof(f)) {
    fgets(line, 1024, f);
    nLines++;
  }
  randLine = rand() % nLines;
  fseek(f, 0, SEEK_SET);
  for(i = 0; !feof(f) && i <= randLine; i++){
    fgets(line, 1024, f);
  }
  char * word = line;
  int x = strlen(word) - 2;//this is supposed to be strlen(word) - 1 but it is hardcoded because for some reason it won't work
  word[x] = '\0';
  printf("while inside generate_word\n");
  printf("%s\n", word);
  printf("strlen(word) is %ld\n", strlen(word));
  fclose(f);
  return word;
}

char **  parse_args( char * line ){
  char ** args = calloc(6, sizeof(char));
  char * current = line;
  char * holder;
  int i = 0;
  while (current != NULL){
    holder = strsep(&current, "\n");
    args[i]  = holder;
    i++;
  }
  args[i] = NULL;
  return args;
}

void words(char * wordbank){
  int x = 0;
  printf("{");
  printf("%s", wordbank);
  printf("}\n");
}

void disasterPreventionText(){
   printf("To properly exit the program, follow Disaster Protocol to step 2.\n\n");

    printf("Disaster Protocol:\n");
    printf("1. All players press Control + C until they reach the guessing screen.\n");
    printf("2. All players type \"exit\" for their guess to exit their programs.\n");
    printf("3. Recompile the program using the following steps:\n");
    printf("  a. Type \"make clean\"\n");
    printf("  b. Type \"make\"\n");
    printf("  c. Type \"make run\"\n\n");

    printf("***To force exit the program (not recommended), press Control + \\ 3 times***\n\n");
    printf("******************************************************************************************\n");
    printf("                                         HANGMAN:\n\n");
}
