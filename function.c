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
//
int counter = 0;

void sighandler(int signal){
  if(signal == SIGINT)
  {
    if(counter < 3)
    {
      printf("type exit in the guess, or control c %d more time(s)\n", 3 - counter);
      counter ++;
    }
    else
    {
      int status;
      exit(status);
    }
  }
}

int shmsetup(key_t key, void ** pointer){
  int shmid = shmget(key, SIZE, IPC_CREAT | IPC_EXCL | 0644);
  printf("shmid is %d\n", shmid);

  if(shmid < 0)
  {
    printf("can't create shared memory (likely cause: shared memory already exists)\n");
    printf("error %d: %s\n", errno, strerror(errno));
    shmid = shmget(key, SIZE, 0644);
    printf("after getting shmid from existing memory\n");
  }

  * pointer = shmat(shmid, 0, 0);//checking array to be shared between players
  return shmid;
}

int semsetup(){
  int semid = semget(SEMKEY, 1, IPC_CREAT | IPC_EXCL | 0644);
  printf("semid is %d\n", semid);
  int semidExistedBefore = 0;
  if(semid < 0)
  {
    printf("can't create semaphore (likely cause: semaphore already exists)\n");
    printf("error %d: %s\n", errno, strerror(errno));
    semid = semget(SEMKEY, 1, 0644);
    printf("getting existing semid: %d\n", semid);
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
    printf("semaphore upped to have a value of %d\n", semval);
  }
  else
  {
    printf("semaphore existed before, was not changed\n");
    int semval = semctl(semid, 0, GETVAL, 0);
    if(semval < 1)//comment this out when semaphores are ready
    {//comment this out when semaphores are ready
      struct sembuf sb;//comment this out when semaphores are ready
      sb.sem_num = 0;//comment this out when semaphores are ready
      sb.sem_op = 1;//comment this out when semaphores are ready
      semop(semid, &sb, 1);//comment this out when semaphores are ready
    }//comment this out when semaphores are ready
    semval = semctl(semid, 0, GETVAL, 0);//comment this out when semaphores are ready
    printf("semaphore has a value of %d\n", semval);
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
  int x = strlen(word) - 1;
  word[x] = '\0';
  printf("%s\n", word);
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
  // while(x < 6){
  //   if (&wordbank[x] != "\0"){
  //   printf("%s", &wordbank[x]);
  //   x++;
  // // }
  //while(wordbank[x]){
  //  printf("%s", &wordbank[x]);
  //  x++ ;
  //}
  // printf("%s\n", &wordbank[0]);
  // printf("%s\n", &wordbank[1]);
  // printf("%s\n", &wordbank[2]);

  printf("}\n");
}
