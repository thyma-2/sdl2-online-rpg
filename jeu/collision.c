#include "collision.h"

void collision(struct linked_list *list)
{
	for (struct linked_list *p = list; p != NULL; p = p->next)
	{
		p->p->sur_plancher = NULL;
		char bord = check_bord(p->p); // collision avec les bords de la map
		char eau = check_eau(p->p, p->p->eau); // collision avec l'eau
		for (struct linked_list *pp = list; pp != NULL; pp = pp->next)
		{
			if (pp != p)
			{
				if (check_obj_obj(pp->p, p->p) == 1)
				{
					if (pp->p->plancher == p->p->plancher)
					{
						if (strcmp(pp->p->skin, "fruit") == 0)
						{
							if (count_item(p->p->i_list) < 9)
								sprintf (ordre + strlen(ordre), "%d 00  0 %d 16 +1 fruit ", pp->p->id, p->p->id);
						}
						else
						{
							if (pp->p->last_x == pp->p->x && pp->p->last_y == pp->p->y) // je percute qqe chose
							{
								float x = p->p->x - p->p->last_x;
								float y = p->p->y - p->p->last_y;
								if (pp->p->vitesse_dep == 0)
								{
									sprintf(ordre + strlen(ordre), "%d 00 -1 %d 01 -%f %d 02 -%f ",pp->p->id, p->p->id, x, p->p->id, y);
								}
								else
								{
									sprintf (ordre + strlen(ordre), "%d 01 +%f %d 02 +%f %d 01 -%f %d 02 -%f ", pp->p->id, x * p->p->poid / pp->p->poid, pp->p->id, y * p->p->poid / pp->p->poid, p->p->id, x, p->p->id, y);
								}
							}
							else // on ce percute mutuellement 
							{
								float x = pp->p->x - pp->p->last_x;
								float y = pp->p->y - pp->p->last_y;
								float x2 = p->p->x - p->p->last_x;
								float y2 = p->p->y - p->p->last_y;
								sprintf (ordre + strlen(ordre), "%d 01 +%f %d 02 +%f %d 01 +%f %d 02 +%f ", p->p->id, x * pp->p->poid / p->p->poid, p->p->id, y * pp->p->poid / p->p->poid, pp->p->id, x2 * p->p->poid / pp->p->poid, pp->p->id, y2 * p->p->poid / pp->p->poid);
							}
						}
					}
					else if (pp->p->plancher > p->p->plancher)
					{
						p->p->sur_plancher = pp->p;
						eau = 0;
					}
				}
			}
		}
		if (bord == 1 || eau == 1)
		{
			float x = (p->p->x - p->p->last_x) * 2.2;
			float y = (p->p->y - p->p->last_y) * 2.2;
			sprintf (ordre + strlen(ordre), "%d 01 -%f %d 02 -%f ", p->p->id, x, p->p->id, y);
		}
	}
}

void coo_corner(struct personnages *perso, int *x1, int *y1, int *x2, int *y2, int *x3, int *y3, int *x4, int *y4)
{
	if (strcmp(perso->skin, "ship1") == 0)
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
}

