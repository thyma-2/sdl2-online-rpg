#pragma once
#include "alloc.h"
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

extern struct personnages *list;

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
    char religion[50];
    char region[50];
    int nb_vassaux;
    struct linked_enemie *e_list;
    struct linked_item *i_list;
    char echange_player[50];
    int item1;
    int item2;
    char speak[90];
    int animation; // gestion frame
    int animation_2; // ce qu'il est en train de faire
    ///////////////////////////////////////
    char animation_time;
    int speak_timer;
    int faim_time; 
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
    struct path *chemin;
};

struct linked_list
{
    struct personnages *p;
    struct linked_list *next;
};

#include "net.h"
#include "diplo.h"
#include "init_sprite.h"
#include "stat.h"
#include "parseur.h"
#include "select_sprite.h"


char exist_in_linked(struct linked_list *list, struct personnages *to_test);
struct linked_list *append_in_linked(struct linked_list *list,struct personnages *p);
struct linked_list *recv_map(int socket, struct linked_list *list);
struct linked_list *append_perso(struct linked_list *list,  char **line);
void disp_perso_list(struct linked_list *list, struct personnages *moi);
//struct personnages *find_perso(struct linked_list *list ,char *name);
void buble_sort_perso(struct linked_list *list, struct personnages *moi);
void free_linked(struct linked_list *list, char free_content);
struct linked_list *death(struct linked_list *list);
struct linked_list *remove_from_linked_list(struct linked_list *list, struct personnages *to_rem);
struct personnages *find_perso_by_name(struct linked_list *list ,char *name);
struct linked_list *clean_selected(struct linked_list *list);
void fix_some_shit(struct linked_list *list);
