#include "control.h"
extern struct lettres *lettres;
void deplacement(struct personnages *moi)
{
	if (moi->faim < 0)
		sprintf (ordre + strlen(ordre), "%d 00 -1 ", moi->id);

	char att = 0;
	char dep = 0;
	char ram = 0;

	if (lettres->r == 1)
	{
		if (moi->sur_plancher != NULL)
		{
			if (strcmp (moi->sur_plancher->skin, "ship1") == 0)
			{
				moi->sur_plancher->vitesse_dep += 1; //TODO
				ram = 1;
			}
		}
	}
	else
	{
		if (lettres->z == 1)
		{
			dep = 1;
			sprintf (ordre + strlen(ordre), "%d 02 -%f %d 01 +%f ", moi->id, moi->vitesse_dep * cos(moi->angle / RADTODEG), moi->id, moi->vitesse_dep * sin(moi->angle / RADTODEG));
		}
		if (lettres->s == 1)
		{
			dep = 1;
			sprintf (ordre + strlen(ordre), "%d 02 +%f %d 01 -%f ", moi->id, moi->vitesse_dep * cos(moi->angle / RADTODEG), moi->id, moi->vitesse_dep * sin(moi->angle / RADTODEG));
		}
		if (lettres->a == 1)
		{
			dep = 1;
			sprintf (ordre + strlen(ordre), "%d 02 +%f %d 01 -%f ", moi->id, moi->vitesse_dep * sin(moi->angle / RADTODEG), moi->id, moi->vitesse_dep * cos(moi->angle / RADTODEG));
		}
		if (lettres->e == 1)
		{
			dep = 1;
			sprintf (ordre + strlen(ordre), "%d 02 -%f %d 01 +%f ", moi->id, moi->vitesse_dep * sin(moi->angle / RADTODEG), moi->id, moi->vitesse_dep * cos(moi->angle / RADTODEG));
		}
		if (lettres->q == 1)
		{
			dep = 1;
			sprintf (ordre + strlen(ordre), "%d 05 -2 ", moi->id);
		}
		if (lettres->d == 1)
		{
			dep = 1;
			sprintf (ordre + strlen(ordre), "%d 05 +2 ", moi->id);
		}
		if (lettres->esp == 1)
		{
			att = 1;
		}
		ram = ram;
		dep = dep;
		att = att;
	}

}
