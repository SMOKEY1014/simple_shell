#include "main.h"


int main(void)
{
    char *input = NULL;
    char cwd[MAX_PATH_LENGTH];

    while (1)
    {
        /* Get and display the current working directory */ 
        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            printf("%s:%s$ ", getenv("USER"), cwd);
        }
        else
        {
            perror("getcwd() error");
            exit(EXIT_FAILURE);
        }
        /* Error handling Memory allocation */ 
        if ((input = (char *)malloc(MAX_INPUT_LENGTH)) == NULL)
        {
            perror("Memory allocation failure");
            exit(EXIT_FAILURE);
        }

        input_tkn(input);
    }
    free(input); /* Free allocated memory */
    printf("Is a TTY: %d\n", isatty(STDIN_FILENO));
	if (isatty(STDIN_FILENO) == 1)
	{
		printf("Inside isatty condition\n");
		write(1, "\n", 1);
	}

    return 0;
}