char check_eau(struct personnages *perso, char eau)
{
	int x,y;
	if (cercle_ou_rectangle(perso) == 1)
	{
		int x1,x2,x3,x4,y1,y2,y3,y4;
		coo_corner(perso, &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4);
		x = (x1 + x2 + x3 + x4) / 4;
		y = (y1 + y2 + y3 + y4) / 4;
	}
	else
	{
		coo_circle(perso, &x, &y);
	}
	y = (y + 12.5) / 25;
	x = (x + 12.5) / 25;
	SDL_Texture *t = ground_texture[y * max_x + x];
	if (t == img->t->ea1 || t == img->t->ea2 || t == img->t->ea3)
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

char cercle_ou_rectangle(struct personnages *perso)
{
	if (strcmp(perso->skin, "ship1") == 0)
		return 1;//rectangle;
	return 0;//cercle
}

int coo_circle(struct personnages *perso, int *x, int *y)
{
	if (strcmp(perso->skin, "archer") == 0 || strcmp(perso->skin, "civil") == 0 || strcmp(perso->skin, "fantassin") == 0)
	{
		*x = perso->x - 8 * sin(perso->angle / 57.3);
		*y = perso->y + 8 * cos(perso->angle / 57.3);
		return 10;
	}
	else if (strcmp(perso->skin, "tour") == 0)
	{
		*x = perso->x - 75 * sin(perso->angle / 57.3);
		*y = perso->y + 75 * cos(perso->angle / 57.3);
		return 50;
	}
	else if (strcmp(perso->skin, "fruit") == 0)
	{
		*x = perso->x - 5 * sin(perso->angle / 57.3);
		*y = perso->y + 5 * cos(perso->angle / 57.3);
		return 6;
	}
	else if (strcmp(perso->skin, "arbre1") == 0)
	{
		*x = perso->x - 15 * sin(perso->angle / 57.3);
		*y = perso->y + 15 * cos(perso->angle / 57.3);
		return 10;
	}
	else if (strcmp(perso->skin, "flag_zone") == 0)
	{
		*x = perso->x - 29 * sin(perso->angle / 57.3);
		*y = perso->y + 29 * cos(perso->angle / 57.3);
		return 20;
	}
	return -1;
}

char check_bord(struct personnages *perso)
{
	int x = max_x * 25;
	int y = max_y * 25;
	if (cercle_ou_rectangle(perso) == 1)
	{
		int x1,x2,x3,x4,y1,y2,y3,y4;
		coo_corner(perso, &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4);
		if (x1 < -10 || x2 < -10 || x3 < -10 || x4 < -10 || y1 < -10 || y2 < -10 || y3 < -10 || y4 < -10 || x1 > x || x2 > x || x3 > x || x4 > x || y1 > y || y2 > y || y3 > y || y4 > y)
			return 1;
	}
	else
	{
		int x1,y1;
		int r = coo_circle(perso, &x1, &y1);
		if (x1 - r < -10 || x1 + r > x || y1 - r < -10 || y1 + r > y)
			return 1;
	}
	return 0;
}

char check_obj_point(struct personnages *perso, int xe, int ye)
{
	if (cercle_ou_rectangle(perso) == 1)
	{
		int x1,x2,x3,x4,y1,y2,y3,y4;
		coo_corner(perso, &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4);
		int res = acos(((x1 - xe)*(x1 - xe) + (y1 - ye)*(y1-ye) + (x2 - xe)*(x2 - xe) + (y2 - ye)*(y2 - ye) - (y1 - y2)*(y1 - y2) - (x1 - x2) * (x1 - x2)) / (2 * sqrt((x1 - xe)*(x1 - xe) + (y1 - ye)*(y1-ye)) * sqrt ((x2 - xe)*(x2 - xe) + (y2 - ye)*(y2-ye)))) * 57.3;
		res += acos(((x2 - xe)*(x2 - xe) + (y2 - ye)*(y2-ye) + (x3 - xe)*(x3 - xe) + (y3 - ye)*(y3 - ye) - (y2 - y3)*(y2 - y3) - (x2 - x3) * (x2 - x3)) / (2 * sqrt((x2 - xe)*(x2 - xe) + (y2 - ye)*(y2-ye)) * sqrt ((x3 - xe)*(x3 - xe) + (y3 - ye)*(y3-ye)))) * 57.3;
		res += acos(((x3 - xe)*(x3 - xe) + (y3 - ye)*(y3-ye) + (x4 - xe)*(x4 - xe) + (y4 - ye)*(y4 - ye) - (y3 - y4)*(y3 - y4) - (x3 - x4) * (x3 - x4)) / (2 * sqrt((x3 - xe)*(x3 - xe) + (y3 - ye)*(y3-ye)) * sqrt ((x4 - xe)*(x4 - xe) + (y4 - ye)*(y4-ye)))) * 57.3;
		res += acos(((x4 - xe)*(x4 - xe) + (y4 - ye)*(y4-ye) + (x1 - xe)*(x1 - xe) + (y1 - ye)*(y1 - ye) - (y4 - y1)*(y4 - y1) - (x4 - x1) * (x4 - x1)) / (2 * sqrt((x4 - xe)*(x4 - xe) + (y4 - ye)*(y4-ye)) * sqrt ((x1 - xe)*(x1 - xe) + (y1 - ye)*(y1-ye)))) * 57.3;
		if (res > 320 && res < 400)
			return 1;
	}
	else
	{
		int x1,y1;
		int r = coo_circle(perso, &x1, &y1);
		if ((x1 - xe) * (x1 - xe) + (y1 - ye) * (y1 - ye) < r * r)
			return 1;
	}
	return 0;
}

char check_obj_obj(struct personnages *perso, struct personnages *perso2)
{
	if (cercle_ou_rectangle(perso) == 1)
	{
		int x1,x2,x3,x4,y1,y2,y3,y4;
		coo_corner(perso, &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4);
		if (cercle_ou_rectangle(perso2) == 1)
		{
			if (check_obj_point(perso2, x1, y1) == 1 || check_obj_point(perso2, x3, y3) == 1 || check_obj_point(perso2, x2, y2) == 1 || check_obj_point(perso2, x4, y4) == 1)
				return 1;
		}
		else
		{
			int x, y;
			int r = coo_circle(perso2, &x, &y);
			float angle = acos((y - (y1 + y2 + y3 + y4)/4) / sqrt(pow(y - (y1 + y2 + y3 + y4)/4, 2) + pow(x - (x1 + x2 + x3 + x4)/4, 2)));
			if (x > (x1 + x2 + x3 + x4)/4)
				angle = 6.2832 - angle;
			int x5 = x + r * cos(angle);
			int y5 = y - r * sin(angle);
			if (check_obj_point(perso, x5, y5) == 1)
				return 1;
		}
	}
	else
	{
		int x,y;
		int r = coo_circle(perso, &x, &y);
		if (cercle_ou_rectangle(perso2) == 0)
		{
			int x2,y2;
			int r2 = coo_circle(perso2, &x2, &y2);
			if ((x - x2) * (x - x2) + (y - y2) * (y - y2) < (r + r2) * (r + r2))
				return 1;
		}
		else
		{
			int x1,x2,x3,x4,y1,y2,y3,y4;
			coo_corner(perso2, &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4);
			float angle = acos((y - (y1 + y2 + y3 + y4)/4) / sqrt(pow(y - (y1 + y2 + y3 + y4)/4, 2) + pow(x - (x1 + x2 + x3 + x4)/4, 2)));
			if (x > (x1 + x2 + x3 + x4)/4)
				angle = 6.2832 - angle;
			int x5 = x + r * sin(angle);
			int y5 = y - r * cos(angle);
			if (check_obj_point(perso2, x5, y5) == 1)
				return 1;

		}
	}
	return 0;
}
