#include "inventaire.h"

struct linked_char *use(int n, struct personnages *p)
{
    struct linked_char *item = get_char_n(n, p->i_list);
    if (item != NULL)
    {
	if (strcmp(item->nom, "fruit") == 0 || strcmp(item->nom, "legume") == 0)
	{
	    p->faim += 25000;
	    p->i_list = remove_enemi(item->nom, p->i_list);
	}
    }
    return p->i_list;
}

int count(char *name)
{
    if (strcmp(name, "fruit") == 0 || strcmp(name, "legume") == 0)
	return 10;
    if (strcmp(name, "fleche") == 0)
	return 20;
    return 1;
}

struct linked_char *append_in_inventory(char *name, struct linked_char *p, int n)
{
    struct linked_char *a = exist_in_linked_char(p, name);
    if (a != NULL)
    {
	int max = count(name);
	if (max >= a->count + n)
	    a->count += n;
	else
	{
	    int b = a->count + n - max;
	    a->count = n;
	    p = append_linked_char(name, p);
	    a = exist_in_linked_char(p, name);
	    a->count = b;
	}
    }
    else
    {
	p = append_linked_char(name, p);
	a = exist_in_linked_char(p, name);
	a->count = n;
    }	
    return p;
}


//on suppose que le personnage possède ce qu'on lui retire (sinon on crash)
struct linked_char *remove_from_inventory(char *name, struct linked_char *p, int n)
{
    while (n > 0)
    {
	struct linked_char *a = exist_in_linked_char(p, name);
	if (a->count > n)
	{
	    a->count -= n;
	    n = 0;
	}
	else
	{
	    n -= a->count;
	    p = remove_enemi(name, p);
	}
    }
    return p;
}
