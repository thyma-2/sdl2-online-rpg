#include "collision.h"

void collision(struct linked_list *list, char *ground, int max_x, int max_y)
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
	char eau = check_eau(x1, y1, ground, max_x, p->p->eau); // collision avec l'eau
	if (eau == 0)
	    eau = check_eau(x2, y2, ground, max_x, p->p->eau);
	if (x1 < 0 || x1 > max_x || x2 < 0 || x2 > max_x || y1 < 0 || y1 > max_y || y2 < 0 || y2 > max_y)
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
    if (strcmp(perso->skin, "archer") == 0 || strcmp(perso->skin, "civil") == 0)
    {
	*x1 = perso->x + 8;
	*x2 = perso->x + 16;
	*x3 = perso->x + 8;
	*x4 = perso->x + 16;
	*y1 = perso->y + 24;
	*y2 = perso->y + 24;
	*y3 = perso->y + 33;
	*y4 = perso->y + 33;
    }
    else if (strcmp(perso->skin, "ship1") == 0)
    {
	if (perso->angle < 23 || perso->angle > 337)
	{
	    *x1 = perso->x + 340;
	    *x2 = perso->x + 455;
	    *x3 = perso->x + 455;
	    *x4 = perso->x + 340;
	    *y1 = perso->y + 260;
	    *y2 = perso->y + 260;
	    *y3 = perso->y + 755;
	    *y4 = perso->y + 755;
	}
	else if (perso->angle < 69  &&  perso->angle >= 23)
	{
	    *x1 = perso->x + 450;
	    *x2 = perso->x + 535;
	    *x3 = perso->x + 190;
	    *x4 = perso->x + 115;
	    *y1 = perso->y + 265;
	    *y2 = perso->y + 340;
	    *y3 = perso->y + 680;
	    *y4 = perso->y + 610;
	}
	else if (perso->angle >= 69  &&  perso->angle < 114)
	{
	    *x1 = perso->x + 540; // droite 
            *x2 = perso->x + 540;
            *x3 = perso->x + 50;
            *x4 = perso->x + 50;
            *y1 = perso->y + 350;
            *y2 = perso->y + 450;
            *y3 = perso->y + 450;
            *y4 = perso->y + 350;
	}
	else if (perso->angle < 159  && perso->angle >= 114)
	{
	    *x4 = perso->x + 190;
	    *x3 = perso->x + 120;
	    *x2 = perso->x + 460;
	    *x1 = perso->x + 536;
	    *y4 = perso->y + 120;
	    *y3 = perso->y + 190;
	    *y2 = perso->y + 535;
	    *y1 = perso->y + 460;
	}
        else if (perso->angle >= 159  &&  perso->angle < 204)
	{
	    *x1 = perso->x + 345;
            *x2 = perso->x + 455;
            *x3 = perso->x + 445;
            *x4 = perso->x + 345;
            *y1 = perso->y + 535;
            *y2 = perso->y + 535;
            *y3 = perso->y + 50;
            *y4 = perso->y + 50;
	}
        else if (perso->angle < 249  &&  perso->angle >= 204)
	{
	    *x4 = perso->x + 605;
	    *y4 = perso->y + 110;
	    *x3 = perso->x + 685;
	    *y3 = perso->y + 190;
	    *x2 = perso->x + 340;
	    *y2 = perso->y + 535;
	    *x1 = perso->x + 265;
	    *y1 = perso->y + 460;
	}
        else if (perso->angle >= 249  && perso-> angle < 294)
	{
	    *x1 = perso->x + 260;
            *x2 = perso->x + 260;
            *x3 = perso->x + 765;
            *x4 = perso->x + 765;
            *y1 = perso->y + 350;
            *y2 = perso->y + 450;
            *y3 = perso->y + 450;
            *y4 = perso->y + 350;
	}
        else
	{
	    *x1 = perso->x + 340;
	    *y1 = perso->y + 265;
	    *x2 = perso->x + 265;
	    *y2 = perso->y + 340;
	    *x3 = perso->x + 605;
	    *y3 = perso->y + 680;
	    *x4 = perso->x + 680; //
	    *y4 = perso->y + 605;
	}
    }
}

char check_eau(int x1, int y1, char *ground, int max_x, char eau)
{
    int i = 0;
    int index = 0;
    while (y1 > 0)
    {
	i++;
	y1 -= 1;
	if (i % 25 == 0)
	    index += max_x / 25 * 3 + 1;
    }
    i = 0;
    while (x1 > 0)
    {
	i++;
	x1 -= 1;
	if (i % 25 == 0)
	    index += 3;
    }
    if (ground[index] == 'e' && ground[index + 1] == 'a')
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
    if (res > 320)
	if (res < 400)
	    return 1;
    return 0;
}
