#define _GNU_SOURCE
#include "perso.h"

struct personnages *init_map(void)
{
	FILE *acount = fopen("map.txt", "r+");
	char *line = NULL;
	size_t len = 0;
	struct personnages *list = NULL;
	while (getline(&line, &len, acount) > 0)
		list = append_perso(line, list);

	return list;
}

void parse_order(struct personnages *list, char *line)
{
	int i = 0;
	int j;
	char tmpC[50];
	while (line[i] != 0)
	{
		struct personnages *p = get_ptr_from_id(get_id(line, &i), list);
		if (p == NULL)
			return;
		p->a_bouger = 1;
		i++;
		int idaction = atoi(&line[i]);
		i += 3;
		switch(idaction)
		{
			case 0:
				if (line[i] == '+')
				{
					i++;
					p->pv += atoi(&line[i]);
				}
				else if (line[i] == '-')
				{
					i++;
					p->pv -= atoi(&line[i]);
				}
				else
				{
					i++;
					p->pv = atoi(&line[i]);
				}
				while(line[i] != ' ')
					i++;
				i++;
				break;
			case 1:
				if (line[i] == '+')
                {
                    i++;
                    p->x += atoi(&line[i]);
                }
                else if (line[i] == '-')
                {
                    i++;
                    p->x -= atoi(&line[i]);
                }
                else
				{
					i++;
					p->x = atof(&line[i]);
				}
                while(line[i] != ' ')
                    i++;
                i++;
				break;
			case 2:
				if (line[i] == '+')
                {
                    i++;
                    p->y += atoi(&line[i]);
                }
                else if (line[i] == '-')
                {
                    i++;
                    p->y -= atoi(&line[i]);
                }
                else
				{
					i++;
					p->y = atof(&line[i]);
				}
                while(line[i] != ' ')
                    i++;
                i++;
				break;
			case 3:
                p->ordrex = atof(&line[i]);
                while(line[i] != ' ')
                    i++;
                i++;
				break;
			case 4:
				p->ordrey = atof(&line[i]);
				while(line[i] != ' ')
					i++;
				i++;
				break;
			case 5:
				if (line[i] == '+')
                {
                    i++;
                    p->angle += atoi(&line[i]);
                }
                else if (line[i] == '-')
                {
                    i++;
                    p->angle -= atoi(&line[i]);
                }
                else
                {
                    i++;
                    p->angle = atoi(&line[i]);
                }
                while(line[i] != ' ')
                    i++;
                i++;
                break;
			case 6:
                p->timer_dom = atoi(&line[i]);
                while(line[i] != ' ')
                    i++;
                i++;
                break;
			case 7:
                p->faim = atoi(&line[i]);
                while(line[i] != ' ')
                    i++;
                i++;
                break;
			case 8:
				j = 0;
                while(line[i] != ' ')
				{
					p->skin[j] = line[i];
                    i++;
					j++;
				}
				p->skin[j] = 0;
                i++;
                break;
			case 10:
				j = 0;
				while(line[i] != ' ')
				{
					p->nom_superieur[j] = line[i];
					i++;
					j++;
				}
				p->nom_superieur[j] = 0;
				i++;
				break;
			case 11:
				j = 0;
				while (line[i] != ' ')
				{
					p->titre[j] = line[i];
					i++;
					j++;
				}
				p->titre[j] = 0;
				i++;
				break;
			case 12:
                j = 0;
                while (line[i] != ' ')
                {
                    p->religion[j] = line[i];
                    i++;
                    j++;
                }
                p->religion[j] = 0;
                i++;
                break;
			case 13:
                j = 0;
                while (line[i] != ' ')
                {
                    p->region[j] = line[i];
                    i++;
                    j++;
                }
                p->region[j] = 0;
                i++;
                break;
			case 14:
				p->est_chef = line[i];
				i += 2;
				break;
			case 15:
				if (line[i] == '+')
				{
					i++;
					int n = atoi(&line[i]);
					while (line[i] != ' ')
						i++;
					i++;
					j = 0;
					while (line[i] != ' ')
					{
						tmpC[j] = line[i];
						j++;
						i++;
					}
					tmpC[j] = 0;
					i++;
					p->e_list = append_enemie(tmpC, p->e_list, n);
				}
				else
				{
					i++;
                    while (line[i] != ' ')
                        i++;
                    i++;
                    j = 0;
                    while (line[i] != ' ')
                    {
                        tmpC[j] = line[i];
                        j++;
                        i++;
                    }
                    tmpC[j] = 0;
                    i++;
                    p->e_list = remove_enemie(tmpC, p->e_list);
				}
				break;
			case 16: // pas sur
				if (line[i] == '+')
                {
                    i++;
                    int n = atoi(&line[i]);
                    while (line[i] != ' ')
                        i++;
                    i++;
                    j = 0;
                    while (line[i] != ' ')
                    {
                        tmpC[j] = line[i];
                        j++;
                        i++;
                    }
                    tmpC[j] = 0;
                    i++;
                    p->i_list = append_in_inventory(tmpC, p->i_list, n);
                }
                else
                {
                    i++;
					int n = atoi(&line[i]);
                    while (line[i] != ' ')
                        i++;
                    i++;
                    j = 0;
                    while (line[i] != ' ')
                    {
                        tmpC[j] = line[i];
                        j++;
                        i++;
                    }
                    tmpC[j] = 0;
                    i++;
                    p->i_list = remove_from_inventory(tmpC, p->i_list, n);
                }
				break;
			case 17:
				j = 0;
                while (line[i] != ' ')
                {
                    p->echange_player[j] = line[i];
                    i++;
                    j++;
                }
                p->echange_player[j] = 0;
                i++;
                break;
			case 18:
				p->item1 = atoi(&line[i]);
                while(line[i] != ' ')
                    i++;
                i++;
                break;
			case 19:
				p->item2 = atoi(&line[i]);
                while(line[i] != ' ')
                    i++;
                i++;
                break;
			case 20: // pas sur
                j = 0;
                while (line[i] != ']')
                {
                    p->speak[j] = line[i];
					i++;
                    j++;
                }
                p->speak[j] = ']';
                list->speak[j + 1] = 0;
                i += 2;
                break;
			case 21:
                p->animation = atoi(&line[i]);
                while(line[i] != ' ')
                    i++;
                i++;
                break;
			case 22:
				p->animation_2 = atoi(&line[i]);
				while (line[i] != ' ')
					i++;
				i++;
				break;
		}
	}
}

