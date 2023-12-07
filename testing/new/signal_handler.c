#include "main.h"

void signal_handler(int signal)
{
	/* We do not want the program to exit but to prompt the user with this*/
	char *prompt = "\nshell$ ";

	(void)signal;
	write(1, prompt, strlen(prompt));
	fflush(stdout);
}
