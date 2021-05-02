#include "diplo.h"

struct linked_enemie *append_enemie(char nom[50], struct linked_enemie *l, int n)
{
	if (l == NULL)
	{
		l = malloc(sizeof(struct linked_enemie));
		l->nom[0] = 0;
		strcat(l->nom, nom);
		l->rang = n;
		l->next = NULL;
		return l;
	}
	else
	{
		struct linked_enemie *parcour = l;
		while (parcour->next != NULL)
		{
			parcour = parcour->next;
			if (strcmp(parcour->nom, nom) == 0)
			{
				if (n < parcour->rang)
					parcour->rang = n;
				return l;
			}
		}
		if (strcmp(parcour->nom, nom) == 0)
		{
			if (n < parcour->rang)
				parcour->rang = n;
			return l;
		}
		struct linked_enemie *new = malloc(sizeof(struct linked_enemie));
		new->nom[0] = 0;
		strcat(new->nom, nom);
		new->rang = n;
		new->next = NULL;
		parcour->next = new;
		return l;
	}
}

struct linked_enemie *remove_enemie(char nom[50], struct linked_enemie *l)
{
	struct linked_enemie *ret = l;
	struct linked_enemie *prev;
	if (l != NULL)
	{
		if (strcmp(l->nom, nom) == 0)
		{
			l = l->next;
			free(ret);
			return l;
		}
		while (l->next != NULL)
		{
			prev = l;
			l = l->next;
			if (strcmp(l->nom, nom) == 0)
			{
				prev->next = l->next;
				free(l);
				return ret;
			}
		}
		if (strcmp(l->nom, nom) == 0)
		{
			free(l);
			prev->next = NULL;
		}
	}
	return ret;
}

void free_linked_enemie(struct linked_enemie *e)
{
	if (e != NULL)
	{
		free_linked_enemie(e->next);
		free(e);
	}
}

struct linked_enemie *exist_in_linked_enemie(struct linked_enemie *e, char *cmp)
{
	while (e != NULL)
	{
		if (strcmp(e->nom, cmp) == 0)
			return e;
		e = e->next;
	}
	return NULL;
}

int max_rang(struct linked_enemie *l)
{
	int ret = 0;
	for (struct linked_enemie *ll = l; ll != NULL; ll = ll->next)
		if (ret < ll->rang)
			ret = ll->rang;
	return ret;
}

void rec_append_enemie(char *nom, struct personnages *p, struct linked_list *l, int n)
{
	p->e_list = append_enemie(nom, p->e_list, n);
	for (struct linked_list *ll = l; ll != NULL; ll = ll->next)
		if (strcmp(ll->p->nom_superieur, p->nom) == 0 && ll->p != p && strcmp(p->nom, "none") != 0)
			rec_append_enemie(nom, ll->p, l, n + 1);
}

int get_rang(char *nom, struct linked_enemie *l)
{
	for (struct linked_enemie *ll = l; ll != NULL; ll = ll->next)
		if (strcmp(ll->nom, nom) == 0)
			return ll->rang;
	return 0;
}

void rec_remove_enemie(char *nom, struct personnages *p, struct linked_list *l, int n)
{
	int r = get_rang(nom, p->e_list);
	if (r >= n)
	{
		p->e_list = remove_enemie(nom, p->e_list);
		for (struct linked_list *ll = l; ll != NULL; ll = ll->next)
			if (strcmp(ll->p->nom_superieur, p->nom) == 0 && ll->p != p && strcmp(p->nom, "none") != 0)
				rec_remove_enemie(nom, ll->p, l, n + 1);	    
	}  
}
