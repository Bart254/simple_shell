#include "shell.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

/**
 * main - creates a shell program
 * @ac: Number of arguments
 * @av: pointer to arguments
 * Return: 0 if successful
 */
int main(int ac __attribute__((unused)), char **av)
{
	int tty = 1, check;
	char **args, *buffer;
	size_t n = 0;
	pid_t child_id;

	while (tty)
	{
		buffer = NULL;
		tty = isatty(STDIN_FILENO);
		if (tty)
			prompt();
		check = getline(&buffer, &n, stdin);
		if (check == -1)
		{
			free(buffer);
			break;
		}
		args = get_args(buffer);
		if (!args)
		{
			free(buffer);
			continue;
		}
		child_id = fork();
		if (child_id)
		{
			wait(NULL);
			_free(args, buffer);
		}
		else
		{
			execve(args[0], args, environ);
			perror(av[0]);
			_free(args, buffer);
			break;
		}
	}
	return (0);
}
