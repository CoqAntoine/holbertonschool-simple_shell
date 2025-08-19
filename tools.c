#include "simple_shell.h"

/**
 * handle_sigint - Handle the SIGINT signal (Ctrl+C)
 * @sig: Signal number (unused)
 *
 * This function intercepts SIGINT. If the shell is running in
 * interactive mode (terminal), it prints a new prompt on a new
 * line instead of terminating the program.
 */
void handle_sigint(int sig)
{
	(void)sig;
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "\n$ ", 3);
	else
		write(STDOUT_FILENO, "\n", 1);
}

/**
 * _getenv - Custom implementation of getenv
 * @string: Name of the environment variable to find
 * @envp: Array of environment variables
 *
 * This function searches the environment list for a variable
 * matching the given name. If found, it returns a pointer to
 * the value part of the variable.
 *
 * Return: Pointer to the variable value, or NULL if not found.
 */
char *_getenv(char *string, char **envp)
{
	int i = 0;
	size_t len = strlen(string);


	for (i = 0; envp[i] != NULL; i++)
	{
		if (strncmp(envp[i], string, len) == 0 && envp[i][len] == '=')
		{
			return (envp[i] + len + 1);
		}
	}
	return (NULL);
}
