#include "main.h"

/**
 * exec_command - This command executes a command
 * based on a specific
 * implementation for handling using execve.
 * @cmd: a particular command to exec
 */

void exec_command(char *cmd, char **env)
{
	if (strcmp(cmd, "exit") == 0)
	{
		free(cmd);
		exit(EXIT_SUCCESS);
	}
	else if (strcmp(cmd, "env") == 0)
	{
		pr_env(env);
	}
	else if (is_cpy(cmd))
	{
		exec_copy_cmd(cmd);
	}
	else if (is_path(cmd))
	{
		exec_path_cmd(cmd);
	}
	else
	{
		exec_std_cmd(cmd);
	}
}
