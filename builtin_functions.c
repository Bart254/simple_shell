#include "shell.h"
#include <string.h>

/**
 * exit_function - exits from the program
 * Return: integer
 */
int exit_function(void)
{
	exit(0);
	return (0);
}

/**
 * env_function - prints current environment
 * Return: number of environment
 */
int env_function(void)
{
	int e;

	for (e = 0; environ[e]; e++)
	{
		printf("%s\n", environ[e]);
		fflush(stdout);
	}
	return (e - 1);
}

/**
 * built_in - checks for a command that calls a builtin
 * @command: command passeda
 * Return: function pointer
 */
int (*built_in(char *command))(void)
{
	int e = 0;
	builtin arr[] = {{"exit", exit_function}, {"env", env_function},
			 {NULL, NULL}};

	while (arr[e].name != NULL)
	{
		if (strcmp(command, arr[e].name) == 0)
			return (arr[e].f);
		e++;
	}
	return (NULL);
}
