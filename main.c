#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

extern char **environ;

int main(void)
{
	char *line = NULL;
	int result = 1;
	size_t buffer = 0;
	char *command[2];
	pid_t child_pid;
	int status;

	while (1)
	{
		printf("$ ");
		result = getline(&line, &buffer, stdin);
		if (result == -1)
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		if (line[result - 1] == '\n')
			line[result - 1] = '\0';

		command[0] = line;
		command[1] = NULL;

		child_pid = fork();
		if (child_pid == -1)
			printf("ERROR\n");
		if (child_pid == 0)
		{
			if ((execve(line, command, environ)) == -1)
				perror("execve");
		}
		else
			wait(&status);
	}
	free(line);
	return (0);
}
