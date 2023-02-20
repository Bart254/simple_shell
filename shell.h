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
int excve_error(char *name, char **args, char *);
extern char **environ;

/**
 * struct shell_bin - structure of shell builtins
 * @name: name of the built in function
 * @f: the actual built in function
 */
typedef struct shell_bin
{
	char *name;
	int (*f)(void);
} builtin;
int env_function(void);
int exit_function(void);
int (*built_in(char *command))(void);
char *_getline(void);
#endif
