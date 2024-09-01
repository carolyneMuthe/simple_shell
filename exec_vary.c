#include "main.h"

/**
 * exec_std_cmd - This function handles simple commands
 * typically found in "PATH".
 * @cmd: The command in PATH to handle.
 */

void exec_std_cmd(char *cmd)
{
	char *cmdpath, *tok, *argv[100];
	int i = 0, status;
	pid_t pid;

	tok = strtok(cmd, " ");
	while (tok != NULL)
	{
		argv[i++] = tok, tok = strtok(NULL, " ");
	}
	argv[i] = NULL;
	cmdpath = find_cmd(argv[0]);
	if (!cmdpath)
	{
		printerr(argv[0]);
		return;
	}
	pid = fork();
	if (pid == -1)
	{
		printerr("fork failed"), free(cmdpath);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (execve(cmdpath, argv, NULL) == -1)
		{
			printerr("execve failed"), free(cmdpath);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		free(cmdpath);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		{
			fprintf(stderr, "%s: cmd failed with stats %d\n",
					argv[0], WEXITSTATUS(status));
			exit(2);
		}
		exit(WEXITSTATUS(status));
	}
}

/**
 * exec_path_cmd - This func handles commands that
 * specify a path,
 * either relative or absolute
 * @cmd: The path command
 */

void exec_path_cmd(char *cmd)
{
	char *argv[100];
	int i = 0;
	char *tok;

	tok = strtok(cmd, " ");
	while (tok != NULL)
	{
		argv[i++] = tok;
		tok = strtok(NULL, " ");
	}
	argv[i] = NULL;

	if (access(cmd, X_OK) != 0)
	{
		printerr(cmd);
		return;
	}
	if (fork() == 0)
	{
		if (execve(cmd, argv, NULL) == -1)
		{
			printerr(cmd);
			exit(2);
		}
	}
	else
	{
		wait(NULL);
	}
}

/**
 * exec_copy_cmd - This function handles commands that
 * involves copying a file before
 * execution.
 * @cmd: The command.
 */
void exec_copy_cmd(char *cmd)
{
	char src[PATH_MAX];
	char dest[PATH_MAX];
	char *argv[2];
	pid_t pid;

	argv[0] = NULL;
	argv[1] = NULL;

	if (sscanf(cmd, "%s %s", src, dest) != 2)
	{
		printerr("Invalid command format");
		return;
	}

	if (copy_file(src, dest) != 0)
	{
		printerr("copy failed");
		return;
	}
	argv[0] = dest;

	pid = fork();
	if (pid == -1)
	{
		printerr("fork failed");
		return;
	}
	if (pid == 0)
	{
		if (execve(dest, argv, NULL) == -1)
		{
			printerr(dest);
			exit(2);
		}
	}
	else
	{
		wait(NULL);
	}
	remove(dest);
}

/**
 * exec_exit - This func specifially handles exit
 * and terminates the shell process.
 */
void exec_exit(void)
{
	exit(EXIT_SUCCESS);
}
