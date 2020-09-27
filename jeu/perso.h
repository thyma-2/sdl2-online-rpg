#include "alloc.h"
#ifndef PERSO
#define PERSO
#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include  <string.h>
#include <SDL2/SDL.h>
#include <math.h>
#include "sys/types.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "arpa/inet.h"
#define order_size 2000

struct personnages
{
    int id;
    int pv;
    char nom_de_compte[50];
    float x;
    float y;
    float ordrex;
    float ordrey;
    int angle;
    int timer_dom;
    int faim;
    char skin[50];
    char nom[50];
    char nom_superieur[50];
    char titre[50];
    char region[50];
    char est_chef;
    struct linked_enemie *e_list;
    struct linked_item *i_list;
    char echange_player[50];
    int item1;
    int item2;
    char speak[90];
    int animation;
    int animation_r;
    ///////////////////////////////////////
    int speak_timer;
    struct personnages *sur_plancher;
    int max_pv;
    int vitesse_dom;
    int vitesse_dep;
    int porte_dom;
    int dom;
    int poid;
    float last_x;
    float last_y;
    char eau; //O si terrestre 1 si aquatique 2 si les deux
    char plancher;
    char a_bouger;
    struct path *chemin;
};

struct linked_list
{
    struct personnages *p;
    struct linked_list *next;
};

#include "diplo.h"
#include "init_sprite.h"
#include "stat.h"
#include "parseur.h"
#include "select_sprite.h"

char exist_in_linked(struct linked_list *list, struct personnages *to_test);
struct linked_list *append_in_linked(struct linked_list *list,struct personnages *p);
struct linked_list *recv_map(int socket, struct linked_list *list);
struct linked_list *append_perso(struct linked_list *list,  char **line);
void disp_perso_list(struct linked_list *list, struct personnages *moi ,SDL_Window *ecran);
void *find_perso(struct linked_list *list ,char *name);
void buble_sort_perso(struct linked_list *list);
void free_linked(struct linked_list *list, char free_content);
struct linked_list *death(struct linked_list *list);
struct linked_list *remove_from_linked_list(struct linked_list *list, struct personnages *to_rem);
void *find_perso_by_name(struct linked_list *list ,char *name);
struct linked_list *clean_selected(struct linked_list *list);
#endif /*PERSO*/
