#include "main.h"
/**
 * handler - handles the prompt
 *
 * @signal: looks out for input signals.
 */

void handler(int signal)
{
	char *prompt = "\n $ ";

	(void)signal;
	write(1, prompt, strlen(prompt));
	fflush(stdout);
}
