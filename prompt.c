#include <unistd.h>

/**
 * prompt - displays a prompt to stdout
 * Return: Nothing
 */
void prompt(void)
{
	write(STDOUT_FILENO, "$ ", 2);
}
