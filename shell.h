#ifndef SHELL_H
#define SHELL_H
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
void prompt(void);
char **get_args(char *buffer);
void _free(char **args, char *path_arg);
char *path(char *arg);
void print_error(char *name, char **args, int line_no);
extern char **environ;

/**
 * struct shell_bin - structure of shell builtins
 * @name: name of the built in function
 * @f: the actual built in function
 */
typedef struct shell_bin
{
	char *name;
	void (*f)(char **);
} builtin;
void env_function(char **);
void exit_function(char **);
void (*built_in(char **args))(char **args);
char *_getline(void);
char *_strtok(char *str, const char *delim);

#endif
