#include "main.h"

/**pr_env - This function prints the current env variables.
 * @envp: The env variables passed from the
 * main function
 */

void pr_env(char **envp)
{
	int i = 0;
	while (envp[i] != NULL)
	{
		write(STDOUT_FILENO, envp[i], strlen(envp[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}
