#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * cd - changes to a new directory
 * @args: arguments passed
 * @status: exit code
 */
void cd(char **args, int status __attribute__((unused)))
{
	char *cwd, *new_d, *buffer = NULL;
	size_t size = 0;

	cwd = getcwd(buffer, size);
	if (args[1] == NULL)
	{
		new_d = getenv("HOME");
		if (new_d == NULL)
		{
			free(cwd);
			free(args);
			return;
		}
	}
	else if (strcmp(args[1], "-") == 0)
	{
		new_d = getenv("OLDPWD");
		if (new_d == NULL)
			new_d = getenv("PWD");
		printf("%s\n", new_d);
	}
	else
		new_d = args[1];
	chdir(new_d);
	setenv("OLDPWD", cwd, 1);
	setenv("PWD", new_d, 1);
	free(cwd);
	free(args);
}
