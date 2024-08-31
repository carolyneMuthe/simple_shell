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
