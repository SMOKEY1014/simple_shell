#include "main.h"
/**
 * builtin_cd - Handles the 'cd' built-in command.
 * @args: Argument passed to the 'cd' command.
 *
 * If the user does not pass any argument, changes to the user's home dir.
 * If an argument is provided, changes to the specified directory.
 */

void builtin_cd(char *args)
{
	/* Handle Built-in commands */
	/* If the user does not pass any argument*/
	if (args == NULL)
	{
		char *home = getenv("HOME");

		if (home == NULL)
		{
			perror("cd: HOME envrionment variable is not set\n");
		}
		else
		{
			/* cd home*/
			if (chdir(home) != 0)
			{
				perror("could not change directory");
			}
		}
	}
	else
	{
		/* If the user adds argument*/
		if (chdir(args) != 0)
		{
			perror("could not change directory");
		}
	}
}
/**
 * builtin_exit - Handles the 'exit' built-in command.
 *
 * Displays an exit message to standard output, sleeps then exits.
 */

void builtin_exit(void)
{
	exit(0);
}
