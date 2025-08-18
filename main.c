#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void handle_sigint(int sig)
{
	(void)sig;
    write(STDOUT_FILENO, "\n", 1);
    write(STDOUT_FILENO, "$ ", 2);
}

/**
 * main - main function that open a shell and permit few commands
 * @argc: none
 * @argv: none
 * @envp: array with all environnement variables
 * Return: 0 (Succes)
 */

int main(int argc, char *argv[], char **envp)
{
	char *line = NULL, *command[10], error_string[256], *folder = NULL, *command_path = NULL, *bl = NULL;
	char *our_path = getenv("PATH");
	size_t buffer = 0;
	pid_t child_pid;
	int result = 0, count_shell = 0, status, i = 0;

	/*prise en compte du ctrl+C lors de la saisie*/
	signal(SIGINT, handle_sigint);

	/*evite le warning (non utilisation de argc)*/
	if (i == 2)
		printf("%d", argc);

	printf("folder : %s, command_path : %s, our_path : %s\n", folder, command_path, our_path);
	while (1)
	{
		/*prompt*/
		if (isatty(STDIN_FILENO))
			printf("$ ");
		count_shell++;

		/*l'utilisateur rentre une commande*/
		result = getline(&line, &buffer, stdin);

		/*prise en compte du ctrl+D lors de la saisie*/
		if (result == -1)
		{
			free(line);
			if (isatty(STDIN_FILENO))
				printf("\n");
			exit(EXIT_SUCCESS);
		}

		/*supprime le retour à la ligne à la fin de la commande*/
		if (line[result - 1] == '\n')
			line[result - 1] = '\0';

		/*vérifie si la ligne de commande existe dans le path*/
		bl = malloc(strlen(our_path) + 1);
		bl = strtok(line, " ");
		folder = malloc(strlen(our_path) + 1);
		command_path = malloc(strlen(our_path) + 1);
		folder = strtok(our_path, ":");
		while (folder != NULL)
		{
			sprintf(command_path, "%s/%s", folder, bl);
			if (access(command_path, X_OK) == 0)
			{
				break;
			}
			else
			{
				folder = strtok(NULL, ":");
			}
		}
			
		/*récupère les arguments de la commande et les rentre dans un tableau*/
		i = 1;
		command[0] = strtok(line, " ");
		while ((command[i] = strtok(NULL, " ")) != NULL)
			i++;
		command[i] = NULL;

		/*créé un processus enfant pour éxecuter la commande à l'aide d'execve*/
		if (command[0] == NULL)
    		continue;
		child_pid = fork();
		if (child_pid == -1)
			perror("./shell");
		if (child_pid == 0)
		{
			if ((execve(command_path, command, envp)) == -1)
			{
				sprintf(error_string, "%s: %i: %s", argv[0], count_shell, command[0]);
				perror(error_string);
				exit(EXIT_FAILURE);
			}
		}
		else
			wait(&status);
	}
	/*retour de fin*/
	free(line);
	return (0);
}
