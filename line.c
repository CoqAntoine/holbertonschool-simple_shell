#include "simple_shell.h"

/**
 * read_line - Read a line of input from the user
 *
 * This function uses getline() to read a line from stdin.
 * If EOF is reached (Ctrl+D), the program exits cleanly.
 * The trailing newline is removed if present.
 *
 * Return: Pointer to the input line (must be freed by caller).
 */
char *read_line(void)
{
	char *line = NULL;
	size_t buffer = 0;
	ssize_t result;

	result = getline(&line, &buffer, stdin);
	if (result == -1)
	{
		free(line);
		if (isatty(STDIN_FILENO))
			printf("\n");
		exit(EXIT_SUCCESS);
	}

	if (line[result - 1] == '\n')
		line[result - 1] = '\0';

	return (line);
}

/**
 * token_command - Split a command line into arguments
 * @line: Input string to parse
 * @args: Array to store the resulting tokens
 *
 * This function tokenizes the input string using spaces as
 * delimiters. Tokens are stored in args[] and terminated by NULL.
 */
void token_command(char *line, char **args)
{
	int i;

	i = 0;
	args[i] = strtok(line, " ");
	while (args[i] != NULL && i < 256 - 1)
	{
		i++;
		args[i] = strtok(NULL, " ");
	}
}
