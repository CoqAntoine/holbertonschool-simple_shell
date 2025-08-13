#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
	ssize_t result = 1;
	size_t buffer = 0;
	char *line = NULL;
	char *delimiter = " ";
	char *arg;

	printf("$ ");

	result = getline(&line, &buffer, stdin);

	if (result == -1)
	{
		free(line);
		return (-1);
	}

	printf("%s\n", line);

	arg = strtok(line, delimiter);
	while (arg != NULL)
	{
		printf("%s ", arg);
		arg = strtok(NULL, delimiter);
	}

	free(line);

	return (0);
}
