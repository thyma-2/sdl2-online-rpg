#pragma once

#include "perso.h"
#include "net.h"

void collision(struct linked_list *list, char *ground, int max_x, int max_y);
void coo_corner(struct personnages *perso, int *x1, int *y1, int *x2, int *y2, int *x3, int *y3, int *x4, int *y4);
char check_eau(int x1, int y1, char *ground, int max_x, char eau);
char check_obj(struct personnages *perso, int xe, int ye);
