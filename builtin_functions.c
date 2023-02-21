#include "shell.h"
#include <string.h>

/**
 * exit_function - exits from the program
 * @args: commands passed
 */
void exit_function(char **args)
{
	int exit_code;

	if (args[1])
		exit_code = atoi(args[1]);
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
	int e = 0, code;
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
				code = atoi(str);
				if ((code == 0 && str[0] != '0') ||
						(code == 0 && strlen(str) != 1) || (args[2] != NULL))
					return (NULL);
			}
			else if (e == 1 && args[1] != NULL)
				return (NULL);
			return (arr[e].f);
		}
		e++;
	}
	return (NULL);
}
