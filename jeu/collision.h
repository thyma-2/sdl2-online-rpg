#pragma once

#include "perso.h"
#include "net.h"
#include "pathfinding.h"

void collision(struct linked_list *list, char *array);
void coo_corner(struct personnages *perso, int *x1, int *y1, int *x2, int *y2, int *x3, int *y3, int *x4, int *y4);
char check_eau(struct personnages *perso, char *array, char eau);
char check_obj_point(struct personnages *perso, int xe, int ye);
char check_obj_obj(struct personnages *perso, struct personnages *perso2);
char check_bord(struct personnages *perso);
char cercle_ou_rectangle(struct personnages *perso);
int coo_circle(struct personnages *perso, int *x, int *y);
