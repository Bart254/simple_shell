#include "shell.h"
#include <string.h>

/**
 * main - creates a shell program
 * @ac: Number of arguments
 * @av: pointer to arguments
 * Return: 0 if successful
 */
int main(int ac __attribute__((unused)), char **av)
{
	int tty, line_no = 0, status = 0;
	char **args, *buffer, *path_arg;
	builtin func;

	tty = isatty(STDIN_FILENO);
	errno = 0;
	while (1)
	{
		line_no++;
		if (tty)
			prompt();
		buffer = _getline();
		if (!buffer)
			break;
		args = get_args(buffer);
		if (!args)
			continue;
		func.f = built_in(args, &status);
		if (func.f != NULL)
		{
			func.f(args, status);
			continue;
		}
		path_arg = path(args[0]);
		if (path_arg == NULL)
		{
			print_error(av[0], args, line_no, &status);
			continue;
		}
		execute(path_arg, args, &status);
	}
	return (status);
}

/**
 * execute - executes commands
 * @path_arg: absolute path of argument
 * @args: arguments to be executed
 * @status: status of program
 */
void execute(char *path_arg, char **args, int *status)
{
	pid_t child_id;

	child_id = fork();
	if (child_id)
	{
		wait(status);
		if (WIFEXITED(*status))
			*status = WEXITSTATUS(*status);
	}
	else
		execve(path_arg, args, environ);
	 _free(args, path_arg);
}

/**
 * print_error - handles execution errors
 * @name: program name
 * @args: pointer of arguments
 * @line_no: line being executed
 * @status: exit code
 * Return: Always 1
 */
void print_error(char *name, char **args, int line_no, int *status)
{
	if (strcmp(args[0], "exit") == 0)
	{
		dprintf(STDERR_FILENO, "%s: %d: %s: Illegal number: %s\n",
				name, line_no, args[0], args[1]);
		*status = 2;
		free(args);
	}
	else
	{
		dprintf(STDERR_FILENO, "%s: %d: %s: not found\n", name, line_no, args[0]);
		*status = 127;
		free(args);
	}
}
