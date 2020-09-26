#include "gui.h"

void blit_mdp(SDL_Rect position, char *text, SDL_Window *ecran, int limite, int couleur)
{
    int pox = position.x;
    int i = 0;
    SDL_Surface *lettre_afficher = select_lettre('x');
    while (text[i] != 0)
    {
        if (i % limite == 0 && i != 0)
        {
            position.y += 20;
            position.x = pox;
        }
        if (text[i] == '\n')
        {
            position.y += 20;
            position.x = pox;
            i++;
        }
        else if (text[i] == ' ')
        {
            position.x += 14;
            i++;
        }
        else
        {
            if (lettre_afficher != NULL)
            {
                SDL_SetColorKey(lettre_afficher, SDL_SCANCODE_Y, SDL_MapRGB(lettre_afficher->format,couleur,couleur,couleur));
                SDL_BlitSurface(lettre_afficher, NULL, SDL_GetWindowSurface(ecran), &position);
                position.x += lettre_afficher->w;
            }
            i++;
        }
    }
}

int blit_text(SDL_Rect position, char *text, SDL_Window *ecran, int limite, int couleur)
{
    int pox = position.x;
    int i = 0;
    int mpox = 0;
    while (text[i] != 0)
    {
        if (i % limite == 0 && i != 0)
        {
            position.y += 20;
            position.x = pox;
        }
        if (text[i] == '\n')
        {
            position.y += 20;
            position.x = pox;
            i++;
        }
        else if (text[i] == ' ')
        {
            position.x += 14;
            i++;
        }
        else
        {
            SDL_Surface *lettre_afficher = select_lettre(text[i]);
            if (lettre_afficher != NULL)
            {
                SDL_SetColorKey(lettre_afficher, SDL_SCANCODE_Y, SDL_MapRGB(lettre_afficher->format,couleur,couleur,couleur));
                SDL_BlitSurface(lettre_afficher, NULL, SDL_GetWindowSurface(ecran), &position);
                position.x += lettre_afficher->w;
		if (position.x - pox> mpox)
	            mpox = position.x - pox;
            }
            i++;
	}
    }
    return mpox;
}

