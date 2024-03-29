#pragma once
#include "alloc.h"
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
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
#include "init_sound.h"
#include "btree.h"

void set_pos(SDL_Rect *pos, int x, int y);
void boucle_jeu(int socket, char *name);
char *log_menu(int socket);
int menu_connection();
int start_menu(int socket);
void free_malloc();
