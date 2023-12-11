#include "main.h"
/**
 * address_tkn - Tokenizes the PATH and returns the tokens to full path(folder)
 * @cmd: Command to be located in the PATH.
 *
 * Return: Full path of the command or cmd itself if full path wasn't found.
 */

char *address_tkn(char *cmd)
{
	FILE *fp;
	char address[MAX_PATH_LENGTH];/* Fixed size array to store address */
	char *cmd_address = malloc(MAX_PATH_LENGTH);/*Allocate memory - cmd_address*/
	char *address_cpy;
	char *folder;

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
	if (fgets(address, sizeof(address) - 1, fp) == NULL)/* Read the output*/
	{
		perror("Failed to read command output");
		exit(EXIT_FAILURE);
	}
	address_cpy = strdup(address);
	folder = strtok(address_cpy, ":");/* Tokenize the address */
	while (folder != NULL)/* Iterate through folders in PATH */
	{
		strcpy(cmd_address, folder);
		if (cmd_address[strlen(cmd_address) - 1] != '/')/*add a slash if not there */
			strcat(cmd_address, "/");
		strcat(cmd_address, cmd);/* Add command to the address */
		if (access(cmd_address, X_OK) == 0)/* Check if the command is executable */
		{
			free(address_cpy);
			return (cmd_address);
		}
		folder = strtok(NULL, ":");
	}
	free(address_cpy);
	return (cmd);
}
