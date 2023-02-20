#include <stdio.h>

/**
 * _strtok - tokenizes a string
 * @str: string to be tokenized
 * @delim: delimiters
 * Return: pointer to string
 */
char *_strtok(char *str, const char *delim)
{
	static char *token;
	int i = 0;
	char *subtoken;

	if (str)
		token = str;
	if (*token == '\0')
		return (NULL);
	while (delim[i] && *token)
	{
		if (*token == delim[i])
		{
			token++;
			i = 0;
			continue;
		}
		i++;
	}
	if (*token == '\0')
		return (NULL);
	subtoken = token;
	while (*token)
	{
		for (i = 0; delim[i]; i++)
		{
			if (*token == delim[i])
			{
				*token = '\0';
				token++;
				return (subtoken);
			}
		}
		token++;
	}
	return (subtoken);
}

