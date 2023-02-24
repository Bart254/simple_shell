#include "shell.h"
#include <string.h>
#include <errno.h>

/**
 * exit_function - exits from the program
 * @args: commands passed
 * @status: returned code
 */
void exit_function(char **args, int status)
{
	free(args);
	exit(status);
}

/**
 * env_function - prints current environment
 * @args: commands passed
 * @status: exit code
 */
void env_function(char **args, int status __attribute__((unused)))
{
	int e;

	free(args);
	for (e = 0; environ[e]; e++)
	{
		printf("%s\n", environ[e]);
		fflush(stdout);
	}
}

/**
 * built_in - checks for a command that calls a builtin
 * @args: commands passed
 * @status: code to be  returned
 * Return: function pointer
 */
void (*built_in(char **args, int *status))(char **, int)
{
	int e = 0, code, i;
	builtin arr[] = {{"exit", exit_function}, {"env", env_function},
			 {NULL, NULL}};
	char *str;

	while (arr[e].name != NULL)
	{
		if (strcmp(args[0], arr[e].name) == 0)
		{
			if (e == 0 && args[1] != NULL)
			{
				str = args[1];
				i = strlen(str) - 1;
				code = atoi(str);
				while (i >= 0)
				{
					if (str[i] != (code % 10 + '0'))
						return (NULL);
					i--;
					code /= 10;
				}
				*status = atoi(str);
				return (arr[0].f);
			}
			else if (e == 1 && args[1] != NULL)
				return (NULL);
			if (e == 1)
				*status = 0;
			return (arr[e].f);
		}
		e++;
	}
	return (NULL);
}
