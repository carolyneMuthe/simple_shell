#include "main.h"

/**
 * read_in - THis function read the input from
 * the user.
 *
 * Return: The input string.
 */

char *read_in(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	read = getline(&line, &len, stdin);
	if (read == -1)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

/**
 * trim_ws - Removes leading and trailing
 * whitespace from a string
 * @str: The string to trim
 * Return: The trimmed string.
 */
char *trim_ws(char *str)
{
	char *start = str;
	char *end;

	if (str == NULL || *str == '\0')
	{
		return (str);
	}

	while (isspace((unsigned char)*start))
	{
		start++;
	}

	if (*start == '0')
	{
		return (start);
	}

	end = start + strlen(start) - 1;
	while (end > start && isspace((unsigned char)*end))
	{
		end--;
	}
	end[1] = '\0';

	return (start);
}

/**
 * find_cmd - Searched for a command in the dirs
 * listed in PATH.
 * @cmd: The command to search
 * Return: The full patth to the command if found,
 * otherwise NULL.
 */

char *find_cmd(char *cmd)
{
	char *pathenv = getenv("PATH");
	char *pathcpy;
	char *pathdir, *fullpath;
	size_t cmdlen, pathlen;

	if (!pathenv)
	{
		return (NULL);
	}
	pathcpy = strdup(pathenv);
	cmdlen = strlen(cmd);

	pathdir = strtok(pathcpy, ":");
	while (pathdir != NULL)
	{
		pathlen = strlen(pathdir);
		fullpath = malloc(pathlen + cmdlen + 2);
		if (!fullpath)
		{
			free(pathcpy);
			return (NULL);
		}

		strcpy(fullpath, pathdir);
		strcat(fullpath, "/");
		strcat(fullpath, cmd);

		if (access(fullpath, X_OK) == 0)
		{
			free(pathcpy);
			return (fullpath);
		}

		free(fullpath);
		pathdir = strtok(NULL, ":");
	}

	free(pathcpy);
	return (NULL);
}
