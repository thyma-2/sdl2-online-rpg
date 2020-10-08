#include "alloc.h"
#ifndef GUI
#define GUI

#include <SDL2/SDL.h>
#include "perso.h"
#include "btree.h"
#include "clavier.h"
#include "ia.h"
#include "init_sprite.h"
#include "stat.h"
#include "ordre.h"
#include "inventaire.h"
#include "init_sound.h"

struct speak
{
    char on;
    char speak[90];
};

struct menu
{
    char on;
    char diplo_on;
    char inventaire_on;
    char action_on;
    char echange_on;
    char capacite_on;
    char technologies_on;
    char economie_on;
    char religion_on;
    char add_enemi[50];
    char rem_enemi[50];
    char sel_diplo;
    char sel_inventaire;
    char sel_action;
    int sel_echange1;
    int sel_echange2;
    char tab_echange;
    int yarbre;
    struct node *t_tree;
    struct node *r_tree;
    struct personnages *echange;
};

void talk(SDL_Window *ecran, struct speak *speak_s, struct personnages *moi);
void gui_event(struct personnages *perso, SDL_Window *ecran, struct linked_list *list);
void *cast(void *p);
void display_selected(struct linked_list *selected, SDL_Window *ecran, struct personnages *moi, struct formation *f);
int blit_text(SDL_Rect position, char *text, SDL_Window *ecran, int limite, int couleur);
void blit_mdp(SDL_Rect position, char *text, SDL_Window *ecran, int limite, int couleur);
void menu(SDL_Window *ecran, struct menu *m, struct personnages *perso, struct linked_list *list);
#endif /*GUI*/
