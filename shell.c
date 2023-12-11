#include "main.h"
void hack(void);
/**
 * main - Entry point for the shell program, it also tokenizes
 * and processes users input.
 *
 * Return: Always 0.
 */


int main(void)
{
	size_t len = 0;
	int chars_read;
	char *input = NULL;

	/* Input String tokening */
	char *delims = " \n\a\t\r";
	char *input_args[MAX_ARGUMENTS];
	char *tkns;
	int pid;

	while (1)
	{

		print_shell_prompt();
		chars_read = getline(&input, &len, stdin);


		if (chars_read == -1)
		{
			/* Exit command from input / Ctrl + D */
			if (feof(stdin))
			{
				/* exit */
				write(1, "\nExiting...\n", 13);
				_print("Exited successfully...\n");
				sleep(1.5);
				free(input);
				exit(0);
			}
			else
			{
				perror("Error recognizing input");
				return (-1);
			}
		}
		else if (chars_read == 1)
		{
			continue;
		}
		else
		{
			int index;
			/* Tokenizing the input string */
			tkns = strtok(input, delims);
			for (index = 0; tkns != NULL && index < MAX_ARGUMENTS - 1; index++)
			{
				input_args[index] = tkns;
				tkns = strtok(NULL, delims);
			}
			input_args[index] = NULL;
			/* Handle Built-in commands */
			if (strcmp(input_args[0], "cd") == 0)
			{
				builtin_cd(input_args[1]);
			}
			else if (strcmp(input_args[0], "exit") == 0)
			{
				builtin_exit();
			}
			else
			{
				/* Forking */
				pid = fork();
				if (pid == -1)
				{
					perror("Program failed to fork");
					free(input);
					exit(EXIT_FAILURE);
				}
				else if (pid == 0)
				{
					char *cmdAddress = address_tkn(input_args[0]);

					if (cmdAddress != NULL)
					{
						execve(cmdAddress, input_args, environ);
						perror("execve");
						free(input);
						exit(1);
					}
				}
				else
				{
					/* Child process cleanup */
					int status;

					waitpid(pid, &status, 0);

					if (WEXITSTATUS(status) && WIFEXITED(status) != 0)
					{
						_print("Child Process -%d exit Status : %d\n", pid, WEXITSTATUS(status));
					}
				}
			}
		}
	}
	free(input);
	return (0);
}
