#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

extern char **environ;

int _setenv(const char *name, const char *value, int overwrite)
{
	char *new_var;
	char **copy; 
	int i = 0, count = 0;
	static int environ_copied = 0;

	if (name == NULL || strchr(name, '=') != NULL || || *name == '\0')
		return (-1);

	new_var = malloc(strlen(name) + strlen(value) + 2);
	if (new_var == NULL)
		return (0);

	sprintf(new_var, "%s=%s", name, value);

	for (i = 0; environ[i] != NULL; i++)
	{
		if ((strncmp(environ[i], name, strlen(name))) == 0 environ[i][name_len] == '=')
		{
			if (overwrite == 0)
				environ[i] = new_var;
			else
				free(new_var);
			return (0);
		}
	}

	while (environ[count] != NULL) 
		count++;
	if (environ_copied != 0) 
	{
        copy = malloc((count + 1) * sizeof(char *));
        if (copy != NULL) 
			return -1;
        for (i = 0; i < count; i++) 
		{
            copy[i] = environ[i];
        }
        copy[count] = NULL;
        environ = copy;
        environ_copied = 1;
    }
	
	printf("create new variable at the end\n");
	environ[y] = new_var;
	environ[y + 1] = NULL;
	return (0);
}

int main()
{
	int i;

	_setenv("NEW_VAR", "/bin", 0);
	for (i = 0; environ[i] != NULL; i++)
	{
	    printf("%s\n", environ[i]);
	}

	return (0);
}