void gui_event(struct personnages *perso, SDL_Window *ecran, struct linked_list *list)
{
    // ordres (que tu recois)
    SDL_Rect position;
    if (perso->ordrex != -1)
    {
        position.x = perso->ordrex + 550 - perso->x;
        position.y = perso->ordrey + 300 - perso->y;
        if (perso->x > perso->ordrex + - 50 && perso->x < perso->ordrex + 50 && perso->y > perso->ordrey - 50 && perso->y < perso->ordrey + 50)
            perso->ordrex = -1;
        SDL_Surface *croix = SDL_LoadBMP("img/gui/croix.bmp");
        SDL_SetColorKey(croix, SDL_SCANCODE_Y, SDL_MapRGB(croix->format, 255, 255, 255));
        SDL_BlitSurface(croix, NULL, SDL_GetWindowSurface(ecran), &position);
    }
    position.x = 50;
    position.y = 50;
    char txt[150];
    txt[0] = 0;
    //proposition d'échange
    if (strcmp(perso->echange_player, "none") != 0)
    {
	struct personnages *p = find_perso_by_name(list, perso->echange_player);
	{
	    if (p != NULL)
	    {
		strcat(txt, perso->echange_player);
		strcat(txt, " vous propose un echange -> ");
		struct linked_item *obj1 = get_item_n(perso->item2, perso->i_list); //le tiens
		struct linked_item *obj2 = get_item_n(perso->item1, p->i_list);
		if (obj1 != NULL)
		    strcat(txt, obj1->nom);
		else
		    strcat(txt, "rien");
		strcat(txt, " contre : ");
		if (obj2 != NULL)
                    strcat(txt, obj2->nom);
                else
                    strcat(txt, "rien");
		strcat(txt, "\nappuyez sur y pour accepter et n pour refuser");
		if (lettres->n == 1)
		{
		    perso->echange_player[0] = 0;
		    strcat(perso->echange_player, "none");
		    lettres->n = 0;
		}
		if (lettres->y == 1)
		{
		    lettres->y = 0;
		    perso->echange_player[0] = 0;
                    strcat(perso->echange_player, "none");
		    if (obj1 != NULL && obj2 != NULL)
		    {
			p->i_list = append_in_inventory(obj1->nom, p->i_list, 1);
			perso->i_list = append_in_inventory(obj2->nom, perso->i_list, 1);
			p->i_list = remove_from_inventory(obj2->nom, p->i_list, 1);
			perso->i_list = remove_from_inventory(obj1->nom, perso->i_list, 1);
			perso->a_bouger = 1;
			p->a_bouger = 1;
		    }
		    else if (obj1 == NULL && obj2 != NULL)
		    {
			perso->i_list = append_in_inventory(obj2->nom, perso->i_list, 1);
		  	p->i_list = remove_from_inventory(obj2->nom, p->i_list, 1);
			perso->a_bouger = 1;
                        p->a_bouger = 1;
		    }
		    else if (obj2 == NULL && obj1 != NULL)
		    {
			p->i_list = append_in_inventory(obj1->nom, p->i_list, 1);
                        perso->i_list = remove_from_inventory(obj1->nom, perso->i_list, 1);
			perso->a_bouger = 1;
                        p->a_bouger = 1;
		    }
		}
	    }
	}
	blit_text(position, txt, ecran, 90, 255);
    }
    //bulle de dialogues
    for (struct linked_list *p = list; p != NULL; p = p->next)
    {
	if (p->p->speak[0] != 0)
	{
	    int s = strlen(p->p->speak);
	    int somme = 0;
	    for (int i = 0; p->p->speak[i] != 0; i++)
		somme += select_lettre(p->p->speak[i])->w;
    	    if (s > 60)
	    {	    
	        position.y = p->p->y + 290 - perso->y;
		position.x = p->p->x + 600 - (somme / s) * 15 - perso->x;
	    }
	    else if (s > 30)
	    {
		position.y = p->p->y + 310 - perso->y;
		position.x = p->p->x + 600 - (somme / s) * 15 - perso->x;
	    }
	    else
	    {
		position.y = p->p->y + 330 - perso->y;
		position.x = p->p->x + 600 - somme / 2 - perso->x;
	    }
 	    blit_text(position, p->p->speak, ecran, 30, 0);    
	}
	if (perso->speak_timer > 0)
	{
	    perso->speak_timer --;
	    if (perso->speak_timer == 0)
	    {
		perso->speak[0] = 0;
		perso->a_bouger = 1;
	    }
	}
    }
}

