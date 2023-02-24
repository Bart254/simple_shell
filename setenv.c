#include <stdlib.h>
#include <stdio.h>

/**
 * setenv_f - sets a variable path to value
 * @args: arguments passed to setenv
 * @status: exit code
 */
void setenv_f(char **args, int status __attribute__((unused)))
{
	if (args[1] == NULL || args[2] == NULL)
		return;
	if (setenv(args[1], args[2], 1) == -1)
		perror(args[0]);
}
