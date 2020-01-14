#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <errno.h>

#define SHMKEY 12345
#define SIZE 1024

int checkletter(char* enter, char** bankletter);

int draw(int lives);

char* generate_word();

char **  parse_args( char * line );

void setup();
