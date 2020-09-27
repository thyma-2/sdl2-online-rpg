#include "pathfinding.h"
extern int max_x;
extern int max_y;

char *create_array(char *ground)
{
    max_x /= 25;
    max_y /= 25;
    int s = (max_x * 3 + 1) * max_y;
    char *array = malloc((max_x * max_y + 1));
    array[max_x * max_y] = 0;
    int i = 0;
    int j = 0;
    while (i < s)
    { 
	if (ground[i] == 'e')
	{
	    if (ground[i + 1] == 'a')
	    {
		if (ground[i + 2] == '1')
		    array[j] = 0;
		else if (ground[i + 2] == '2')
		    array[j] = 1;
		else if (ground[i + 2] == '3')
		    array[j] = 2;
	    }
	    i += 3;
	}
	else if (ground[i] == 't')
	{
	    if (ground[i + 1] == 'e')
	    {
		if (ground[i + 2] == '1')
		    array[j] = 3;
		else if (ground[i + 2] == '2')
		    array[j] = 4;
		else if (ground[i + 2] == '3')
		    array[j] = 5;
	    }
	    i += 3;
	}
	else if (ground[i] == 'h')
	{
	    if (ground[i + 1] == 'e')
	    {
		if (ground[i + 2] == '1')
		    array[j] = 6;
		else if (ground[i + 2] == '2')
		    array[j] = 7;
		else if (ground[i + 2] == '3')
		    array[j] = 8;
		else if (ground[i + 2] == '4')
		    array[j] = 9;
		else if (ground[i + 2] == '5')
		    array[j] = 10;
	    }
	    i += 3;
	}
	else if (ground[i] == 's')
	{
	    if (ground[i + 1] == 'a')
	    {
		if (ground[i + 2] == '1')
		    array[j] = 11;
		else if (ground[i + 2] == '2')
		    array[j] = 12;
		else if (ground[i + 2] == '3')
		    array[j] = 13;
	    }
	    i += 3;
	}
	else if (ground[i] == 'b')
	{
	    if (ground[i + 1] == 'l')
	    {
		if (ground[i + 2] == '1')
		    array[j] = 14;
		else if (ground[i + 2] == '2')
		    array[j] = 15;
		else if (ground[i + 2] == '3')
		    array[j] = 16;
	    }
	    i += 3;
	}
	else if (ground[i] == 'n')
	{
	    if (ground[i + 1] == 'e')
	    {
		if (ground[i + 2] == '1')
		    array[j] = 17;
		else if (ground[i + 2] == '2')
		    array[j] = 18;
		else if (ground[i + 2] == '3')
		    array[j] = 19;
	    }
	    i += 3;
	}
	else if (ground[i] == 'g')
	{
	    if (ground[i + 1] == 'r')
	    {
		if (ground[i + 2] == '1')
		    array[j] = 20;
		if (ground[i + 2] == '2')
		    array[j] = 21;
	    }
	    i += 3;
	}
	else if (ground[i] == '\n')
	{
	    i++;
	    j--;
	}
	j++;
    }
    return array;
}

void print_array(struct path *array)
{
    for (int i = 0; i < max_y; i++)
    {
	for (int j = 0; j < max_x; j++)
	    printf ("%d-", array[i * max_x + j].value);
        putchar('\n');
    }
    printf ("\n\n--------------------\n\n");
}

char *actualise_array(char *array, struct linked_list *list)
{
    int s = max_x * max_y + 1;
    char *array_cp = malloc(s);
    for (int i = 0; i < s; i++)
	array_cp[i] = array[i];
    for (struct linked_list *ll = list; ll != NULL; ll = ll->next)
    {
	if (strcmp(ll->p->skin, "arbre1") == 0)
	{
	    int xx = ((int)round(ll->p->x) - (int)round(ll->p->x) % 25) / 25;
	    int yy = ((int)round(ll->p->y) - (int)round(ll->p->y) % 25) / 25;
	    array_cp[yy * max_x + xx] = -3;
	}
    }
    return array_cp;
}

