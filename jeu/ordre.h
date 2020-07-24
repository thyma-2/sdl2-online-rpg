#include "alloc.h"
#ifndef ORDRE
#define ORDRE
#include "clavier.h"
#include "perso.h"
#include "collision.h"

struct linked_list *select(struct linked_list *list, struct personnages *moi, struct linked_list *selected);
void commande(struct linked_list *selected, struct personnages *moi);
void gui_order(struct personnages *moi, SDL_Window *ecran);

#endif /*ORDRE*/

