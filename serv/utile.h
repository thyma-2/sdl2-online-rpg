#pragma once

#include "perso.h"

int append(int *list, int to_add, int size);
int have_char(struct personnages *list, char *name);
int find_smalest_valid_id(struct personnages *list, int from);
