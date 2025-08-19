#include "simple_shell.h"

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
