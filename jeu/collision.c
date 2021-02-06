#include "collision.h"

void collision(struct linked_list *list, char *array)
{
    for (struct linked_list *p = list; p != NULL; p = p->next)
    {
	p->p->sur_plancher = NULL;
        int x1;
	int x2;
	int x3;
	int x4;
	int y1;
	int y2;
	int y3;
	int y4;
	coo_corner(p->p, &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4);
	char obj; // colision avec un objet
	char bord = 0; // colision avec le bord
	char eau = check_eau(x1, y1, array, p->p->eau); // collision avec l'eau
	if (eau == 0)
	    eau = check_eau(x2, y2, array, p->p->eau);
	if (x1 < -12.5 || x1 > max_x * 25 - 12.5 || x2 < -12.5 || x2 > max_x * 25 - 12.5 || y1 < -12.5 || y1 > max_y * 25 - 12.5 || y2 < - 12.5 || y2 > max_y * 25 - 12.5)
	    bord = 1;
	for (struct linked_list *pp = list; pp != NULL; pp = pp->next)
	{
	    if (pp != p)
	    {
		if (pp->p->plancher == p->p->plancher)
		{
		    obj = 0;
		    if (obj == 0)
			obj = check_obj(pp->p, x1, y1);
		    if (obj == 0)
			obj = check_obj(pp->p, x2, y2);
		    if (obj == 0)
			obj = check_obj(pp->p, x3, y3);
		    if (obj == 0)
			obj = check_obj(pp->p, x4, y4);
		    if (obj == 1)
		    {
			if (strcmp(pp->p->skin, "fruit") == 0)
			{
			    if (count_item(p->p->i_list) < 9)
			    {
			        pp->p->pv = 0;
				pp->p->a_bouger = 1;
				p->p->a_bouger = 1;
				p->p->i_list = append_in_inventory("fruit", p->p->i_list, 1);
			    }
			}
			else if (strcmp(p->p->skin, "fruit") == 0)
                        {
                            if (count_item(pp->p->i_list) < 9)
                            {
                                p->p->pv = 0;
				pp->p->a_bouger = 1;
                                p->p->a_bouger = 1;
                                pp->p->i_list = append_in_inventory("fruit", pp->p->i_list, 1);
                            }
			}
			else
			{
		            if (p->p->last_x == p->p->x && p->p->last_y == p->p->y) // je me fait percuter
			    {
			        int x = pp->p->x - pp->p->last_x;
			        int y = pp->p->y - pp->p->last_y;
			        p->p->x += x * pp->p->poid / p->p->poid;
			        p->p->y += y * pp->p->poid / p->p->poid;
			        pp->p->x = pp->p->last_x;
			        pp->p->y = pp->p->last_y;
			    }
			    else if (pp->p->last_x == p->p->x && pp->p->last_y == p->p->y) // je percute qqe chose
		    	    {
			        int x = p->p->x - p->p->last_x;
                                int y = p->p->y - p->p->last_y;
                                pp->p->x += x * p->p->poid / pp->p->poid;
                                pp->p->y += y * p->p->poid / pp->p->poid;
                                p->p->x = p->p->last_x;
                                p->p->y = p->p->last_y;
			    }
			    else // on ce percute mutuellement 
			    {
			        int x = pp->p->x - pp->p->last_x;
                                int y = pp->p->y - pp->p->last_y;
			        int x2 = p->p->x - p->p->last_x;
                                int y2 = p->p->y - p->p->last_y;
			        p->p->x += x * pp->p->poid / p->p->poid;
			        p->p->y += y * pp->p->poid / p->p->poid;
			        pp->p->x += x2 * p->p->poid / pp->p->poid;
                                pp->p->y += y2 * p->p->poid / pp->p->poid;
			    }
		 	    pp->p->a_bouger = 1;
			    p->p->a_bouger = 1;
			}
		    }
		}
		else if (eau == 1 && pp->p->eau != p->p->eau)
         	{
   		    if (check_obj(pp->p, x1, y1) == 1)
		    {
		        p->p->sur_plancher = pp->p;
		        eau = 0;
		    }
                    if (check_obj(pp->p, x2, y2) == 1)
	            {
	    	        p->p->sur_plancher = pp->p;
                        eau = 0;
		    }
                    if (check_obj(pp->p, x3, y3) == 1)
		    {
		        p->p->sur_plancher = pp->p;
                        eau = 0;
		    }
                    if (check_obj(pp->p, x4, y4) == 1)
		    {
		        p->p->sur_plancher = pp->p;
                        eau = 0;
		    }
		}
	    }
	}
	if (bord == 1 || eau == 1)
	{
            p->p->x = p->p->last_x;
	    p->p->y = p->p->last_y;
	    p->p->a_bouger = 1;
	}
    }
}

