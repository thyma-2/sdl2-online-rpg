#define _GNU_SOURCE
#include "perso.h"

struct personnages *init_map(void)
{
	FILE *acount = fopen("map.txt", "r+");
	char *line = NULL;
	size_t len = 0;
	struct personnages *list = NULL;
	char *buffer = malloc(10000);
	buffer[0] = 0;
	while (getline(&line, &len, acount) > 0)
		strcat(buffer, line);
	while (*buffer != 0)
	{
		list = append_perso(&buffer, list);
		buffer = buffer + 1;
	}
	return list;
}

int parse_order(struct personnages *list, char *line)
{
	int i = 0;
	int j = 0;
	int tmpint;
	float tmpfloat;
	char tmpI[10];
	char tmpF[30];
	char tmpC[90];
	while (line[i] != ' ')
	{
		tmpI[j] = line[i];
		j++;
		i++;
	}
	tmpI[j] = 0;
	tmpint = atoi(tmpI);
	if (list->original->id != tmpint)
		list->id = tmpint;
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
	tmpint = atoi(tmpI);
	if (list->original->id != tmpint)
		list->pv = tmpint;
	while (line[i] != ' ')
	{
		tmpC[j] = line[i];
		j++;
		i++;
	}
	tmpC[j] = 0;
	if (strcmp(list->original->nom_de_compte, tmpC) != 0)
		strcpy(list->nom_de_compte, tmpC);
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
	tmpfloat = atof(tmpF);
	if (list->original->x != tmpfloat)
		list->x = tmpfloat;
	i++;
	while (line[i] != ' ')
	{
		tmpF[j] = line[i];
		i++;
		j++;
	}
	tmpF[j] = 0;
	j = 0;
	tmpfloat = atof(tmpF);
	if (tmpfloat != list->original->y)
		list->y = tmpfloat;
	i++;
	while (line[i] != ' ')
	{
		tmpF[j] = line[i];
		i++;
		j++;
	}
	tmpF[j] = 0;
	j = 0;
	tmpfloat = atof(tmpF);
	if (tmpfloat != list->original->ordrex)
		list->ordrex = tmpfloat;
	i++;
	while (line[i] != ' ')
	{
		tmpF[j] = line[i];
		i++;
		j++;
	}
	tmpF[j] = 0;
	j = 0;
	tmpfloat = atof(tmpF);
	if (tmpfloat != list->original->ordrey)
		list->ordrey = tmpfloat;
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
	tmpint = atoi(tmpI);
	if (tmpint != list->original->angle)
		list->angle = tmpint;
	while (line[i] != ' ')
	{
		tmpI[j] = line[i];
		i++;
		j++;
	}
	tmpI[j] = 0;
	j = 0;
	i++;
	tmpint = atoi(tmpI);
	if (tmpint != list->original->timer_dom)
		list->timer_dom = tmpint;
	while (line[i] != ' ')
	{
		tmpI[j] = line[i];
		i++;
		j++;
	}
	tmpI[j] = 0;
	j = 0;
	i++;
	tmpint = atoi(tmpI);
	if (tmpint != list->original->faim)
		list->faim = tmpint;
	while (line[i] != ' ')
	{
		tmpC[j] = line[i];
		j++;
		i++;
	}
	tmpC[j] = 0;
	if (strcmp(tmpC, list->original->skin) != 0)
		strcpy(list->skin, tmpC);
	j = 0;
	i++;
	while (line[i] != ' ')
	{
		tmpC[j] = line[i];
		j++;
		i++;
	}
	tmpC[j] = 0;
	j = 0;
	i++;
	if (strcmp(tmpC, list->original->nom) != 0)
		strcpy(list->nom, tmpC);
	while (line[i] != ' ')
	{
		tmpC[j] = line[i];
		j++;
		i++;
	}
	tmpC[j] = 0;
	j = 0;
	i++;
	if (strcmp(tmpC, list->original->nom_superieur) != 0)
		strcpy(list->nom_superieur, tmpC);
	while (line[i] != ' ')
	{
		tmpC[j] = line[i];
		j++;
		i++;
	}
	tmpC[j] = 0;
	j = 0;
	i++;
	if (strcmp(tmpC, list->original->titre) != 0)
		strcpy(list->titre, tmpC);
	while (line[i] != ' ')
	{
		tmpC[j] = line[i];
		j++;
		i++;
	}
	tmpC[j] = 0;
	j = 0;
	i++;
	if (strcmp(tmpC, list->original->religion) != 0)
		strcpy(list->religion, tmpC);
	while (line[i] != ' ')
	{
		tmpC[j] = line[i];
		j++;
		i++;
	}
	tmpC[j] = 0;
	if (strcmp(tmpC, list->original->region) != 0)
		strcpy(list->region, tmpC);
	if (list->original->est_chef != line[i + 1])
		list->est_chef = line[i + 1];
	i += 3;
	j = 0;
	while (line[i] != ']')
	{
		i += 1;
		j += 1;
	}
	if (strncmp(&line[i - j], list->original->e_list, j + 1) != 0)
	{
		list->e_list = realloc(list->e_list, j + 2);
		strncpy(list->e_list, &line[i -j], j + 1);
		list->e_list[j + 1] = 0;
	}
	i += 2;
	j = 0;
	while (line[i] != ']')
	{
		i += 1;
		j += 1;
	}
	if (strncmp(&line[i - j], list->original->i_list, j + 1) != 0)
    {
        list->i_list = realloc(list->i_list, j + 2);
        strncpy(list->i_list, &line[i -j], j + 1);
		list->i_list[j + 1] = 0;
    }
	i += 2;
	j = 0;
	while (line[i] != ' ')
	{
		tmpC[j] = line[i];
		j++;
		i++;
	}
	tmpC[j] = 0;
	if (strcmp(tmpC, list->original->echange_player) != 0)
        strcpy(list->echange_player, tmpC);
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
	tmpint = atoi(tmpI);
	if (list->original->item1 != tmpint)
		list->item1 = tmpint;
	while (line[i] != ' ')
	{
		tmpI[j] = line[i];
		i++;
		j++;
	}
	tmpI[j] = 0;
	tmpint = atoi(tmpI);
	if (list->original->item2 != tmpint)
		list->item2 = tmpint;
	i += 2;
	j = 0;
	while (line[i] != ']')
	{
		tmpC[j] = line[i];
		i++;
		j++;
	}
	tmpC[j] = 0;
	i += 2;
	j = 0;
	if (strcmp(tmpC, list->original->speak) != 0)
		strcpy(list->speak, tmpC);
	while (line[i] != ' ')
	{
		tmpI[j] = line[i];
		j++;
		i++;
	}
	i++;
	tmpI[j] = 0;
	j = 0;
	tmpint = atoi(tmpI);
	if (tmpint != list->original->animation)
		list->animation = tmpint;
	while (line[i] != 0 && line[i] != '\n')
	{
		tmpI[j] = line[i];
		j++;
		i++;
	}
	tmpI[j] = 0;
	tmpint = atoi(tmpI);
	if (tmpint != list->original->animation_r)
		list->animation_r = tmpint;
	return i;
}

