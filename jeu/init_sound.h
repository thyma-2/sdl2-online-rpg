#pragma once
#include "main.h"

struct sound
{
    Mix_Music *menu;
};

struct sound *init_sound(void);
