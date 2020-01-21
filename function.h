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

#define CHECK_KEY 123
#define BANK_KEY 456
#define ANSWER_KEY 789
#define WON_KEY 012
#define LOST_KEY 345

#define SEMKEY 67890
#define SIZE 100


void sighandler(int signal);

int shmsetup(key_t key, void ** pointer);

int semsetup();

void clear();

int draw(int lives);

char* generate_word();

char **  parse_args( char * line );

void words(char * wordbank);

void disasterPreventionText();
