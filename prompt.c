#include "main.h"
/**
 * print_shell_prompt - Prints prompt with the current user and working dir.
 *
 * Format: "<user>@<current_directory>$ ".
 * If an error occurs during the retrieval of the current working directory,
 * an error message is printed, and the program exits with a failure status.
 */

void print_shell_prompt(void)
{
/*
 *	char cwd[MAX_PATH_LENGTH];
 *	if (getcwd(cwd, sizeof(cwd)) != NULL)
 *	{
 *		_print("%s@%s$ ", getenv("USER"), cwd);
 *	}
 *	else
 *	{
 *		_print(" $ - ");
 *	}
 */
	_print(" $ - ");
}
