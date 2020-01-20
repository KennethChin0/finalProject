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

int shmsetup(int ** check){
  int shmid = shmget(SHMKEY, SIZE, IPC_CREAT | IPC_EXCL | 0644);
  printf("shmid is %d\n", shmid);

  if(shmid < 0)
  {
    printf("error likely from getting id from existing file\n");
    printf("error %d: %s\n", errno, strerror(errno));
    shmid = shmget(SHMKEY, SIZE, 0644);
    printf("after getting shmid from existing memory\n");
  }

  * check = shmat(shmid, 0, 0);//checking array to be shared between players
  return shmid;
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
