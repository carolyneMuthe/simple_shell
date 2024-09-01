#include "main.h"

/**
 * open_files - Opens the source and destination files.
 * @src: The source file path
 * @dest: The destination file path
 * @src_fd: Pointer to the source file descriptor
 * @dest_fd: Pointer to the destination file descriptor
 * Return: 0 on success, -1 on failure
 */
int open_files(const char *src, const char *dest, int *src_fd, int *dest_fd)
{
	*src_fd = open(src, O_RDONLY);
	if (*src_fd < 0)
	{
		printerr("open source file");
		return (-1);
	}

	*dest_fd = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (*dest_fd < 0)
	{
		printerr("open destination file");
		close(*src_fd);
		return (-1);
	}

	return (0);
}

/**
 * read_write_loop - Reads from source and writes to destination file.
 * @src_fd: The source file descriptor
 * @dest_fd: The destination file descriptor
 * Return: 0 on success, -1 on failure
 */
int read_write_loop(int src_fd, int dest_fd)
{
	char buffer[1024];
	ssize_t bt_read, bt_written;

	while ((bt_read = read(src_fd, buffer, sizeof(buffer))) > 0)
	{
		bt_written = write(dest_fd, buffer, bt_read);
		if (bt_written != bt_read)
		{
			printerr("write to dest file");
			close(src_fd);
			close(dest_fd);
			return (-1);
		}
	}

	if (bt_read < 0)
	{
		printerr("read from source file");
		return (-1);
	}

	return (0);
}

/**
 * copy_file - Copies a file from src to dest.
 * @src: The source file path
 * @dest: The destination file path
 * Return: 0 on success, -1 on failure
 */
int copy_file(const char *src, const char *dest)
{
	int src_fd, dest_fd;
	int status;

	status = open_files(src, dest, &src_fd, &dest_fd);
	if (status != 0)
		return (-1);

	status = read_write_loop(src_fd, dest_fd);

	close(src_fd);
	close(dest_fd);

	return (status);
}

/**
 * fexists - This func checks if the file exists in the path.
 * @path: the path to check for file
 * Return: The access to the file.
 */
int fexists(const char *path)
{
	return (access(path, F_OK) == 0);
}

/**
 * isexec - this func checks if the file in path is executable.
 * @path: the path to check for exe file.
 * Return: An int
 */
int isexec(const char *path)
{
	return (access(path, X_OK) == 0);
}
