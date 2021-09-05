#pragma once
#include "alloc.h"
#include "perso.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

char *create_array(char *ground);


struct path
{
    int value;
    char type;
    char already;
    int prev;
};

int can_walk(char type, struct personnages *p);
char *actualise_array(char *array, struct linked_list *list);
int find_next(struct path *array);
void generate_around(struct path *array, int src, struct personnages *p);
int findpath(struct personnages *p, char *array);

extern int max_x;
extern int max_y;
