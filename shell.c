#include "shell.h"

/**
 * main - creates a shell program
 * @ac: Number of arguments
 * @av: pointer to arguments
 * Return: 0 if successful
 */
int main(int ac __attribute__((unused)), char **av)
{
	int tty = 1;
	char **args, *buffer, *path_arg;
	pid_t child_id;
	builtin func;

	while (tty)
	{
		tty = isatty(STDIN_FILENO);
		if (tty)
			prompt();
		buffer = _getline();
		if (!buffer)
			break;
		args = get_args(buffer);
		if (!args)
			continue;
		func.f = built_in(args);
		if (func.f != NULL/* && args[1] == NULL*/)
		{
			/*free(args);*/
			func.f(args);
			continue;
		}
		path_arg = path(args[0]);
		if (path_arg == NULL)
		{
			_free(args, path_arg);
			continue;
		}
		child_id = fork();
		if (child_id)
			wait(NULL);
		else
		{
			execve(path_arg, args, environ);
			excve_error(av[0], args, path_arg);
		}
		 _free(args, path_arg);
	}
	return (0);
}

/**
 * excve_error - handles execution errors
 * @name: program name
 * @args: pointer of arguments
 * @path_arg: path file command
 * Return: Always 1
 */
void excve_error(char *name, char **args, char *path_arg)
{
	perror(name);
	_free(args, path_arg);
}
