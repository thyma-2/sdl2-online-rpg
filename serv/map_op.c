#include "map_op.h"

void save_map(struct personnages *list)
{
	FILE *file = fopen("map.txt","w");
	char order[100000]; //TODO
	order[0] = 0;
	while (list != NULL)
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
		list = list->next;
	}
	fprintf(file, "%s", order);
	fclose(file);
}
