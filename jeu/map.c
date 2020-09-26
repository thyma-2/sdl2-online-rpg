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
    int i = 0;
    while (map[i] != '\n')
    {
        i += 1;
        if (i % 3 == 0)
           max_x += 25;
    }
    max_y = 25;
    while (map[i] != 0)
    {
        i += (max_x / 25) * 3 + 1;
        max_y += 25;
    }
    max_y -= 25;
    return map;
}

void display_ground(struct personnages *moi, char *ground, SDL_Window *ecran)
{
    SDL_Renderer* renderer = SDL_CreateRenderer(ecran, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    int gauche = moi->x - 600;
    int haut = moi->y - 350;
    int droite = moi->x + 600;
    int bas = moi->y + 350;

    SDL_Rect position;
    position.x = 0;
    position.y = 0;
    SDL_BlitSurface(img->t->fond, NULL, SDL_GetWindowSurface(ecran), &position);
    int x = 0;
    int y = 0;
    int i = 0;

    position.y = 350 - moi->y;
    while ((x < droite || y < bas) && i < max_x * max_y)
    {
	for (int j = 0; j < max_x; j++)
	{
	    if (y >= haut && x >= gauche && y <= bas && x <= droite)
	    {
		position.x = 600 + x - moi->x;
		SDL_BlitSurface(select_texture(ground[j + i]), NULL, SDL_GetWindowSurface(ecran), &position);
	    }
	    x += 25;
	}
	i += max_x;
	x = 0;
	y += 25;
	position.y += 25;
    }


}
