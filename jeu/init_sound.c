#include "init_sound.h"

struct sound *init_sound(void)
{
    struct sound *ret = malloc(sizeof(struct sound));
    ret->menu = Mix_LoadMUS("sons/musiques/menu.mp3");
    return ret;
}
