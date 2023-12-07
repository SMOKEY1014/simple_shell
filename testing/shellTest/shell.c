#include "shell.h"

#define MAX_TOKENS 50
int main(void) {
    FILE *fp;
    char path[1035];

    // Open the command for reading
    fp = popen("echo $PATH", "r");
    if (fp == NULL) {
        printf("Failed to run command\n");
        exit(EXIT_FAILURE);
    }

    // Read the output a line at a time
    if (fgets(path, sizeof(path) - 1, fp) != NULL) {
        // Tokenize the path using ":"
        char *delimiters = ":";
        char *tokens[MAX_ARGUMENTS];
        int num_tokens = 0;

        char *token = strtok(path, delimiters);
        while (token != NULL && num_tokens < MAX_ARGUMENTS) {
            tokens[num_tokens] = token;
            num_tokens++;
            token = strtok(NULL, delimiters);
        }
        /*added code */
        printf("Tokens:\n");
        for (int i = 0; i < num_tokens; i++) {
            
            printf("%s\n", tokens[i]);
        }

        // Close the pipe
        pclose(fp);
        char *input[100];
        /* Prompt for user input*/
		write(1, "Shell$ ", 7);

		/* Getting users input*/
		input = getline(&line, &len, stdin);

        // Execute the command using the path tokens
        executeCommand(input, tokens[0]);
    }

    return 0;
}