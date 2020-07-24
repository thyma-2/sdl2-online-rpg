#include "alloc.h"

#ifndef MAP
#define MAP
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>

#include <unistd.h>
#include <err.h>
#include "net.h"
#include "init_sprite.h"

char *rec_ground(int socket, int *x, int *y); 
void display_ground(struct personnages *moi, char *ground, SDL_Window *ecran);
char *ground(struct personnages *perso, char *ground);

#endif /*MAP*/

