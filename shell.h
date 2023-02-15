#ifndef SHELL_H
#define SHELL_H
void prompt(void);
char **get_args(char *buffer);
void _free(char **args, char *buffer);
extern char **environ;
#endif
