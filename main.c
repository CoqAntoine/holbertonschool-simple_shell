#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

/**
 * main - main function that open a shell and permit few commands
 * @argc: none
 * @argv: none
 * @envp: array with all environnement variables
 * Return: 0 (Succes)
 */

int main(int argc, char *argv[], char **envp)
{
	char *line = NULL, *command[10];
	size_t buffer = 0;
	pid_t child_pid;
	int result = 0, status, i = 1;

	if (i == 2)
	{
		printf("%d, %s", argc, argv[0]);
	}
	while (1)
	{
		printf("$ ");
		/*l'utilisateur rentre une commande*/
		result = getline(&line, &buffer, stdin);
		if (result == -1)
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		/*supprime le retour à la ligne à la fin de la commande*/
		if (line[result - 1] == '\n')
			line[result - 1] = '\0';
		/*récupère les arguments de la commande et les rentre dans un tableau*/
		command[0] = strtok(line, " ");
		do {
			command[i] = strtok(NULL, " ");
			i++;
		} while (command[i] != NULL);
		command[i] = NULL;
		/*créé un processus enfant pour éxecuter la commande à l'aide d'execve*/
		child_pid = fork();
		if (child_pid == -1)
			perror("./shell");
		if (child_pid == 0)
		{
			if ((execve(command[0], command, envp)) == -1)
				perror("./shell"), exit(EXIT_FAILURE);
		}
		else
			wait(&status);
	}
	/*retour de fin*/
	free(line);
	return (0);
}
