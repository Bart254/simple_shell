#ifndef SHELL_H
#define SHELL_H
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
void prompt(void);
char **get_args(char *buffer);
void execute(char *path_arg, char **args, int *status);
void _free(char **args, char *path_arg);
char *path(char *arg);
void print_error(char *name, char **args, int line_no, int *status);
extern char **environ;

/**
 * struct shell_bin - structure of shell builtins
 * @name: name of the built in function
 * @f: the actual built in function
 */
typedef struct shell_bin
{
	char *name;
	void (*f)(char **args, int status);
} builtin;
void env_function(char **args, int status);
void exit_function(char **args, int status);
void setenv_f(char **args, int status);
void unsetenv_f(char **args, int status);
void cd(char **args, int status);
void (*built_in(char **args, int *status))(char **args, int status);
char *_getline(void);
char *_strtok(char *str, const char *delim);

#endif
