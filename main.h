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
#include <fcntl.h>
#include <ctype.h>

#define PROMPT "Nana$ "
#define PATH_MAX 1024
/* Function prototypes */
void execute_command(char *cmd, char **env);
char *read_in(void);
char *trim_ws(char *str);
void printerr(char *cmd);
char *find_cmd(char *cmd);
void shell(char **env);
/* The prototypes for env */
void pr_env(char **envp);
/* specilized exec func prototypes */
void exec_std_cmd(char *cmd);
void exec_path_cmd(char *cmd);
void exec_copy_cmd(char *cmd);

/* helper utils prototypes for exec func */
int is_cpy(char *cmd);
int is_path(char *cmd);
int fexists(const char *path);
int isexec(const char *path);

/* More utils */
int copy_file(const char *src, const char *dest);

#endif /* SHELL_H */
