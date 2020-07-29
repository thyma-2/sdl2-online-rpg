#include "ia.h"

void append_enemi_list(struct linked_list *list, struct personnages *p)
{
    for (struct linked_list *l = list; l != NULL; l = l->next)
	if (strcmp(l->p->nom, p->nom_superieur) == 0)
	    for (struct linked_char *e = l->p->e_list; e != NULL; e = e->next)
		if (exist_in_linked_char(p->e_list, e->nom) == 0)
	            p->e_list = append_linked_char(e->nom, p->e_list);
}

void ia(struct linked_list *list)
{
    for (struct linked_list *parcour = list; parcour != NULL; parcour = parcour->next)
    {
        if (strcmp(parcour->p->nom_de_compte, "none") == 0)
        {
	    if (strncmp(parcour->p->skin, "ship", 4) == 0)
		ia_ship(list, parcour);
	    //else if (strncmp(skin "build", 5) == 0)
		//ordres = ia_build(list, ordres);
	    else
		ia_man(list, parcour);
	}
    }
}

void ia_ship(struct linked_list *list, struct linked_list *parcour)
{
    if (parcour->p->vitesse_dep > 0)
    {
	int x1;
	int x2;
	int x3;
	int x4;
	int y1;
	int y2;
	int y3;
	int y4;
	coo_corner(parcour->p, &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4);
	int x = ((x1 + x2 + x3 + x4) / 4) - parcour->p->ordrex;
	int y = parcour->p->ordrey - ((y1 + y2 + y3 + y4) / 4);
	int angle;
	if (y > 0)
	    angle = (atan(x/y) * 57.3) + 180;
	else if (y < 0)
	{	
	    if (x > 0)
 	         angle = (atan(x/y) * 57.3) + 360;
	    else
      	        angle = atan(x/y) * 57.3;
	}
	if (angle > parcour->p->angle)
	{
	    if (angle - parcour->p->angle < 180)
		parcour->p->angle += 1;
	    else
		parcour->p->angle -= 1;
	}
	else
	{
	    if (parcour->p->angle - angle < 180)
	        parcour->p->angle -= 1;
	    else
		parcour->p->angle += 1;
	}
	if (parcour->p->angle > 360)
	    parcour->p->angle = 0;
	else if (parcour->p->angle < 0)
	    parcour->p->angle = 360;
        parcour->p->y -= parcour->p->vitesse_dep * cos(parcour->p->angle / 57.3);
        parcour->p->x += parcour->p->vitesse_dep * sin(parcour->p->angle / 57.3);
        parcour->p->ordrey -= cos(angle / 57.3);
	parcour->p->ordrex += sin(angle / 57.3);
	for (struct linked_list *parcour2 = list; parcour2 != NULL; parcour2 = parcour2->next)
	{
	    if (parcour2->p->sur_plancher == parcour->p)
	    {
		parcour2->p->last_x = parcour2->p->x;
		parcour2->p->last_y = parcour2->p->y;
		parcour2->p->x += parcour->p->vitesse_dep * sin(parcour->p->angle / 57.3);
        	parcour2->p->y -= parcour->p->vitesse_dep * cos(parcour->p->angle / 57.3);
		parcour2->p->a_bouger = 1;;
	    }
	}
	parcour->p->vitesse_dep -= 1;
    }
    if (strcmp(parcour->p->echange_player, "none") != 0)
    {
        struct personnages *p = find_perso_by_name(list, parcour->p->echange_player);
        if (p != NULL)
        {
	    struct linked_char *obj1 = get_char_n(parcour->p->item2, parcour->p->i_list);
	    struct linked_char *obj2 = get_char_n(parcour->p->item1, p->i_list);
	    parcour->p->echange_player[0] = 0;
            strcat(parcour->p->echange_player, "none");
	    if (obj1 != NULL && obj2 != NULL)
	    {
                char tmp[50];
                tmp[0] = 0;
                strcat(tmp, obj1->nom);
                obj1->nom[0] = 0;
                strcat(obj1->nom, obj2->nom);
                obj2->nom[0] = 0;
                strcat(obj2->nom, tmp);
		p->a_bouger = 1;
                parcour->p->a_bouger = 1;
	    }
	    else if (obj1 == NULL && obj2 != NULL)
	    {
	        parcour->p->i_list = append_linked_char(obj2->nom, parcour->p->i_list);
                p->i_list = remove_enemi(obj2->nom, p->i_list);
		p->a_bouger = 1;
                parcour->p->a_bouger = 1;
	    }
	    else if (obj2 == NULL && obj1 != NULL)
	    {
	        p->i_list = append_linked_char(obj1->nom, p->i_list);
                parcour->p->i_list = remove_enemi(obj1->nom, parcour->p->i_list);
	        p->a_bouger = 1;
		parcour->p->a_bouger = 1;
	    }
	}
    }
}

