#include "simple_shell.h"

/**
 * find_command_path - Search for a command in the PATH variable
 * @cmd: Command name to search
 * @envp: Array of environment variables
 * @cmd_path: Buffer to store the complete path if found
 *
 * This function searches through all directories listed in PATH
 * for the given command. If found, the full path is stored in
 * cmd_path.
 *
 * Return: 1 if the command is found, 0 otherwise.
 */
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

/**
 * execute_command - Execute a user-entered command
 * @args: Array of command arguments
 * @envp: Array of environment variables
 * @argv0: Name of the shell program (for error messages)
 * @count: Command counter (for error display)
 *
 * This function executes a command either by absolute/relative
 * path or by searching through PATH. If the command is not
 * found, an error message is printed.
 */
void execute_command(char **args, char **envp, char *argv0, int count)
{
	pid_t child_pid;
	int status;
	char cmd_path[1024];

	if (strchr(args[0], '/'))
	{
		if (access(args[0], X_OK) == 0)
		{
			child_pid = fork();
			if (child_pid == -1)
			{
				perror("fork");
				return;
			}
			if (child_pid == 0)
			{
				execve(args[0], args, envp);
				perror(args[0]);
				exit(EXIT_FAILURE);
			}
			else
				wait(&status);
				if (WIFSIGNALED(status))
					fprintf(stderr, "%s: %d: %s: terminated by signal %d\n", argv0, count, args[0], WTERMSIG(status));
			return;
		}
	}
	if (find_command_path(args[0], envp, cmd_path))
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("fork");
			return;
		}
		if (child_pid == 0)
		{
			execve(cmd_path, args, envp);
			perror(args[0]);
			exit(EXIT_FAILURE);
		}
		else
			wait(&status);
			if (WIFSIGNALED(status))
				fprintf(stderr, "%s: %d: %s: terminated by signal %d\n", argv0, count, args[0], WTERMSIG(status));
	}
	else
		fprintf(stderr, "%s: %d: %s: not found\n", argv0, count, args[0]);
}
