#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/**
 * shell_loop - Main loop for the shell
 *
 * Continuously prompts the user for input and executes commands.
 */
void shell_loop(void)
{
	char *line;
	char *command;
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
		command = strtok(line, "\n");
		if (command == NULL)
		{
			free(line);
			continue;
		}
		if (strcmp(command, "exit") == 0)
		{
			free(line);
			break;
		}
		execute_command(command);
		free(line);
	}
}

