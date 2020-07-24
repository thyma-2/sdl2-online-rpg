#include "map.h"

char *rec_ground(int socket, int *x, int *y)
{
    char b[] = "get_ground";
    char *map;
    if (access( "ground.txt", F_OK ) != -1 )
    {
        FILE *f = fopen("ground.txt", "rb");
        fseek(f, 0, SEEK_END);
        size_t fsize = ftell(f);
        fseek(f, 0, SEEK_SET);  /* same as rewind(f); */
        map = malloc(fsize + 1);
        fread(map, 1, fsize, f);
        fclose(f);
        map[fsize] = 0;
    }
    else
    {
        send(socket, b,10,0);
        map = ecalloc(sizeof(char), 9);
        recv(socket, map, 8, 0);
        int nb_char = atoi(map);
        free(map);
        map = emalloc(nb_char);
        recv(socket, map, nb_char, 0);
        FILE *fp = fopen("ground.txt", "w");
        fwrite( map, nb_char, 1, fp );
        fclose(fp);
    }
    int i = 0;
    while (map[i] != '\n')
    {
        i += 1;
        if (i % 3 == 0)
           *x += 25;
    }
    *y = 25;
    while (map[i] != 0)
    {
        i += (*x / 25) * 3 + 1;
        *y += 25;
    }
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

    position.y =  350 + y - moi->y;
    while ((x < droite || y < bas) && ground[i] != 0)
    {
        if (ground[i] == '\n')
        {
            i += 1;
            y += 25;
            position.y = 350 + y - moi->y;
            x = 0;
        }
        else
        {
            if (y >= haut && x >= gauche && y <= bas && x <= droite)
            {
                position.x = 600 + x - moi->x;
                SDL_BlitSurface(select_texture(&ground[i]), NULL,
                        SDL_GetWindowSurface(ecran), &position);
            }
            i += 3;
            x += 25;
        }
    }
}

char *ground(struct personnages *perso, char *ground)
{
    int x = 0;
    int y = 0;
    int i = 0;
    while (ground[i] != 0)
    {
	if (ground[i] == '\n')
	{
	    y += 25;
	    x = 0;
	    i++;
	}
	else
	{
	    if (x >= perso->x && y >= perso->y)
		return &ground[i];
	    x += 25;
	    i += 3;
	}
    }
    return NULL;
}
