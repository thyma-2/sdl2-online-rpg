#pragma once
#include "perso.h"
#include "net.h"
#include "collision.h"

void ia(struct linked_list *list, char *ground, int max_x);
void ia_man(struct linked_list *list, struct linked_list *parcour);
void ia_ship(struct linked_list *list, struct linked_list *parcour);
void ia_arbre(struct linked_list *list, struct linked_list *parcour);
void ia_fruit(struct linked_list *list, struct linked_list *parcour, char *ground, int max_x);
void append_enemi_list(struct linked_list *list, struct personnages *p);