void display_selected(struct linked_list *selected, SDL_Window *ecran, struct personnages *moi, struct formation *f)
{
    char txt[200] = "pv\nvitesse\nperiode d attaque\nporte\npoid\nfaim";
    char txt2[200];
    char tmp[20];
    SDL_Rect position;
    position.x = 0;
    position.y = 550;
    SDL_BlitSurface(img->g->demarcation, NULL, SDL_GetWindowSurface(ecran), &position);
    position.x = 12;
    txt2[0] = 0;
    tmp[0] = 0;
    sprintf(tmp, "%d", moi->pv);
    strcat(txt2, tmp);
    strcat(txt2, "/");
    tmp[0] = 0;
    sprintf(tmp, "%d", moi->max_pv);
    strcat(txt2, tmp);
    strcat(txt2, "\n");
    tmp[0] = 0;
    sprintf(tmp, "%d", moi->vitesse_dep);
    strcat(txt2, tmp);
    strcat(txt2, "\n");
    tmp[0] = 0;
    sprintf(tmp, "%d", moi->vitesse_dom);
    strcat(txt2, tmp);
    strcat(txt2, "\n");
    tmp[0] = 0;
    sprintf(tmp, "%d", moi->porte_dom);
    strcat(txt2, tmp);
    strcat(txt2, "\n");
    tmp[0] = 0;
    sprintf(tmp, "%d", moi->poid);
    strcat(txt2, tmp);
    strcat(txt2, "\n");
    tmp[0] = 0;
    sprintf(tmp, "%d", moi->faim / 1000);
    strcat(txt2, tmp);
    position.x += blit_text(position, txt, ecran, 200, 255) + 20;
    position.x += blit_text(position, txt2, ecran, 200, 255) + 8;
    SDL_BlitSurface(img->g->demarcation, NULL, SDL_GetWindowSurface(ecran), &position);
    position.x += 12;
    int pv = 0;
    int pvm = 0;
    int vitesse_dom = 0;
    int i = 0;
    int vitesse_dep = 99999;
    int portee = 99999;
    int poid = 0;
    int faim = 99999;
    txt[0] = 0;
    txt2[0] = 0;
    for (struct linked_list *parcour = selected; parcour != NULL; parcour = parcour->next)
    {
	if (strcmp(parcour->p->nom_superieur, moi->nom) == 0)
	{
	    strcat(txt, parcour->p->nom);
	    strcat(txt, "\n");
	    i++;
	    pvm += parcour->p->max_pv;
	    pv += parcour->p->pv;
	    vitesse_dom += parcour->p->vitesse_dom;
	    poid += parcour->p->poid;
	    if (parcour->p->vitesse_dep < vitesse_dep)
	        vitesse_dep = parcour->p->vitesse_dep;
	    if (parcour->p->porte_dom < portee)
	        portee = parcour->p->porte_dom;
	    if (parcour->p->faim < faim)
		faim = parcour->p->faim;
	}
	else
	{
	    strcat(txt2, parcour->p->nom);
	    strcat(txt2, "\n");
	}
    }
    position.x += blit_text(position,txt2,ecran, 200, 255) + 8;
    SDL_BlitSurface(img->g->demarcation, NULL, SDL_GetWindowSurface(ecran), &position);
    position.x += 12;
    position.x += blit_text(position,txt,ecran, 200, 255) + 8;
    SDL_BlitSurface(img->g->demarcation, NULL, SDL_GetWindowSurface(ecran), &position);
    position.x += 12;
    if (i > 0)
    {
        txt[0] = 0;
	txt2[0] = 0;
        strcat(txt, "pv\nvitesse\nperiode d attaque\nportee\npoid\nfaim");
        tmp[0] = 0;
        sprintf(tmp, "%d", pv / i);
	strcat(txt2, tmp);
	strcat(txt2, "/");
	tmp[0] = 0;
	sprintf(tmp, "%d", pvm / i);
	strcat(txt2, tmp);
	strcat(txt2, "\n");
	tmp[0] = 0;
        sprintf(tmp, "%d", vitesse_dep);
	strcat(txt2, tmp);
	strcat(txt2, "\n");
	tmp[0] = 0;
        sprintf(tmp, "%d", vitesse_dom / i);
	strcat(txt2, tmp);
	strcat(txt2, "\n");
	tmp[0] = 0;
        sprintf(tmp, "%d", portee);
        strcat(txt2, tmp);
	strcat(txt2, "\n");
	tmp[0] = 0;
        sprintf(tmp, "%d", poid / i);
        strcat(txt2, tmp);
	strcat(txt2, "\n");
	tmp[0] = 0;
	sprintf(tmp, "%d", faim / 1000);
	strcat(txt2, tmp);
        position.x += blit_text(position, txt, ecran, 200, 255) + 20;
	position.x += blit_text(position, txt2, ecran, 200, 255);
    }
    position.x += 8;
    SDL_BlitSurface(img->g->demarcation, NULL, SDL_GetWindowSurface(ecran), &position);
    if (i > 0)
    {
        position.x += 12;
	if (lettres->Mouse_Lclick == 1)
	{
	    if (lettres->Mouse_pos_x > position.x && lettres->Mouse_pos_x < position.x + 30 && lettres->Mouse_pos_y > position.y && lettres->Mouse_pos_y < position.y + 30)
	    {
                f->ecart_x += 1;
	    }
	}
	SDL_BlitSurface(img->g->plus, NULL, SDL_GetWindowSurface(ecran), &position);
	position.x += 35;
	if (lettres->Mouse_Lclick == 1)
        {
            if (lettres->Mouse_pos_x > position.x && lettres->Mouse_pos_x < position.x + 30 && lettres->Mouse_pos_y > position.y && lettres->Mouse_pos_y < position.y + 30)
            {
                f->ecart_y += 1;
            }
        }
	SDL_BlitSurface(img->g->plus, NULL, SDL_GetWindowSurface(ecran), &position);
        position.x += 35;
	if (lettres->Mouse_Lclick == 1)
        {
            if (lettres->Mouse_pos_x > position.x && lettres->Mouse_pos_x < position.x + 30 && lettres->Mouse_pos_y > position.y && lettres->Mouse_pos_y < position.y + 30)
            {
                f->n_par_lignes += 1;
            }
        }
	SDL_BlitSurface(img->g->plus, NULL, SDL_GetWindowSurface(ecran), &position);
	position.y += 60;
	position.x -= 70;
	if (lettres->Mouse_Lclick == 1)
        {
            if (lettres->Mouse_pos_x > position.x && lettres->Mouse_pos_x < position.x + 30 && lettres->Mouse_pos_y > position.y && lettres->Mouse_pos_y < position.y + 30)
            {
                f->ecart_x -= 1;
            }
        }
	SDL_BlitSurface(img->g->moins, NULL, SDL_GetWindowSurface(ecran), &position);
        position.x += 35;
	if (lettres->Mouse_Lclick == 1)
        {
            if (lettres->Mouse_pos_x > position.x && lettres->Mouse_pos_x < position.x + 30 && lettres->Mouse_pos_y > position.y && lettres->Mouse_pos_y < position.y + 30)
            {
                f->ecart_y -= 1;
            }
        }
        SDL_BlitSurface(img->g->moins, NULL, SDL_GetWindowSurface(ecran), &position);
        position.x += 35;
	if (lettres->Mouse_Lclick == 1)
        {
            if (lettres->Mouse_pos_x > position.x && lettres->Mouse_pos_x < position.x + 30 && lettres->Mouse_pos_y > position.y && lettres->Mouse_pos_y < position.y + 30)
            {
                f->n_par_lignes -= 1;
            }
        }
        SDL_BlitSurface(img->g->moins, NULL, SDL_GetWindowSurface(ecran), &position);
	position.x += 18;
	position.y -= 60;
    }
    position.x += 20;
    SDL_BlitSurface(img->g->demarcation, NULL, SDL_GetWindowSurface(ecran), &position);
}