void ia_man(struct linked_list *list, struct linked_list *parcour)
{
    append_enemi_list(list, parcour->p);
    if (parcour->p->ordrex >= 0)
    {
        int x = parcour->p->x - parcour->p->ordrex;
        int y = parcour->p->ordrey - parcour->p->y;
        if (y > 0)
            parcour->p->angle = (atan(x/y) * 57.3) + 180;
        else if (x > 0 && y < 0)
            parcour->p->angle = (atan(x/y) * 57.3) + 360;
        else if (x < 0 && y < 0)
            parcour->p->angle = (atan(x/y) * 57.3);
        parcour->p->y -= parcour->p->vitesse_dep * cos(parcour->p->angle / 57.3);
        parcour->p->x += parcour->p->vitesse_dep * sin(parcour->p->angle / 57.3);
        if (fabs(parcour->p->x - parcour->p->ordrex) <= 2 && fabs(parcour->p->y - parcour->p->ordrey) <= 2)
            parcour->p->ordrex = -1;
	parcour->p->a_bouger = 1;
    }
    else
    {
	if (parcour->p->sur_plancher != NULL)
	{
	    if (strcmp(parcour->p->sur_plancher->skin, "ship1") == 0)
	    {
      	        int x1;
 	        int x2;
	        int x3;
    	        int x4;
	        int y1;
	        int y2;
	        int y3;
	        int y4;
	        coo_corner(parcour->p->sur_plancher, &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4);
		int x;
		int y;
		if (parcour->p->id % 2 == 0)
		{
		    x = parcour->p->x - (x1 + x4 * parcour->p->id) / (parcour->p->id + 1);
	            y = (y1 + y4 * parcour->p->id) / (parcour->p->id + 1)  - parcour->p->y;
		}

		else
		{
 		    x = parcour->p->x - (x2 + x3 * parcour->p->id) / (parcour->p->id + 1);
                    y = (y2 + y3 * parcour->p->id) / (parcour->p->id + 1) - parcour->p->y;
		}
         	if (y > 0)
                    parcour->p->angle = (atan(x/y) * 57.3) + 180;
                else if (x > 0 && y < 0)
                    parcour->p->angle = (atan(x/y) * 57.3) + 360;
                else if (x < 0 && y < 0)
                    parcour->p->angle = (atan(x/y) * 57.3);
                parcour->p->y -= parcour->p->vitesse_dep * cos(parcour->p->angle / 57.3);
                parcour->p->x += parcour->p->vitesse_dep * sin(parcour->p->angle / 57.3);
                parcour->p->sur_plancher->vitesse_dep += 1;
		parcour->p->a_bouger = 1;
	    }
	}
    }
    if (parcour->p->timer_dom > 0)
        parcour->p->timer_dom -= 1;
    else
    {
        for (struct linked_list *parcour2 = list; parcour2 != NULL; parcour2 = parcour2->next)
	{
	    for (struct linked_char *e = parcour->p->e_list; e != NULL; e = e->next)
	    {
		if (parcour->p->timer_dom == 0)
		{
		    if (strcmp(e->nom, parcour2->p->nom) == 0)
		    {
		        if ((parcour->p->x - parcour2->p->x) * (parcour->p->x - parcour2->p->x) + (parcour->p->y - parcour2->p->y) * (parcour->p->y - parcour2->p->y) < parcour->p->porte_dom * parcour->p->porte_dom)
			{
			    parcour->p->timer_dom = parcour->p->vitesse_dom;
			    parcour2->p->pv -= 5;
			    parcour->p->a_bouger = 1;
			    parcour2->p->a_bouger = 1;
			}
		    }
		}
	    }
	}
    }
}
