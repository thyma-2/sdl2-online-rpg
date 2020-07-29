#include "select_sprite.h"

SDL_Surface *select_good_img(struct personnages *moi, int i)
{
    int angle = moi->angle;
    if (strcmp(moi->skin, "archer") == 0)
    {
        if (i == 0)
        {
            if (angle < 23 || angle > 337)
                return img->s->hoArDoMa1;
            else if (angle < 69  &&  angle >= 23)
                return img->s->hoArDdMa1;
            else if (angle >= 69  &&  angle < 114)
                return img->s->hoArDrMa1;
            else if (angle < 159  &&  angle >= 114)
                return img->s->hoArDfMa1;
            else if (angle >= 159  &&  angle < 204)
                return img->s->hoArFaMa1;
            else if (angle < 249  &&  angle >= 204)
                return img->s->hoArGfMa1;
            else if (angle >= 249  &&  angle < 294)
                return img->s->hoArGaMa1;
            return img->s->hoArGdMa1;
        }
        else if (i == 1)
        {
            if (angle < 23 || angle > 337)
                return img->s->hoArDoMa2;
            else if (angle < 69  &&  angle >= 23)
                return img->s->hoArDdMa2;
            else if (angle >= 69  &&  angle < 114)
                return img->s->hoArDrMa2;
	    else if (angle >= 69  &&  angle < 114)
                return img->s->hoArDrMa2;
            else if (angle < 159  &&  angle >= 114)
                return img->s->hoArDfMa2;
            else if (angle >= 159  &&  angle < 204)
                return img->s->hoArFaMa2;
            else if (angle < 249  &&  angle >= 204)
                return img->s->hoArGfMa2;
            else if (angle >= 249  &&  angle < 294)
                return img->s->hoArGaMa2;
            return img->s->hoArGdMa2;
        }
        else if (i == 2)
        {
            if (angle < 23 || angle > 337)
                return img->s->hoArDoMa3;
            else if (angle < 69  &&  angle >= 23)
                return img->s->hoArDdMa3;
            else if (angle >= 69  &&  angle < 114)
                return img->s->hoArDrMa3;
            else if (angle < 159  &&  angle >= 114)
                return img->s->hoArDfMa3;
            else if (angle >= 159  &&  angle < 204)
                return img->s->hoArFaMa3;
            else if (angle < 249  &&  angle >= 204)
                return img->s->hoArGfMa3;
            else if (angle >= 249  &&  angle < 294)
                return img->s->hoArGaMa3;
            return img->s->hoArGdMa3;
        }
        else if (i == 3)
	{
	    if (angle < 23 || angle > 337)
                return img->s->hoArDoMa4;
            else if (angle < 69  &&  angle >= 23)
                return img->s->hoArDdMa4;
            else if (angle >= 69  &&  angle < 114)
                return img->s->hoArDrMa4;
            else if (angle < 159  &&  angle >= 114)
                return img->s->hoArDfMa4;
            else if (angle >= 159  &&  angle < 204)
                return img->s->hoArFaMa4;
            else if (angle < 249  &&  angle >= 204)
                return img->s->hoArGfMa4;
            else if (angle >= 249  &&  angle < 294)
                return img->s->hoArGaMa4;
            return img->s->hoArGdMa4;
        }
        else if (i == 4)
        {
            if (angle < 23 || angle > 337)
                return img->s->hoArDoMa5;
            else if (angle < 69  &&  angle >= 23)
                return img->s->hoArDdMa5;
            else if (angle >= 69  &&  angle < 114)
                return img->s->hoArDrMa5;
            else if (angle < 159  &&  angle >= 114)
                return img->s->hoArDfMa5;
            else if (angle >= 159  &&  angle < 204)
                return img->s->hoArFaMa5;
            else if (angle < 249  &&  angle >= 204)
                return img->s->hoArGfMa5;
	    else if (angle >= 249  &&  angle < 294)
                return img->s->hoArGaMa5;
            return img->s->hoArGdMa5;
        }
    }
    if (strcmp(moi->skin, "ship1") == 0)
    {
        if (angle < 23 || angle > 337)
            return img->s->ship1haut;
        else if (angle < 69  &&  angle >= 23)
            return img->s->ship1droitehaut;
        else if (angle >= 69  &&  angle < 114)
            return img->s->ship1droite;
        else if (angle < 159  &&  angle >= 114)
            return img->s->ship1droitebas;
        else if (angle >= 159  &&  angle < 204)
            return img->s->ship1bas;
        else if (angle < 249  &&  angle >= 204)
            return img->s->ship1gauchebas;
        else if (angle >= 249  &&  angle < 294)
            return img->s->ship1gauche;
        return img->s->ship1gauchehaut;
    }
    return img->s->hoArGdMa5;
}

