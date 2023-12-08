#include "main.h"

char *input_tkn(char *input)
{
	size_t len = 0;
	int chars_read;

	/* Input String tokening */ 
	char *delims = " \n\a\t\r";
	char *input_args[MAX_ARGUMENTS];
	char *tkns;
	int pid;

	chars_read = getline(&input, &len, stdin);
    

	if (chars_read == -1)
	{
		/* Exit command from input / Ctrl + D */ 
		if (feof(stdin))
		{
			/* exit */ 
			write(1, "\nExiting...\n", 13);
				sleep(1.5);
			free(input);
				exit(0);
		}
		else
		{
			perror("Error recognizing input");
			free(input);
			exit(EXIT_FAILURE);
		}
	}
	else if (chars_read == 1)
	{
		return(input);
	}
	else
	{
		int index = 0;

		/* Tokenizing the input string */ 
		tkns = strtok(input, delims);

		/* while (tkns != NULL && index < MAX_ARGUMENTS - 1)
		   {
		   input_args[index++] = tkns;
		   tkns = strtok(NULL, delims);
		   }*/
		for( index; tkns != NULL && index < MAX_ARGUMENTS - 1; index++)
		{
			input_args[index] = tkns;
			tkns = strtok(NULL, delims);
		}

		input_args[index] = NULL;

		/* Handle Built-in commands */ 
		if (strcmp(input_args[0], "cd") == 0)
		{

			/* If the user does not pass any argument*/
			if (input_args[1] == NULL)
			{
                {
			   printf("cd : error recognizing directory name\n");
			   printf("cd 'enter the name of the directory'\n");
			   printf("enter command : \"cd --help\" for more information\n");
			   }
			}
			
			else {
				struct stat st;
				if (stat(input_args[1], &st) == 0 && S_ISDIR(st.st_mode)) 
                {
					/* Directory exists, change to it */ 
					if (chdir(input_args[1]) == -1) {
						perror("cd");
					}
				} 
                else 
                {
					/* Directory does not exist */ 
					printf("cd: Directory '%s' does not exist\n", input_args[1]);
				}
			}

		}
		else if(strcmp(input_args[0], "exit")== 0)
		{
			write(1, "Exiting...\n", 12);
			sleep(1.5);
			exit(0);
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
					exit(EXIT_FAILURE);
				}
				else
				{
					/* Child process cleanup */ 
					int status;
					waitpid(pid, &status, 0);

					if (WEXITSTATUS(status) && WIFEXITED(status) != 0)
					{
						printf("Child Process -%d exit Status : %d\n", pid, WEXITSTATUS(status));
					}
				}
                printf(PROMPT);
                fflush(stdout);
			}
		}
	}
}
