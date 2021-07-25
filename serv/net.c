#include "net.h"

int generate_order(struct personnages *list, char *ret)
{
    char *order = &ret[20];
    while (list != NULL)
    {
        if (list->a_bouger == 1)
        {
			sprintf(order + strlen(order), "%d %d %s %f %f %f %f %d %d %d %s %s %s %s %s %s %c [", list->id, list->pv, list->nom_de_compte, list->x, list->y, list->ordrex, list->ordrey, list->angle, list->timer_dom, list->faim, list->skin, list->nom, list->nom_superieur, list->titre, list->religion, list->region, list->est_chef);
			for (struct linked_enemie *p = list->e_list; p != NULL; p = p->next)
			{
				if (p->next != NULL)
					sprintf (order + strlen(order), "%s %d ", p->nom, p->rang);
				else
					sprintf (order + strlen(order), "%s %d", p->nom, p->rang);
			}
			strcat(order, "] [");
			for (struct linked_item *p = list->i_list; p != NULL; p =p->next)
			{
				if (p->next != NULL)
                    sprintf (order + strlen(order), "%s %d ", p->nom, p->count);
                else
                    sprintf (order + strlen(order), "%s %d", p->nom, p->count);
			}
			sprintf(order + strlen(order),  "] %s %d %d %s %d %d", list->echange_player, list->item1, list->item2, list->speak, list->animation, list->animation_2);
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
    char order[100020] = {0};
	char *ordre = &order[20];
    while (list)
    {
		sprintf(ordre + strlen(ordre), "%d %d %s %f %f %f %f %d %d %d %s %s %s %s %s %s %c [", list->id, list->pv, list->nom_de_compte, list->x, list->y, list->ordrex, list->ordrey, list->angle, list->timer_dom, list->faim, list->skin, list->nom, list->nom_superieur, list->titre, list->religion, list->region, list->est_chef);
        for (struct linked_enemie *p = list->e_list; p != NULL; p = p->next)
        {
            if (p->next != NULL) 
                sprintf (ordre + strlen(order), "%s %d ", p->nom, p->rang);
            else
                sprintf (ordre + strlen(order), "%s %d", p->nom, p->rang);
        }
        strcat(ordre, "] [");
        for (struct linked_item *p = list->i_list; p != NULL; p =p->next)
        {
            if (p->next != NULL) 
                sprintf (ordre + strlen(ordre), "%s %d ", p->nom, p->count);
            else
                sprintf (ordre + strlen(ordre), "%s %d", p->nom, p->count);
        }
        sprintf(ordre + strlen(ordre),  "] %s %d %d %s %d %d", list->echange_player, list->item1, list->item2, list->speak, list->animation, list->animation_2);
        if (list->next != NULL)
            strcat(ordre, "\n");
        list = list->next;
    }
	int s = strlen(ordre);
    if (s > 0)
    {
        sprintf (order, "%d", s);
        send(socket, order, s + 20, MSG_NOSIGNAL);
    }
}
