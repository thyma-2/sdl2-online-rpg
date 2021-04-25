#include "control.h"
extern struct lettres *lettres;
void deplacement(struct personnages *moi)
{
	if (moi->faim < 0)
		sprintf (ordre + strlen(ordre), "%d 0 %d ", moi->id, moi->pv - 1);
	else
		sprintf (ordre + strlen(ordre), "%d 7 %d ", moi->id, moi->faim - 1);
	if (lettres->z == 1)
	{
		sprintf (ordre + strlen(ordre), "%d 2 %f %d 1 %f ", moi->id, moi->y - moi->vitesse_dep * cos(moi->angle / RADTODEG), moi->id, moi->x + moi->vitesse_dep * sin(moi->angle / RADTODEG));
	}
	if (lettres->s == 1)
	{
		sprintf (ordre + strlen(ordre), "%d 2 %f %d 1 %f ", moi->id, moi->y + moi->vitesse_dep * cos(moi->angle / RADTODEG), moi->id, moi->x - moi->vitesse_dep * sin(moi->angle / RADTODEG));
	}
	if (lettres->a == 1)
	{
		sprintf (ordre + strlen(ordre), "%d 2 %f %d 1 %f ", moi->id, moi->y + moi->vitesse_dep * sin(moi->angle / RADTODEG), moi->id, moi->x - moi->vitesse_dep * cos(moi->angle / RADTODEG));
	}
	if (lettres->e == 1)
	{
		sprintf (ordre + strlen(ordre), "%d 2 %f %d 1 %f ", moi->id, moi->y - moi->vitesse_dep * sin(moi->angle / RADTODEG), moi->id, moi->x + moi->vitesse_dep * cos(moi->angle / RADTODEG));
	}
	if (lettres->q == 1)
		sprintf (ordre + strlen(ordre), "%d 5 %d ", moi->id, moi->angle - 2);
	if (lettres->d == 1)
		sprintf (ordre + strlen(ordre), "%d 5 %d ", moi->id, moi->angle + 2);
	if (lettres->r == 1)
	{
		if (moi->sur_plancher != NULL)
		{
			if (strcmp (moi->sur_plancher->skin, "ship1") == 0)
			{
				moi->sur_plancher->vitesse_dep += 1; //TODO
			}
		}
	}
}
