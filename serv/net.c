#include "net.h"

int generate_order(struct personnages *list, char *ret)
{
    char *order = &ret[20];
    char tmp[20] = "\0";
    while (list != NULL)
    {
        if (list->original != NULL)
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
            free(list->original->e_list);
            free(list->original->i_list);
            free(list->original);
			list->original = NULL;
        }
        list = list->next;
    }
    tmp[0] = 0;
    int s = strlen(order);
    sprintf (ret, "%d", s);
    return s;
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
