#pragma once
#include "perso.h"
#include "init_sprite.h"

SDL_Texture *select_good_img(struct personnages *perso, struct personnages *moi);
SDL_Texture *select_texture(char ground);
SDL_Texture *select_lettre(char lettre);
char plat_ou_volumineux(char *skin);
