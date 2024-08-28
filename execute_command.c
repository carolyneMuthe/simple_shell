#include "shell.h"

/**
 * execute_command - Executes a command
 * @command: The command to execute
 */
void execute_command(char *command)
{
	pid_t pid;
	int status;
	char *args[2];

	 args[0] = command;
	 args[1] = NULL;

	pid = fork();
	if (pid == 0)  /* Child process */
	{
		if (execve(command, args, NULL) == -1)
		{
			perror(command);
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
