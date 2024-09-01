#include "main.h"

/**
 * exec_std_cmd - Handles simple commands typically found in "PATH".
 * @cmd: The command in PATH to handle.
 *
 * Return: void
 */
void exec_std_cmd(char *cmd)
{
	char *cmdpath, *argv[100];

	parse_cmd(cmd, argv);
	cmdpath = find_cmd(argv[0]);
	if (!cmdpath)
	{
		printerr(argv[0]);
		return;
	}
	fork_and_exec(cmdpath, argv);
}

/**
 * exec_path_cmd - Handles commands that specify a path,
 * either relative or absolute.
 * @cmd: The path command.
 *
 * Return: void
 */
void exec_path_cmd(char *cmd)
{
	char *argv[100];

	parse_cmd(cmd, argv);

	if (access(cmd, X_OK) != 0)
	{
		printerr(cmd);
		return;
	}

	fork_and_exec(cmd, argv);
}

/**
 * exec_copy_cmd - Handles commands that involve,
 * copying a file before execution.
 * @cmd: The command.
 *
 * Return: void
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
 * exec_exit - Handles exit and terminates the shell process.
 *
 * Return: void
 */
void exec_exit(void)
{
	exit(EXIT_SUCCESS);
}
