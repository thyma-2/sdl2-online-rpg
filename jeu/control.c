#include "control.h"
extern struct lettres *lettres;
void deplacement(struct personnages *moi, char *ground, int max_x)
{
    max_x = max_x;
    ground = ground;
    if (lettres->z == 1)
    {
        moi->a_bouger = 1;
	moi->y -= moi->vitesse_dep * cos(moi->angle / RADTODEG);
        moi->x += moi->vitesse_dep * sin(moi->angle / RADTODEG);
    }
    if (lettres->s == 1)
    {
        moi->a_bouger = 1;
        moi->y += moi->vitesse_dep * cos(moi->angle / RADTODEG);
        moi->x -= moi->vitesse_dep * sin(moi->angle / RADTODEG);
    }
    if (lettres->a == 1)
    {
        moi->a_bouger = 1;
	moi->y += moi->vitesse_dep * sin(moi->angle / RADTODEG) / 1.5;
        moi->x -= moi->vitesse_dep * cos(moi->angle / RADTODEG) / 1.5;
    }
    if (lettres->e == 1)
    {
	moi->a_bouger = 1;
        moi->y -= (moi->vitesse_dep * sin(moi->angle / RADTODEG) / 1.5);
        moi->x += moi->vitesse_dep * cos(moi->angle / RADTODEG) / 1.5;
    }
    if (lettres->q == 1)
    {
        moi->a_bouger = 1;
	moi->angle -= 1;
        if (moi->angle < 0)
            moi->angle = 359;
    }
    if (lettres->d == 1)
    {
	moi->a_bouger = 1;
        moi->angle += 1;
        if (moi->angle > 360)
            moi->angle = 1;
    }
    if (lettres->r == 1)
    {
	if (moi->sur_plancher != NULL)
	{
	    if (strcmp (moi->sur_plancher->skin, "ship1") == 0)
	    {
		moi->sur_plancher->vitesse_dep += 1;
		moi->sur_plancher->a_bouger = 1;
	    }
	}
    }
}
