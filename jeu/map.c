#include "map.h"

SDL_Texture **ground_texture;
int *ground_altitude;

char *rec_ground(int socket)
{
	char *map = ecalloc(sizeof(char), 9);
	recv(socket, map, 8, 0);
	int nb_char = atoi(map);
	free(map);
	map = calloc(nb_char + 1, sizeof(char));
	int a = 0;
	while (a < nb_char)
		a += recv(socket, map +strlen(map), nb_char, 0);
	map[nb_char] = 0;
	return map;
}

void display_ground(struct personnages *moi)
{
	SDL_Rect position;
	for (int y = 0; y < max_y; y++)
	{
		for (int x = 0; x < max_x; x++)
		{
			float newx1 = 25*((x+0.5-moi->x) * cos(moi->angle/57.3) - (y+0.5-moi->y) * sin(moi->angle/57.3))+600;
			float newy1 = 25*((x+0.5-moi->x) * sin(moi->angle/57.3) + (y+0.5-moi->y) * cos(moi->angle/57.3))+100;
			float newx2 = 25*((x+0.5-moi->x) * cos(moi->angle/57.3) - (y-0.5-moi->y) * sin(moi->angle/57.3))+600;
			float newy2 = 25*((x+0.5-moi->x) * sin(moi->angle/57.3) + (y-0.5-moi->y) * cos(moi->angle/57.3))+100;
			
			float newx3 = 25*((x-0.5-moi->x) * cos(moi->angle/57.3) - (y-0.5-moi->y) * sin(moi->angle/57.3))+600;
			float newy3 = 25*((x-0.5-moi->x) * sin(moi->angle/57.3) + (y-0.5-moi->y) * cos(moi->angle/57.3))+100;
			
			float newx4 = 25*((x-0.5-moi->x) * cos(moi->angle/57.3) - (y+0.5-moi->y) * sin(moi->angle/57.3))+600;
			float newy4 = 25*((x-0.5-moi->x) * sin(moi->angle/57.3) + (y+0.5-moi->y) * cos(moi->angle/57.3))+100;
			
			SDL_Vertex vertex_1 = {{newx1, newy1},{newx2, newy2},{newx3, newy3},{newx4, newy4}};
	
//			if (position.x > -24 && position.x < 1224 && position.y > -24 && position.y < 575)
//			{
				SDL_QueryTexture(ground_texture[j + i], NULL, NULL, &position.w, &position.h);
				SDL_RenderCopyEx(renderer, ground_texture[j + i], NULL, &position,-moi->angle, NULL, 0);
				SDL_Vertex vertex_1 = {};
				SDL_RenderGeometry(renderer, ground_texture[j + i], vertices, 4, NULL, 0);
//			}
		}
	}
}
