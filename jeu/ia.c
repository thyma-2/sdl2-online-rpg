#include "ia.h"

void ia(struct linked_list *list, char *array)
{
    for (struct linked_list *parcour = list; parcour != NULL; parcour = parcour->next)
    {
        if (strcmp(parcour->p->nom_de_compte, "none") == 0)
        {
	    if (strncmp(parcour->p->skin, "ship", 4) == 0)
		ia_ship(list, parcour);
	    //else if (strncmp(skin "build", 5) == 0)
		//ordres = ia_build(list, ordres);
	    else if(strncmp(parcour->p->skin, "arbre", 5) == 0)
		ia_arbre(list, parcour);
	    else if(strncmp(parcour->p->skin, "fruit", 5) == 0)
		ia_fruit(list, parcour, array);
	    else
		ia_man(list, parcour, array);
	}
    }
}

void ia_fruit(struct linked_list *list, struct linked_list *parcour, char *ground)
{
    if (parcour->p->faim < 0)
    {
        parcour->p->a_bouger = 1;
	parcour->p->pv = 0;
	int x = ((int)(parcour->p->x + 0.5) - (int)(parcour->p->x + 0.5) % 25) / 25;
        int y = ((int)(parcour->p->y + 0.5) - (int)(parcour->p->y + 0.5) % 25) / 25;
	int src = y * max_x + x;
	if (rand() % 3 == 1 && (ground[src] == 6 || ground[src] == 7 || ground[src] == 8 || ground[src] == 9 || ground[src] == 10 || ground[src] == 3 || ground[src] == 4 || ground[src] == 5))
	{
            char *line = malloc(1000);
            char *s = line;
            line[0] = 0;
            strcat(line, "-1 100 none ");
            char tmpI[20];
            tmpI[0] = 0;
            sprintf (tmpI, "%f", parcour->p->x - 45);
            strcat(line, tmpI);
            strcat(line, " ");
            tmpI[0] = 0;
            sprintf (tmpI, "%f", parcour->p->y - 153);
            strcat(line, tmpI);
            strcat(line, " 0 0 0 0 100000 arbre1 none none none region1 n [] [] none 0 0 [] 0 0");
            append_perso(list, &line);
            struct personnages *p = get_ptr_from_id(s, list);
            p->a_bouger = 1;
	}
    }
    else
        parcour->p->faim -= 1;
}

void ia_arbre(struct linked_list *list, struct linked_list *parcour)
{
    if (parcour->p->faim < 0)
    {
        parcour->p->a_bouger = 1;
	parcour->p->faim = 100000;
	char *line = malloc(1000);
	char *s = line;
	line[0] = 0;
        strcat(line, "-1 1 none ");
        char tmpI[20];
        tmpI[0] = 0;
        sprintf (tmpI, "%f", parcour->p->x + rand() % 100 - rand() % 100 + 45);
        strcat(line, tmpI);
        strcat(line, " ");
        tmpI[0] = 0;
        sprintf (tmpI, "%f", parcour->p->y + rand() % 100 - rand() % 100 + 153);
        strcat(line, tmpI);
        strcat(line, " 0 0 0 0 100000 fruit none none none region1 n [] [] none 0 0 [] 0 0");
	append_perso(list, &line);
	struct personnages *p = get_ptr_from_id(s, list);
	p->a_bouger = 1;
    }
    else
        parcour->p->faim -= 1;
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
		//parcour2->p->last_x = parcour2->p->x;
		//parcour2->p->last_y = parcour2->p->y;
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
	    struct linked_item *obj1 = get_item_n(parcour->p->item2, parcour->p->i_list);
	    struct linked_item *obj2 = get_item_n(parcour->p->item1, p->i_list);
	    parcour->p->echange_player[0] = 0;
            strcat(parcour->p->echange_player, "none");
	    if (obj1 != NULL && obj2 != NULL)
	    {
	        p->i_list = append_in_inventory(obj1->nom, p->i_list, 1);
                parcour->p->i_list = append_in_inventory(obj2->nom, parcour->p->i_list, 1);
                p->i_list = remove_from_inventory(obj2->nom, p->i_list, 1);
                parcour->p->i_list = remove_from_inventory(obj1->nom, parcour->p->i_list, 1);
		p->a_bouger = 1;
                parcour->p->a_bouger = 1;
	    }
	    else if (obj1 == NULL && obj2 != NULL)
	    {
		parcour->p->i_list = append_in_inventory(obj2->nom, parcour->p->i_list, 1);
                p->i_list = remove_from_inventory(obj2->nom, p->i_list, 1);
		p->a_bouger = 1;
                parcour->p->a_bouger = 1;
	    }
	    else if (obj2 == NULL && obj1 != NULL)
	    {
		p->i_list = append_in_inventory(obj1->nom, p->i_list, 1);
                parcour->p->i_list = remove_from_inventory(obj1->nom, parcour->p->i_list, 1);
	        p->a_bouger = 1;
		parcour->p->a_bouger = 1;
	    }
	}
    }
}

