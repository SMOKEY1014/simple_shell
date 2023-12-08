#include "main.h"

void builtin_cd(char *args)
{
    /* Handle Built-in commands */ 
	/* If the user does not pass any argument*/
	if (args == NULL)
  {
    char *home = getenv("HOME");
    
    if(home == NULL)
    {
        perror("cd: HOME envrionment variable is not set\n");
    }
    else
    {
        /* Take the user home*/
        if (chdir(home) != 0)
        {
            perror("could not change directory");
        }
    }
  }
else
  {
     /* If the user adds an argument*/
     if (chdir(args) != 0)
        {
            perror("could not change directory");
        }
  }
}


void builtin_exit(void)
{	
    write(1, "Exiting...\n", 12);
	sleep(1.5);
	exit(0);
}
        