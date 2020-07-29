#include "parseur.h"
struct personnages *get_ptr_from_id(char *line, struct linked_list *list)
{
    int i = 0;
    char tmp[10];
    while (line[i] != ' ' && line[i] != 0)
    {
        tmp[i] = line[i];
        i++;
    }
    int id = atoi(tmp);
    struct linked_list *parcour = list;
    while (parcour != NULL)
    {
        if (parcour->p->id == id)
            return parcour->p;
        parcour = parcour->next;
    }
    return NULL;
}

int parse_order(struct personnages *list, char *line)
{
    list->e_list = NULL;
    list->i_list = NULL;
    list->a_bouger = 0;
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
    list->last_x = list->x;
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
    list->last_y = list->y;
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
        j = 0;
        tmpN[0] = 0;
        while (line[i] != ' ' && line[i] != ']')
        {
            tmpN[j] = line[i];
            i++;
            j++;
        }
        tmpN[j] = 0;
        if (tmpN[0] != 0)
            list->e_list = append_linked_char(tmpN, list->e_list);
    }
    i += 2;
    while (line[i] != ']')
    {
	i += 1;
        j = 0;
        tmpN[0] = 0;
        while (line[i] != ' ' && line[i] != ']')
        {
            tmpN[j] = line[i];
            i++;
            j++;
        }
        tmpN[j] = 0;
        if (tmpN[0] != 0)
            list->i_list = append_linked_char(tmpN, list->i_list);
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
    i += 2;
    j = 0;
    while (line[i] != ']')
    {
        list->speak[j] = line[i];
	i++;
	j++;
    }
    list->speak[j] = 0;
    return i + 1;
}
