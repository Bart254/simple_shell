#include <stdlib.h>

/**
 * unsetenv_f - unsets environment variable
 * @args: arguments passed
 * @status: exit code
 */
void unsetenv_f(char **args, int status __attribute__((unused)))
{
	if (args[1] == NULL)
	{
		free(args);
		return;
	}
	unsetenv(args[1]);
}
