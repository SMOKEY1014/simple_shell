#include "main.h"

void handler(int signal)
{
    char *prompt = "\n $ ";

    (void)signal;
    write(1, prompt, strlen(prompt));
    fflush(stdout);
}