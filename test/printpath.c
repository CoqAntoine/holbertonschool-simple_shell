#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

extern char **environ;

int main()
{
    int i = 0;
    char *_path, *token;

    _path = getenv("PATH");
    token = strtok(_path, ":");
    for (i = 0; token != NULL; i++)
    {
        printf("%s\n", token);
        token = strtok(NULL, ":");
    }

    return (0);
}
