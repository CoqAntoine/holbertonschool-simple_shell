#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern char **environ;

int my_setenv(const char *name, const char *value, int overwrite) {
    if (!name || strchr(name, '=') != NULL || *name == '\0') {
        return -1;
    }

    size_t name_len = strlen(name);
    size_t value_len = strlen(value);

    char *new_var = malloc(name_len + value_len + 2);
    if (!new_var) return -1;

    sprintf(new_var, "%s=%s", name, value);

    // Chercher si la variable existe déjà
    for (int i = 0; environ[i] != NULL; i++) {
        if (strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=') 
        {
            if (overwrite) {
                environ[i] = new_var;
            } else {
                free(new_var);
            }
            return 0;
        }
    }

    // Compter
    int count = 0;
    while (environ[count] != NULL) count++;

    // Copier environ si c'est la première fois qu'on le modifie
    static int environ_copied = 0;
    if (!environ_copied) {
        char **copy = malloc((count + 1) * sizeof(char *));
        if (!copy) return -1;
        for (int i = 0; i < count; i++) {
            copy[i] = environ[i];
        }
        copy[count] = NULL;
        environ = copy;
        environ_copied = 1;
    }

    // Agrandir et ajouter
    char **new_environ = realloc(environ, (count + 2) * sizeof(char *));
    if (!new_environ) {
        free(new_var);
        return -1;
    }
    environ = new_environ;
    environ[count] = new_var;
    environ[count + 1] = NULL;

    return 0;
}


int main()
{
	int i;

	my_setenv("NEW_VAR", "/bin", 0);
	for (i = 0; environ[i] != NULL; i++)
	{
	    printf("%s\n", environ[i]);
	}

	return (0);
}
