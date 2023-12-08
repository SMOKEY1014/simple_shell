#include "main.h"

char *address_tkn(char *cmd)
{
	FILE *fp;
	
	char address[MAX_PATH_LENGTH];/* Fixed size array to store address */
	char *cmd_address = malloc(MAX_PATH_LENGTH);/*Allocate memory - cmd_address*/
	char *address_cpy;

	if (cmd_address == NULL)
	{
		perror("Memory allocation error");
		exit(EXIT_FAILURE);
	}
	fp = popen("echo $PATH", "r");/* Open the command for reading */
	if (fp == NULL)
	{
		perror("Failed to run command");
		exit(EXIT_FAILURE);
	}
	/* Read the output a line at a time */
	if (fgets(address, sizeof(address) - 1, fp) == NULL)
	{
		perror("Failed to read command output");
		exit(EXIT_FAILURE);
	}
	address_cpy = strdup(address);
	char *folder = strtok(address_cpy, ":");/* Tokenize the address */
	while (folder != NULL)/* Iterate through folders in PATH */
	{
		strcpy(cmd_address, folder);
		if (cmd_address[strlen(cmd_address) - 1] != '/')/* Check if cmd_address ends with a slash */
			strcat(cmd_address, "/");

		strcat(cmd_address, cmd);/* Add command to the address */ 
		 
		if (access(cmd_address, X_OK) == 0)/* Check if the command is executable */
		{
			free(address_cpy);
			return cmd_address;
		}
		folder = strtok(NULL, ":");
	}
	free(address_cpy);
	return (cmd);
}