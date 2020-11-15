#include "map.h"

char *rec_ground(int socket)
{
    char *map = ecalloc(sizeof(char), 9);
    recv(socket, map, 8, 0);
    int nb_char = atoi(map);
    free(map);
    map = emalloc(nb_char + 1);
    recv(socket, map, nb_char, 0);
    map[nb_char] = 0;
    max_x = 0;
    int i = 0;
    while (map[i] != '\n')
    {
        i += 1;
        if (i % 3 == 0)
           max_x += 25;
    }
    max_y = 25 * nb_char / i;
    return map;
}

void display_ground(struct personnages *moi, char *ground, SDL_Window *ecran)
{
    SDL_Renderer* renderer = SDL_CreateRenderer(ecran, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    SDL_Rect position;
    position.x = 0;
    position.y = 0;
    SDL_BlitSurface(img->t->fond, NULL, SDL_GetWindowSurface(ecran), &position);
    int x = 0;
    int y = 0;
    int i = 0;
    int s = max_x * max_y;
    while (i < s)
    {
	for (int j = 0; j < max_x; j++)
	{
	    position.x = (x - moi->x) * cos(moi->angle / 57.3) + (y - moi->y) * sin(moi->angle / 57.3) + 600;
	    position.y = (y - moi->y) * cos(moi->angle / 57.3) - (x - moi->x) * sin(moi->angle / 57.3) + 550;
	    SDL_BlitSurface(select_texture(ground[j + i]), NULL, SDL_GetWindowSurface(ecran), &position);
	    x += 25;
	}
	i += max_x;
	x = 0;
	y += 25;
    }
}
