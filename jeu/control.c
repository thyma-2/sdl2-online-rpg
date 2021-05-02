#include "control.h"
extern struct lettres *lettres;
void deplacement(struct personnages *moi)
{
	if (moi->faim < 0)
		sprintf (ordre + strlen(ordre), "%d 00 -1 ", moi->id);
	if (lettres->z == 1)
	{
		sprintf (ordre + strlen(ordre), "%d 02 -%f %d 01 +%f ", moi->id, moi->vitesse_dep * cos(moi->angle / RADTODEG), moi->id, moi->vitesse_dep * sin(moi->angle / RADTODEG));
	}
	if (lettres->s == 1)
	{
		sprintf (ordre + strlen(ordre), "%d 02 +%f %d 01 -%f ", moi->id, moi->vitesse_dep * cos(moi->angle / RADTODEG), moi->id, moi->vitesse_dep * sin(moi->angle / RADTODEG));
	}
	if (lettres->a == 1)
	{
		sprintf (ordre + strlen(ordre), "%d 02 +%f %d 01 -%f ", moi->id, moi->vitesse_dep * sin(moi->angle / RADTODEG), moi->id, moi->vitesse_dep * cos(moi->angle / RADTODEG));
	}
	if (lettres->e == 1)
	{
		sprintf (ordre + strlen(ordre), "%d 02 -%f %d 01 +%f ", moi->id, moi->vitesse_dep * sin(moi->angle / RADTODEG), moi->id, moi->vitesse_dep * cos(moi->angle / RADTODEG));
	}
	if (lettres->q == 1)
		sprintf (ordre + strlen(ordre), "%d 05 %d ", moi->id, moi->angle - 2);
	if (lettres->d == 1)
		sprintf (ordre + strlen(ordre), "%d 05 %d ", moi->id, moi->angle + 2);
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
