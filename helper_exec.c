#include "main.h"

/**
 * parse_cmd - Parses a command into arguments.
 * @cmd: The command to parse.
 * @argv: Array to store the arguments.
 *
 * Return: void
 */
void parse_cmd(char *cmd, char *argv[])
{
	int i = 0;
	char *tok;

	tok = strtok(cmd, " ");
	while (tok != NULL)
	{
		argv[i++] = tok;
		tok = strtok(NULL, " ");
	}
	argv[i] = NULL;
}

/**
 * fork_and_exec - Forks a process and executes the command.
 * @cmdpath: The path to the command.
 * @argv: The command arguments.
 *
 * Return: void
 */
void fork_and_exec(char *cmdpath, char *argv[])
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		printerr("fork failed");
		free(cmdpath);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (execve(cmdpath, argv, NULL) == -1)
		{
			printerr("execve failed");
			free(cmdpath);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		handle_exit_status(status, argv);
	}
	free(cmdpath);
}

/**
 * handle_exit_status - Handles the exit status of a child process.
 * @status: The exit status.
 * @argv: The command arguments.
 *
 * Return: void
 */
void handle_exit_status(int status, char *argv[])
{
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		fprintf(stderr, "%s: cmd failed with status %d\n",
			argv[0], WEXITSTATUS(status));
		exit(2);
	}
	exit(WEXITSTATUS(status));
}