void menu(SDL_Window *ecran, struct menu *m, struct personnages *perso, struct linked_list *list)
{
    char txt[] = "Menu inventaire -> Taper i.\nMenu diplomatique -> Taper d.\nMenu action -> taper a";
    char txt1[] = "Ajouter un enemi";
    char txt2[] = "Retirer un enemi";
    char txt4[] = "Changer de suzerain";
    char txt5[] = "Prendre possession";
    char txt6[] = "Main Gauche";
    char txt7[] = "Main Droite";
    char txt8[] = "Vetements";
    char txt9[] = "Stockage";
    char tmpI[10] = "";
    char *e_list = malloc(200);
    SDL_Rect position1;
    SDL_Rect position2;
    SDL_Rect position3;
    SDL_Rect position4;
    SDL_Rect position5;
    SDL_Rect position7;
    SDL_Rect position8;
    SDL_Rect position9;
    SDL_Rect position10;
    SDL_Rect position11;
    SDL_Rect position12;
    SDL_Rect position13;
    SDL_Rect position14;
    position1.x = 50;
    position2.x = 50;
    position3.x = 50;
    position4.x = 50;
    position4.x = 50;
    position5.x = 700;
    position7.x = 50;
    position8.x = 50;
    position9.x = 50;
    position10.x = 50;
    position11.x = 50;
    position12.x = 50;
    position13.x = 200;
    position14.x = 250;
    position1.y = 70;
    position2.y = 100;
    position3.y = 170;
    position4.y = 200;
    position5.y = 70;
    position7.y = 270;
    position8.y = 300;
    position9.y = 100;
    position10.y = 120;
    position11.y = 140;
    position12.y = 160;
    position13.y = 100;
    position14.y = 0;
    if (lettres->esc == 1)
    {
	lettres->esc = 0;
	if (m->echange_on != 0)
	    m->echange_on = 0;
	else if (m->inventaire_on != 0)
	    m->inventaire_on = 0;
	else if (m->diplo_on != 0)
	    m->diplo_on = 0;
	else if (m->action_on != 0)
	    m->action_on = 0;
	else
	    m->on = 0;
    }
    if (m->inventaire_on == 0 && m->diplo_on == 0 && m->action_on == 0 && m->echange_on == 0)
    {
	blit_text(position1, txt, ecran, 200, 255);
	if (lettres->i == 1)
	{
	    lettres->i = 0;
	    m->inventaire_on = 1;
        }
        if (lettres->d == 1)
        {
            lettres->d = 0;
	    m->diplo_on = 1;
	}
	if (lettres->a == 1)
	{
	    lettres->a = 0;
	    m->action_on = 1;
	}
    }
    if (m->echange_on == 1)
    {
	struct linked_item *t = perso->i_list;
	e_list[0] = 0;
        for (int i = 0; i < 10; i++)
        {
            if (m->sel_echange1 == position14.y / 20)
                SDL_BlitSurface(img->g->narrowSelTextInput, NULL, SDL_GetWindowSurface(ecran), &position14);
            else
                SDL_BlitSurface(img->g->narrowTextInput, NULL, SDL_GetWindowSurface(ecran), &position14);
            if (t != NULL)
            {
		strcat(e_list, t->nom);
		strcat(e_list, " - ");
		tmpI[0] = 0;
                sprintf (tmpI, "%d", t->count);
                strcat(e_list, tmpI);
		strcat(e_list, "\n");
                t = t->next;
            }
            position14.y += 20;
        }
	position14.y = 0;
	blit_text(position14, e_list, ecran, 20000, 255);
	position14.y = 220;
	t = m->echange->i_list;
	e_list[0] = 0;
        for (int i = 0; i < 10; i++)
        {
            if (m->sel_echange2 == (position14.y - 220) / 20)
                SDL_BlitSurface(img->g->narrowSelTextInput, NULL, SDL_GetWindowSurface(ecran), &position14);
            else
                SDL_BlitSurface(img->g->narrowTextInput, NULL, SDL_GetWindowSurface(ecran), &position14);
            if (t != NULL)
            {
		strcat(e_list, t->nom);
                strcat(e_list, " - ");
		tmpI[0] = 0;
                sprintf (tmpI, "%d", t->count);
                strcat(e_list, tmpI);
                strcat(e_list, "\n");
                t = t->next;
            }
            position14.y += 20;
        }
	position14.y = 220;
	blit_text(position14, e_list, ecran, 20000, 255);
	if (lettres->enter == 1)
	{
	    lettres->enter = 0;
	    m->echange->echange_player[0] = 0;
	    m->echange->a_bouger = 1;
	    strcat(m->echange->echange_player, perso->nom);
	    m->echange->item1 = m->sel_echange1 + 1;
	    m->echange->item2 = m->sel_echange2 + 1;
	}
        if (lettres->s == 1)
        {
            lettres->s = 0;
	    if (m->tab_echange == 1)
	    {
                if (m->sel_echange1 == 9)
                    m->sel_echange1 = 0;
                else
                    m->sel_echange1 += 1;
	    }
	    else
	    {
		if (m->sel_echange2 == 9)
                    m->sel_echange2 = 0;
		else
		    m->sel_echange2 += 1;
	    }
        }
        if (lettres->z == 1)
        {
	    lettres->z = 0;
	    if (m->tab_echange == 1)
	    {
                if (m->sel_echange1 == 0)
                    m->sel_echange1 = 9;
                else
                    m->sel_echange1 -= 1;
	    }
	    else
	    {
		if (m->sel_echange2 == 0)
                    m->sel_echange2 = 9;
                else
                    m->sel_echange2 -= 1;
	    }

        }
	if (lettres->tab == 1)
	{
	    lettres->tab = 0;
	    if (m->tab_echange == 0)
		m->tab_echange = 1;
	    else
		m->tab_echange = 0;
	}
    }
    else if (m->action_on == 1)
    {
	int c = 0;
	if (perso->sur_plancher != NULL)
	{
	    if (m->sel_action == 0)
		SDL_BlitSurface(img->g->selTextInput, NULL, SDL_GetWindowSurface(ecran),
                    &position2);
	    else
		SDL_BlitSurface(img->g->textInput, NULL, SDL_GetWindowSurface(ecran),
                    &position2);
     	    blit_text(position2, txt5, ecran, 20, 255);
   	    if (lettres->enter == 1 && m->sel_action == 0)
	    {
	        lettres->enter = 0;
		perso->sur_plancher->nom_superieur[0] = 0;
		strcat(perso->sur_plancher->nom_superieur, perso->nom);
	    }
	}
	for (struct linked_list *l = list; l != NULL; l = l->next)
	{
	    if (l->p != perso)
	    {
		int x1, x2, x3, x4, y1, y2, y3, y4;
		coo_corner(l->p, &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4);
		x2 = (x1 + x2 + x3 + x4) / 4;
		y2 = (y1 + y2 + y3 + y4) / 4;
	        if (sqrt((x2 - perso->x)*(x2 - perso->x) + (y2 - perso->y)*(y2 - perso->y)) < 99 + sqrt(((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1))/2))
		{
		    c += 1;
		    position2.y += 50;
		    if (m->sel_action == (position2.y - 100) / 50)
		    {
  		        SDL_BlitSurface(img->g->selTextInput, NULL, SDL_GetWindowSurface(ecran),
 	                    &position2);
			m->echange = l->p;
		    }
		    else
			SDL_BlitSurface(img->g->textInput, NULL, SDL_GetWindowSurface(ecran),
                            &position2);
		    blit_text(position2, l->p->nom, ecran, 20, 255);
		}
	    }
	}
	if (lettres->enter == 1 && m->sel_action > 0)
        {
            lettres->enter = 0;
	    m->echange_on = 1;
        }
	if (lettres->s == 1)
        {
            lettres->s = 0;
            m->sel_action += 1;
        }
        if (lettres->z == 1)
        {
            lettres->z = 0;
	    if (m->sel_action > 0)
	        m->sel_action -= 1;
        }
	if (m->sel_action > c)
	    m->sel_action = c;
    }
    else if (m->inventaire_on == 1)
    {
	blit_text(position9, txt6, ecran, 20, 255);
	blit_text(position10, txt7, ecran, 20, 255);
	blit_text(position11, txt8, ecran, 20, 255);
	blit_text(position12, txt9, ecran, 20, 255);
	struct linked_item *t = perso->i_list;
	e_list[0] = 0;
	for (int i = 0; i < 10; i++)
	{
	    if (m->sel_inventaire == (position13.y - 100) / 20)
	        SDL_BlitSurface(img->g->narrowSelTextInput, NULL, SDL_GetWindowSurface(ecran), &position13);
	    else
 	        SDL_BlitSurface(img->g->narrowTextInput, NULL, SDL_GetWindowSurface(ecran), &position13);
	    position13.y += 20;
	    if (t != NULL)
	    {
		strcat(e_list, t->nom);
		strcat(e_list, " - ");
		tmpI[0] = 0;
		sprintf (tmpI, "%d", t->count);
		strcat(e_list, tmpI);
		strcat(e_list, "\n");
		t = t->next;
	    }

	}
	position13.y = 100;
	blit_text(position13, e_list, ecran, 2000, 255);
	if (lettres->s == 1)
        {
            lettres->s = 0;
            if (m->sel_inventaire == 9)
                m->sel_inventaire = 0;
            else
                m->sel_inventaire += 1;
	}
	if (lettres->z == 1)
	{
	    lettres->z = 0;
	    if (m->sel_inventaire == 0)
		m->sel_inventaire = 9;
	    else
		m->sel_inventaire -= 1;
	}
	if (lettres->k1 == 1)
	{
	    exchange_item(0, m->sel_inventaire, perso->i_list);
	    lettres->k1 = 0;
	}
	else if (lettres->k2 == 1)
	{
	    exchange_item(1, m->sel_inventaire, perso->i_list);
	    lettres->k2 = 0;
	}
	else if (lettres->k3 == 1)
	{
	    exchange_item(2, m->sel_inventaire, perso->i_list);
	    lettres->k3 = 0;
	}
	else if (lettres->enter == 1)
	{
	    perso->i_list = use(get_item_n(m->sel_inventaire + 1, perso->i_list), perso);
	    lettres->enter = 0;
	}
    }
    else if (m->diplo_on == 1)
    {
	blit_text(position1, txt1, ecran, 20, 255);
	blit_text(position3, txt2, ecran, 20, 255);
	blit_text(position7, txt4, ecran, 20, 255);
	if (m->sel_diplo == 0)
	{
	    text_input(m->add_enemi, 50);
            SDL_BlitSurface(img->g->selTextInput, NULL, SDL_GetWindowSurface(ecran),
                &position2);
	    SDL_BlitSurface(img->g->textInput, NULL, SDL_GetWindowSurface(ecran),
                &position4);
	    SDL_BlitSurface(img->g->textInput, NULL, SDL_GetWindowSurface(ecran),
                &position8);
	    if (lettres->enter == 1)
	    {
		lettres->enter = 0;
  		rec_append_enemie(m->add_enemi, perso, list, 1);
	    }
	}
	else if (m->sel_diplo == 1)
	{
	    text_input(m->rem_enemi, 50);
	    SDL_BlitSurface(img->g->selTextInput, NULL, SDL_GetWindowSurface(ecran),
                &position4);
            SDL_BlitSurface(img->g->textInput, NULL, SDL_GetWindowSurface(ecran),
                &position2);
	    SDL_BlitSurface(img->g->textInput, NULL, SDL_GetWindowSurface(ecran),
                &position8);
	    if (lettres->enter == 1)
	    {
		lettres->enter = 0;
		rec_remove_enemie(m->rem_enemi, perso, list, get_rang(m->rem_enemi, perso->e_list));
	    }
	}
	else
	{
	    text_input(perso->nom_superieur, 50);
	    SDL_BlitSurface(img->g->textInput, NULL, SDL_GetWindowSurface(ecran),
                &position2);
            SDL_BlitSurface(img->g->textInput, NULL, SDL_GetWindowSurface(ecran),
                &position4);
            SDL_BlitSurface(img->g->selTextInput, NULL, SDL_GetWindowSurface(ecran),
                &position8);
	}
	blit_text(position2, m->add_enemi, ecran, 20, 255);
        blit_text(position4, m->rem_enemi, ecran, 20, 255);
	blit_text(position8, perso->nom_superieur, ecran, 20, 255);
	if (lettres->tab == 1)
	{
	    lettres->tab = 0;
	    if (m->sel_diplo == 2)
		m->sel_diplo = 0;
	    else
		m->sel_diplo += 1;
	}
	int max = max_rang(perso->e_list);
	int rang = 1;
	while (rang <= max)
	{
	    struct linked_enemie *parcour = perso->e_list;
	    e_list[0] = 0;
	    while (parcour != NULL)
	    {
		if (parcour->rang == rang)
		{
	            strcat(e_list, parcour->nom);
	            strcat(e_list, "\n");
		}
		parcour = parcour->next;
	    }
	    position5.x += blit_text(position5, e_list, ecran, 9999, 255) + 10;
	    rang += 1;
	}
    }
}

void talk(SDL_Window *ecran, struct speak *speak_s, struct personnages *moi)
{
    if (lettres->esc == 1)
	speak_s->on = 0;
    SDL_Rect position1;
    position1.x = 50;
    position1.y = 50;
    text_input(speak_s->speak, 90);
    SDL_BlitSurface(img->g->selTextInput, NULL, SDL_GetWindowSurface(ecran), &position1);
    blit_text(position1, speak_s->speak, ecran, 30, 255);
    if (lettres->enter == 1)
    {
	moi->speak[0] = 0;
	moi->speak_timer = strlen(speak_s->speak) * 100;
	strcat(moi->speak, speak_s->speak);
	speak_s->speak[0] = 0;
	lettres->enter = 0;
	moi->a_bouger = 1;
    }
}