void parse_new(struct personnages *list, char *line)
{
	int i = 0;
	int j = 0;
	char tmpI[10];
	char tmpF[30];
	char tmpN[50];
	while (line[i] != ' ')
	{
		tmpI[j] = line[i];
		j++;
		i++;
	}
	tmpI[j] = 0;
	list->id = atoi(tmpI);
	i++;
	j = 0;
	while (line[i] != ' ')
	{
		tmpI[j] = line[i];
		i++;
		j++;
	}
	tmpI[j] = 0;
	j = 0;
	i++;
	list->pv = atoi(tmpI);
	while (line[i] != ' ')
	{
		list->nom_de_compte[j] = line[i];
		j++;
		i++;
	}
	list->nom_de_compte[j] = 0;
	i++;
	j = 0;
	while (line[i] != ' ')
	{
		tmpF[j] = line[i];
		j++;
		i++;
	}
	tmpF[j] = 0;
	j = 0;
	list->x = atof(tmpF);
	i++;
	while (line[i] != ' ')
	{
		tmpF[j] = line[i];
		i++;
		j++;
	}
	tmpF[j] = 0;
	j = 0;
	list->y = atof(tmpF);
	i++;
	while (line[i] != ' ')
	{
		tmpF[j] = line[i];
		i++;
		j++;
	}
	tmpF[j] = 0;
	j = 0;
	list->ordrex = atof(tmpF);
	i++;
	while (line[i] != ' ')
	{
		tmpF[j] = line[i];
		i++;
		j++;
	}
	tmpF[j] = 0;
	j = 0;
	list->ordrey = atof(tmpF);
	i++;
	while (line[i] != ' ')
	{
		tmpI[j] = line[i];
		i++;
		j++;
	}
	tmpI[j] = 0;
	j = 0;
	i++;
	list->angle = atoi(tmpI);
	while (line[i] != ' ')
	{
		tmpI[j] = line[i];
		i++;
		j++;
	}
	tmpI[j] = 0;
	j = 0;
	i++;
	list->timer_dom = atoi(tmpI);
	while (line[i] != ' ')
	{
		tmpI[j] = line[i];
		i++;
		j++;
	}
	tmpI[j] = 0;
	j = 0;
	i++;
	list->faim = atoi(tmpI);
	while (line[i] != ' ')
	{
		list->skin[j] = line[i];
		j++;
		i++;
	}
	list->skin[j] = 0;
	j = 0;
	i++;
	while (line[i] != ' ')
	{
		list->nom[j] = line[i];
		j++;
		i++;
	}
	list->nom[j] = 0;
	j = 0;
	i++;
	while (line[i] != ' ')
	{
		list->nom_superieur[j] = line[i];
		j++;
		i++;
	}
	list->nom_superieur[j] = 0;
	j = 0;
	i++;
	while (line[i] != ' ')
	{
		list->titre[j] = line[i];
		j++;
		i++;
	}
	list->titre[j] = 0;
	j = 0;
	i++;
	while (line[i] != ' ')
	{
		list->religion[j] = line[i];
		j++;
		i++;
	}
	list->religion[j] = 0;
	j = 0;
	i++;
	while (line[i] != ' ')
	{
		list->region[j] = line[i];
		j++;
		i++;
	}
	list->region[j] = 0;
	list->est_chef = line[i + 1];
	i += 3;
	while (line[i] != ']')
    {
        i += 1;
        if (line[i] != ']')
        {
            j = 0;
            while (line[i] != ' ')
            {
                tmpN[j] = line[i];
                i++;
                j++;
            }
            tmpN[j] = 0;
            i++;
            j = 0;
            while (line[i] != ' ' && line[i] != ']')
            {
                tmpI[j] = line[i];
                i++;
                j++;
            }
            tmpI[j] = 0;
            list->e_list = append_enemie(tmpN, list->e_list, atoi(tmpI));
        }
    }
    i += 2;
	while (line[i] != ']')
	{
        i += 1;
        if (line[i] != ']')
        {
            j = 0;
            while (line[i] != ' ')
            {
                tmpN[j] = line[i];
                i++;
                j++;
            }
            tmpN[j] = 0;
            i++;
            j = 0;
            while (line[i] != ' ' && line[i] != ']')
            {
                tmpI[j] = line[i];
                i++;
                j++;
            }
            tmpI[j] = 0;
            list->i_list = append_in_inventory(tmpN, list->i_list, atoi(tmpI));
        }
    }
	i += 2;
	j = 0;
	while (line[i] != ' ')
	{
		list->echange_player[j] = line[i];
		j++;
		i++;
	}
	list->echange_player[j] = 0;
	i++;
	j = 0;
	while (line[i] != ' ')
	{
		tmpI[j] = line[i];
		i++;
		j++;
	}
	tmpI[j] = 0;
	j = 0;
	i++;
	list->item1 = atoi(tmpI);
	while (line[i] != ' ')
	{
		tmpI[j] = line[i];
		i++;
		j++;
	}
	tmpI[j] = 0;
	list->item2 = atoi(tmpI);
	i++;
	j = 0;
	while (line[i] != ']')
	{
		list->speak[j] = line[i];
		i++;
		j++;
	}
	list->speak[j] = ']';
	list->speak[j + 1] = 0;
	i += 2;
	j = 0;
	while (line[i] != ' ')
	{
		tmpI[j] = line[i];
		j++;
		i++;
	}
	i++;
	tmpI[j] = 0;
	j = 0;
	list->animation = atoi(tmpI);
	while (line[i] != 0 && line[i] != '\n')
	{
		tmpI[j] = line[i];
		j++;
		i++;
	}
	i++;
	tmpI[j] = 0;
	j = 0;
	list->animation_2 = atoi(tmpI);
	
}

