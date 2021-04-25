#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#define size_order 2000

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
    char est_chef;
    char *e_list;
    char *i_list;
    char echange_player[50];
    int item1;
    int item2;
    char speak[90];
    int animation;
    int animation_r;
    struct personnages *next;
    /////////////
	char a_bouger;
};

void parse_new(struct personnages *list, char *line);
void parse_order(struct personnages *list, char *line);
struct personnages *append_perso(char *line, struct personnages *list);
struct personnages *init_map(void);
struct personnages *get_ptr_from_id(int id, struct personnages *list);
int get_id(char *line, int *i);
void append_enemi(char *name, struct personnages *p);
struct personnages *remove_perso(struct personnages *list);