SDL_Surface *select_texture(char *ground)
{
    if (ground[0] == 'h')
    {
        if (ground[1] == 'e')
        {
            if (ground[2] == '1')
                return img->t->he1;
            else if (ground[2] == '2')
                return img->t->he2;
            else if (ground[3] == '3')
                return img->t->he3;
            else if (ground[4] == '4')
                return img->t->he4;
            return img->t->he5;
        }
    }
    else if (ground[0] == 's')
    {
        if (ground[1] == 'a')
        {
            if (ground[2] == '1')
                return img->t->sa1;
            if (ground[2] == '2')
                return img->t->sa2;
            return img->t->sa3;
        }
    }
    else if (ground[0] == 'e')
    {
        if (ground[1] == 'a')
        {
            if (ground[2] == '1')
                return img->t->ea1;
            else if (ground[2] == '2')
                return img->t->ea2;
            return img->t->ea3;
        }
    }
    else if (ground[0] == 't')
    {
        if (ground[1] == 'e')
        {
            if (ground[2] == '1')
                return img->t->te1;
            else if (ground[2] == '2')
                return img->t->te2;
            return img->t->te3;
        }
    }
    else if (ground[0] == 'b')
    {
        if (ground[1] == 'l')
        {
		if (ground[2] == '1')
                return img->t->bl1;
            else if (ground[2] == '2')
                return img->t->bl2;
            return img->t->bl3;
        }
    }
    else if (ground[0] == 'n')
    {
        if (ground[1] == 'e')
        {
            if (ground[2] == '1')
                return img->t->ne1;
            else if (ground[2] == '2')
                return img->t->ne2;
            return img->t->ne3;
        }
    }
    else if (ground[0] == 'g')
    {
        if (ground[1] == 'r')
        {
            if (ground[2] == '1')
                return img->t->gr1;
            return img->t->gr2;
        }
    }
    return NULL;
}

SDL_Surface *select_lettre(char lettre)
{
    if (lettre < 64)
    {
	if (lettre < 32)
	{
	    if (lettre < 16)
	    {
		return NULL;
	    }
	    else
	    {
		return NULL;
	    }
	}
	else
	{
	    if (lettre < 48)
	    {
	        if (lettre == 45)
		    return img->li->tirret;
		if (lettre == 46)
		    return img->li->point;
		if (lettre == 47)
		    return img->li->slash;
	    }
	    else
	    {
		if (lettre == 48)
		    return img->li->k0;
		if (lettre == 49)
                    return img->li->k1;
		if (lettre == 50)
                    return img->li->k2;
		if (lettre == 51)
                    return img->li->k3;
		if (lettre == 52)
                    return img->li->k4;
		if (lettre == 53)
                    return img->li->k5;
		if (lettre == 54)
                    return img->li->k6;
		if (lettre == 55)
                    return img->li->k7;
		if (lettre == 56)
                    return img->li->k8;
		if (lettre == 57)
                    return img->li->k9;
		if (lettre == 62)
		    return img->li->sup;
	    }
	}
    }
    else
    {
        if (lettre < 96)
	{
	    if (lettre < 80)
	    {
		if (lettre == 65)
		    return img->li->A;
		if (lettre == 66)
		    return img->li->B;
		if (lettre == 67)
		    return img->li->C;
		if (lettre == 68)
		    return img->li->D;
		if (lettre == 69)
		    return img->li->E;
		if (lettre == 70)
		    return img->li->F;
		if (lettre == 71)
		    return img->li->G;
		if (lettre == 72)
		    return img->li->H;
		if (lettre == 73)
		    return img->li->I;
		if (lettre == 74)
                    return img->li->J;
		if (lettre == 75)
                    return img->li->K;
		if (lettre == 76)
                    return img->li->L;
		if (lettre == 77)
                    return img->li->M;
		if (lettre == 78)
                    return img->li->N;
                return img->li->O;
	    }
	    else
	    {
		if (lettre == 80)
                    return img->li->P;
		if (lettre == 81)
                    return img->li->Q;
		if (lettre == 82)
                    return img->li->R;
		if (lettre == 83)
                    return img->li->S;
		if (lettre == 84)
                    return img->li->T;
		if (lettre == 85)
                    return img->li->U;
		if (lettre == 86)
                    return img->li->V;
		if (lettre == 87)
                    return img->li->W;
		if (lettre == 88)
                    return img->li->X;
		if (lettre == 89)
                    return img->li->Y;
		if (lettre == 90)
                    return img->li->Z;
		if (lettre == 95)
		    return img->li->tirret_bas;
	    }
	}
	else
	{
	    if (lettre < 112)
	    {
		if (lettre == 97)
		    return img->li->a;
		if (lettre == 98)
                    return img->li->b;
		if (lettre == 99)
                    return img->li->c;
		if (lettre == 100)
                    return img->li->d;
		if (lettre == 101)
                    return img->li->e;
		if (lettre == 102)
                    return img->li->f;
		if (lettre == 103)
                    return img->li->g;
		if (lettre == 104)
                    return img->li->h;
		if (lettre == 105)
                    return img->li->i;
		if (lettre == 106)
                    return img->li->j;
		if (lettre == 107)
                    return img->li->k;
		if (lettre == 108)
                    return img->li->l;
		if (lettre == 109)
                    return img->li->m;
		if (lettre == 110)
                    return img->li->n;
                return img->li->o;
	    }
	    else
	    {
		if (lettre == 112)
		    return img->li->p;
		if (lettre == 113)
		    return img->li->q;
		if (lettre == 114)
                    return img->li->r;
		if (lettre == 115)
                    return img->li->s;
		if (lettre == 116)
                    return img->li->t;
		if (lettre == 117)
                    return img->li->u;
		if (lettre == 118)
                    return img->li->v;
		if (lettre == 119)
                    return img->li->w;
		if (lettre == 120)
                    return img->li->x;
		if (lettre == 121)
                    return img->li->y;
		if (lettre == 122)
                    return img->li->z;
	    }
	}
    }
    return img->li->X;
}
