#include <unistd.h>
#include "shell.h"

/**
 * _getline - reads the command in stdin
 * Return: the command read
 */
char *_getline(void)
{
	static char buffer[200000];
	char c;
	int check, e = 0;

	check = read(STDIN_FILENO, &c, 1);
	if (check <= 0)
		return (NULL);
	while (e < 200000 && check != 0)
	{
		buffer[e] = c;
		if (c == '\n' || c == ';')
			break;
		check = read(STDIN_FILENO, &c, 1);
		e++;
	}
	buffer[e] = '\0';
	return (buffer);
}
