#include "shell.h"

/**
 * read_line - Reads a line from stdin
 *
 * Return: The input line or NULL on failure
 */
char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;

	if (getline(&line, &bufsize, stdin) == -1)
	{
		if (feof(stdin))
			return (NULL);
		perror("getline");
		exit(EXIT_FAILURE);
	}
	return (line);
}
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
