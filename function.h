#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

int checkletter(char* enter, char* bankletter);

int draw(int lives);

int generate_word(char* word);

void setup();
