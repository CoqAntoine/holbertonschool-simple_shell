#include "simple_shell.h"

/*Read of a line given by user*/
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

	return line;
}

/*Tokenizing (parse tokens in args[])*/
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
