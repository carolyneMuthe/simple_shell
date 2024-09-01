#include "main.h"
/**
 * shell - The ,main loop of the shell
 * @env: The environment varible
 */

void shell(char **env)
{
	char *line;
	char *trline;

	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
		write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
		}

		line = read_in();
		if (line == NULL)
		{
			exit(EXIT_SUCCESS);
		}

		trline = trim_ws(line);

		if (trline[0] != '\0')
		{
			exec_command(trline, env);
		}

		free(line);
	}
}
/**
 * main - the entry
 * @argc: The number of cli arg
 * @argv: The cli arguments
 * @envp: The enviornment var
 * Return: 0 Always success
 */

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	shell(envp);
	return (0);
}
