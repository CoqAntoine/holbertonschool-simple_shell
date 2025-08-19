#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

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

/*Research of complete path in $PATH*/
int find_command_path(char *cmd, char **envp, char *cmd_path)
{
	char *path, *copy, *folder;

	path = _getenv("PATH", envp);
	if (!path)
		return (0);

	copy = strdup(path);
	if (!copy)
		return (0);

	folder = strtok(copy, ":");
	while (folder != NULL)
	{
		snprintf(cmd_path, 1024, "%s/%s", folder, cmd);
		if (access(cmd_path, X_OK) == 0)
		{
			free(copy);
			return (1);
		}
		folder = strtok(NULL, ":");
	}

	free(copy);
	return (0);
}

/*Execute the command the user entered*/
void execute_command(char **args, char **envp, char *argv0, int count)
{
	pid_t child_pid;
	int status;
	char cmd_path[1024];

	if (strchr(args[0], '/'))
	{
		/*execute_command_complete_path(args, envp, argv0, count);*/
		if (access(args[0], X_OK) == 0)
		{
			child_pid = fork();
			if (child_pid == -1)
			{
				perror(argv0);
			}
			if (child_pid == 0)
			{
				execve(args[0], args, envp);
				perror(argv0);
				exit(EXIT_FAILURE);
			}
			else
				wait(&status);
			return;
		}
	}

	if (find_command_path(args[0], envp, cmd_path))
	{
		/*execute_command_PathCommand(args, envp, argv0, count);*/
		child_pid = fork();
		if (child_pid == -1)
		{
			perror(argv0);
		}
		if (child_pid == 0)
		{
			execve(cmd_path, args, envp);
			perror(argv0);
			exit(EXIT_FAILURE);
		}
		else
			wait(&status);
	}
	else
	{
		fprintf(stderr, "%s: %d: %s: not found\n", argv0, count, args[0]);
	}
}

/*Main loop of the program*/
void main_loop(char *argv0, char **envp)
{
	char *line;
	char *args[1024];
	int count;

	count = 0;
	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");
		count++;

		line = read_line();
		token_command(line, args);

		if (!built_in_checks(args, envp, line))
			execute_command(args, envp, argv0, count);

		free(line);
	}
}

/*MAIN*/
int main(int argc, char *argv[], char **envp)
{
	if (argc > 256)
		return(1);
	signal(SIGINT, handle_sigint);
	main_loop(argv[0], envp);
	return (0);
}
