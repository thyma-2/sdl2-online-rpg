#include "utile.h"

int append(int *list, int to_add, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (list[i] == to_add)
            return i;
        else if (list[i] < 0)
        {
            list[i] = to_add;
            return i;
        }
    }
    return -1;
}

int have_char(struct personnages *list, char *name)
{
    while (list)
    {
        if (strcmp(list->nom_de_compte, name) == 0)
	{
            printf ("%s\n", list->nom_de_compte);
            return 1;
	}
        list = list->next;
    }
    return -1;
}

int find_smalest_valid_id(struct personnages *list, int from)
{
    for (struct personnages *l = list; l != NULL; l = l->next)
	if (l->id == from)
	    return find_smalest_valid_id(list, from + 1);
    return from;
}