void ia_man(struct linked_list *list, struct linked_list *parcour, char *array)
{
    if (parcour->p->faim < 0)
    {
	parcour->p->pv -= 1;
	parcour->p->a_bouger = 1;
    }
    else
	parcour->p->faim -= 1;
    if (parcour->p->ordrex > 0)
    {
        int angle = findpath(parcour->p, array);
	parcour->p->a_bouger = 1;
	if (angle > 0)
	{
	    parcour->p->angle = angle;
	    parcour->p->x += parcour->p->vitesse_dep * sin(angle / 57.3);
	    parcour->p->y -= parcour->p->vitesse_dep * cos(angle / 57.3);
	}
	else
	{
	    if (angle < 0)
	        parcour->p->ordrex = 0;
	    free(parcour->p->chemin);
	    parcour->p->chemin = NULL;
	}
    }
    if (parcour->p->timer_dom > 0)
        parcour->p->timer_dom -= 1;
    else
    {
        for (struct linked_list *parcour2 = list; parcour2 != NULL; parcour2 = parcour2->next)
	{
	    for (struct linked_enemie *e = parcour->p->e_list; e != NULL; e = e->next)
	    {
		if (parcour->p->timer_dom == 0)
		{
		    if (strcmp(e->nom, parcour2->p->nom) == 0)
		    {
		        if ((parcour->p->x - parcour2->p->x) * (parcour->p->x - parcour2->p->x) + (parcour->p->y - parcour2->p->y) * (parcour->p->y - parcour2->p->y) < parcour->p->porte_dom * parcour->p->porte_dom)
			{
			    if (strcmp(parcour->p->skin, "archer") == 0)
			    {
				if (exist_in_linked_item(parcour->p->i_list, "fleche") != NULL)
				{
				    parcour->p->i_list = remove_from_inventory("fleche", parcour->p->i_list, 1);
			            parcour->p->timer_dom = parcour->p->vitesse_dom;
         	   	            parcour2->p->pv -= 5;
			            parcour->p->a_bouger = 1;
			            parcour2->p->a_bouger = 1;
				}
			    }
			    else
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
    if (strcmp(parcour->p->echange_player, "none") != 0)
    {
	parcour->p->speak[0] = 0;
	strcat(parcour->p->speak, "Votre proposition est ininteressante");
	parcour->p->speak_timer = 1350;
	parcour->p->echange_player[0] = 0;
	strcat(parcour->p->echange_player, "none");
	parcour->p->a_bouger = 1;
    }
    if (parcour->p->faim == 50000)
    {
	struct linked_item *a = exist_in_linked_item(parcour->p->i_list, "fruit");
	if (a != NULL)
	    use(a, parcour->p);
	else
	{
    	    parcour->p->speak[0] = 0;
            strcat(parcour->p->speak, "J'ai faim! Je n ai rien a manger !");
            parcour->p->speak_timer = 1350;
	    parcour->p->a_bouger = 1;
	}
    }
    if (parcour->p->speak_timer >= 0)
	parcour->p->speak_timer --;
    else if (parcour->p->speak_timer == 0)
    {
        parcour->p->speak[0] = 0;
        parcour->p->a_bouger = 1;
    }
}
