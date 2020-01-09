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


int main() {
    int lives = 6;
    // setup();
    char* word[512];
    while (lives > 0){
      lives-- ;
      printf("hi\n");
    }

  }