int findpath(struct personnages *p, char *array)
{
    if (p->y >= 25 * (max_y - 2))
	return 360;
    if (p->y <= 25)
	return 180;
    if (p->x <= 25)
	return 90;
    if (p->x >= 25 * (max_x - 1))
	return 270;

    int s = max_x * max_y;
    int x;
    int y;
    if (p->angle == 90)
    {
	x = ((int)round(p->x) - (int)round(p->x) % 25) / 25;
        y = ((int)round(p->y - 3) - (int)round(p->y - 3) % 25) / 25;
    }
    if (p->angle == 270)
    {
	x = ((int)round(p->x + 20) - (int)round(p->x + 20) % 25) / 25;
        y = ((int)round(p->y - 3) - (int)round(p->y - 3) % 25) / 25;
    }
    if (p->angle == 360)
    {
	x = ((int)round(p->x + 4) - (int)round(p->x + 4) % 25) / 25;
        y = ((int)round(p->y + 10) - (int)round(p->y + 10) % 25) / 25;
    }
    if (p->angle == 180)
    {
	x = ((int)round(p->x + 4) - (int)round(p->x + 4) % 25) / 25;
        y = ((int)round(p->y - 10) - (int)round(p->y - 10) % 25) / 25;
    }
    int src = (y + 1) * max_x + x;
    int srcs = src;
    x = ((int)round(p->ordrex) - (int)round(p->ordrex) % 25) / 25;
    y = ((int)round(p->ordrey) - (int)round(p->ordrey) % 25) / 25;
    int dest = y * max_x + x;
    if (src == dest)
    {
            p->x = p->ordrex;
            p->y = p->ordrey;
            return -1;
    }
    if (p->chemin == NULL)
    {
        p->chemin = malloc(sizeof(struct path) * s);
        for (int i = 0; i < s; i++)
        {
            p->chemin[i].type = array[i];
            p->chemin[i].already = 0;
            p->chemin[i].prev = -1;
            p->chemin[i].value = 0;
        }
        p->chemin[src].value = sqrt((p->x - p->ordrex) * (p->x - p->ordrex) + (p->y - p->ordrey) * (p->y - p->ordrey));
        p->chemin[src].already = 1;
	if (can_walk(p->chemin[dest].type, p) == 0)
            return -1;
        while (1 == 1)
        {
            generate_around(p->chemin, src, p);
            src = find_next(p->chemin);
  	    if (src == -1)
	        return -1;
 	    else if (src == dest)
	    {
	        while (srcs != p->chemin[src].prev)
	            src = p->chemin[src].prev;
	        if (srcs - max_x == src)
		    return 360;
	        if (srcs + 1 == src)
		    return 90;
	        if (srcs + max_x == src)
		    return 180;
	        if (srcs - 1 == src)
		    return 270;
 	    }
	    else
                p->chemin[src].already = 1;
        }
    }
    src = dest;
    while (srcs != p->chemin[src].prev)
    {
        src = p->chemin[src].prev;
	if (src == -1)
	    return 0;//try again
    }
    if (srcs - max_x == src)
        return 360;
    if (srcs + 1 == src)
        return 90;
    if (srcs + max_x == src)
        return 180;
    return 270;
}

int find_next(struct path *array)
{
    int min = 99999;
    int index = -1;
    int s = max_x * max_y;
    for (int i = 0; i < s; i++)
    {
	if (array[i].already == 0 && array[i].value < min && array[i].prev != -1)
	{
	    min = array[i].value;
	    index = i;
	}
    }
    return index;
}

int can_walk(char type, struct personnages *p)
{
    if (strcmp(p->skin, "archer") == 0 || strcmp(p->skin, "civil") == 0 || strcmp(p->skin, "fantassin") == 0)
        if (type > 2)
	    return 1;	
    return 0;
}

void generate_around(struct path *array, int src, struct personnages *p)
{
    int xsrc = (src % max_x);
    int ysrc = (int)floor(src / max_x);
    int x = xsrc * 25;
    int y = ysrc * 25;
    int a;
    
    if (xsrc < max_x - 1)
    {
	if (can_walk(array[src + 1].type, p) == 1)
	{
  	    a = sqrt((x + 25 - p->ordrex) * (x + 25 - p->ordrex) + (y - p->ordrey) * (y - p->ordrey)) + sqrt((x + 25 - p->x) * (x + 25 - p->x) + (y - p->y) * (y - p->y));
 	    if (a < array[src + 1].value || array[src + 1].already == 0)
	    {
	        array[src + 1].value = a;
  	        array[src + 1].already = 0;
		array[src + 1].prev = src;
  	    }
	}
    }
    if (xsrc > 0)
    {
	if (can_walk(array[src - 1].type, p) == 1)
	{
	    a = sqrt((x - 25 - p->ordrex) * (x - 25 - p->ordrex) + (y - p->ordrey) * (y - p->ordrey)) + sqrt((x - 25 - p->x) * (x - 25 - p->x) + (y - p->y) * (y - p->y));
	    if (a < array[src - 1].value  || array[src - 1].already == 0)
	    {
	        array[src - 1].value = a;
	        array[src - 1].already = 0;
		array[src - 1].prev = src;
	    }
	}
    }
    if (ysrc > 0 && can_walk(array[src - max_x].type, p) == 1)
    {
	a = sqrt((x - p->ordrex) * (x - p->ordrex) + (y - 25 - p->ordrey) * (y - 25 - p->ordrey)) + sqrt((x - p->x) * (x - p->x) + (y - 25 - p->y) * (y - 25 - p->y));
	if (a < array[src - max_x].value || array[src - max_x].already == 0)
	{
	    array[src - max_x].value = a;
	    array[src - max_x].already = 0;
	    array[src - max_x].prev = src;
	}
    }
    if (ysrc < max_y - 1 && can_walk(array[src + max_x].type, p) == 1)
    {
	a = sqrt((x - p->ordrex) * (x - p->ordrex) + (y + 25 - p->ordrey) * (y + 25 - p->ordrey)) + sqrt((x - p->x) * (x - p->x) + (y + 25 - p->y) * (y + 25 - p->y));
	if (a < array[src + max_x].value || array[src + max_x].already == 0)
	{
	    array[src + max_x].value = a;
	    array[src + max_x].already = 0;
	    array[src + max_x].prev = src;
	}
    }
}
