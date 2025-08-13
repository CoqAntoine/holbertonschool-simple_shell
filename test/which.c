#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main(int ac, char *av[])
{
	char *_path = getenv("PATH");
	char *dossier;
	char *line;

	if (ac < 2)
		return (-1);

	dossier = strtok(_path, ":");

	while (1)
	{
		line = malloc(strlen(dossier)+(strlen(av[1])) + 1);
		if (line == NULL)
		{
			printf("Malloc failed\n");
			break;
		}

		strcat(line, dossier);
		strcat(line, "/");
		strcat(line, av[1]);

		if ((access(line, X_OK)) == 0)
		{
			printf("%s\n", line);
			break;
		}
		dossier = strtok(NULL, ":");
		if (dossier == NULL)
			break;
	}
	free(line);
	return (0);
}
