#include <unistd.h>
#include <stdio.h>

/**
 * prompt - displays a prompt to stdout
 * Return: Nothing
 */
void prompt(void)
{
	write(STDOUT_FILENO, "$ ", 2);
	fflush(stdout);
}
