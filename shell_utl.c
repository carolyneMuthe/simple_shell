#include "main.h"

/**
 * printerr - Prints an error message
 * @cmd: The command that caused the error
 */

void printerr(char *cmd)
{
	perror(cmd);
}

/**
 * copy_file - copies a file from src to dest
 * @src: The source file path
 * @dest: The destination file path
 * Return: 0 on success, -1 on failure
 */

int copy_file(const char *src, const char *dest)
{
	int src_fd, dest_fd;
	char buffer[1024];
	ssize_t bt_read, bt_writn;

	src_fd = open(src, O_RDONLY);
	if (src_fd < 0)
	{
		printerr("open source file");
		return (-1);
	}

	dest_fd = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (dest_fd < 0)
	{
		printerr("open destination file");
		close(src_fd);
		return (-1);
	}
	while ((bt_read = read(src_fd, buffer, sizeof(buffer))))
	{
		bt_writn = write(dest_fd, buffer, bt_read);
		if (bt_writn != bt_read)
		{
			printerr("write to dest file");
			close(src_fd);
			close(dest_fd);
			return (-1);
		}
	}
	close(src_fd);
	close(dest_fd);
	if (bt_read < 0)
	{
		perror("read from source file");
		return (-1);
	}
	return (0);
}

/* EXEC UTILS */

/**
 * is_cpy - func to handle copyomg if files
 * @cmd: The copy command
 * Return: a integer
 */
int is_cpy(char *cmd)
{
	return (strncmp(cmd, "cp_", 3) == 0);
}

/**
 * is_path - func to handle path commands
 * @cmd: The path command
 * Return: an int
 */
int is_path(char *cmd)
{
	return (strchr(cmd, '/') != NULL);
}
