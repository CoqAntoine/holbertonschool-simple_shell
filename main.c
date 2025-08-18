#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

void handle_sigint(int sig)
{
	(void)sig;
    write(STDOUT_FILENO, "\n", 1);
    write(STDOUT_FILENO, "$ ", 2);
}

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

/**
 * main - main function that open a shell and permit few commands
 * @argc: none
 * @argv: none
 * @envp: array with all environnement variables
 * Return: 0 (Succes)
 */

int main(int argc, char *argv[], char **envp)
{
	char *line = NULL, *command[10], error_string[256], *folder = NULL, command_path[1024], *mini_command = NULL, str_exit[256];
	char *copy_line = NULL;
	char *our_path = NULL;
	char *copy_our_path = NULL;
	size_t buffer = 0;
	pid_t child_pid;
	int result = 0, count_shell = 0, status, i = 0, y = 0;

	/*prise en compte du ctrl+C lors de la saisie*/
	signal(SIGINT, handle_sigint);

	/*evite le warning (non utilisation de argc)*/
	if (i == 2)
		printf("%d", argc);

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

		/*sort du programme si exit est entré */
		y = 0;
		for (i = 0; line[i] != '\0'; i++)
		{
			if (line[i] >= 'a' && line[i] <= 'z')
			{
				str_exit[y] = line[i];
				i++;
				while (line[i] != ' ' && line[i] != '\0')
				{
					y++;
					str_exit[y] = line[i];
					i++;
				}
			}
		}
		if (strcmp (str_exit, "exit") == 0)
			exit(0);

		/*affiche l'environnement si env est entré */
		if (strcmp (line, "env") == 0)
		{
			for (i = 0; envp[i] != NULL; i++)
			{
				printf("%s\n", envp[i]);
			}
			continue;
		}

		/*faire des copies pour éviter de perdre les valeurs de base*/
		our_path = _getenv("PATH", envp);
		copy_our_path = strdup(our_path);
		copy_line = strdup(line);
		/*mini_commande exemple = ls 	folder exemple = /user/bin */
		mini_command = strtok(copy_line, " ");
		folder = strtok(copy_our_path, ":");
		/*vérifie si la ligne de commande existe dans le path*/
		while (folder != NULL)
		{
			sprintf(command_path, "%s/%s", folder, mini_command);
			if (access(command_path, X_OK) == 0)
				break;
			folder = strtok(NULL, ":");
		}
		/*récupère les arguments de la commande et les rentre dans un tableau*/
		i = 0;
		command[i] = strtok(line, " ");
		while (command[i] != NULL)
		{
    		i++;
    		command[i] = strtok(NULL, " ");
		}
		free(copy_our_path);
		free(copy_line);
		/*si l'utilisateur n'entre rien, le prompt se réaffiche*/
		if (command[0] == NULL)
    		continue;
		/*créé un processus enfant pour éxecuter la commande à l'aide d'execve*/
		child_pid = fork();
		if (child_pid == -1)
			perror("./shell");
		if (child_pid == 0)
		{
			/*s'il a trouvé une correspondance*/
			if (folder != NULL)
			{
				/*on execute avec la commande_path créée */
				if ((execve(command_path, command, envp)) == -1)
				{
					sprintf(error_string, "%s: %i: %s", argv[0], count_shell, command[0]);
					perror(error_string);
					exit(EXIT_FAILURE);
				}
			}
			/*s'il n'a pas trouvé de correspondance*/
			else
			{
				/*on vérifie si c'est un dossier (contenant un '/') ou si c'est juste une commande*/
				if (strchr(command[0], '/'))
				{
					/*si c'est un dossier, on exécute avec la commande donnée*/
					if (access(command[0], X_OK) == 0)
					{
    					execve(command[0], command, envp);
   						perror(error_string);
    					exit(EXIT_FAILURE);
					}
					else
					{
    					fprintf(stderr, "%s: %d: %s: not found\n", argv[0], count_shell, command[0]);
    					exit(127);
					}
				}
				/*sinon, on sors une erreur "not found"*/
				else
				{
					fprintf(stderr, "%s: %d: %s: not found\n", argv[0], count_shell, command[0]);
					exit(127);
				}
			}
		}
		else
			wait(&status);
	}
	/*retour de fin*/
	return (0);
}
