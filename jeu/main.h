#include "alloc.h"

#ifndef MAIN
#define MAIN
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <err.h>
#include "clavier.h"
#include "gui.h"
#include "net.h"
#include "perso.h"
#include "control.h"
#include "collision.h"
#include "ordre.h"
#include "ia.h"
#include "map.h"
#include <fcntl.h>
#include "init_sprite.h"
#include "chiffrement.h"
#include "pathfinding.h"

void set_pos(SDL_Rect *pos, int x, int y);
void boucle_jeu(int socket, SDL_Window *ecran, struct linked_list *list, char *name);
char *log_menu(int socket, SDL_Window *ecran);
int menu_connection(SDL_Window *ecran);
int start_menu(int socket, SDL_Window *ecran);
void free_malloc();
#endif /*MAIN*/
