#include "simple_shell.h"

/**
 * main_loop - Main execution loop of the shell
 * @argv0: Program name (used for error messages)
 * @envp: Array of environment variables
 *
 * This function runs an infinite loop that prompts the user for input,
 * reads a command line, tokenizes it, checks if it matches a built-in,
 * and executes it. The loop only exits when the program is terminated
 * explicitly (for example with the built-in "exit").
 */
void main_loop(char *argv0, char **envp, int *last_status)
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
			execute_command(args, envp, argv0, count, last_status);

		free(line);
		if (!isatty(STDIN_FILENO))
			exit(*last_status);
	}
}

/**
 * main - Entry point of the program
 * @argc: Argument count
 * @argv: Argument vector
 * @envp: Environment variables
 *
 * This function sets up the signal handler for SIGINT and then launches
 * the main shell loop. Returns 0 on success, 1 if too many arguments
 * are provided.
 *
 * Return: 0 on success, 1 on failure.
 */
int main(int argc, char *argv[], char **envp)
{
	int last_status = 0;

	if (argc > 256)
		return (1);
	signal(SIGINT, handle_sigint);
	main_loop(argv[0], envp, &last_status);
	return (last_status);
}
