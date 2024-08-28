#include "shell.h"

/**
 * main - Entry point of the simple shell program
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	shell_loop();
	return (0);
}
/**
 * shell_loop - The main loop of the shell,
 *handles reading, parsing, and executing commands
 */
void shell_loop(void)
{
	 char *line;
	 char **args;
	 int status = 1;

	do {
	if (isatty(STDIN_FILENO))
		printf("($) ");
	line = read_line();
	args = split_line(line);
	execute_command(args);
	free(line);
	free(args);
	} while (status);
}
/**
 * read_line - Reads a line of input from stdin
 *
 * Return: The input line as a string
 */
char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;

	if (getline(&line, &bufsize, stdin) == -1)
	{
		if (feof(stdin))
			exit(EXIT_SUCCESS);
		else
		{
			perror("read_line");
			exit(EXIT_FAILURE);
		}
	}
	return (line);
}
/**
 * split_line - Splits a line into arguments
 * @line: The line to be split
 *
 * Return: An array of arguments
 */
char **split_line(char *line)
{
	int bufsize = 64, position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!tokens)
	{
		perror("split_line");
		exit(EXIT_FAILURE);
	}
	token = strtok(line, " \t\r\n\a");
	while (token != NULL)
	{
		tokens[position++] = token;
		if (position >= bufsize)
		{
			bufsize += 64;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				perror("split_line");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, " \t\r\n\a");
	}
	tokens[position] = NULL;
	return (tokens);
}
/**
 * execute_command - Executes a command in a child process
 * @args: An array of arguments for the command
 */
void execute_command(char **args)
{
	pid_t pid;
	int status;

	if (args[0] == NULL)
		return;

	pid = fork();
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			perror("hsh");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("hsh");
	}
	else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}

