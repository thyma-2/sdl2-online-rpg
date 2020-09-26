#pragma once

#include "perso.h"
#include "net.h"
#include "pathfinding.h"

void collision(struct linked_list *list, char *array);
void coo_corner(struct personnages *perso, int *x1, int *y1, int *x2, int *y2, int *x3, int *y3, int *x4, int *y4);
char check_eau(int x1, int y1, char *array, char eau);
char check_obj(struct personnages *perso, int xe, int ye);
