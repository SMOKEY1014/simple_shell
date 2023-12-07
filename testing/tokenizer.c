#include "main.h"



char *address_tkn(char *cmd)
{
    FILE *fp;
    char address[MAX_PATH_LENGTH];  // Fixed size array to store address
    char *cmd_address = malloc(MAX_PATH_LENGTH);  // Allocate memory for cmd_address
    char *address_cpy;

    if (cmd_address == NULL)
    {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    // Open the command for reading
    fp = popen("echo $PATH", "r");
    if (fp == NULL)
    {
        perror("Failed to run command");
        exit(EXIT_FAILURE);
    }

    // Read the output a line at a time
    if (fgets(address, sizeof(address) - 1, fp) == NULL)
    {
        perror("Failed to read command output");
        exit(EXIT_FAILURE);
    }

    address_cpy = strdup(address);

    // Tokenize the address
    char *folder = strtok(address_cpy, ":");
    
    // Iterate through folders in PATH
    while (folder != NULL)
    {
        strcpy(cmd_address, folder);

        // Check if cmd_address ends with a slash
        if (cmd_address[strlen(cmd_address) - 1] != '/')
            strcat(cmd_address, "/");

        // Add command to the address
        strcat(cmd_address, cmd);

        // Check if the command is executable
        if (access(cmd_address, X_OK) == 0)
        {
            free(address_cpy);
            return cmd_address;
        }

        folder = strtok(NULL, ":");
    }

    free(address_cpy);
    return (cmd);
}



void input_tkn(char *input)
{
    size_t len = 0;
    int chars_read;

    // Input String tokening
    char *delims = " \n\a\t\r";
    char *input_args[MAX_ARGUMENTS];
    char *tkns;
    int pid;
    

    chars_read = getline(&input, &len, stdin);

    if (chars_read == -1)
    {
        // Exit command from input / Ctrl + D
        if (feof(stdin))
        {
            // exit
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
        return;
    }
    else
    {
        int index = 0;

        // Tokenizing the input string
        tkns = strtok(input, delims);

        while (tkns != NULL && index < MAX_ARGUMENTS - 1)
        {
            input_args[index++] = tkns;
            tkns = strtok(NULL, delims);
        }

        input_args[index] = NULL;

        // Handle Built-in commands
        

        // Forking
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
                // Child process cleanup
                int status;
                waitpid(pid, &status, 0);

                if (WEXITSTATUS(status) && WIFEXITED(status) != 0)
                {
                    printf("\nChild Process - %d exit Status : %d(non-zero)\n", pid, WEXITSTATUS(status));
                }
            }
        }
    }
}