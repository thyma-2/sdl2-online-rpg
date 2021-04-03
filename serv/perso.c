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
	char tmpI[10];
	char tmpF[30];
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
	j = 0;
	while (line[i] != ']')
	{
		i += 1;
		j += 1;
	}
	list->e_list = realloc(list->e_list, j + 2);
	list->e_list[0] = 0;
	strncat(list->e_list, &line[i - j], j + 1);
	i += 2;
	j = 0;
	while (line[i] != ']')
	{
		i += 1;
		j += 1;
	}
	list->i_list = realloc(list->i_list, j + 2);
	list->i_list[0] = 0;
	strncat(list->i_list, &line[i - j], j + 1);
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
	i += 2;
	j = 0;
	while (line[i] != ']')
	{
		list->speak[j] = line[i];
		i++;
		j++;
	}
	list->speak[j] = 0;
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
	tmpI[j] = 0;
	list->animation_r = atoi(tmpI);
	return i;
}

struct personnages *append_perso(char **line, struct personnages *list)
{
	if (list == NULL)
	{
		list = malloc(sizeof(struct personnages));
		list->e_list = NULL;
		list->i_list = NULL;
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

void send_map(int socket, struct personnages *list)
{
	char order[100000];
	order[0] = 0;
	char tmp[20] = "\0";
	while (list)
	{
		sprintf (tmp, "%d", list->id);
		strcat(order, tmp);
		strcat(order , " ");
		tmp[0] = 0;
		sprintf (tmp, "%d", list->pv);
		strcat(order, tmp);
		strcat(order, " ");
		strcat(order, list->nom_de_compte);
		strcat(order, " ");
		tmp[0] = 0;
		sprintf(tmp, "%f", list->x);
		strcat(order, tmp);
		strcat(order , " ");
		tmp[0] = 0;
		sprintf(tmp, "%f", list->y);
		strcat(order, tmp);
		strcat(order , " ");
		tmp[0] = 0;
		sprintf(tmp, "%f", list->ordrex);
		strcat(order, tmp);
		strcat(order , " ");
		tmp[0] = 0;
		sprintf(tmp, "%f", list->ordrey);
		strcat(order, tmp);
		strcat(order , " ");
		tmp[0] = 0;
		sprintf (tmp, "%d", list->angle);
		strcat (order, tmp);
		strcat(order , " ");
		tmp[0] = 0;
		sprintf (tmp, "%d", list->timer_dom);
		strcat (order, tmp);
		strcat(order , " ");
		tmp[0] = 0;
		sprintf (tmp, "%d", list->faim);
		strcat (order, tmp);
		strcat(order , " ");
		strcat(order, list->skin);
		strcat(order, " ");
		strcat(order, list->nom);
		strcat(order , " ");
		strcat(order, list->nom_superieur);
		strcat(order , " ");
		strcat(order, list->titre);
		strcat(order , " ");
		strcat(order, list->religion);
		strcat(order, " ");
		strcat(order, list->region);
		if (list->est_chef == 'y')
			strcat(order, " y ");
		else
			strcat(order, " n ");
		strcat(order, list->e_list);
		strcat(order, " ");
		strcat(order, list->i_list);
		strcat(order, " ");
		strcat(order, list->echange_player);
		strcat(order, " ");
		tmp[0] = 0;
		sprintf (tmp, "%d", list->item1);
		strcat (order, tmp);
		strcat(order , " ");
		tmp[0] = 0;
		sprintf (tmp, "%d", list->item2);
		strcat (order, tmp);
		strcat (order, " [");
		strcat (order, list->speak);
		strcat (order, "] ");
		tmp[0] = 0;
		sprintf (tmp, "%d", list->animation);
		strcat (order, tmp);
		strcat (order, " ");
		tmp[0] = 0;
		sprintf (tmp, "%d", list->animation_r);
		strcat (order, tmp);
		if (list->next != NULL)
			strcat(order, "\n");
		list = list->next;
	}
	tmp[0] = 0;
	int s = strlen(order);
	if (s > 0)
	{
		sprintf (tmp, "%d", s);
		send(socket, tmp, 20, MSG_NOSIGNAL);
		send(socket, order, s, MSG_NOSIGNAL);
	}
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

int in_list(int *list, int id, int size)
{
	int i = 0;
	while (i < size)
	{
		if (list[i] == id)
			return 1;
		i++;
	}
	return -1;
}

int generate_order(struct personnages *list, int *moveObj, char *ret)
{
	char *order = &ret[20];	
	char tmp[20] = "\0";
	while (list != NULL)
	{
		if (in_list(moveObj, list->id, 400) == 1)
		{
			sprintf(tmp, "%d", list->id);
			strcat(order, tmp);
			strcat(order , " ");
			tmp[0] = 0;
			sprintf(tmp, "%d", list->pv);
			strcat(order, tmp);
			strcat(order, " ");
			strcat(order, list->nom_de_compte);
			strcat(order , " ");
			tmp[0] = 0;
			sprintf(tmp, "%f", list->x);
			strcat(order, tmp);
			strcat(order , " ");
			tmp[0] = 0;
			sprintf(tmp, "%f", list->y);
			strcat(order, tmp);
			strcat(order , " ");
			tmp[0] = 0;
			sprintf(tmp, "%f", list->ordrex);
			strcat(order, tmp);
			strcat(order , " ");
			tmp[0] = 0;
			sprintf(tmp, "%f", list->ordrey);
			strcat(order, tmp);
			strcat(order , " ");
			tmp[0] = 0;
			sprintf (tmp, "%d", list->angle);
			strcat (order, tmp);
			strcat(order , " ");
			tmp[0] = 0;
			sprintf (tmp, "%d", list->timer_dom);
			strcat (order, tmp);
			strcat(order , " ");
			tmp[0] = 0;
			sprintf (tmp, "%d", list->faim);
			strcat (order, tmp);
			strcat(order , " ");
			strcat(order, list->skin);
			strcat(order, " ");
			strcat(order, list->nom);
			strcat(order , " ");
			strcat(order, list->nom_superieur);
			strcat(order , " ");
			strcat(order, list->titre);
			strcat(order , " ");
			strcat(order, list->religion);
			strcat(order, " ");
			strcat(order, list->region);
			if (list->est_chef == 'y')
				strcat(order, " y ");
			else
				strcat(order, " n ");
			strcat(order, list->e_list);
			strcat(order, " ");
			strcat(order, list->i_list);
			strcat(order, " ");
			strcat(order, list->echange_player);
			strcat(order, " ");
			tmp[0] = 0;
			sprintf (tmp, "%d", list->item1);
			strcat (order, tmp);
			strcat(order , " ");
			tmp[0] = 0;
			sprintf (tmp, "%d", list->item2);
			strcat (order, tmp);
			strcat (order, " [");
			strcat (order, list->speak);
			strcat (order, "] ");
			tmp[0] = 0;
			sprintf (tmp, "%d", list->animation);
			strcat (order, tmp);
			strcat (order, " ");
			tmp[0] = 0;
			sprintf (tmp, "%d", list->animation_r);
			strcat (order, tmp);
			if (list->next != NULL)
				strcat(order, "\n");
		}
		list = list->next;
	}
	tmp[0] = 0;
	int s = strlen(order);
	sprintf (ret, "%d", s);
	return s;
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
			free(ret);
			free(ret->e_list);
			free(ret->i_list);
			ret = list;
		}
		while (list->next != NULL)
		{
			prev = list;
			list = list->next;
			if (list->pv <= 0)
			{
				prev->next = list->next;
				free(list);
				free(list->e_list);
				free(list->i_list);
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
