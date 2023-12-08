#include "main.h"


int main(void)
{
	
	char *input = NULL;

	while (1)
	{
		printf(PROMPT);

		input_tkn(input);
	}
	free(input); /* Free allocated memory */
	return (0);
}
