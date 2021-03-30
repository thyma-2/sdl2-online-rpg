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
		j++;
		i++;
	}
	tmpI[j] = 0;
	list->pv = atoi(tmpI);
	i++;
	j = 0;
	while (line[i] != ' ')
	{
		list->nom_de_compte[j] = line[i];
		j++;
		i++;
	}
	list->nom_de_compte[j] = 0;
	i++;
	j = 0;
	while (line[i] != 0 && line[i] != '\n')
	{
		list->tout_le_reste[j] = line[i];
		j++;
		i++;
	}
	list->tout_le_reste[j] = 0;
	return i;
}

struct personnages *append_perso(char **line, struct personnages *list)
{
	if (list == NULL)
	{
		list = malloc(sizeof(struct personnages));
		int a = parse_order(list, *line);
		*line = *line + a;
		list->next = NULL;
	}
	else
	{
		if (list->next == NULL)
		{
			struct personnages *n = malloc(sizeof(struct personnages));
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
	char *a = malloc(10000);
	a[0] = 0;
	char tmp[20] = "\0";
	while (list)
	{
		sprintf (tmp, "%d", list->id);
		strcat(a, tmp);
		strcat(a , " ");
		tmp[0] = 0;
		sprintf (tmp, "%d", list->pv);
		strcat(a, tmp);
		strcat(a, " ");
		strcat(a, list->nom_de_compte);
		strcat(a , " ");
		strcat (a, list->tout_le_reste);
		if (list->next != NULL)
			strcat(a, "\n");
		list = list->next;
	}
	tmp[0] = 0;
	int s = strlen(a);
	if (s > 0)
	{
		sprintf (tmp, "%d", s);
		send(socket, tmp, 20, MSG_NOSIGNAL);
		send(socket, a, s, MSG_NOSIGNAL);
	}
	free(a);
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

void send_order(int socket, struct personnages *list, int *moveObj)
{
	char *a = malloc(10000);
	char tmp[20] = "\0";
	a[0] = 0;
	while (list != NULL)
	{
		if (in_list(moveObj, list->id, 400) == 1)
		{
			sprintf(tmp, "%d", list->id);
			strcat(a, tmp);
			strcat(a , " ");
			tmp[0] = 0;
			sprintf(tmp, "%d", list->pv);
			strcat(a, tmp);
			strcat(a, " ");
			strcat(a, list->nom_de_compte);
			strcat(a , " ");
			strcat(a, list->tout_le_reste);
			if (list->next != NULL)
				strcat(a, "\n");
		}
		list = list->next;
	}
	tmp[0] = 0;
	int s = strlen(a);
	sprintf (tmp, "%d", s);
	send(socket, tmp, 20, MSG_NOSIGNAL);
	if (s > 0)
		send(socket, a, s, MSG_NOSIGNAL);
	free(a);
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
				list = prev;
			}
		}
		if (list->pv <= 0)
		{
			prev->next = NULL;
			free(list);
		}
	}
	return ret;
}
