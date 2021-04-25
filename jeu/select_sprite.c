#include "select_sprite.h"

char plat_ou_volumineux(char *skin)
{
	if (strcmp(skin, "ship1") == 0 /*|| strcmp(skin, "tour") == 0*/)
		return 1;
	if (strcmp(skin, "tour") == 0)
		return 2;
	return 0;
}

SDL_Texture *select_good_img(struct personnages *perso, struct personnages *moi)
{
	int angle;
	if (moi == perso)
		angle = 1;
	else
	{
		angle = perso->angle - moi->angle;
		if (angle < 0)
			angle += 360;
	}
	perso->animation += 1;
	if (perso->animation > 20)
		perso->animation = 0;
	if (strcmp(perso->skin, "fantassin") == 0)
	{
		if (perso->animation <= 0)
		{
			if (angle < 15 || angle >= 345)
				return img->s->hoFaDoRien;
			else if (angle < 45 && angle >= 15)
				return img->s->hoFaDoDrRien;
			else if (angle < 75 && angle >= 45)
				return img->s->hoFaDrDoRien;
			else if (angle < 105 && angle >= 75)
				return img->s->hoFaDrRien;
			else if (angle < 135 && angle >= 105)
				return img->s->hoFaDrFaRien;
			else if (angle < 165 && angle >= 135)
				return img->s->hoFaFaDrRien;
			else if (angle < 195 && angle >= 165)
				return img->s->hoFaFaRien;
			else if (angle < 225 && angle >= 195)
				return img->s->hoFaFaGaRien;
			else if (angle < 255 && angle >= 225)
				return img->s->hoFaGaFaRien;
			else if (angle < 285 && angle >= 255)
				return img->s->hoFaGaRien;
			else if (angle < 315 && angle >= 285)
				return img->s->hoFaGaDoRien;
			else if (angle < 345 && angle >= 315)
				return img->s->hoFaDoGaRien;
		}
		else if (perso->animation < 4)
		{
			if (angle < 15 || angle >= 345)
				return img->s->hoFaDoMa1;
			else if (angle < 45 && angle >= 15)
				return img->s->hoFaDoDrMa1;
			else if (angle < 75 && angle >= 45)
				return img->s->hoFaDrDoMa1;
			else if (angle < 105 && angle >= 75)
				return img->s->hoFaDrMa1;
			else if (angle < 135 && angle >= 105)
				return img->s->hoFaDrFaMa1;
			else if (angle < 165 && angle >= 135)
				return img->s->hoFaFaDrMa1;
			else if (angle < 195 && angle >= 165)
				return img->s->hoFaFaMa1;
			else if (angle < 225 && angle >= 195)
				return img->s->hoFaFaGaMa1;
			else if (angle < 255 && angle >= 225)
				return img->s->hoFaGaFaMa1;
			else if (angle < 285 && angle >= 255)
				return img->s->hoFaGaMa1;
			else if (angle < 315 && angle >= 285)
				return img->s->hoFaGaDoMa1;
			else if (angle < 345 && angle >= 315)
				return img->s->hoFaDoGaMa1;
		}
		else if (perso->animation < 8)
		{
			if (angle < 15 || angle >= 345)
				return img->s->hoFaDoMa2;
			else if (angle < 45 && angle >= 15)
				return img->s->hoFaDoDrMa2;
			else if (angle < 75 && angle >= 45)
				return img->s->hoFaDrDoMa2;
			else if (angle < 105 && angle >= 75)
				return img->s->hoFaDrMa2;
			else if (angle < 135 && angle >= 105)
				return img->s->hoFaDrFaMa2;
			else if (angle < 165 && angle >= 135)
				return img->s->hoFaFaDrMa2;
			else if (angle < 195 && angle >= 165)
				return img->s->hoFaFaMa2;
			else if (angle < 225 && angle >= 195)
				return img->s->hoFaFaGaMa2;
			else if (angle < 255 && angle >= 225)
				return img->s->hoFaGaFaMa2;
			else if (angle < 285 && angle >= 255)
				return img->s->hoFaGaMa2;
			else if (angle < 315 && angle >= 285)
				return img->s->hoFaGaDoMa2;
			else if (angle < 345 && angle >= 315)
				return img->s->hoFaDoGaMa2;
		}
		else if (perso->animation < 12)
		{
			if (angle < 15 || angle >= 345)
				return img->s->hoFaDoMa3;
			else if (angle < 45 && angle >= 15)
				return img->s->hoFaDoDrMa3;
			else if (angle < 75 && angle >= 45)
				return img->s->hoFaDrDoMa3;
			else if (angle < 105 && angle >= 75)
				return img->s->hoFaDrMa3;
			else if (angle < 135 && angle >= 105)
				return img->s->hoFaDrFaMa3;
			else if (angle < 165 && angle >= 135)
				return img->s->hoFaFaDrMa3;
			else if (angle < 195 && angle >= 165)
				return img->s->hoFaFaMa3;
			else if (angle < 225 && angle >= 195)
				return img->s->hoFaFaGaMa3;
			else if (angle < 255 && angle >= 225)
				return img->s->hoFaGaFaMa3;
			else if (angle < 285 && angle >= 255)
				return img->s->hoFaGaMa3;
			else if (angle < 315 && angle >= 285)
				return img->s->hoFaGaDoMa3;
			else if (angle < 345 && angle >= 315)
				return img->s->hoFaDoGaMa3;
		}
		else if (perso->animation < 16)
		{
			if (angle < 15 || angle >= 345)
				return img->s->hoFaDoMa4;
			else if (angle < 45 && angle >= 15)
				return img->s->hoFaDoDrMa4;
			else if (angle < 75 && angle >= 45)
				return img->s->hoFaDrDoMa4;
			else if (angle < 105 && angle >= 75)
				return img->s->hoFaDrMa4;
			else if (angle < 135 && angle >= 105)
				return img->s->hoFaDrFaMa4;
			else if (angle < 165 && angle >= 135)
				return img->s->hoFaFaDrMa4;
			else if (angle < 195 && angle >= 165)
				return img->s->hoFaFaMa4;
			else if (angle < 225 && angle >= 195)
				return img->s->hoFaFaGaMa4;
			else if (angle < 255 && angle >= 225)
				return img->s->hoFaGaFaMa4;
			else if (angle < 285 && angle >= 255)
				return img->s->hoFaGaMa4;
			else if (angle < 315 && angle >= 285)
				return img->s->hoFaGaDoMa4;
			else if (angle < 345 && angle >= 315)
				return img->s->hoFaDoGaMa4;
		}
		else
		{
			if (angle < 15 || angle >= 345)
				return img->s->hoFaDoMa5;
			else if (angle < 45 && angle >= 15)
				return img->s->hoFaDoDrMa5;
			else if (angle < 75 && angle >= 45)
				return img->s->hoFaDrDoMa5;
			else if (angle < 105 && angle >= 75)
				return img->s->hoFaDrMa5;
			else if (angle < 135 && angle >= 105)
				return img->s->hoFaDrFaMa5;
			else if (angle < 165 && angle >= 135)
				return img->s->hoFaFaDrMa5;
			else if (angle < 195 && angle >= 165)
				return img->s->hoFaFaMa5;
			else if (angle < 225 && angle >= 195)
				return img->s->hoFaFaGaMa5;
			else if (angle < 255 && angle >= 225)
				return img->s->hoFaGaFaMa5;
			else if (angle < 285 && angle >= 255)
				return img->s->hoFaGaMa5;
			else if (angle < 315 && angle >= 285)
				return img->s->hoFaGaDoMa5;
			else if (angle < 345 && angle >= 315)
				return img->s->hoFaDoGaMa5;
		}
	}
	if (strcmp(perso->skin, "archer") == 0)
	{
		if (perso->animation < 4)
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
		else if (perso->animation < 8)
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
		else if (perso->animation < 12)
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
		else if (perso->animation < 16)
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
		else
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
	if (strcmp(perso->skin, "ship1") == 0)
		return img->s->ship1haut;
	if (strcmp(perso->skin, "chateau") == 0)
	{

		if (angle < 15 || angle >= 345)
			return img->s->chateauDos;
		else if (angle < 45 && angle >= 15)
			return img->s->chateauDosDroite;
		else if (angle < 75 && angle >= 45)
			return img->s->chateauDroiteDos;
		else if (angle < 105 && angle >= 75)
			return img->s->chateauDroite;
		else if (angle < 135 && angle >= 105)
			return img->s->chateauDroiteFace;
		else if (angle < 165 && angle >= 135)
			return img->s->chateauFaceDroite;
		else if (angle < 195 && angle >= 165)
			return img->s->chateauFace;
		else if (angle < 225 && angle >= 195)
			return img->s->chateauFaceGauche;
		else if (angle < 255 && angle >= 225)
			return img->s->chateauGaucheFace;
		else if (angle < 285 && angle >= 255)
			return img->s->chateauGauche;
		else if (angle < 315 && angle >= 285)
			return img->s->chateauGaucheDos;
		else if (angle < 345 && angle >= 315)
			return img->s->chateauDosGauche;
	}
	if (strcmp(perso->skin, "tour") == 0)
	{
		if (angle < 75 || angle >= 285)
			return img->s->tourDos;
		else if (angle < 105 && angle >= 75)
			return img->s->tourDroite;
		else if (angle < 135 && angle >= 105)
			return img->s->tourDroiteFace;
		else if (angle < 165 && angle >= 135)
			return img->s->tourFaceDroite;
		else if (angle < 195 && angle >= 165)
			return img->s->tourFace;
		else if (angle < 225 && angle >= 195)
			return img->s->tourFaceGauche;
		else if (angle < 255 && angle >= 225)
			return img->s->tourGaucheFace;
		return img->s->tourGauche;
	}

	if (strncmp(perso->skin, "arbre", 5) == 0)
	{
		if (perso->skin[5] == '1')
			return img->s->arbre1;
	}
	if (strncmp(perso->skin, "fruit", 5) == 0)
		return img->s->fruit;
	return img->s->hoArGdMa5;
}

SDL_Texture *select_texture(char ground)
{

	if (ground == 20)
		return img->t->gr1;
	if (ground == 21)
		return img->t->gr2;
	if (ground >= 10)
	{
		if (ground >= 15)
		{
			if (ground == 15)
				return img->t->bl2;
			if (ground == 16)
				return img->t->bl3;
			if (ground == 17)
				return img->t->ne1;
			if (ground == 18)
				return img->t->ne2;
			return img->t->ne3;
		}
		else
		{
			if (ground == 14)
				return img->t->bl1;
			if (ground == 13)
				return img->t->sa3;
			if (ground == 12)
				return img->t->sa2;
			if (ground == 11)
				return img->t->sa1;
			return img->t->he5;

		}
	}
	else
	{
		if (ground >= 5)
		{
			if (ground == 5)
				return img->t->te3;
			if (ground == 6)
				return img->t->he1;
			if (ground == 7)
				return img->t->he2;
			if (ground == 8)
				return img->t->he3;
			return img->t->he4;
		}
		else
		{
			if (ground == 0)
				return img->t->ea1;
			if (ground == 1)
				return img->t->ea2;
			if (ground == 2)
				return img->t->ea3;
			if (ground == 3)
				return img->t->te1;
			return img->t->te2;
		}
	}
	return NULL;
}

SDL_Texture *select_lettre(char lettre)
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
				if (lettre == 32)
					return img->li->espace;
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
