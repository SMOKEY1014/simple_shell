#include "shell.h"


void executeCommand(char *input, char *path) {
    // Tokenize the input string
    char *delimiters = " \n";
    char *args[MAX_ARGUMENTS];
    int num_args = 0;

    char *token = strtok(input, delimiters);
    while (token != NULL && num_args < MAX_ARGUMENTS) {
        args[num_args] = token;
        num_args++;
        token = strtok(NULL, delimiters);
    }
    args[num_args] = NULL;

    // Search for the executable in the directories listed in path
    char *programPath = NULL;
    for (int i = 0; i < MAX_ARGUMENTS; i++) {
        char full_path[MAX_PATH_LENGTH];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, args[0]);

        if (access(full_path, X_OK) == 0 && access(full_path, F_OK)) {
            programPath = strdup(full_path);
            
            printf("Program path now is : %s ",programPath);
            break;
        }
    }

    if (programPath == NULL) {
        fprintf(stderr, "Command '%s' not found in $PATH\n", args[0]);
        exit(EXIT_FAILURE);
    }

    // Execute the program
    char *envp[] = { NULL };
    execve(programPath, args, envp);
    if (execve(programPath, args, envp) == -1) {
        perror("execve");
        exit(EXIT_FAILURE);
    }
}