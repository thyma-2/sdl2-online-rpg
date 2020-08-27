#pragma once
#include "perso.h"
#include "net.h"
#include "collision.h"

void ia(struct linked_list *list);
void ia_man(struct linked_list *list, struct linked_list *parcour);
void ia_ship(struct linked_list *list, struct linked_list *parcour);
void ia_arbre(struct linked_list *list, struct linked_list *parcour);
void ia_fruit(struct linked_list *list, struct linked_list *parcour);
void append_enemi_list(struct linked_list *list, struct personnages *p);
