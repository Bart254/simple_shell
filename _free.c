#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * _free - free all memory when execve fails
 * @args: arrays of arguments
 * @path_arg: first argument
 */
void _free(char **args, char *path_arg)
{
	if (path_arg)
	{
		free(path_arg);
		path_arg = NULL;
	}
	if (args)
		free(args);
}
