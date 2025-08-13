#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

extern char **environ;

typedef struct list_s
{
    char *value;
    struct list_s *prev;
    struct list_s *next;
} list_t;

list_t *add_end_list(list_t **head, char *folder)
{
    list_t *temp;
    list_t *new_node;

    if (head == NULL)
        return (NULL);
    new_node = malloc(sizeof(list_t));
    if (new_node == NULL)
        return (NULL);
    if (*head != NULL)
        {   
            temp = *head;
            while (temp->next != NULL)
                temp = temp->next;
            temp->next = new_node;
            new_node->value = folder;
            new_node->prev = temp;
            new_node->next = NULL; 
        }
        else
        {
            new_node->value = folder;
            new_node->next = NULL;
            new_node->prev = NULL;
            *head = new_node;
            return (*head);
        }


    return (*head);
}

size_t print_dlistint(list_t *h)
{
	size_t count = 0;

	while (h != NULL)
	{
		printf("%s\n", h->value);
		h = h->next;
		count++;
	}

	return (count);
}

int main()
{
    int i = 0;
    char *_path, *token;
    list_t *list = NULL;

    _path = getenv("PATH");
    token = strtok(_path, ":");
    for (i = 0; token != NULL; i++)
    {
        if (add_end_list(&list, token) == NULL)
        {
            printf("Error\n");
            break;
        }
        token = strtok(NULL, ":");
    }

    print_dlistint(list);

    return (0);
}
