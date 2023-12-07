#ifndef MAIN_H
/*! \file main.h */
#define MAIN_H

#define MAX_PATH_LENGTH 1024
#define MAX_ARGUMENTS 10
#define MAX_INPUT_LENGTH 100
#define PROMPT " $ - "

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

char *address_tkn(char *cmd);
extern char **environ;
void input_tkn(char *input);
int main(void);


#endif
