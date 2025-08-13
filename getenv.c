#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

extern char **environ;

int main()
{
    int size, i = 0;
    char *line = NULL;
    size_t buffer = 0;
    char *variable;

    size = getline(&line, &buffer, stdin);
    if (line[size -1] == '\n')
        line[size - 1] = '\0';

    for (i = 0; environ[i] != NULL; i++)
    {
        variable = strtok(environ[i], "=");
        if (strcmp(line, variable) == 0)
        {
            variable = strtok(NULL, "=");
            printf("%s\n", variable);
        }
    }
    return (0);
}