struct personnages *append_perso(char *line, struct personnages *list)
{
	if (list == NULL)
	{
		list = malloc(sizeof(struct personnages));
		list->e_list = NULL;
		list->i_list = NULL;
		parse_new(list, line);
		list->next = NULL;
	}
	else
	{
		if (list->next == NULL)
		{
			struct personnages *n = malloc(sizeof(struct personnages));
			n->e_list = NULL;
			n->i_list = NULL;
			parse_new(n, line);
			list->next = n;
			n->next = NULL;
		}
		else
			append_perso(line, list->next);
	}
	return list;
}

int get_id(char *line, int *i)
{
	char tmp[10] = "\0";
	int j = 0;
	while ((line[*i] >= '0' && line[*i] <= '9'))
	{
		tmp[j] = line[*i];
		*i = *i + 1;
		j++;
	}
	return atoi(tmp);
}


struct personnages *get_ptr_from_id(int id, struct personnages *list)
{
	struct personnages *parcour = list;
	while (parcour != NULL)
	{
		if (parcour->id == id)
			return parcour;
		parcour = parcour->next;
	}
	return NULL;
}

struct personnages *remove_perso(struct personnages *list)
{
	struct personnages *ret = list;
	struct personnages *prev;
	if (list != NULL)
	{
		if (list->pv <= 0)
		{
			list = list->next;
			free_linked_enemie(ret->e_list);
			free_linked_item(ret->i_list);
			free(ret);
			ret = list;
		}
		while (list->next != NULL)
		{
			prev = list;
			list = list->next;
			if (list->pv <= 0)
			{
				prev->next = list->next;
				free_linked_enemie(list->e_list);
				free_linked_item(list->i_list);
				free(list);
				list = prev;
			}
		}
		if (list->pv <= 0)
		{
			prev->next = NULL;
			free_linked_enemie(list->e_list);
			free_linked_item(list->i_list);
			free(list);
		}
	}
	return ret;
}
