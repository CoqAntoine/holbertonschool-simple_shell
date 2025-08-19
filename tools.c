#include "simple_shell.h"

/*Signal Ctrl+C*/
void handle_sigint(int sig)
{
	(void)sig;
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "\n$ ", 3);
	else
		write(STDOUT_FILENO, "\n", 1);
}

/*custom getenv*/
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
