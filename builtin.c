#include "simple_shell.h"

/*Built-ins (exit, env)*/
int built_in_checks(char **args, char **envp, char *line)
{
	int i;

	if (args[0] == NULL)
		return (1);

	if (strcmp(args[0], "exit") == 0)
	{
		free(line);
		exit(0);
	}

	if (strcmp(args[0], "env") == 0)
	{
		for (i = 0; envp[i] != NULL; i++)
			printf("%s\n", envp[i]);
		return (1);
	}

	return (0);
}
