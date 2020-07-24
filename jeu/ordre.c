#include "ordre.h"

struct linked_list *select(struct linked_list *list, struct personnages *moi, struct linked_list *selected)
{
    if (lettres->Mouse_Lclick == 1)
    {
        for (struct linked_list *a = list; a != NULL; a = a->next)
        {
	    int xe = lettres->Mouse_pos_x - 600 + moi->x;
            int ye = lettres->Mouse_pos_y - 350 + moi->y;
            if (check_obj(a->p, xe, ye) == 1)
                selected = append_in_linked(selected, a->p);
        }
    }
    return selected;
}

void commande(struct linked_list *selected, struct personnages *moi)
{
    if (lettres->Mouse_Rclick == 1)
    {
        for (struct linked_list *a = selected; a != NULL; a = a->next)
        {
            if (strcmp(a->p->nom_superieur, moi->nom) == 0)
            {
                a->p->ordrex = lettres->Mouse_pos_x - 600 + moi->x;
                a->p->ordrey = lettres->Mouse_pos_y - 350 + moi->y;
            }
        }
        lettres->Mouse_Rclick = 0;
    }
}

void gui_order(struct personnages *moi, SDL_Window *ecran)
{
    if (moi->ordrex != -1)
    {
        SDL_Rect position;
        position.x = moi->ordrex + 550 - moi->x;
        position.y = moi->ordrey + 300 - moi->y;
        if (moi->x > moi->ordrex + - 50 && moi->x < moi->ordrex + 50 && moi->y > moi->ordrey - 50 && moi->y < moi->ordrey + 50)
            moi->ordrex = -1;
        SDL_Surface *croix = SDL_LoadBMP("img/gui/croix.bmp");
        SDL_SetColorKey(croix, SDL_SCANCODE_Y, SDL_MapRGB(croix->format, 255, 255, 255));
        SDL_BlitSurface(croix, NULL, SDL_GetWindowSurface(ecran), &position);
    }
}
