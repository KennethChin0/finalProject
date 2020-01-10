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

int checkletter(char* enter, char** bankletter)//derek
{
  int bankLength = strlen(*bankletter);
  char * charIndex = strchr(*bankletter, *enter);
  if(charIndex)
  {
    *charIndex = bankletter[bankLength - 1];
    bankletter[bankLength -1] = NULL;
    //set the last letter to null, and the last letter replaces the given letter
    return 1;
  }
  else
  {
    return 0;
  }
}

int draw(int lives);

int generate_word(char* word);

void setup();
