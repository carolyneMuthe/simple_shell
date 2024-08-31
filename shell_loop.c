#include "shell.h"

/**
 * shell_loop - Main loop for the shell
 *
 * Continuously prompts the user for input and executes commands.
 */
void shell_loop(void)
{
	char *line;
	char **args;
	int status = 1;

	while (status)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "#cisfun$ ", 9);
		line = read_line();
		if (line == NULL)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}
		args = split_line(line);
		if (args[0] == NULL)
		{
			free(line);
			free(args);
			continue;
		}
		if (strcmp(args[0], "exit") == 0)
		{
			free(line);
			free(args);
			break;
		}
		execute_command(args);
		free(args);
		free(line);
	}
}

