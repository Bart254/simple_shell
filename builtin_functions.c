#include "shell.h"
#include <string.h>
#include <errno.h>

/**
 * exit_function - exits from the program
 * @args: commands passed
 */
void exit_function(char **args)
{
	int exit_code;

	if (args[1])
		exit_code = atoi(args[1]);
	else if (errno && isatty(STDIN_FILENO) == 0)
		exit_code = 2;
	else
		exit_code = 0;
	free(args);
	exit(exit_code);
}

/**
 * env_function - prints current environment
 * @args: commands passed
 */
void env_function(char **args)
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
 * Return: function pointer
 */
void (*built_in(char **args))(char **)
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
			}
			else if (e == 1 && args[1] != NULL)
				return (NULL);
			return (arr[e].f);
		}
		e++;
	}
	return (NULL);
}
