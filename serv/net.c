#include "net.h"

int generate_order(struct personnages *list, char *ret)
{
    char *order = &ret[20];
    while (list != NULL)
    {
        if (list->a_bouger == 1)
        {
			sprintf(order + strlen(order), "%d %d %s %f %f %f %f %d %d %d %s %s %s %s %s %s %c %s %s %s %d %d %s %d", list->id, list->pv, list->nom_de_compte, list->x, list->y, list->ordrex, list->ordrey, list->angle, list->timer_dom, list->faim, list->skin, list->nom, list->nom_superieur, list->titre, list->religion, list->region, list->est_chef, list->e_list, list->i_list, list->echange_player, list->item1, list->item2, list->speak, list->animation);
            if (list->next != NULL)
                strcat(order, "\n");
			list->a_bouger = 0;
        }
        list = list->next;
    }
    int s = strlen(order);
    sprintf (ret, "%d", s);
    return s;
}

void send_map(int socket, struct personnages *list)
{
    char order[100020];
	char *ordre = &order[20];
    ordre[0] = 0;
    while (list)
    {
		sprintf(ordre + strlen(ordre), "%d %d %s %f %f %f %f %d %d %d %s %s %s %s %s %s %c %s %s %s %d %d %s %d", list->id, list->pv, list->nom_de_compte, list->x, list->y, list->ordrex, list->ordrey, list->angle, list->timer_dom, list->faim, list->skin, list->nom, list->nom_superieur, list->titre, list->religion, list->region, list->est_chef, list->e_list, list->i_list, list->echange_player, list->item1, list->item2, list->speak, list->animation);
        if (list->next != NULL)
            strcat(order, "\n");
        list = list->next;
    }
	int s = strlen(ordre);
    if (s > 0)
    {
        sprintf (order, "%d", s);
        send(socket, order, s + 20, MSG_NOSIGNAL);
    }
}
