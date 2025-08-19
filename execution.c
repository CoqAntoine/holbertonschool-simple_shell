#include "simple_shell.h"

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
