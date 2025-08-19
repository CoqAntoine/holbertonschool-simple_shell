#include "simple_shell.h"

/**
 * built_in_checks - Handle built-in commands (exit, env)
 * @args: Array of command arguments
 * @envp: Array of environment variables
 * @line: Original input line (freed if needed)
 *
 * This function checks if the first argument matches a built-in
 * command. If "exit" is entered, the shell exits after freeing
 * the line buffer. If "env" is entered, it prints the current
 * environment variables.
 *
 * Return: 1 if a built-in command was executed, 0 otherwise.
 */
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
