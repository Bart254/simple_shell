#include <stdlib.h>

/**
 * _free - free all memory when execve fails
 * @args: arrays of arguments
 * @buffer: contains passed commands
 */
void _free(char **args, char *buffer)
{
	if (args)
	{
		free(args);
		args = NULL;
	}
	if (buffer)
	{
		free(buffer);
		buffer = NULL;
	}
}
