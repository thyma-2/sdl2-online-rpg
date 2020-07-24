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
    char tout_le_reste[1940];
    struct personnages *next;
};

int parse_order(struct personnages *list, char *line);
struct personnages *append_perso(char **line, struct personnages *list);
struct personnages *init_map(void);
void send_map(int socket, struct personnages *list);
struct personnages *get_ptr_from_id(int id, struct personnages *list);
int get_id(char *line);
void send_order(int socket, struct personnages *list, int *movedObj);
void append_enemi(char *name, struct personnages *p);
struct personnages *remove_perso(struct personnages *list);
