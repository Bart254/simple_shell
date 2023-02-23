#include "shell.h"

/**
 * main - creates a shell program
 * @ac: Number of arguments
 * @av: pointer to arguments
 * Return: 0 if successful
 */
int main(int ac __attribute__((unused)), char **av)
{
	int tty = 1, line_no = 0;
	char **args, *buffer, *path_arg;
	pid_t child_id;
	builtin func;

	while (1)
	{
		line_no++;
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
		if (func.f != NULL)
		{
			func.f(args);
			continue;
		}
		path_arg = path(args[0]);
		if (path_arg == NULL)
		{
			print_error(av[0], args, line_no);
			free(args);
			continue;
		}
		child_id = fork();
		if (child_id)
			wait(NULL);
		else
			execve(path_arg, args, environ);
		 _free(args, path_arg);
	}
	return (0);
}

/**
 * print_error - handles execution errors
 * @name: program name
 * @args: pointer of arguments
 * @line_no: line being executed
 * Return: Always 1
 */
void print_error(char *name, char **args, int line_no)
{
	dprintf(STDERR_FILENO, "%s: %d: %s: not found\n", name, line_no, args[0]);
}
