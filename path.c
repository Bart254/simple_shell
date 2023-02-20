#include <string.h>
#include "shell.h"
#include <sys/stat.h>

/**
 * path - returns absolute path name of command
 * @args: arguments
 * Return: absolute path name
 */
char *path(char *args)
{
	char *path, *cwd = NULL, *dir, *fdir = NULL, *new_arg;
	int size;
	struct stat buffer;
	size_t a = 0;

	if (stat(args, &buffer) == 0)
		return (strdup(args));
	cwd = getcwd(cwd, a);
	path = strdup(getenv("PATH"));
	dir = _strtok(path, ":\n");
	while (dir != NULL)
	{
		chdir(dir);
		if (stat(args, &buffer) == 0)
			fdir = dir;
		dir = _strtok(NULL, ":\n");
	}
	chdir(cwd);
	free(cwd);
	if (fdir != NULL)
	{
		size = strlen(fdir) + strlen(args) + 1;
		new_arg = malloc((size + 1) * sizeof(char));
		if (new_arg == NULL)
		{
			free(path);
			return (NULL);
		}
		new_arg = strcpy(new_arg, fdir);
		new_arg = strcat(new_arg, "/");
		new_arg = strcat(new_arg, args);
		free(path);
		return (new_arg);
	}
	free(path);
	return (NULL);
}
