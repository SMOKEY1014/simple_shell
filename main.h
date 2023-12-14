#ifndef MAIN_H
/*! \file main.h */
#define MAIN_H

#define MAX_PATH_LENGTH 1024
#define MAX_ARGUMENTS 10
#define MAX_INPUT_LENGTH 100


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>


char *address_tkn(char *cmd);
extern char **environ;
char *input_tkn(char *input);
void handler(int signal);
void print_shell_prompt(void);
void _print(const char *format, ...);
void builtin_cd(char *input_args);
void builtin_exit();
int main(void);


#endif
