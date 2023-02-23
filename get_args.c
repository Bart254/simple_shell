#include "shell.h"

/**
 * get_args- gets the command passed to stdin
 * @buffer: pointer to args passed
 * Once a command is captured from stdin, the function
 * breaks it down into several arguments that are to be processed
 * Return: arrays of arguments
 */
char **get_args(char *buffer)
{
	char *token, *args[50], **commands;
	int e, size;

	token = _strtok(buffer, " \t\n");
	if (!token)
		return (NULL);
	for (e = 0, size = 0; e < 50 && token; e++)
	{
		args[e] = token;
		size++;
		token = _strtok(NULL, " \t\n");
	}
	commands = malloc((size + 1) * sizeof(char *));
	if (commands == NULL)
		return (NULL);
	for (e = 0; e < size; e++)
		commands[e] = args[e];
	commands[e] = NULL;
	return (commands);
}