struct personnages *append_perso(char **line, struct personnages *list)
{
	if (list == NULL)
	{
		list = malloc(sizeof(struct personnages));
		list->e_list = NULL;
		list->i_list = NULL;
		cp_original(list, 1);
		int a = parse_order(list, *line);
		*line = *line + a;
		list->next = NULL;
	}
	else
	{
		if (list->next == NULL)
		{
			struct personnages *n = malloc(sizeof(struct personnages));
			n->e_list = NULL;
			n->i_list = NULL;
			cp_original(n, 1);
			int a = parse_order(n, *line);
			*line = *line + a;
			list->next = n;
			n->next = NULL;
		}
		else
			append_perso(line, list->next);
	}
	return list;
}

int get_id(char *line)
{
	int i = 0;
	char tmp[10] = "\0";
	while ((line[i] >= '0' && line[i] <= '9') || line[i] == '-')
	{
		tmp[i] = line[i];
		i++;
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
			free(ret->e_list);
			free(ret->i_list);
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
				free(list->e_list);
				free(list->i_list);
				free(list);
				list = prev;
			}
		}
		if (list->pv <= 0)
		{
			prev->next = NULL;
			free(list->e_list);
			free(list->i_list);
			free(list);
		}
	}
	return ret;
}

void cp_original(struct personnages *p, char new)
{
	p->original = malloc(sizeof(struct personnages));
	if (new == 0)
	{
		p->original->id = p->id;
		p->original->pv = p->pv;
		strcpy(p->original->nom_de_compte, p->nom_de_compte);
		p->original->x = p->x;
		p->original->y = p->y;
		p->original->ordrex = p->x;
		p->original->ordrey = p->y;
		p->original->angle = p->angle;
		p->original->timer_dom = p->timer_dom;
		p->original->faim = p->faim;
		strcpy(p->original->skin, p->skin);
		strcpy(p->original->nom, p->nom);
	    strcpy(p->original->nom_superieur, p->nom_superieur);
		strcpy(p->original->titre, p->titre);
		strcpy(p->original->religion, p->religion);
		strcpy(p->original->region, p->region);
		p->original->est_chef = p->est_chef;
		p->original->e_list = malloc(strlen(p->e_list) + 1);
		strcpy(p->original->e_list, p->e_list);
		p->original->i_list = malloc(strlen(p->i_list) + 1);
	    strcpy(p->original->i_list, p->i_list);
		strcpy(p->original->echange_player, p->echange_player);
		p->original->item1 = p->item1;
		p->original->item2 = p->item2;
		strcpy(p->original->speak, p->speak);
		p->original->animation = p->animation;
		p->original->animation_r = p->animation_r;
	}
	else
	{
		p->original->id = -1;
		p->original->i_list = malloc(1);
		p->original->i_list[0] = 0;
		p->original->e_list = malloc(1);
        p->original->e_list[0] = 0;
	}
}
