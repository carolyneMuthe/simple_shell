#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

extern char **environ;

void execute_command(char **argsd);
char *read_line(void);
char **split_line(char *line);
void shell_loop(void);

#endif /* SHELL_H */
