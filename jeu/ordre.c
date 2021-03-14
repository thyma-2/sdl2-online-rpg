#include "ordre.h"

struct linked_list *select(struct linked_list *list, struct personnages *moi, struct linked_list *selected)
{
    if (lettres->Mouse_Lclick == 1)
    {
	lettres->Mouse_Lclick = 0;
        for (struct linked_list *a = list; a != NULL; a = a->next)
        {
	    int xe = (lettres->Mouse_pos_x - 600) * cos(moi->angle / 57.3) - (lettres->Mouse_pos_y - 550) * sin(moi->angle / 57.3) + moi->x;
            int ye = (lettres->Mouse_pos_x - 600) * sin(moi->angle / 57.3) + (lettres->Mouse_pos_y - 550) * cos(moi->angle / 57.3) + moi->y;
            if (check_obj_point(a->p, xe, ye) == 1)
	    {
		if (exist_in_linked(selected, a->p) == 0)
                    selected = append_in_linked(selected, a->p);
		else
		    selected  = remove_from_linked_list(selected, a->p);
	    }
        }
    }
    return selected;
}

void commande(struct linked_list *selected, struct personnages *moi, struct formation *f)
{
    if (lettres->Mouse_Rclick == 1)
    {
	int i = 0;
	int j = 0;
        for (struct linked_list *a = selected; a != NULL; a = a->next)
        {
            if (strcmp(a->p->nom_superieur, moi->nom) == 0)
            {
                a->p->ordrex = (lettres->Mouse_pos_x - 600) * cos(moi->angle / 57.3) - (lettres->Mouse_pos_y - 550) * sin(moi->angle / 57.3) + moi->x + f->ecart_x * i;
                a->p->ordrey = (lettres->Mouse_pos_x - 600) * sin(moi->angle / 57.3) + (lettres->Mouse_pos_y - 550) * cos(moi->angle / 57.3) + moi->y + f->ecart_y * j;
		i++;
		if (a->p->chemin != NULL)
		{
		    free(a->p->chemin);
		    a->p->chemin = NULL;
		}
		if (i > f->n_par_lignes)
		{
		    i = 0;
		    j++;
		}
            }
        }
        lettres->Mouse_Rclick = 0;
    }
}