void coo_corner(struct personnages *perso, int *x1, int *y1, int *x2, int *y2, int *x3, int *y3, int *x4, int *y4)
{
    if (strcmp(perso->skin, "archer") == 0 || strcmp(perso->skin, "civil") == 0 || strcmp(perso->skin, "fantassin") == 0)
    {
	*x1 = 10 + perso->x;
        *y1 = perso->y;
        *x2 = -10 + perso->x;
        *y2 = perso->y;
        *x3 = 10 + perso->x;
        *y3 = 33 + perso->y;
        *x4 = -10 + perso->x;
        *y4 = 33 + perso->y;
    }
    else if (strcmp(perso->skin, "ship1") == 0)
    {
	*x1 = perso->x + 65 * cos(perso->angle / 57.3) + 135 * sin(perso->angle / 57.3);
	*y1 = perso->y + 65 * sin(perso->angle / 57.3) - 135 * cos(perso->angle / 57.3);
	*x2 = perso->x + 65 * cos(perso->angle / 57.3) - 370 * sin(perso->angle / 57.3);
        *y2 = perso->y + 65 * sin(perso->angle / 57.3) + 370 * cos(perso->angle / 57.3);
	*x3 = perso->x - 65 * cos(perso->angle / 57.3) - 370 * sin(perso->angle / 57.3);
	*y3 = perso->y - 65 * cos(perso->angle / 57.3) + 370 * cos(perso->angle / 57.3);
	*x4 = perso->x - 65 * cos(perso->angle / 57.3) + 135 * sin(perso->angle / 57.3);
	*y4 = perso->y - 65 * cos(perso->angle / 57.3) - 135 * sin(perso->angle / 57.3);
    }
    else if (strcmp(perso->skin, "arbre1") == 0)
    {
	*x1 = perso->x + 10;
        *x2 = perso->x - 10;
        *x3 = perso->x - 10;
        *x4 = perso->x + 10;
	*y1 = perso->y;
	*y2 = perso->y;
	*y3 = perso->y + 77;
	*y4 = perso->y + 77;
    }
    else if (strcmp(perso->skin, "fruit") == 0)
    {
	*x1 = perso->x - 10;
	*x2 = perso->x + 10;
	*x3 = perso->x - 10;
	*x4 = perso->x + 10;
	*y1 = perso->y - 10;
	*y2 = perso->y - 10;
	*y3 = perso->y + 10;
	*y4 = perso->y + 10;
    }
    else if (strcmp(perso->skin, "chateau") == 0)
    {
	*x1 = perso->x - 450;
        *x2 = perso->x + 450;
        *x3 = perso->x - 450;
        *x4 = perso->x + 450;
        *y1 = perso->y - 130;
        *y2 = perso->y - 130;
        *y3 = perso->y + 130;
        *y4 = perso->y + 130;
    }
}

char check_eau(int x1, int y1, char *array, char eau)
{
    x1 += 12.5;
    y1 += 12.5;
    int xx = (x1 - (x1  % 25)) / 25;
    int yy = (y1 - (y1  % 25)) / 25;
    if (array[yy * max_x + xx] < 3)
    {
       if (eau == '0')
            return 1;
    }
    else
    {
        if (eau == '1')
            return 1;
    }
    return 0;
}

char check_obj(struct personnages *perso, int xe, int ye)
{
    int x1;
    int x2;
    int x3;
    int x4;
    int y1;
    int y2;
    int y3;
    int y4;
    coo_corner(perso, &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4);
    int res = acos(((x1 - xe)*(x1 - xe) + (y1 - ye)*(y1-ye) + (x2 - xe)*(x2 - xe) + (y2 - ye)*(y2 - ye) - (y1 - y2)*(y1 - y2) - (x1 - x2) * (x1 - x2)) / (2 * sqrt((x1 - xe)*(x1 - xe) + (y1 - ye)*(y1-ye)) * sqrt ((x2 - xe)*(x2 - xe) + (y2 - ye)*(y2-ye)))) * 57.3;
    res += acos(((x2 - xe)*(x2 - xe) + (y2 - ye)*(y2-ye) + (x3 - xe)*(x3 - xe) + (y3 - ye)*(y3 - ye) - (y2 - y3)*(y2 - y3) - (x2 - x3) * (x2 - x3)) / (2 * sqrt((x2 - xe)*(x2 - xe) + (y2 - ye)*(y2-ye)) * sqrt ((x3 - xe)*(x3 - xe) + (y3 - ye)*(y3-ye)))) * 57.3;
    res += acos(((x3 - xe)*(x3 - xe) + (y3 - ye)*(y3-ye) + (x4 - xe)*(x4 - xe) + (y4 - ye)*(y4 - ye) - (y3 - y4)*(y3 - y4) - (x3 - x4) * (x3 - x4)) / (2 * sqrt((x3 - xe)*(x3 - xe) + (y3 - ye)*(y3-ye)) * sqrt ((x4 - xe)*(x4 - xe) + (y4 - ye)*(y4-ye)))) * 57.3;
    res += acos(((x4 - xe)*(x4 - xe) + (y4 - ye)*(y4-ye) + (x1 - xe)*(x1 - xe) + (y1 - ye)*(y1 - ye) - (y4 - y1)*(y4 - y1) - (x4 - x1) * (x4 - x1)) / (2 * sqrt((x4 - xe)*(x4 - xe) + (y4 - ye)*(y4-ye)) * sqrt ((x1 - xe)*(x1 - xe) + (y1 - ye)*(y1-ye)))) * 57.3;
    if (res > 320 && res < 400)
	return 1;
    return 0;
}
