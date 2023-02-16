#include "shell.h"

/**
 * main - creates a shell program
 * @ac: Number of arguments
 * @av: pointer to arguments
 * Return: 0 if successful
 */
int main(int ac __attribute__((unused)), char **av)
{
	int tty = 1, check;
	char **args, *buffer, *path_arg;
	size_t n = 0;
	pid_t child_id;
	builtin func;

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
			continue;
		func.f = built_in(args[0]);
		if (func.f != NULL && args[1] == NULL)
		{
			free(buffer);
			func.f();
			continue;
		}
		path_arg = path(args[0]);
		if (path_arg == NULL)
		{
			_free(args, buffer, path_arg);
			continue;
		}
		child_id = fork();
		if (child_id)
		{
			wait(NULL);
			_free(args, buffer, path_arg);
		}
		else
		{
			execve(path_arg, args, environ);
			excve_error(av[0], args, buffer, path_arg);
		}
	}
	return (0);
}

/**
 * excve_error - handles execution errors
 * @name: program name
 * @args: pointer of arguments
 * @buffer: data read by getline
 * @path_arg: path file command
 */
int excve_error(char *name, char **args, char *buffer, char *path_arg)
{
	perror(name);
	_free(args, buffer, path_arg);
	return (1);
}
