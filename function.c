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
// int checkletter(char* enter, char** bankletter)//derek
// {
//   int bankLength = strlen(*bankletter);
//   char * charIndex = strchr(*bankletter, *enter);
//   if(charIndex)
//   {
//     *charIndex = bankletter[bankLength - 1];
//     bankletter[bankLength -1] = NULL;
//     //set the last letter to null, and the last letter replaces the given letter
//     return 1;
//   }
//   else
//   {
//     return 0;
//   }
// }

int draw(int lives){
  printf("Lives: %d\n", lives);
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

void setup();
