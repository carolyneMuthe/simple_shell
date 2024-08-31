#include "shell.h"

/**
 * execute_command - Executes a command
 * @args: array of arguments to execute
 */
void execute_command(char **args)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)  /* Child process */
	{
		if (execve(args[0], args, environ) == -1)
		{
			perror(args[0]);
			_exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)  /* Fork error */
	{
		perror("fork");
	}
	else  /* Parent process */
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}
